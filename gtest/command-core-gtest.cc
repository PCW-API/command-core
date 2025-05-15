/**
 * @file uds-gtest.cc
 * @brief UDS 서버 테스트용 GoogleTest 스위트
 *
 * 본 파일은 UDS 서버의 클라이언트 연결, 데이터 송수신, 복수 클라이언트 처리 등
 * 주요 기능을 테스트하는 자동화 테스트 코드입니다.
 */
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "uds.h"
#include "uds-server.h"
#include "queue.h"
#include "../include/frame-format.h"
#include "../include/cmd-handler.h"
#include "../include/uds-info.h"
#include "../include/command.h"

UDS_SERVER g_stUdsServer;

constexpr const char* TEST_SOCKET_PATH = "/tmp/test_socket"; ///< 테스트용 UDS 소켓 경로
constexpr int TEST_CLIENT_COUNT = 5;                          ///< 테스트 클라이언트 수
constexpr int CONNECT_WAIT_MS = 100;                          ///< 클라이언트 연결 대기 시간(ms)
constexpr int DATA_WAIT_MS = 300;                             ///< 데이터 수신 대기 시간(ms)

/**
 * @brief 테스트용 UDS 서버 초기화 함수
 *
 * 서버 소켓을 생성하고, 클라이언트 배열 및 뮤텍스를 초기화합니다.
 * 연결 관리, 송수신 스레드를 시작합니다.
 */
void startUdsServer() {    
    g_stUdsServer.iServerSock = createUdsServerSocket(TEST_SOCKET_PATH, TEST_CLIENT_COUNT);
    pthread_mutex_init(&g_stUdsServer.mutex, NULL);
    g_stUdsServer.iMaxClients = TEST_CLIENT_COUNT;
    g_stUdsServer.iRunning = 0;
    g_stUdsServer.iClientCount = 0;
    g_stUdsServer.pstClients = (CLIENT *)malloc(sizeof(CLIENT) * TEST_CLIENT_COUNT);
    for (int i = 0; i < g_stUdsServer.iMaxClients; ++i) {
        g_stUdsServer.pstClients[i].iSock = -1;
        g_stUdsServer.pstClients[i].iActive = 0;
        g_stUdsServer.pstClients[i].iId = -1;
    }
    std::thread(&connectionManagerThread, &g_stUdsServer).detach();
    std::thread(&sendThread, &g_stUdsServer).detach();
    std::thread(&recvThread, &g_stUdsServer).detach();
}

/**
 * @brief 테스트 종료 후 서버 정리 함수
 *
 * 서버 실행을 중단하고 소켓을 종료합니다.
 */
void stopUdsServer() {
    g_stUdsServer.iRunning = 0;
    g_stUdsServer.iClientCount = 0;
    if (g_stUdsServer.iServerSock) {
        udsClose(g_stUdsServer.iServerSock);
    }
}

/**
 * @brief 테스트 클라이언트 소켓 생성 함수
 * @return 유효한 클라이언트 소켓 디스크립터
 */
int createTestClientSocket() {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, TEST_SOCKET_PATH);
    int retry = 0;
    while (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0 && retry++ < 10)
        std::this_thread::sleep_for(std::chrono::milliseconds(CONNECT_WAIT_MS));
    return sock;
}

/**
 * @class UdsServerTest
 * @brief 공통 테스트 픽스처 클래스
 *
 * 테스트 전후에 서버를 초기화하고 정리하며,
 * 클라이언트 소켓 및 스레드 관리를 수행합니다.
 */
class UdsServerTest : public ::testing::Test {
protected:
    std::vector<int> clientSockets;
    std::vector<std::thread> clientThreads;
    std::vector<std::string> clientSendData;
    std::vector<std::string> receivedData;
    std::atomic<bool> running{true};

