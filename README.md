# 🧭 Command Dispatcher and UDS Communication Framework

이 프로젝트는 다양한 명령(Command)를 처리하기 위한 커맨드 디스패처(Command Dispatcher) 및 UDS(Unix Domain Socket) 기반의 통신 프레임워크를 구현한 것입니다. 주요 목적은 **제어 명령의 분산 처리**, **로컬 데이터 송수신**, **패킷 포맷 검사 및 로깅**을 통해 신뢰성 높은 통신 시스템을 구축하는 것입니다.




---
## 📁 디렉토리 구조

```bash
├── src/
│   ├── cmd-handler.c       # 명령 처리 분배기
│   ├── command.c           # 각 명령별 실제 핸들러 구현
│   ├── frame-format.c      # 패킷 포맷 및 CRC 생성/검사
│   ├── logger.c            # 로깅 함수
├── include/
│   ├── cmd-handler.h       # 명령 처리 분배기
│   ├── command.h           # 각 명령별 실제 핸들러 구현
│   ├── frame-format.h      # 패킷 포맷 및 CRC 생성/검사
│   ├── logger.h            # 로깅 함수
│   └── uds-info.h               # UDS 경로 및 ID 정의
├── gtest/
│   └── command-core-gtest.cc    # GoogleTest 기반 테스트 코드
├── include/                     # 헤더 파일 포함 경로
├── Makefile                     # 빌드 설정
└── README.md                    # 설명 파일 (현재 파일)
```






---
## 🔧 주요 구성 요소

### ✅ 1. 명령 디스패처 (`cmd-handler`)

- `cmd_handler_t handlers[]` : 명령 ID와 해당 핸들러 매핑
- `dispatchCommand(...)` : 요청 명령을 찾아 핸들러 실행 및 응답 생성
- `getCmdName`, `getReqestCmdSize`, `getResponseCmdSize` 지원 함수 포함

### ✅ 2. 명령 핸들러 (`command`)

- `keepAlive`, `iBit`, `acuModeSelect`, `trackingModeSelect` 등 명령별 처리 함수 구현
- UDS를 통한 센서 데이터 수신 핸들러도 포함 (`recvGpsData`, `recvImuData` 등)
- 기본적으로 `pchRequest`, `pchResponse`, `pvData`를 인자로 받아 로직 수행

### ✅ 3. 프레임 포맷 처리 (`frame-format`)

- `FRAME_HEADER` / `FRAME_TAIL` 구조 정의
- `calculatePacketCrc`, `checkPacketCrc` 등 CRC 검사 함수 제공
- `makeRequestPacket`, `makeResponsePacket`, `checkPacketFormat` 등 프레임 생성 함수 포함

### ✅ 4. 로깅 기능 (`logger`)

- `logging()` 함수: 명령 실행 시 상태 출력 (`[LOG] CMD_ID: XX (NAME), STATUS: YY`)




------
## 🧪 테스트 (Google Test 기반)

### 테스트 대상

- UDS 서버 클라이언트 연결
- 클라이언트의 ID 송신
- 수신 데이터 포맷 검증

### 실행 방법

```bash
make gtest
./gtest/command-core-gtest
```



### 예시 테스트

```cpp
TEST_F(UdsServerTest, ClientSendIdTest) {
    createClientsAndSendID(TEST_CLIENT_COUNT);
    collectReceivedClientIdData();
}
```



------
##  통신 흐름

1. 클라이언트 → 서버로 UDS 통해 요청 전송
2. 서버는 `dispatchCommand()`로 명령 분류 후 응답 생성
3. 응답 프레임은 `makeResponsePacket()`으로 작성되어 클라이언트로 전송
4. 로깅은 `logging()`을 통해 상태 추적 가능



------
## ⚙️ 동적 라이브러리 빌드 방법

```
make desktop
```

빌드 타겟은 `Makefile`의 설정에 따라 분리 가능하며,



------
## 📌 참고 사항

- `cmd_id_t`는 명령의 ID를 나타내며 0~500 이상까지 범위별로 용도 구분됨
- `REQ_XXX`, `RES_XXX` 구조체는 요청/응답 포맷을 지정하며 packed 구조로 정의
- UDS 경로는 `/tmp/uds1.sock`, `/tmp/uds2.sock` 등 고정값으로 지정되어 있음





## ✍️ 작성자

- 박철우 (Embedded Software Engineer, Acewave Tech)
- GitHub ID: `pcw1029`
