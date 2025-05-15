#ifndef COMMAND_H
#define COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#define CMD_SUCCESS     0
#define CMD_FAILURE     -1

/**
 * @brief RES_KEEPALIVE 구조체
 * 제어PC와 TCP/IP통신에 사용되는 데이터 포멧
 */
typedef struct __attribute__((__packed__)){
	char chTmp;
}REQ_KEEP_ALIVE;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_KEEP_ALIVE;


typedef struct __attribute__((__packed__)){
	char chIbit;
}REQ_IBIT;
typedef struct __attribute__((__packed__)){
	char chBitTotResult;
	char chPositionResult;
}RES_IBIT;


typedef struct __attribute__((__packed__)){
	char chRbit;
}REQ_RBIT;
typedef struct __attribute__((__packed__)){
	char chBitTotResult;
	char chPositionResult;
}RES_RBIT;


typedef struct __attribute__((__packed__)){
	char chCbit;
}REQ_CBIT;
typedef struct __attribute__((__packed__)){
	char chBitTotResult;
	char chPositionResult;
}RES_CBIT;


typedef struct __attribute__((__packed__)){
	double dAz;
	double dEl;
}REQ_POSITION_AZ_EL_SET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_POSITION_AZ_EL_SET;


typedef struct __attribute__((__packed__)){
	char chTrackingSelect;
}REQ_TRACKING_MODE_SELECT;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_TRACKING_MODE_SELECT;


typedef struct __attribute__((__packed__)){
	char chTrackingStartMode;
}REQ_TRACKING_START_MODE;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_TRACKING_START_MODE;


typedef struct __attribute__((__packed__)){
	char *pchData;
}REQ_TRAJECTORY_INFO;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_TRAJECTORY_INFO;


typedef struct __attribute__((__packed__)){
	double dLatitude;//위도
	double dLongitude;//경도
	double dAltitude;//고도
}REQ_SHELTER_COORDINATE;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_SHELTER_COORDINATE;


typedef struct __attribute__((__packed__)){
	double dLatitude;//위도
	double dLongitude;//경도
	double dAltitude;//고도
}REQ_EXTERN_DEV_COORDINATE;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_EXTERN_DEV_COORDINATE;


typedef struct __attribute__((__packed__)){
	double dLatitude;//위도
	double dLongitude;//경도
	double dAltitude;//고도
}REQ_CANNON_COORDINATE;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_CANNON_COORDINATE;


typedef struct __attribute__((__packed__)){
	char chTrackingStartStop;
}REQ_TRACKING_START_STOP;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_TRACKING_START_STOP;


typedef struct __attribute__((__packed__)){
	char chSendOnOff;
}REQ_POSITION_DEG_SEND;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_POSITION_DEG_SEND;


typedef struct __attribute__((__packed__)){
	char chAcuMode;
}REQ_ACU_MODE_SELECT;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_ACU_MODE_SELECT;


typedef struct __attribute__((__packed__)){
	char chTimeSyncCheck;
}REQ_TIME_SYNC_CHECK;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_TIME_SYNC_CHECK;


typedef struct __attribute__((__packed__)){
	short nYear;
	char chMonth;
	char chDay;
	char chHour;
	char chMinute;
	char chSec;
}REQ_TIME_SYNC_SET;
typedef struct __attribute__((__packed__)){
	short nYear;
	char chMonth;
	char chDay;
	char chHour;
	char chMinute;
	char chSec;
}RES_TIME_SYNC_SET;


typedef struct __attribute__((__packed__)){
	int iAz;
	int iEl;
}REQ_POSITION_AZ_EL_OFFSET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_POSITION_AZ_EL_OFFSET;


typedef struct __attribute__((__packed__)){
	int iAz;
	int iEl;
}REQ_EXTERN_DEV_IP_SET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_EXTERN_DEV_IP_SET;


typedef struct __attribute__((__packed__)){
	char chSendAcuOn;
}REQ_SEND_ACU_DATA;
typedef struct __attribute__((__packed__)){
	char *chAcuData;
}RES_SEND_ACU_DATA;


typedef struct __attribute__((__packed__)){
	char chFpgaTimeSet;
}REQ_FPGA_TIME_SET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_FPGA_TIME_SET;


