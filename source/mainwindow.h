#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QTimer>
#include <QDateTime>
#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QObject>
#include <QMouseEvent>
#include <QThread>
#include <QFontDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

#define DEFAULT_TIMER_TIME			50
#define DEFAULT_WINDOW_CHANGE_TIME (30000 / (DEFAULT_TIMER_TIME))

// P1 UI Scale
#define MIN_RPM_VALUE 1000
#define MAX_RPM_VALUE 2000

#define WARNING_TEMP_VAL	90
#define ERROR_TEMP_VAL		100

#define WARNING_CURRENT_VAL	50
#define ERROR_CURRENT_VAL	80

#define MAX_TEMP_VAL	200
#define MAX_CURRENT_VAL	322


#define DEF_STX     0x44
#define DEF_ETX     0x43

#define	ID_MASTER	0
#define	ID_SUB1	1
#define	ID_SUB2	2
#define	ID_SUB3	3

#define	SET_NOTUSED	0
#define	SET_USE	1

#define	SET_NOTCONN	0
#define	SET_CONN	1

#define	SET_NORMAL	0
#define	SET_WARNING	1
#define	SET_ERROR	2

#define	SET_CCW	0
#define	SET_CW	1

#define	SET_STOP	0
#define	SET_RUN	1

#define	SET_RUNTYPE1	0	// 개별자동운전
#define	SET_RUNTYPE2	1	// 자동연동운전
#define	SET_RUNTYPE3	2	// 수동운전

#define	SET_LO	0
#define	SET_LL	1
#define	SET_L	2
#define	SET_H	3
#define	SET_HH	4


