/*!
 * @file command.c
 * @brief 각 명령 ID에 대응하는 처리 함수 정의
 * @details ACU 제어 명령, 센서 데이터 처리 등 다양한 요청 명령에 대한 응답 데이터를 구성합니다.
 */
#include <stdio.h>
#include <string.h>
#include "command.h"
#include "uds-server.h"
#include "frame-format.h"
#include "cmd-handler.h"
#include "uds-info.h"
#include "queue.h"

/**
 * @brief KeepAlive 요청에 대한 응답을 처리합니다.
 * @return CMD_SUCCESS
 */
int keepAlive(char* pchRequest, char* pchResponse, void* pvData)
{
    RES_KEEP_ALIVE* pstResKeepAlive = (RES_KEEP_ALIVE *)pchResponse;
    pstResKeepAlive->chResult = 0x01;
    return CMD_SUCCESS;
}

/**
 * @brief IBIT 요청을 처리하고 응답을 생성합니다.
 */
int iBit(char* pchRequest, char* pchResponse, void* pvData)
{
    RES_IBIT* pstResIBit = (RES_IBIT *)pchResponse;
    pstResIBit->chBitTotResult = 0x01;
    pstResIBit->chPositionResult = 0x01;
    return CMD_SUCCESS;
}

int rBit(char* pchRequest, char* pchResponse, void* pvData)
{
    RES_RBIT* pstResRBit = (RES_RBIT *)pchResponse;
    pstResRBit->chBitTotResult = 0x01;
    pstResRBit->chPositionResult = 0x01;
    return CMD_SUCCESS;
}

int cBit(char* pchRequest, char* pchResponse, void* pvData)
{
    RES_CBIT* pstResCBit = (RES_CBIT *)pchResponse;    
    pstResCBit->chBitTotResult = 0x01;
    pstResCBit->chPositionResult = 0x01;
    return CMD_SUCCESS;
}


int positionAzElSet(char* pchRequest, char* pchResponse, void* pvData)
{
    RES_POSITION_AZ_EL_SET* pstResPositionAzElSet = (RES_POSITION_AZ_EL_SET *)pchResponse;
    
    //todo ACU 제어 프로세스로 명령 전송

    pstResPositionAzElSet->chResult = 0x01;
    return CMD_SUCCESS;
}

int trackingModeSelect(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_TRACKING_MODE_SELECT* pstReqTrackingModeSelect = (REQ_TRACKING_MODE_SELECT *)pchRequest;
    RES_TRACKING_MODE_SELECT* pstResTrackingModeSelect = (RES_TRACKING_MODE_SELECT *)pchResponse;

    //todo ACU 제어 프로세스로 명령 전송
    pstResTrackingModeSelect->chResult = 0x01;
    return CMD_SUCCESS;
}

int trackingStartMode(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_TRACKING_START_MODE* pstReqTrackingStartMode = (REQ_TRACKING_START_MODE *)pchRequest;
    RES_TRACKING_START_MODE* pstResTrackingStartMode = (RES_TRACKING_START_MODE *)pchResponse;
    //todo ACU 제어 프로세스로 명령 전송
    pstResTrackingStartMode->chResult = 0x01;
    return CMD_SUCCESS;
}

int trajectoryInfo(char* pchRequest, char* pchResponse, void* pvData)
{
    //도플러에서 사용 안함
    // REQ_TRAJECTORY_INFO* pstReqTrajectoryInfo = (REQ_TRAJECTORY_INFO *)pchRequest;
    // RES_TRAJECTORY_INFO* pstResTrajectoryInfo = (RES_TRAJECTORY_INFO *)pchResponse;
    // pstResTrajectoryInfo->chResult = 0x01;
    return CMD_SUCCESS;
}

int shelterCoordinate(char* pchRequest, char* pchResponse, void* pvData)
{
    //도플러에서 사용 안함
    // REQ_SHELTER_COORDINATE* pstReqShelterCoordinate = (REQ_SHELTER_COORDINATE *)pchRequest;
    // RES_SHELTER_COORDINATE* pstResShelterCoordinate = (RES_SHELTER_COORDINATE *)pchResponse;
    // pstResShelterCoordinate->chResult = 0x01;
    return CMD_SUCCESS;
}

int externDevCoordinate(char* pchRequest, char* pchResponse, void* pvData)
{
    //도플러에서 사용 안함
    // REQ_EXTERN_DEV_COORDINATE* pstReqExternDevCoordinate = (REQ_EXTERN_DEV_COORDINATE *)pchRequest;
    // RES_EXTERN_DEV_COORDINATE* pstResExternDevCoordinate = (RES_EXTERN_DEV_COORDINATE *)pchResponse;
    // pstResExternDevCoordinate->chResult = 0x01;
    return CMD_SUCCESS;
}