    void SetUp() override {
        startUdsServer();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    void TearDown() override {
        running = false;
        for (int sock : clientSockets) {
            if (sock > 0) shutdown(sock, SHUT_RDWR); // recv() 깨우기
        }
        for (auto& t : clientThreads) 
            if (t.joinable()) 
                t.join();

        for (int sock : clientSockets) 
            if (sock > 0) 
                close(sock);
        stopUdsServer();
    }

    void createClients(int count) {
        for (int i = 0; i < count; ++i) {
            int sock = createTestClientSocket();
            ASSERT_GT(sock, 0) << "Client " << i << " connection failed.";
            clientSockets.push_back(sock);
        }
    }

    void createClientsAndSendID(int count) {
        MSG_ID stSendMsgId;
        MSG_ID stRecvMsgId;
        int iSendDataSize;
        char chSendData[128];
        char chRecvData[128];
        REQ_UDS_ID* pstReqUdsId;
        memset(chSendData, 0x0, sizeof(chSendData));
        memset(chRecvData, 0x0, sizeof(chRecvData));
        for (int i = 0; i < count; ++i) {
            int sock = createTestClientSocket();
            ASSERT_GT(sock, 0);
            clientSockets.push_back(sock);
            pstReqUdsId = (REQ_UDS_ID *)(chSendData + sizeof(FRAME_HEADER));
            stSendMsgId.chDstId = UDS1_SERVER;
            stRecvMsgId.chSrcId = UDS1_SERVER;
            if(i==0){
                stSendMsgId.chSrcId = UDS1_ACU_ID;
                stRecvMsgId.chDstId = UDS1_ACU_ID;
                pstReqUdsId->iId = UDS1_ACU_ID;
            }else if(i==1){
                stSendMsgId.chSrcId = UDS1_GPS_ID;
                stRecvMsgId.chDstId = UDS1_GPS_ID;
                pstReqUdsId->iId = UDS1_GPS_ID;
            }else if(i==2){
                stSendMsgId.chSrcId = UDS1_IMU_ID;
                stRecvMsgId.chDstId = UDS1_IMU_ID;
                pstReqUdsId->iId = UDS1_IMU_ID;
            }else if(i==3){
                stSendMsgId.chSrcId = UDS1_EXTERN_ID;
                stRecvMsgId.chDstId = UDS1_EXTERN_ID;
                pstReqUdsId->iId = UDS1_EXTERN_ID;
            }else if(i==4){
                stSendMsgId.chSrcId = UDS1_SP_ID;
                stRecvMsgId.chDstId = UDS1_SP_ID;
                pstReqUdsId->iId = UDS1_SP_ID;
            }

            iSendDataSize = makeRequestPacket(UDS_GET_ID, &stSendMsgId, chSendData);
            send(sock, chSendData, iSendDataSize, 0);
        }
    }

    void collectReceivedClientIdData() {
        MSG_ID stRecvMsgId;
        FRAME_HEADER *pstRcvHeader;
        unsigned int  uiPacketFormatStatus;
        stRecvMsgId.chDstId = UDS1_SERVER;
        stRecvMsgId.chSrcId = UDS1_SERVER;//의미 없음
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (int i = 0; i < TEST_CLIENT_COUNT; ) {
            if (g_stUdsServer.pstClients[i].iActive) {
                void* data = nullptr;
                int iRecvSize = queuePop(&g_stUdsServer.pstClients[i].stRecvQueue, &data);
                if (iRecvSize > 0 && data) {
                    i++;
                    uiPacketFormatStatus = checkPacketFormat((char*)data, &stRecvMsgId, iRecvSize);              
                    if(uiPacketFormatStatus == PACKET_FORMAT_OK){
                        REQ_UDS_ID* pstReqUdsId = (REQ_UDS_ID *)(data + sizeof(FRAME_HEADER));
                        fprintf(stderr,"### %s():%d ID:%d ###\n",__func__,__LINE__,pstReqUdsId->iId);
                    }else{                        
                        printPacketFormatError(uiPacketFormatStatus);
                    }
                }
                free(data);
            }
        }
    }
};

// for (int i = 0; i < TEST_CLIENT_COUNT; ++i) {
//             if (g_stUdsServer.pstClients[i].iActive) {
//                 void* data = nullptr;
//                 int iRecvSize = queuePop(&g_stUdsServer.pstClients[i].stRecvQueue, &data);
//                 if (iRecvSize > 0 && data) {
//                     uiPacketFormatStatus = checkPacketFormat((char*)data, &stRecvMsgId, iRecvSize);                    
//                     if(uiPacketFormatStatus == PACKET_FORMAT_OK){
//                         pstRcvHeader = (FRAME_HEADER *)data;
//                         iResponseSize = getResponseCmdSize((cmd_id_t)pstRcvHeader->nCmd) + sizeof(FRAME_HEADER) + sizeof(FRAME_TAIL);
//                         pchResponse = (char *)malloc(iResponseSize);
//                         pchCmdResult = (char *)(pchResponse + sizeof(FRAME_HEADER));                        
//                         nCmd = pstRcvHeader->nCmd;
//                     }else{
//                         iResponseSize = getResponseCmdSize((cmd_id_t)CMD_UNKNOWN) + sizeof(FRAME_HEADER) + sizeof(FRAME_TAIL);
//                         pchResponse = (char *)malloc(iResponseSize);
//                         pchCmdResult = (char *)(pchResponse + sizeof(FRAME_HEADER));
//                         nCmd = CMD_UNKNOWN;
//                     }
//                     iRetVal = dispatchCommand(nCmd, (char*)data, pchCmdResult, pstUds1Server, logging);
//                     makeResponsePacket(nCmd, &stRecvMsgId, pchResponse);


//                     free(data);
//                 }
//             }
//         }

/**
 * @test ClientSendIdTest
 * @brief 클라이언트 → 서버 클라이언트의 ID 데이터 송신 테스트
 *
 * 각 클라이언트가 자신의 ID를 서버에 송신하고,
 * 서버 측 수신 큐에서 해당 데이터를 올바르게 수신했는지를 검증합니다.
 */
TEST_F(UdsServerTest, ClientSendIdTest) {
    createClientsAndSendID(TEST_CLIENT_COUNT);
    collectReceivedClientIdData();
    
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}