#define	PUMP_ID	0	// Device ID [ ID_MASTER=Master, ID_SUB1=Sub1, ID_SUB2=Sub2, ID_SUB3=Sub3 ]
#define	PUMP_ATYPE	1	// 운전 상태 [ SET_RUNTYPE1=개별자동운전, SET_RUNTYPE2=자동연동운전, SET_RUNTYPE3=수동운전 ]
#define	PUMP_STAT	2	// 현재 모터 스테이터스 [ SET_NORMAL=정상, SET_WARNING=경보 이벤트 발생, SET_ERROR=에러 이벤트 발생 ]
#define	PUMP_RUN	3	// 현재 모터 상태 [ SET_STOP=STOP, SET_RUN=RUN ]
#define	PUMP_DIR	4	// 현재 모터 회전 방향 [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_RPM	5	// 현재 RPM
#define	PUMP_M1T	6	// 현재 모터1 온도
#define	PUMP_M2T	7	// 현재 모터2 온도
#define	PUMP_M3T	8	// 현재 모터3 온도
#define	PUMP_M4T	9	// 현재 베어링(상) 온도
#define	PUMP_M5T	10	// 현재 베어링(하) 온도
#define	PUMP_M1C	11	// 현재 모터 전류1
#define	PUMP_M2C	12	// 현재 모터 전류2
#define	PUMP_M3C	13	// 현재 모터 전류3
#define	PUMP_OC	14	// 현재 최대 전류
#define	PUMP_UC	15	// 현재 최소 전류
#define	PUMP_UB	16	// 현재 불평형
#define	PUMP_FM	17	// 모터 누수 여부 [ SET_NORMAL=안전, SET_ERROR=정지 ]
#define	PUMP_FO	18	// 오일 누수 여부 [ SET_NORMAL=안전, SET_ERROR=정지 ]
#define	PUMP_FC	19	// 제어 누수 여부 [ SET_NORMAL=안전, SET_ERROR=정지 ]
#define	PUMP_WL	20	// 현재 수위 위치 [ SET_LO=LO, SET_LL=LL, SET_L=L, SET_H=H, SET_HH=HH ]
#define	PUMP_MP	21	// 현재 가동 중 펌프 [ ID_MASTER=Master, ID_SUB1=Sub1, ID_SUB2=Sub2, ID_SUB3=Sub3 ]
#define	PUMP_EM1T	22	// 모터1 에러 온도 설정 값 [ 단위 5℃ , WMxT ~ 200℃ ]
#define	PUMP_EM2T	23	// 모터2 에러 온도 설정 값 [ 단위 5℃ , WMxT ~ 200℃ ]
#define	PUMP_EM3T	24	// 모터3 에러 온도 설정 값 [ 단위 5℃ , WMxT ~ 200℃ ]
#define	PUMP_EM4T	25	// 베어링(상) 에러 온도 설정 값 [ 단위 5℃ , WMxT ~ 200℃ ]
#define	PUMP_EM5T	26	// 베어링(하) 에러 온도 설정 값 [ 단위 5℃ , WMxT ~ 200℃ ]
#define	PUMP_WM1T	27	// 모터1 경고 온도 설정 값 [ 단위 5℃ , 40 ~ EMxT ]
#define	PUMP_WM2T	28	// 모터2 경고 온도 설정 값 [ 단위 5℃ , 40 ~ EMxT ]
#define	PUMP_WM3T	29	// 모터3 경고 온도 설정 값 [ 단위 5℃ , 40 ~ EMxT ]
#define	PUMP_WM4T	30	// 베어링(상) 경고 온도 설정 값 [ 단위 5℃ , 40 ~ EMxT ]
#define	PUMP_WM5T	31	// 베어링(하) 경고 온도 설정 값 [ 단위 5℃ , 40 ~ EMxT ]
#define	PUMP_RM1T	32	// 모터1 재가동 온도 설정 값 [ 단위 5℃ , 40 ~ WMxT ]
#define	PUMP_RM2T	33	// 모터2 재가동 온도 설정 값 [ 단위 5℃ , 40 ~ WMxT ]
#define	PUMP_RM3T	34	// 모터3 재가동 온도 설정 값 [ 단위 5℃ , 40 ~ WMxT ]
#define	PUMP_RM4T	35	// 베어링(상) 재가동 온도 설정 값 [ 단위 5℃ , 40 ~ WMxT ]
#define	PUMP_RM5T	36	// 베어링(하) 재가동 온도 설정 값 [ 단위 5℃ , 40 ~ WMxT ]
#define	PUMP_EUC	37	// 비상신호출력이 발생되는 “UC” 값을 설정 [ 단위 0.1A , 0.5 ~ WUC ] -> 2Byte 필요
#define	PUMP_WUC	38	// 경보신호출력이 발생되는 “UC” 값을 설정 [ 단위 0.1A , 0.5 ~ WOC ] -> 2Byte 필요
#define	PUMP_EOC	39	// 비상신호출력이 발생되는 “OC” 값을 설정 [ 단위 0.1A , WUC ~ 40A ] -> 2Byte 필요
#define	PUMP_WOC	40	// 경보신호출력이 발생되는 “OC” 값을 설정 [ 단위 0.1A , 0.5 ~ EOC ] -> 2Byte 필요
#define	PUMP_WRPM	41	// 경고 RPM 설정 값 (현재 RPM이 경고RPM 이하 일 시 경고 발생)
#define	PUMP_ERPM	42	// 에러 RPM 설정 값 (현재 RPM이 경고RPM 이상 일 시 경고 발생)
#define	PUMP_RS	43	// 기동 시 최대 RPM [ 기동구속 ] (????????????????????????)
#define	PUMP_RJ	44	// 운전 시 변동 RPM [ 운전구속 ] (???????????????????????? RPM이랑 동일 한 것인가?)
#define	PUMP_RUNT	45	// 총 누적 사용시간
#define	PUMP_C1	46	// 스트레이너 주기 시간
#define	PUMP_C2	47	// 임펠러 주기 시간
#define	PUMP_C3	48	// 베어링 주기 시간
#define	PUMP_HH	49	// HH 수위 센서 가동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_MH	50	// H 수위 센서 가동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_ML	51	// L 수위 센서 가동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_LL	52	// LL 수위 센서 가동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_LO	53	// LO 수위 센서 가동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_PL	54	// 펌프수위 여부(???????????????????????????????????? 어디는 "사용안함"or"가동" 이고.. 어디는 "High"or"Low" 이고..) [ 0=사용안함, 1=가동 ]
#define	PUMP_Ryqjs_Run	55	// 교번 운전으로 움직이는 모터 위치 [ ID_MASTER=Master, ID_SUB1=Sub1, ID_SUB2=Sub2, ID_SUB3=Sub3 ]
#define	PUMP_YD_Master	56	// Master의 연결 상태 [ SET_NOTCONN=미연결, SET_CONN=연결됨 ] (연동 운동 정보에서 Motor Icon 표시 여부)
#define	PUMP_YD_Sub1	57	// Sub1의 연결 상태 [ SET_NOTCONN=미연결, SET_CONN=연결됨 ] (연동 운동 정보에서 Motor Icon 표시 여부)
#define	PUMP_YD_Sub2	58	// Sub2의 연결 상태 [ SET_NOTCONN=미연결, SET_CONN=연결됨 ] (연동 운동 정보에서 Motor Icon 표시 여부)
#define	PUMP_YD_Sub3	59	// Sub3의 연결 상태 [ SET_NOTCONN=미연결, SET_CONN=연결됨 ] (연동 운동 정보에서 Motor Icon 표시 여부)
#define	PUMP_GYD_Master	60	// Master의 교번운전 연동 여부 [ SET_NOTUSED=사용안함, SET_RUN=가동 ]
#define	PUMP_GYD_Sub1	61	// Sub1의 교번운전 연동 여부 [ SET_NOTUSED=사용안함, SET_RUN=가동 ]
#define	PUMP_GYD_Sub2	62	// Sub2의 교번운전 연동 여부 [ SET_NOTUSED=사용안함, SET_RUN=가동 ]
#define	PUMP_GYD_Sub3	63	// Sub3의 교번운전 연동 여부 [ SET_NOTUSED=사용안함, SET_RUN=가동 ]
#define	PUMP_MYD_Master	64	// Master의 만수위 연동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_MYD_Sub1	65	// Sub1의 만수위 연동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_MYD_Sub2	66	// Sub2의 만수위 연동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_MYD_Sub3	67	// Sub3의 만수위 연동 여부 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_DIR_Master	68	// Master의 모터 방향 [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_DIR_Sub1	69	// Sub1의 모터 방향 [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_DIR_Sub2	70	// Sub2의 모터 방향 [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_DIR_Sub3	71	// Sub3의 모터 방향 [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_EVT_RETRY	72	// 이벤트 재가동 현재 횟수
#define	PUMP_EVT_TOT	73	// 이벤트 재가동 최대 횟수
#define	PUMP_WF	74	// 위험 수위 [ SET_STOP=정지, SET_RUN=가동 ]
#define	PUMP_RETRY	75	// 에러 시 재시도 횟수
#define	PUMP_DET	76	// 모터 기동 시의 전류 측정 지연시간 [ 단위 1초 , 0 ~ 200 초]
#define	PUMP_OVT	77	// 과전류 동작 지속시간 [ 단위 0.1초 , 0.2 ~ 25 초 ] -> 단위 초과로 단위 조절
#define	PUMP_UCT	78	// 저전류 동작 지속시간 [ 단위 0,1초 , 0.5 ~ 25 초 ] -> 단위 초과로 단위 조절
#define	PUMP_UBT	79	// 불평형 동작 지속시간 [ 단위 1초 , 1 ~ 10 초 ]
#define	PUMP_RET	80	// 비상정지 후 재가동 지연시간 [ 단위 5초 , 5 ~ 1250초 ] -> 단위 초과로 단위 조절
#define	PUMP_WUB	81	// 경보신호출력이 발생되는 “UB” 값을 설정 [ 1% ~ EUC ]
#define	PUMP_EUB	82	// 비상신호출력이 발생되는 “UB” 값을 설정 [ WUB ~ 100% ]
#define	PUMP_RST	83
#define	PUMP_RJT	84
#define	PUMP_WRS	85
#define	PUMP_ERS	86
#define	PUMP_WRJ	87
#define	PUMP_ERJ	88
#define PUMP_CHK_MECHA	89 // 메카니즘실 확인 [SET_NORMAL=정상, SET_ERROR=에러]
#define PUMP_CHK_BEARING	90 // 베어링 확인 [SET_NORMAL=정상, SET_ERROR=에러]
#define PUMP_CHK_OIL	91 // 오일 확인 [SET_NORMAL=정상, SET_ERROR=에러]

