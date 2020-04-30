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

#define	SET_RUNTYPE1	0	// �����ڵ�����
#define	SET_RUNTYPE2	1	// �ڵ���������
#define	SET_RUNTYPE3	2	// ��������

#define	SET_LO	0
#define	SET_LL	1
#define	SET_L	2
#define	SET_H	3
#define	SET_HH	4


#define	PUMP_ID	0	// Device ID [ ID_MASTER=Master, ID_SUB1=Sub1, ID_SUB2=Sub2, ID_SUB3=Sub3 ]
#define	PUMP_ATYPE	1	// ���� ���� [ SET_RUNTYPE1=�����ڵ�����, SET_RUNTYPE2=�ڵ���������, SET_RUNTYPE3=�������� ]
#define	PUMP_STAT	2	// ���� ���� �������ͽ� [ SET_NORMAL=����, SET_WARNING=�溸 �̺�Ʈ �߻�, SET_ERROR=���� �̺�Ʈ �߻� ]
#define	PUMP_RUN	3	// ���� ���� ���� [ SET_STOP=STOP, SET_RUN=RUN ]
#define	PUMP_DIR	4	// ���� ���� ȸ�� ���� [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_RPM	5	// ���� RPM
#define	PUMP_M1T	6	// ���� ����1 �µ�
#define	PUMP_M2T	7	// ���� ����2 �µ�
#define	PUMP_M3T	8	// ���� ����3 �µ�
#define	PUMP_M4T	9	// ���� ���(��) �µ�
#define	PUMP_M5T	10	// ���� ���(��) �µ�
#define	PUMP_M1C	11	// ���� ���� ����1
#define	PUMP_M2C	12	// ���� ���� ����2
#define	PUMP_M3C	13	// ���� ���� ����3
#define	PUMP_OC	14	// ���� �ִ� ����
#define	PUMP_UC	15	// ���� �ּ� ����
#define	PUMP_UB	16	// ���� ������
#define	PUMP_FM	17	// ���� ���� ���� [ SET_NORMAL=����, SET_ERROR=���� ]
#define	PUMP_FO	18	// ���� ���� ���� [ SET_NORMAL=����, SET_ERROR=���� ]
#define	PUMP_FC	19	// ���� ���� ���� [ SET_NORMAL=����, SET_ERROR=���� ]
#define	PUMP_WL	20	// ���� ���� ��ġ [ SET_LO=LO, SET_LL=LL, SET_L=L, SET_H=H, SET_HH=HH ]
#define	PUMP_MP	21	// ���� ���� �� ���� [ ID_MASTER=Master, ID_SUB1=Sub1, ID_SUB2=Sub2, ID_SUB3=Sub3 ]
#define	PUMP_EM1T	22	// ����1 ���� �µ� ���� �� [ ���� 5�� , WMxT ~ 200�� ]
#define	PUMP_EM2T	23	// ����2 ���� �µ� ���� �� [ ���� 5�� , WMxT ~ 200�� ]
#define	PUMP_EM3T	24	// ����3 ���� �µ� ���� �� [ ���� 5�� , WMxT ~ 200�� ]
#define	PUMP_EM4T	25	// ���(��) ���� �µ� ���� �� [ ���� 5�� , WMxT ~ 200�� ]
#define	PUMP_EM5T	26	// ���(��) ���� �µ� ���� �� [ ���� 5�� , WMxT ~ 200�� ]
#define	PUMP_WM1T	27	// ����1 ��� �µ� ���� �� [ ���� 5�� , 40 ~ EMxT ]
#define	PUMP_WM2T	28	// ����2 ��� �µ� ���� �� [ ���� 5�� , 40 ~ EMxT ]
#define	PUMP_WM3T	29	// ����3 ��� �µ� ���� �� [ ���� 5�� , 40 ~ EMxT ]
#define	PUMP_WM4T	30	// ���(��) ��� �µ� ���� �� [ ���� 5�� , 40 ~ EMxT ]
#define	PUMP_WM5T	31	// ���(��) ��� �µ� ���� �� [ ���� 5�� , 40 ~ EMxT ]
#define	PUMP_RM1T	32	// ����1 �簡�� �µ� ���� �� [ ���� 5�� , 40 ~ WMxT ]
#define	PUMP_RM2T	33	// ����2 �簡�� �µ� ���� �� [ ���� 5�� , 40 ~ WMxT ]
#define	PUMP_RM3T	34	// ����3 �簡�� �µ� ���� �� [ ���� 5�� , 40 ~ WMxT ]
#define	PUMP_RM4T	35	// ���(��) �簡�� �µ� ���� �� [ ���� 5�� , 40 ~ WMxT ]
#define	PUMP_RM5T	36	// ���(��) �簡�� �µ� ���� �� [ ���� 5�� , 40 ~ WMxT ]
#define	PUMP_EUC	37	// ����ȣ����� �߻��Ǵ� ��UC�� ���� ���� [ ���� 0.1A , 0.5 ~ WUC ] -> 2Byte �ʿ�
#define	PUMP_WUC	38	// �溸��ȣ����� �߻��Ǵ� ��UC�� ���� ���� [ ���� 0.1A , 0.5 ~ WOC ] -> 2Byte �ʿ�
#define	PUMP_EOC	39	// ����ȣ����� �߻��Ǵ� ��OC�� ���� ���� [ ���� 0.1A , WUC ~ 40A ] -> 2Byte �ʿ�
#define	PUMP_WOC	40	// �溸��ȣ����� �߻��Ǵ� ��OC�� ���� ���� [ ���� 0.1A , 0.5 ~ EOC ] -> 2Byte �ʿ�
#define	PUMP_WRPM	41	// ��� RPM ���� �� (���� RPM�� ���RPM ���� �� �� ��� �߻�)
#define	PUMP_ERPM	42	// ���� RPM ���� �� (���� RPM�� ���RPM �̻� �� �� ��� �߻�)
#define	PUMP_RS	43	// �⵿ �� �ִ� RPM [ �⵿���� ] (????????????????????????)
#define	PUMP_RJ	44	// ���� �� ���� RPM [ �������� ] (???????????????????????? RPM�̶� ���� �� ���ΰ�?)
#define	PUMP_RUNT	45	// �� ���� ���ð�
#define	PUMP_C1	46	// ��Ʈ���̳� �ֱ� �ð�
#define	PUMP_C2	47	// ���緯 �ֱ� �ð�
#define	PUMP_C3	48	// ��� �ֱ� �ð�
#define	PUMP_HH	49	// HH ���� ���� ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_MH	50	// H ���� ���� ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_ML	51	// L ���� ���� ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_LL	52	// LL ���� ���� ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_LO	53	// LO ���� ���� ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_PL	54	// �������� ����(???????????????????????????????????? ���� "������"or"����" �̰�.. ���� "High"or"Low" �̰�..) [ 0=������, 1=���� ]
#define	PUMP_Ryqjs_Run	55	// ���� �������� �����̴� ���� ��ġ [ ID_MASTER=Master, ID_SUB1=Sub1, ID_SUB2=Sub2, ID_SUB3=Sub3 ]
#define	PUMP_YD_Master	56	// Master�� ���� ���� [ SET_NOTCONN=�̿���, SET_CONN=����� ] (���� � �������� Motor Icon ǥ�� ����)
#define	PUMP_YD_Sub1	57	// Sub1�� ���� ���� [ SET_NOTCONN=�̿���, SET_CONN=����� ] (���� � �������� Motor Icon ǥ�� ����)
#define	PUMP_YD_Sub2	58	// Sub2�� ���� ���� [ SET_NOTCONN=�̿���, SET_CONN=����� ] (���� � �������� Motor Icon ǥ�� ����)
#define	PUMP_YD_Sub3	59	// Sub3�� ���� ���� [ SET_NOTCONN=�̿���, SET_CONN=����� ] (���� � �������� Motor Icon ǥ�� ����)
#define	PUMP_GYD_Master	60	// Master�� �������� ���� ���� [ SET_NOTUSED=������, SET_RUN=���� ]
#define	PUMP_GYD_Sub1	61	// Sub1�� �������� ���� ���� [ SET_NOTUSED=������, SET_RUN=���� ]
#define	PUMP_GYD_Sub2	62	// Sub2�� �������� ���� ���� [ SET_NOTUSED=������, SET_RUN=���� ]
#define	PUMP_GYD_Sub3	63	// Sub3�� �������� ���� ���� [ SET_NOTUSED=������, SET_RUN=���� ]
#define	PUMP_MYD_Master	64	// Master�� ������ ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_MYD_Sub1	65	// Sub1�� ������ ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_MYD_Sub2	66	// Sub2�� ������ ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_MYD_Sub3	67	// Sub3�� ������ ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_DIR_Master	68	// Master�� ���� ���� [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_DIR_Sub1	69	// Sub1�� ���� ���� [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_DIR_Sub2	70	// Sub2�� ���� ���� [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_DIR_Sub3	71	// Sub3�� ���� ���� [ SET_CCW=CCW, SET_CW=CW ]
#define	PUMP_EVT_RETRY	72	// �̺�Ʈ �簡�� ���� Ƚ��
#define	PUMP_EVT_TOT	73	// �̺�Ʈ �簡�� �ִ� Ƚ��
#define	PUMP_WF	74	// ���� ���� [ SET_STOP=����, SET_RUN=���� ]
#define	PUMP_RETRY	75	// ���� �� ��õ� Ƚ��
#define	PUMP_DET	76	// ���� �⵿ ���� ���� ���� �����ð� [ ���� 1�� , 0 ~ 200 ��]
#define	PUMP_OVT	77	// ������ ���� ���ӽð� [ ���� 0.1�� , 0.2 ~ 25 �� ] -> ���� �ʰ��� ���� ����
#define	PUMP_UCT	78	// ������ ���� ���ӽð� [ ���� 0,1�� , 0.5 ~ 25 �� ] -> ���� �ʰ��� ���� ����
#define	PUMP_UBT	79	// ������ ���� ���ӽð� [ ���� 1�� , 1 ~ 10 �� ]
#define	PUMP_RET	80	// ������� �� �簡�� �����ð� [ ���� 5�� , 5 ~ 1250�� ] -> ���� �ʰ��� ���� ����
#define	PUMP_WUB	81	// �溸��ȣ����� �߻��Ǵ� ��UB�� ���� ���� [ 1% ~ EUC ]
#define	PUMP_EUB	82	// ����ȣ����� �߻��Ǵ� ��UB�� ���� ���� [ WUB ~ 100% ]
#define	PUMP_RST	83
#define	PUMP_RJT	84
#define	PUMP_WRS	85
#define	PUMP_ERS	86
#define	PUMP_WRJ	87
#define	PUMP_ERJ	88
#define PUMP_CHK_MECHA	89 // ��ī����� Ȯ�� [SET_NORMAL=����, SET_ERROR=����]
#define PUMP_CHK_BEARING	90 // ��� Ȯ�� [SET_NORMAL=����, SET_ERROR=����]
#define PUMP_CHK_OIL	91 // ���� Ȯ�� [SET_NORMAL=����, SET_ERROR=����]

#define 	MAX_PUMP_DEFINE	100

//frame : ����
//frame_2 : �µ������丮
//frame_3 : ���������丮
//frame_4 : �����𵨼���
//frame_5 : ����-�µ�����
//frame_6 : ����-��������
//frame_7 : ����-RPM
//frame_8 : ����-��������
//frame_9 : ����-�ð�����
//frame_10 : �̺�Ʈ�������
//frame_11 : Serial Port ����

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
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void mouseMoveEvent(QMouseEvent *event1); //���콺 ������ �̺�Ʈ
	void mouseReleaseEvent(QMouseEvent *event); //���콺 Ŭ�� �� ������ �� �̺�Ʈ
	void mousePressEvent(QMouseEvent *event); //���콺�� Ŭ���ϰ� ���� �� �̺�Ʈ
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

	int iXdifferent,iYdifferent; //X,Y�� ������ ���庯��
	bool b_MousePressed; //���콺 ���� ����ǥ��


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
