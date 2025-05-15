/* cmd_handler.c */
#include "cmd-handler.h"
#include "command.h"
#include <stdio.h>
#include <string.h>

// 명령 테이블
static cmd_handler_t handlers[] = {
    { CMD_KEEP_ALIVE,               "KEEP ALIVE",               keepAlive },
    { CMD_IBIT,                     "IBIT",                     iBit },
    { CMD_RBIT,                     "RBIT",                     rBit },
    { CMD_CBIT,                     "CBIT",                     cBit },
    { CMD_POSITION_AZ_EL_SET,       "AZ/EL SET",                positionAzElSet },
    { CMD_TRACKING_MODE_SELECT,     "TRACKING MODE SELECT",     trackingModeSelect },
    { CMD_TRACKING_START_MODE,      "TRACKING START MODE",      trackingStartMode },
    { CMD_TRAJECTORY_INFO,          "TRAJECTORY INFO",          trajectoryInfo },
    { CMD_SHELTER_COORDINATE,       "SHELTER COORDINATE",       shelterCoordinate },
    { CMD_EXTERN_DEV_COORDINATE,    "EXTERN DEV COORDINATE",    externDevCoordinate },
    { CMD_CANNON_COORDINATE,        "CANNON COORDINATE",        cannonCoordinate },
    { CMD_TRACKING_START_STOP,      "TRACKING START STOP",      trackingStartStop },
    { CMD_POSITION_DEG_SEND,        "POSITION DEGREE SEND",     positionDegSend },
    { CMD_ACU_MODE_SELECT,          "ACU MODE SELECT",          acuModeSelect },
    { CMD_TIME_SYNC_CHECK,          "TIME SYNC CHECK",          timeSyncCheck },
    { CMD_TIME_SYNC_SET,            "TIME SYNC SET",            timeSyncSet },
    { CMD_POSITION_AZ_EL_OFFSET,    "TRACKING MODE SELECT",     positionAzElOffset },
    { CMD_EXTERN_DEV_IP_SET,        "EXTERN DEV IP SET",        externDevIpSet },
    { CMD_SEND_ACU_DATA,            "SEND ACU DATA",            sendAcuData },
    { CMD_FPGA_TIME_SET,            "FPGA TIME SET",            fpgaTimeSet },
    { CMD_FPGA_TIME_SYNC_CHECK,     "FPGA TIME SYNC CHECK",     fpgaTimeSyncCheck },
    { CMD_PRE_PROGRAM_START_POINT,  "PROGRAM START POINT",      preProgramStartPoint },
    { CMD_EL_CALIBRATION_SET,       "EL CALIBRATION SET",       elCalibrationSet },
    { CMD_TRUE_NORTH_OFFSET,        "TRUE NORTH OFFSET",        trueNorthOffset },
    { CMD_KALMAN_FILTER_INFO,       "KALMAN FILTER INFO",       kalmanFilterInfo },
    { CMD_GPS_ALTITUDE_OFFSET,      "GPS ALTITUDE OFFSET",      gpsAltitudeOffset },
    { CMD_EXTERN_PARAM_SET,         "EXTERN PARAM SET",         externParamSet },
    { CMD_IMU_OFFSET,               "IMU OFFSET",               imuOffset },
    { CMD_TARGET_LLA,               "TARGET LLA",               targetLla },

    /* UDS */
    { UDS_GET_ID,                   "GET UDS ID",               responseUdsId },
    { UDS_TRACKING_MODE,            "UDS TRACKING MODE",        udsTrackingMode },
    // { IPC_SENSOR_DATA,              "IPC SENSOR DATA",          ipcSensorData },
    { UDS2_GPS_DATA,                "GPS DATA",                 recvGpsData },
    { UDS2_IMU_DATA,                "IMU DATA",                 recvImuData },
    { UDS2_SP_DATA,                 "SP DATA",                  recvSpData },
    { UDS2_EXTERN_DATA,             "EXTERNAL DATA",            recvExternData },
    { UDS2_KEYBOARD_DATA,           "KEYBOARD DATA",            recvKeyboardData },
    { UDS3_PROCESSING_DATA,     "PROCESSING DATA",      recvProcessingData },
    { UDS4_CTRL_DATA,           "CONTROLL DATA",        recvControllData },
    { UDS4_COMMAND,             "COMMAND",              recvCommandData },
    { CMD_UNKNOWN,                  "UNKOWN COMMAND",           unknownCommand }
};
        