#define 	MAX_PUMP_DEFINE	100



#define	S_P5_V1	0
#define	S_P5_V2	1
#define	S_P5_V3	2
#define	S_P5_V4	3
#define	S_P5_V5	4
#define	S_P5_V6	5
#define	S_P5_V7	6
#define	S_P5_V8	7
#define	S_P5_V9	8
#define	S_P5_V10	9
#define	S_P5_V11	10
#define	S_P5_V12	11
#define	S_P5_V13	12
#define	S_P5_V14	13
#define	S_P5_V15	14
#define	S_P5_V16	15
#define	S_P5_V17	16
#define	S_P5_V18	17
#define	S_P5_V19	18
#define	S_P5_V20	19
#define	S_P6_V1	20
#define	S_P6_V2	21
#define	S_P6_V3	22
#define	S_P6_V4	23
#define	S_P6_V5	24
#define	S_P6_V6	25
#define	S_P6_V7	26
#define	S_P6_V8	27
#define	S_P6_V9	28
#define	S_P6_V10	29
#define	S_P6_V11	30
#define	S_P7_V1	31
#define	S_P7_V2	32
#define	S_P7_V3	33
#define	S_P7_V4	34
#define	S_P7_V5	35
#define	S_P8_V1	36
#define	S_P8_V2	37
#define	S_P8_V3	38
#define	S_P8_V4	39
#define	S_P8_V5	40
#define	S_P8_V6	41
#define	S_P8_V7	42
#define	S_P8_V8	43
#define	S_P8_V9	44
#define	S_P8_V10	45
#define	S_P8_V11	46
#define	S_P8_V12	47
#define	S_P8_V13	48
#define	S_P8_V14	49
#define	S_P8_V15	50
#define	S_P8_V16	51
#define	S_P8_V17	52
#define	S_P8_V18	53
#define	S_P8_V19	54
#define	S_P8_V20	55
#define	S_P8_V21	56
#define	S_P8_V22	57
#define	S_P8_V23	58
#define	S_P8_V24	59
#define	S_P8_V25	60
#define	S_P8_V26	61
#define	S_P8_V27	62