int cannonCoordinate(char* pchRequest, char* pchResponse, void* pvData)
{
    //도플러에서 사용 안함
    // REQ_CANNON_COORDINATE* pstReqCannonCoordinate = (REQ_CANNON_COORDINATE *)pchRequest;
    // RES_CANNON_COORDINATE *pstResCannonCoordinate = (RES_CANNON_COORDINATE *)pchResponse;
    // pstResCannonCoordinate->chResult = 0x01;
    return CMD_SUCCESS;
}

int trackingStartStop(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_TRACKING_START_STOP* pstReqTrackingStartStop = (REQ_TRACKING_START_STOP *)pchRequest;
    RES_TRACKING_START_STOP* pstResTrackingStartStop = (RES_TRACKING_START_STOP *)pchResponse;
    //todo ACU 제어 프로세스로 명령 전송
    pstResTrackingStartStop->chResult = 0x01;
    return CMD_SUCCESS;
}

int positionDegSend(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_POSITION_DEG_SEND* pstReqPositionDegSend = (REQ_POSITION_DEG_SEND *)pchRequest;
    RES_POSITION_DEG_SEND* pstResPositionDegSend = (RES_POSITION_DEG_SEND *)pchResponse;
    //todo ACU 제어 프로세스로 명령 전송
    pstResPositionDegSend->chResult = 0x01;
    return CMD_SUCCESS;
}

int acuModeSelect(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_ACU_MODE_SELECT* pstReqAcuModeSelect = (REQ_ACU_MODE_SELECT *)pchRequest;
    RES_ACU_MODE_SELECT* pstResAcuModeSelect = (RES_ACU_MODE_SELECT *)pchResponse;
    //todo ACU 제어 프로세스로 명령 전송
    pstResAcuModeSelect->chResult = 0x01;
    return CMD_SUCCESS;
}
int timeSyncCheck(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_TIME_SYNC_CHECK* pstReqTimeSyncCheck = (REQ_TIME_SYNC_CHECK *)pchRequest;
    RES_TIME_SYNC_CHECK* pstResTimeSyncCheck = (RES_TIME_SYNC_CHECK *)pchResponse;    
    pstResTimeSyncCheck->chResult = 0x01;
    return CMD_SUCCESS;
}

int timeSyncSet(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_TIME_SYNC_SET* pstReqTimeSyncSet = (REQ_TIME_SYNC_SET *)pchRequest;
    RES_TIME_SYNC_SET* pstResTimeSyncSet = (RES_TIME_SYNC_SET *)pchResponse;    
    //todo 
    // pstResTimeSyncSet->chResult = 0x01;
    return CMD_SUCCESS;
}
int positionAzElOffset(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_POSITION_AZ_EL_OFFSET* pstReqPositionAzElOffset = (REQ_POSITION_AZ_EL_OFFSET *)pchRequest;
    RES_POSITION_AZ_EL_OFFSET* pstResPositionAzElOffset = (RES_POSITION_AZ_EL_OFFSET *)pchResponse;
    //todo ACU 제어 프로세스로 명령 전송
    pstResPositionAzElOffset->chResult = 0x01;
    return CMD_SUCCESS;
}

int externDevIpSet(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_EXTERN_DEV_IP_SET* pstReqExternDevIpSet = (REQ_EXTERN_DEV_IP_SET *)pchRequest;
    RES_EXTERN_DEV_IP_SET* pstResExternDevIpSet = (RES_EXTERN_DEV_IP_SET *)pchResponse;
    //todo Extern Uart Recver에 명령 전송
    pstResExternDevIpSet->chResult = 0x01;
    return CMD_SUCCESS;
}

int sendAcuData(char* pchRequest, char* pchResponse, void* pvData)
{
    //도플러에서 사용 안함
    // REQ_SEND_ACU_DATA* pstReqSendAcuData = (REQ_SEND_ACU_DATA *)pchRequest;
    // RES_SEND_ACU_DATA* pstResSendAcuData = (RES_SEND_ACU_DATA *)pchResponse;
    return CMD_SUCCESS;
}
int fpgaTimeSet(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_FPGA_TIME_SET* pstReqFpgaTimeSet = (REQ_FPGA_TIME_SET *)pchRequest;
    RES_FPGA_TIME_SET* pstResFpgaTimeSet = (RES_FPGA_TIME_SET *)pchResponse;    
    pstResFpgaTimeSet->chResult = 0x01;
    return CMD_SUCCESS;
}
int fpgaTimeSyncCheck(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_FPGA_TIME_SYNC_CHECK* pstReqFpgaTimeSyncCheck = (REQ_FPGA_TIME_SYNC_CHECK *)pchRequest;
    RES_FPGA_TIME_SYNC_CHECK* pstResFpgaTimeSyncCheck = (RES_FPGA_TIME_SYNC_CHECK *)pchResponse;
    //todo
    return CMD_SUCCESS;
}