static const int iNumOfHandlers = sizeof(handlers) / sizeof(handlers[0]);

int getReqestCmdSize(cmd_id_t id)
{
    switch (id) {
        case CMD_KEEP_ALIVE:                return sizeof(REQ_KEEP_ALIVE);
        case CMD_IBIT:                      return sizeof(REQ_IBIT);
        case CMD_RBIT:                      return sizeof(REQ_RBIT);
        case CMD_CBIT:                      return sizeof(REQ_CBIT);

        case CMD_POSITION_AZ_EL_SET:        return sizeof(REQ_POSITION_AZ_EL_SET);
        case CMD_TRACKING_MODE_SELECT:      return sizeof(REQ_TRACKING_MODE_SELECT);
        case CMD_TRACKING_START_MODE:       return sizeof(REQ_TRACKING_START_MODE);
        case CMD_TRAJECTORY_INFO:           return sizeof(REQ_TRAJECTORY_INFO);
        case CMD_SHELTER_COORDINATE:        return sizeof(REQ_SHELTER_COORDINATE);
        case CMD_EXTERN_DEV_COORDINATE:     return sizeof(REQ_EXTERN_DEV_COORDINATE);
        case CMD_CANNON_COORDINATE:         return sizeof(REQ_CANNON_COORDINATE);
        case CMD_TRACKING_START_STOP:       return sizeof(REQ_TRACKING_START_STOP);
        case CMD_POSITION_DEG_SEND:         return sizeof(REQ_POSITION_DEG_SEND);
        case CMD_ACU_MODE_SELECT:           return sizeof(REQ_ACU_MODE_SELECT);
        case CMD_TIME_SYNC_CHECK:           return sizeof(REQ_TIME_SYNC_CHECK);
        case CMD_TIME_SYNC_SET:             return sizeof(REQ_TIME_SYNC_SET);
        case CMD_POSITION_AZ_EL_OFFSET:     return sizeof(REQ_POSITION_AZ_EL_OFFSET);
        case CMD_EXTERN_DEV_IP_SET:         return sizeof(REQ_EXTERN_DEV_IP_SET);
        case CMD_SEND_ACU_DATA:             return sizeof(REQ_SEND_ACU_DATA);
        case CMD_FPGA_TIME_SET:             return sizeof(REQ_FPGA_TIME_SET);
        case CMD_FPGA_TIME_SYNC_CHECK:      return sizeof(REQ_FPGA_TIME_SYNC_CHECK);
        case CMD_PRE_PROGRAM_START_POINT:   return sizeof(REQ_PRE_PROGRAM_START_POINT);
        case CMD_EL_CALIBRATION_SET:        return sizeof(REQ_EL_CALIBRATION_SET);
        case CMD_TRUE_NORTH_OFFSET:         return sizeof(REQ_TRUE_NORTH_OFFSET);
        case CMD_KALMAN_FILTER_INFO:        return sizeof(REQ_KALMAN_FILTER_INFO);
        case CMD_GPS_ALTITUDE_OFFSET:       return sizeof(REQ_GPS_ALTITUDE_OFFSET);
        case CMD_EXTERN_PARAM_SET:          return sizeof(REQ_EXTERN_PARAM_SET);
        case CMD_IMU_OFFSET:                return sizeof(REQ_IMU_OFFSET);
        case CMD_TARGET_LLA:                return sizeof(REQ_TARGET_LLA);

        case UDS_GET_ID:                    return sizeof(REQ_UDS_ID);
        case UDS_TRACKING_MODE:             return sizeof(REQ_TRACKING_MODE_SELECT);        
        case UDS2_GPS_DATA:                 return sizeof(GPS_DATA);
        case UDS2_IMU_DATA:                 return sizeof(IMU_DATA);
        case UDS2_SP_DATA:                  return sizeof(SP_DATA);
        case UDS2_EXTERN_DATA:              return sizeof(EXTERN_DATA);
        case UDS2_KEYBOARD_DATA:            return sizeof(KEYBOARD_DATA);
        case UDS3_PROCESSING_DATA:          return sizeof(PROCESSING_DATA);
        case UDS4_CTRL_DATA:                return sizeof(REQ_CONTROLL_DATA);
        case UDS4_COMMAND:                  return sizeof(REQ_COMMAND_DATA);
        default:                            return 0;
    }
}