#define		MAX_SET_DEFINE	100

//frame : 운전
//frame_2 : 온도히스토리
//frame_3 : 전류히스토리
//frame_4 : 펌프모델선택
//frame_5 : 설정-온도설정
//frame_6 : 설정-전류설정
//frame_7 : 설정-RPM
//frame_8 : 설정-운전설정
//frame_9 : 설정-시간설정
//frame_10 : 이벤트정보기록
//frame_11 : Serial Port 선택

	typedef enum{
		WIN_1,
		WIN_2,
		WIN_3,
		WIN_4,
		WIN_5,
		WIN_6,
		WIN_7,
		WIN_8,
		WIN_9,
		WIN_10,
		WIN_99
	}WIN_VAR;

	typedef enum{
		CHK_START,
		CHK_HEADER,
		CHK_LENGTH,
		CHK_DATA,
		CHK_CRC,
		CHK_END
	}COMM_VAR;

	// 7
	QString P1_RPM1_STR=":/new/1P/UIUX/1p/rpm/1P_Group1 (2).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (4).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (5).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (6).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (7).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (8).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (9).png";
	// 16
	QString P1_RPM2_STR=":/new/1P/UIUX/1p/rpm/1P_Group1 (10).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (11).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (12).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (13).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (14).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (15).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (16).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (17).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (18).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (19).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (20).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (21).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (22).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (23).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (24).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (25).png";
	// 3
	QString P1_MotorDir_STR=":/new/1P/UIUX/1p/rpm/1P_Group1 (1).png,:/new/1P/UIUX/1p/rpm/1P_Group1 (3).png";
	// 5
	QString P1_WaterLevel_STR=":/new/1P/UIUX/1p/level/1P_Group2 (5).png,:/new/1P/UIUX/1p/level/1P_Group2 (11).png,:/new/1P/UIUX/1p/level/1P_Group2 (12).png,:/new/1P/UIUX/1p/level/1P_Group2 (13).png,:/new/1P/UIUX/1p/level/1P_Group2 (14).png";
	// 2
	QString P1_MotorSafe_STR=":/new/1P/UIUX/1p/safe/1P_Group3 (1).png,:/new/1P/UIUX/1p/safe/1P_Group3 (8).png";
	// 2
	QString P1_OilSafe_STR=":/new/1P/UIUX/1p/safe/1P_Group3 (2).png,:/new/1P/UIUX/1p/safe/1P_Group3 (9).png";
	// 2
	QString P1_ControlSafe_STR = ":/new/1P/UIUX/1p/safe/1P_Group3 (3).png,:/new/1P/UIUX/1p/safe/1P_Group3 (10).png";
	// 2
	QString P1_AutoSafe_STR = ":/new/1P/UIUX/1p/safe/1P_Group3 (4).png,:/new/1P/UIUX/1p/safe/1P_Group3 (11).png";
	// 2
	QString P1_SafeMecha_STR = ":/new/1P/UIUX/1p/safe/1P_Group3 (7).png,:/new/1P/UIUX/1p/safe/1P_Group3 (12).png";
	// 2
	QString P1_BRSafe_STR = ":/new/1P/UIUX/1p/safe/1P_Group3 (6).png,:/new/1P/UIUX/1p/safe/1P_Group3 (13).png";
	// 2
	QString P1_OilSafe_2_STR = ":/new/1P/UIUX/1p/safe/1P_Group3 (5).png,:/new/1P/UIUX/1p/safe/1P_Group3 (14).png";

	QStringList P1_RPM1_STRList;
	QStringList P1_RPM2_STRList;
	QStringList P1_MotorDir_STRList;
	QStringList P1_WaterLevel_STRList;
	QStringList P1_MotorSafe_STRList;
	QStringList P1_OilSafe_STRList;
	QStringList P1_ControlSafe_STRList;
	QStringList P1_AutoSafe_STRList;
	QStringList P1_SafeMecha_STRList;
	QStringList P1_BRSafe_STRList;
	QStringList P1_OilSafe_2_STRList;
	int P1_RPM1_STRCnt;
	int P1_RPM2_STRCnt;
	int P1_MotorDir_STRCnt;
	int P1_WaterLevel_STRCnt;
	int P1_MotorSafe_STRCnt;
	int P1_OilSafe_STRCnt;
	int P1_ControlSafe_STRCnt;
	int P1_AutoSafe_STRCnt;
	int P1_SafeMecha_STRCnt;
	int P1_BRSafe_STRCnt;
	int P1_OilSafe_2_STRCnt;

	int mRPMIndex = 0;

	int P1_M1Val = 0;
	int P1_M2Val = 0;
	int P1_M3Val = 0;
	int P1_M4Val = 0;
	int P1_M5Val = 0;

	int P1_RCVal = 0;
	int P1_SCVal = 0;
	int P1_TCVal = 0;

	int ScrollVar[50][4];