int preProgramStartPoint(char* pchRequest, char* pchResponse, void* pvData)
{
    //도플러에서 사용 안함
    // REQ_PRE_PROGRAM_START_POINT* pstReqPreProgramStartPoint = (REQ_PRE_PROGRAM_START_POINT *)pchRequest;
    // RES_PRE_PROGRAM_START_POINT* pstResPreProgramStartPoint = (RES_PRE_PROGRAM_START_POINT *)pchResponse;
    // pstResPreProgramStartPoint->chResult = 0x01;
    return CMD_SUCCESS;
}
int elCalibrationSet(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_EL_CALIBRATION_SET* pstReqElCalibrationSet = (REQ_EL_CALIBRATION_SET *)pchRequest;
    RES_EL_CALIBRATION_SET* pstResElCalibrationSet = (RES_EL_CALIBRATION_SET *)pchResponse;
    //todo ACU 제어 프로세스로 명령 전송
    pstResElCalibrationSet->chResult = 0x01;
    return CMD_SUCCESS;
}
int trueNorthOffset(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_TRUE_NORTH_OFFSET* pstReqTrueNorthOffset = (REQ_TRUE_NORTH_OFFSET *)pchRequest;
    RES_TRUE_NORTH_OFFSET* pstResTrueNorthOffset = (RES_TRUE_NORTH_OFFSET *)pchResponse; 
    //todo Gps Uart Recver에 명령 전송   
    pstResTrueNorthOffset->chResult = 0x01;
    return CMD_SUCCESS;
}
int kalmanFilterInfo(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_KALMAN_FILTER_INFO* pstReqKalmanFilterInfo = (REQ_KALMAN_FILTER_INFO *)pchRequest;
    RES_KALMAN_FILTER_INFO* pstResKalmanFilterInfo = (RES_KALMAN_FILTER_INFO *)pchResponse;    
    pstResKalmanFilterInfo->chResult = 0x01;
    return CMD_SUCCESS;
}
int gpsAltitudeOffset(char* pchRequest, char* pchResponse, void* pvData)
{
    UDS_SERVER* pstUds1Server = (UDS_SERVER *)pvData;
    int iUdsIndex;
    int iUdsSendSize = sizeof(FRAME_HEADER)+sizeof(FRAME_TAIL)+getReqestCmdSize(CMD_GPS_ALTITUDE_OFFSET);
    RES_GPS_ALTITUDE_OFFSET* pstResGpsAltitudeOffset = (RES_GPS_ALTITUDE_OFFSET *)pchResponse;
    for(int i=0; i<pstUds1Server->iClientCount; i++){
        fprintf(stderr,"### %s():%d index is %d %d ###\n",__func__,__LINE__, pstUds1Server->pstClients[i].iId, UDS1_GPS_ID);
        if(pstUds1Server->pstClients[i].iId == UDS1_GPS_ID){
            iUdsIndex = i;
            queuePush(&pstUds1Server->pstClients[i].stSendQueue, pchRequest, iUdsSendSize);
            // break;
        }
    }
    fprintf(stderr,"### %s():%d index is %d ###\n",__func__,__LINE__,iUdsIndex);

    //todo Gps Uart Recver에 명령 전송
    // pstResGpsAltitudeOffset->chResult = udsSendToClient((UDS_SERVER *)pvData, GPS_ID, pchRequest, iUdsSendSize);
    pstResGpsAltitudeOffset->chResult = 0x01;
    return CMD_SUCCESS;
}

int externParamSet(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_EXTERN_PARAM_SET* pstReqExternParamSet = (REQ_EXTERN_PARAM_SET *)pchRequest;
    RES_EXTERN_PARAM_SET* pstResExternParamSet = (RES_EXTERN_PARAM_SET *)pchResponse;
    //todo Extern Uart Recver에 명령 전송
    pstResExternParamSet->chResult = 0x01;
    return CMD_SUCCESS;
}
int imuOffset(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_IMU_OFFSET* pstReqImuOffset = (REQ_IMU_OFFSET *)pchRequest;
    RES_IMU_OFFSET* pstResImuOffset = (RES_IMU_OFFSET *)pchResponse;
    pstResImuOffset->chResult = 0x01;
    return CMD_SUCCESS;
}
int targetLla(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_TARGET_LLA* pstReqTargetLla = (REQ_TARGET_LLA *)pchRequest;
    RES_TARGET_LLA* pstResTargetLla = (RES_TARGET_LLA *)pchResponse;
    pstResTargetLla->chResult = 0x01;
    return CMD_SUCCESS;
}