int getResponseCmdSize(cmd_id_t id)
{
    switch (id) {
        case CMD_KEEP_ALIVE:                return sizeof(RES_KEEP_ALIVE);
        case CMD_IBIT:                      return sizeof(RES_IBIT);
        case CMD_RBIT:                      return sizeof(RES_RBIT);
        case CMD_CBIT:                      return sizeof(RES_CBIT);

        case CMD_POSITION_AZ_EL_SET:        return sizeof(RES_POSITION_AZ_EL_SET);
        case CMD_TRACKING_MODE_SELECT:      return sizeof(RES_TRACKING_MODE_SELECT);
        case CMD_TRACKING_START_MODE:       return sizeof(RES_TRACKING_START_MODE);
        case CMD_TRAJECTORY_INFO:           return sizeof(RES_TRAJECTORY_INFO);
        case CMD_SHELTER_COORDINATE:        return sizeof(RES_SHELTER_COORDINATE);
        case CMD_EXTERN_DEV_COORDINATE:     return sizeof(RES_EXTERN_DEV_COORDINATE);
        case CMD_CANNON_COORDINATE:         return sizeof(RES_CANNON_COORDINATE);
        case CMD_TRACKING_START_STOP:       return sizeof(RES_TRACKING_START_STOP);
        case CMD_POSITION_DEG_SEND:         return sizeof(RES_POSITION_DEG_SEND);
        case CMD_ACU_MODE_SELECT:           return sizeof(RES_ACU_MODE_SELECT);
        case CMD_TIME_SYNC_CHECK:           return sizeof(RES_TIME_SYNC_CHECK);
        case CMD_TIME_SYNC_SET:             return sizeof(RES_TIME_SYNC_SET);
        case CMD_POSITION_AZ_EL_OFFSET:     return sizeof(RES_POSITION_AZ_EL_OFFSET);
        case CMD_EXTERN_DEV_IP_SET:         return sizeof(RES_EXTERN_DEV_IP_SET);
        case CMD_SEND_ACU_DATA:             return sizeof(RES_SEND_ACU_DATA);
        case CMD_FPGA_TIME_SET:             return sizeof(RES_FPGA_TIME_SET);
        case CMD_FPGA_TIME_SYNC_CHECK:      return sizeof(RES_FPGA_TIME_SYNC_CHECK);
        case CMD_PRE_PROGRAM_START_POINT:   return sizeof(RES_PRE_PROGRAM_START_POINT);
        case CMD_EL_CALIBRATION_SET:        return sizeof(RES_EL_CALIBRATION_SET);
        case CMD_TRUE_NORTH_OFFSET:         return sizeof(RES_TRUE_NORTH_OFFSET);
        case CMD_KALMAN_FILTER_INFO:        return sizeof(RES_KALMAN_FILTER_INFO);
        case CMD_GPS_ALTITUDE_OFFSET:       return sizeof(RES_GPS_ALTITUDE_OFFSET);
        case CMD_EXTERN_PARAM_SET:          return sizeof(RES_EXTERN_PARAM_SET);
        case CMD_IMU_OFFSET:                return sizeof(RES_IMU_OFFSET);
        case CMD_TARGET_LLA:                return sizeof(RES_TARGET_LLA);

        /* UDS */
        case UDS_GET_ID:                    return sizeof(RES_UDS_ID);
        case UDS_TRACKING_MODE:             return sizeof(RES_TRACKING_MODE_SELECT);
        case IPC_SENSOR_DATA:               return sizeof(SENSOR_DATA);
        case UDS2_GPS_DATA:                 return sizeof(GPS_DATA);
        case UDS2_IMU_DATA:                 return sizeof(IMU_DATA);
        case UDS2_SP_DATA:                  return sizeof(SP_DATA);
        case UDS2_EXTERN_DATA:              return sizeof(EXTERN_DATA);
        case UDS2_KEYBOARD_DATA:            return sizeof(KEYBOARD_DATA);
        case UDS3_PROCESSING_DATA:  return sizeof(PROCESSING_DATA);
        case UDS4_CTRL_DATA:        return sizeof(RES_CONTROLL_DATA);
        case UDS4_COMMAND:          return sizeof(RES_COMMAND_DATA);
        default:                            return sizeof(RES_UNKNOWN_COMMAND);
    }
}