public:
	void SettingVar_Init();
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void mouseMoveEvent(QMouseEvent *event1); //마우스 움직임 이벤트
	void mouseReleaseEvent(QMouseEvent *event); //마우스 클릭 후 떼었을 때 이벤트
	void mousePressEvent(QMouseEvent *event); //마우스를 클릭하고 있을 때 이벤트
	int TouchMatching(int val, int minimum, int maximum);
	void TouchProcess_WIN1(int x,int y);
	void TouchProcess_WIN2(int x,int y);
	void TouchProcess_WIN3(int x,int y);
	void TouchProcess_WIN5(int x,int y);
	void TouchProcess_WIN6(int x,int y);
	void TouchProcess_WIN7(int x,int y);
	void TouchProcess_WIN8(int x,int y);
	void TouchProcess_WIN9(int x,int y);
	void TouchProcess_WIN10(int x,int y);
	void TouchMove_WIN5(int orgX, int orgY);
	void TouchMove_WIN6(int orgX, int orgY);
	void TouchMove_WIN7(int orgX, int orgY);
	void ChangeWindow_WIN1(void);
	void ChangeWindow_WIN2(void);
	void ChangeWindow_WIN3(void);
	void ChangeWindow_WIN5(void);
	void ChangeWindow_WIN6(void);
	void ChangeWindow_WIN7(void);
	void ChangeWindow_WIN8(void);
	void ChangeStringList(void);


	WIN_VAR nNowWindow;
	QTimer *timer;
	int count;
	int nExitCnt;

	// Comport
	COMM_VAR m_rcvIndex;
	QSerialPort *m_port;
	QByteArray m_send;
	QByteArray m_rcv;
	QElapsedTimer m_rcvTimer;
	int i_rcvCnt;
	int i_rcvHeader;
	QByteArray m_rcvData;
	int i_rcvDataCnt;
	int i_rcvCRC;

	int Motor_Var[MAX_PUMP_DEFINE];

	int Setting_Var[MAX_SET_DEFINE];

	int iXdifferent,iYdifferent; //X,Y축 움직임 저장변수
	bool b_MousePressed; //마우스 눌림 상태표시


private slots:
	bool eventFilter(QObject *object, QEvent *event);

	void Init_Timer(void);
	int Init_Serial(void);
	void breakCaught(void);
	void on_readyRead(void);
	void Display_UI_Value(void);
	void timer_Update(void);
	void Select_Window(WIN_VAR nSelWin);

	void on_CMD_SelUART_clicked();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