typedef struct __attribute__((__packed__)){
	char chFpgaTimeSyncCheck;
}REQ_FPGA_TIME_SYNC_CHECK;
typedef struct __attribute__((__packed__)){
	int iFpgaTime;
}RES_FPGA_TIME_SYNC_CHECK;


typedef struct __attribute__((__packed__)){
	int iAzElStartPoint;
	int iSzElSendPeriod;
}REQ_PRE_PROGRAM_START_POINT;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_PRE_PROGRAM_START_POINT;


typedef struct __attribute__((__packed__)){
	char *chElData;
}REQ_EL_CALIBRATION_SET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_EL_CALIBRATION_SET;


typedef struct __attribute__((__packed__)){
	int iTrueNorthOffset;
}REQ_TRUE_NORTH_OFFSET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_TRUE_NORTH_OFFSET;


typedef struct __attribute__((__packed__)){
	short nAzProcNoise;
	short nElProcNoise;
	short nAzMaesNoise;
	short nElMeasNoise;
	int iAzInitValue;
	int iElInitValue;
	short nTimeInterval;
}KALMAN_FILTER_CFG;
typedef struct __attribute__((__packed__)){
	char chUsingFlag;
	KALMAN_FILTER_CFG stExtKalmanCfg;
	KALMAN_FILTER_CFG stProgramKalmanCfg;
	KALMAN_FILTER_CFG stMcrKalmanCfg;
}REQ_KALMAN_FILTER_INFO;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_KALMAN_FILTER_INFO;


typedef struct __attribute__((__packed__)){
	double dGpsAltitudeOffset;
}REQ_GPS_ALTITUDE_OFFSET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_GPS_ALTITUDE_OFFSET;


typedef struct __attribute__((__packed__)){
	char chExternModeSelect;
	char chAtsVid;
	int iMulticastIP;
	int iMulticastPort;
	int iLimit;
}REQ_EXTERN_PARAM_SET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_EXTERN_PARAM_SET;


typedef struct __attribute__((__packed__)){
	double dRollOffset;
	double dPitchOffset;
	double dYawOffset;
}REQ_IMU_OFFSET;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_IMU_OFFSET;



typedef struct __attribute__((__packed__)){
	double dLatitude;//위도
	double dLongitude;//경도
	double dAltitude;//고도
}REQ_TARGET_LLA;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_TARGET_LLA;





// 명령별 핸들러 함수 선언
/**
 * @brief KeepAlive 응답 메시지를 생성합니다.
 * 
 * @param pchRequest 수신된 페이로드 (미사용)
 * @param pchResponse 응답 버퍼 (RES_KEEP_ALIVE 구조체 형태)
 * @return CMD_SUCCESS (정상)
 */
int keepAlive(const char* pchRequest, char* response, void* pvData);

/**
 * @brief iBIT 응답 메시지를 생성합니다.
 * 
 * @param pchRequest 수신된 페이로드 (미사용)
 * @param pchResponse 응답 버퍼 (RES_IBIT 구조체 형태)
 * @return CMD_SUCCESS (정상)
 */
int iBit(const char* pchRequest, char* response, void* pvData);

/**
 * @brief rBIT 응답 메시지를 생성합니다.
 * 
 * @param pchRequest 수신된 페이로드 (미사용)
 * @param pchResponse 응답 버퍼 (RES_RBIT 구조체 형태)
 * @return CMD_SUCCESS (정상)
 */
int rBit(const char* pchRequest, char* response, void* pvData);

/**
 * @brief cBIT 요청을 처리하고 응답 메시지를 생성합니다.
 * 
 * @param pchRequest 수신된 페이로드 (REQ_CBIT 구조체)
 * @param pchResponse 응답 버퍼 (RES_CBIT 구조체)
 * @return CMD_SUCCESS (정상)
 */
int cBit(const char* pchRequest, char* response, void* pvData);