const char* getCmdName(cmd_id_t id) 
{
    switch (id) {
        case CMD_KEEP_ALIVE:                return "KEEP ALIVE";
        case CMD_IBIT:                      return "IBIT";
        case CMD_RBIT:                      return "RBIT";
        case CMD_CBIT:                      return "CBIT";
        case CMD_POSITION_AZ_EL_SET:        return "AZ/EL SET";
        case CMD_TRACKING_MODE_SELECT:      return "TRACKING MODE SELECT";
        case CMD_TRACKING_START_MODE:       return "TRACKING START MODE";
        case CMD_TRAJECTORY_INFO:           return "TRAJECTORY INFO";
        case CMD_SHELTER_COORDINATE:        return "SHELTER COORDINATE";
        case CMD_EXTERN_DEV_COORDINATE:     return "EXTERN DEV COORDINATE";
        case CMD_CANNON_COORDINATE:         return "CANNON COORDINATE";
        case CMD_TRACKING_START_STOP:       return "TRACKING START STOP";
        case CMD_POSITION_DEG_SEND:         return "POSITION DEGREE SEND";
        case CMD_ACU_MODE_SELECT:           return "ACU MODE SELECT";
        case CMD_TIME_SYNC_CHECK:           return "TIME SYNC CHECK";
        case CMD_TIME_SYNC_SET:             return "TIME SYNC SET";
        case CMD_POSITION_AZ_EL_OFFSET:     return "TRACKING MODE SELECT";
        case CMD_EXTERN_DEV_IP_SET:         return "EXTERN DEV IP SET";
        case CMD_SEND_ACU_DATA:             return "SEND ACU DATA";
        case CMD_FPGA_TIME_SET:             return "FPGA TIME SET";
        case CMD_FPGA_TIME_SYNC_CHECK:      return "FPGA TIME SYNC CHECK";
        case CMD_PRE_PROGRAM_START_POINT:   return "PROGRAM START POINT";
        case CMD_EL_CALIBRATION_SET:        return "EL CALIBRATION SET";
        case CMD_TRUE_NORTH_OFFSET:         return "TRUE NORTH OFFSET";
        case CMD_KALMAN_FILTER_INFO:        return "KALMAN FILTER INFO";
        case CMD_GPS_ALTITUDE_OFFSET:       return "GPS ALTITUDE OFFSET";
        case CMD_EXTERN_PARAM_SET:          return "EXTERN PARAM SET";
        case CMD_IMU_OFFSET:                return "IMU OFFSET";
        case CMD_TARGET_LLA:                return "TARGET LLA";
        /* UDS */
        case UDS_GET_ID:                    return "UDS GET ID";
        case UDS_TRACKING_MODE:             return "UDS TRACKING MODE";
        // case UDS2_SENSOR_DATA:              return "SENSOR DATA";
        case UDS2_GPS_DATA:                 return "GPS DATA";
        case UDS2_IMU_DATA:                 return "IMU DATA";
        case UDS2_SP_DATA:                  return "SP DATA";
        case UDS2_EXTERN_DATA:              return "EXTERNAL DATA";
        case UDS2_KEYBOARD_DATA:            return "KEYBOARD DATA";
        case UDS3_PROCESSING_DATA:  return "PROCESSING DATA";
        case UDS4_CTRL_DATA:        return "CONTROLL DATA";
        case UDS4_COMMAND:          return "COMMAND";
        default:                            return "UNKNOWN";
    }
}


// 명령 분배 처리
int dispatchCommand(int iCmdId, const char* pchRequest, char* pchResponse, void* pvUdsInfo, logger_func_t logger) {
    for (int i = 0; i < iNumOfHandlers; ++i) {
        if (handlers[i].cmdId == iCmdId) {
            if (logger) logger(handlers[i].cmdId, "Start");            
            int result = handlers[i].handler(pchRequest, pchResponse, pvUdsInfo);
            if (logger) logger(handlers[i].cmdId, (result == 0) ? "Success" : "Fail");

            return result;
        }
    }
    
    if (logger) logger(CMD_UNKNOWN, "Unknown Command");    
    return -1;
}
