/*!
 * @file cmd-handler.h
 * @brief 명령 처리 관련 정의 및 함수 선언 헤더
 */
#ifndef CMD_HANDLER_H
#define CMD_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "logger.h"

/**
 * @enum cmd_id_t
 * @brief 명령 ID 정의
 */
typedef enum {
    CMD_KEEP_ALIVE = 0,
    CMD_IBIT,
    CMD_RBIT,
    CMD_CBIT,
    CMD_POSITION_AZ_EL_SET,
    CMD_TRACKING_MODE_SELECT,
    CMD_TRACKING_START_MODE,   
    CMD_TRAJECTORY_INFO,        //사용 안함
    CMD_SHELTER_COORDINATE,     //사용안함
    CMD_EXTERN_DEV_COORDINATE,  //사용안함
    CMD_CANNON_COORDINATE,      //사용 안함
    CMD_TRACKING_START_STOP,
    CMD_POSITION_DEG_SEND,
    CMD_ACU_MODE_SELECT,
    CMD_TIME_SYNC_CHECK,
    CMD_TIME_SYNC_SET,
    CMD_POSITION_AZ_EL_OFFSET,
    CMD_EXTERN_DEV_IP_SET,
    CMD_SEND_ACU_DATA,
    CMD_FPGA_TIME_SET,
    CMD_FPGA_TIME_SYNC_CHECK,
    CMD_PRE_PROGRAM_START_POINT = 0x16,
    CMD_EL_CALIBRATION_SET,
    CMD_TRUE_NORTH_OFFSET,
    CMD_KALMAN_FILTER_INFO = 0x1A,
    CMD_GPS_ALTITUDE_OFFSET,
    CMD_EXTERN_PARAM_SET,
    CMD_IMU_OFFSET,
    CMD_TARGET_LLA,

    UDS_GET_ID  = 100,
    UDS_TRACKING_MODE,
    IPC_SENSOR_DATA,


    // process2에서 UDS2에 사용되는 ID (값의 범위 : 200 ~ 299)
    UDS2_SENSOR_DATA = 200,
    UDS2_GPS_DATA,
    UDS2_IMU_DATA,
    UDS2_SP_DATA,
    UDS2_EXTERN_DATA,
    UDS2_KEYBOARD_DATA,


    // process2에서 UDS3에 사용되는 ID (값의 범위 : 300 ~ 399)
    UDS3_PROCESSING_DATA = 300,

    // process3에서 UDS4에 사용되는 ID (값의 범위 : 400 ~ 499)
    UDS4_CTRL_DATA = 400,
    UDS4_COMMAND,
        
    CMD_UNKNOWN = 500 //todo ICD문서에 추가 필요
} cmd_id_t;

// 핸들러 함수 타입
typedef int (*command_func_t)(char* pchRequest, char* pchResponse, void* pvUdsInfo);

// 로그 함수 타입
typedef void (*logger_func_t)(int iCmdId, const char* pchStatus);

const char* getCmdName(cmd_id_t id);
int getReqestCmdSize(cmd_id_t id);
int getResponseCmdSize(cmd_id_t id);

// 명령 처리 함수 (로그 포함)
int dispatchCommand(int iCmdId, char* pchRequest, char* pchResponse, void* pvUdsInfo, logger_func_t logger);


// 명령 핸들러 구조체
typedef struct  __attribute__((__packed__)){
    cmd_id_t cmdId;
    const char* chpCmdName;
    command_func_t handler;
} cmd_handler_t;


#ifdef __cplusplus
}
#endif
#endif // ICD_HANDLER_H