//todo 
int positionAzElSet(const char* pchRequest, char* response, void* pvData);
int trackingModeSelect(const char* pchRequest, char* response, void* pvData);
int trackingStartMode(const char* pchRequest, char* response, void* pvData);
int trajectoryInfo(const char* pchRequest, char* response, void* pvData);
int shelterCoordinate(const char* pchRequest, char* response, void* pvData);
int externDevCoordinate(const char* pchRequest, char* response, void* pvData);
int cannonCoordinate(const char* pchRequest, char* response, void* pvData);
int trackingStartStop(const char* pchRequest, char* response, void* pvData);
int positionDegSend(const char* pchRequest, char* response, void* pvData);
int acuModeSelect(const char* pchRequest, char* response, void* pvData);
int timeSyncCheck(const char* pchRequest, char* response, void* pvData);
int timeSyncSet(const char* pchRequest, char* response, void* pvData);
int positionAzElOffset(const char* pchRequest, char* response, void* pvData);
int externDevIpSet(const char* pchRequest, char* response, void* pvData);
int sendAcuData(const char* pchRequest, char* response, void* pvData);
int fpgaTimeSet(const char* pchRequest, char* response, void* pvData);
int fpgaTimeSyncCheck(const char* pchRequest, char* response, void* pvData);
int preProgramStartPoint(const char* pchRequest, char* response, void* pvData);
int elCalibrationSet(const char* pchRequest, char* response, void* pvData);
int trueNorthOffset(const char* pchRequest, char* response, void* pvData);
int kalmanFilterInfo(const char* pchRequest, char* response, void* pvData);
int gpsAltitudeOffset(const char* pchRequest, char* response, void* pvData);
int externParamSet(const char* pchRequest, char* response, void* pvData);
int imuOffset(const char* pchRequest, char* response, void* pvData);
int targetLla(const char* pchRequest, char* response, void* pvData);
int unknownCommand(const char* pchRequest, char* response, void* pvData);

/* UDS */
typedef struct __attribute__((__packed__)){	
	int iId;
}REQ_UDS_ID;
typedef struct __attribute__((__packed__)){
	char chResult;
}RES_UDS_ID;


typedef struct __attribute__((__packed__)){
	double dLatitude;//위도
	double dLongitude;//경도
	double dAltitude;//고도
}GPS_DATA;


typedef struct __attribute__((__packed__)){
	double dRoll;
	double dPitch;
	double dYaw;
}IMU_DATA;


typedef struct __attribute__((__packed__)){
    double dAz;
    double dEl;
}SP_DATA;


typedef struct __attribute__((__packed__)){
    double dData1;
	double dData2;
	double dData3;
}EXTERN_DATA;


typedef struct __attribute__((__packed__)){
    double dAz;
    double dEl;
}KEYBOARD_DATA;


typedef struct __attribute__((__packed__)){
	double dAz;
    double dEl;
}PROCESSING_DATA;


typedef struct __attribute__((__packed__)){
	char chTmp;
}REQ_CONTROLL_DATA;
typedef struct __attribute__((__packed__)){
	double dAz;
    double dEl;
}RES_CONTROLL_DATA;


typedef struct __attribute__((__packed__)){
	char chCmd;
}REQ_COMMAND_DATA;
typedef struct __attribute__((__packed__)){
	char chCmd;
}RES_COMMAND_DATA;

typedef struct __attribute__((__packed__)){
	char chResult;
}RES_UNKNOWN_COMMAND;

/**
 * @brief 외부 시스템으로부터 받은 위치 데이터(EXTERNAL1_DATA)를 저장합니다.
 * 
 * @param pchRequest 수신된 위치 데이터 (EXTERNAL1_DATA)
 * @param pchResponse 응답 버퍼 (SENSOR_DATA에 저장됨)
 * @return CMD_SUCCESS (정상)
 */
int responseUdsId(const char* pchRequest, char* pchResponse, void* pvData);
int recvGpsData(const char* pchRequest, char* pchResponse, void* pvData);
int recvImuData(const char* pchRequest, char* pchResponse, void* pvData);
int recvSpData(const char* pchRequest, char* pchResponse, void* pvData);
int recvExternData(const char* pchRequest, char* pchResponse, void* pvData);
int recvKeyboardData(const char* pchRequest, char* pchResponse, void* pvData);
int recvProcessingData(const char* pchRequest, char* pchResponse, void* pvData);
int recvControllData(const char* pchRequest, char* pchResponse, void* pvData);
int recvCommandData(const char* pchRequest, char* pchResponse, void* pvData);

int udsTrackingMode(const char* pchRequest, char* pchResponse, void* pvData);

typedef struct __attribute__((__packed__)){
	GPS_DATA stGpsData;
    IMU_DATA stImuData;
    SP_DATA stSpData;
    EXTERN_DATA stExternData;
	KEYBOARD_DATA stKeyboardData;
}SENSOR_DATA;

#ifdef __cplusplus
}
#endif
#endif