/* UDS */
int responseUdsId(char* pchRequest, char* pchResponse, void* pvData)
{
    FRAME_HEADER* pstFrameHeader  = (FRAME_HEADER *)pchRequest;
    REQ_UDS_ID* pstReqUdsId = (REQ_UDS_ID *)pchRequest;
    RES_UDS_ID* pstResUdsId = (RES_UDS_ID *)pchResponse;
    fprintf(stderr,"### ID : %d ###\n",pstReqUdsId->iId);
    pstResUdsId->chResult  = 0x1;    
    return CMD_SUCCESS;
}



int recvGpsData(char* pchRequest, char* pchResponse, void* pvData)
{
    GPS_DATA* pstGpsData = (GPS_DATA *)pchRequest + sizeof(FRAME_HEADER);
    SENSOR_DATA* pstSensorData = (SENSOR_DATA *)pchResponse;
    pstSensorData->stGpsData.dLatitude  = pstGpsData->dLatitude;
    pstSensorData->stGpsData.dLongitude = pstGpsData->dLongitude;
    pstSensorData->stGpsData.dAltitude  = pstGpsData->dAltitude;
    return CMD_SUCCESS;
}

int recvImuData(char* pchRequest, char* pchResponse, void* pvData)
{
    IMU_DATA* pstImuData = (IMU_DATA *)pchRequest + sizeof(FRAME_HEADER);
    SENSOR_DATA* pstSensorData = (SENSOR_DATA *)pchResponse;
    pstSensorData->stImuData.dRoll  = pstImuData->dRoll;
    pstSensorData->stImuData.dPitch = pstImuData->dPitch;
    pstSensorData->stImuData.dYaw   = pstImuData->dYaw;
    return CMD_SUCCESS;
}

int recvSpData(char* pchRequest, char* pchResponse, void* pvData)
{
    SP_DATA* pstSpData = (SP_DATA *)pchRequest + sizeof(FRAME_HEADER);
    SENSOR_DATA* pstSensorData = (SENSOR_DATA *)pchResponse;
    pstSensorData->stSpData.dAz = pstSpData->dAz;
    pstSensorData->stSpData.dEl = pstSpData->dEl;
    return CMD_SUCCESS;
}

int recvExternData(char* pchRequest, char* pchResponse, void* pvData)
{
    EXTERN_DATA* pstExternData = (EXTERN_DATA *)(pchRequest + sizeof(FRAME_HEADER));
    SENSOR_DATA* pstSensorData = (SENSOR_DATA *)pchResponse;    
    fprintf(stderr,"### %s():%d %lf, %lf, %lf ###\n", __func__, __LINE__, pstExternData->dData1, pstExternData->dData2, pstExternData->dData3);
    pstSensorData->stExternData.dData1  = pstExternData->dData1;
    pstSensorData->stExternData.dData2 = pstExternData->dData2;
    pstSensorData->stExternData.dData3  = pstExternData->dData3;
    
    return CMD_SUCCESS;
}

int recvKeyboardData(char* pchRequest, char* pchResponse, void* pvData)
{
    KEYBOARD_DATA* pstKeyboardData = (KEYBOARD_DATA *)pchRequest + sizeof(FRAME_HEADER);
    SENSOR_DATA* pstSensorData = (SENSOR_DATA *)pchResponse;
    pstSensorData->stKeyboardData.dAz = pstKeyboardData->dAz;
    pstSensorData->stKeyboardData.dEl = pstKeyboardData->dEl;
    return CMD_SUCCESS;
}

int recvProcessingData(char* pchRequest, char* pchResponse, void* pvData)
{
    return CMD_SUCCESS;
}

int recvControllData(char* pchRequest, char* pchResponse, void* pvData)
{
    RES_CONTROLL_DATA* pstReqControllData = (RES_CONTROLL_DATA *)pchRequest;
    return CMD_SUCCESS;
}

int recvCommandData(char* pchRequest, char* pchResponse, void* pvData)
{
    RES_COMMAND_DATA* pstReqCommandData = (RES_COMMAND_DATA *)pchRequest;
    return CMD_SUCCESS;
}



int udsTrackingMode(char* pchRequest, char* pchResponse, void* pvData)
{
    REQ_TRACKING_MODE_SELECT* pstReqTrackingModeSelect = (REQ_TRACKING_MODE_SELECT *)pchRequest;
    RES_TRACKING_MODE_SELECT* pstResTrackingModeSelect = (RES_TRACKING_MODE_SELECT *)pchResponse;
    pstResTrackingModeSelect->chResult = 0x01;
    return CMD_SUCCESS;
}


int unknownCommand(char* pchRequest, char* pchResponse, void* pvData)
{
    RES_UNKNOWN_COMMAND* pstResUnknownCommand = (RES_UNKNOWN_COMMAND *)pchResponse;
    pstResUnknownCommand->chResult = 0x00;
    return CMD_SUCCESS;
}