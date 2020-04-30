#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	int i;

	for(i=0;i<MAX_PUMP_DEFINE;i++)
	{
		Motor_Var[i] = 0;
	}

	ui->setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint|Qt::CustomizeWindowHint);
	this->setGeometry(0,0,800,480);

	nExitCnt = 0;

	iXdifferent=-1;
	iYdifferent=-1;
	b_MousePressed=false;

	ChangeStringList();

	int id = QFontDatabase::addApplicationFont(qApp->applicationDirPath()+"/Roboto-Bold.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);

	QFont SerifFont(family);
	this->setFont(SerifFont);

	ui->P1_ValMotor1->setFont(QFont("Roboto",24));
	ui->P1_ValMotor2->setFont(QFont("Roboto",24));
	ui->P1_ValMotor3->setFont(QFont("Roboto",24));
	ui->P1_ValBR1->setFont(QFont("Roboto",24));
	ui->P1_ValBR2->setFont(QFont("Roboto",24));

	ui->P1_ValRPM->setFont(QFont("Roboto",22));
	ui->P1_ValOpTime->setFont(QFont("Roboto",15));

	ui->P1_ValRCur->setFont(QFont("Roboto",24));
	ui->P1_ValSCur->setFont(QFont("Roboto",24));
	ui->P1_ValTCur->setFont(QFont("Roboto",24));

	ui->P1_ValMaxCur->setFont(QFont("Roboto",21));
	ui->P1_ValMinCur->setFont(QFont("Roboto",21));
	ui->P1_ValBP->setFont(QFont("Roboto",21));

	ui->P2_ValMotor1->setFont(QFont("Roboto",24));
	ui->P2_ValMotor2->setFont(QFont("Roboto",24));
	ui->P2_ValMotor3->setFont(QFont("Roboto",24));
	ui->P2_ValBR1->setFont(QFont("Roboto",24));
	ui->P2_ValBR2->setFont(QFont("Roboto",24));

	ui->P3_ValR->setFont(QFont("Roboto",24));
	ui->P3_ValS->setFont(QFont("Roboto",24));
	ui->P3_ValT->setFont(QFont("Roboto",24));
	ui->P3_ValBAL->setFont(QFont("Roboto",24));

	// label Ŭ�� ����
	//ui->label_204->installEventFilter(this);
	ui->P1_ValRPM->installEventFilter(this);



	if(Init_Serial()){
		Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
			//ui->comboBox->addItem(port.portName() + "  " + port.description());
			ui->comboBox->addItem(port.portName());
		}

		Select_Window(WIN_5);
	}
	else{
		Select_Window(WIN_1);
	}

	Init_Timer();

}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
   if(event->type() == QMouseEvent::MouseButtonPress)
   {
	}
	return QWidget::eventFilter(object,event);
}

void MainWindow::Init_Timer(void)
{
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timer_Update()));
	timer->start(DEFAULT_TIMER_TIME);
}

void MainWindow::mousePressEvent (QMouseEvent * event) {
	b_MousePressed = true;

	if(nNowWindow == WIN_4)
	{

	}
	else if(nNowWindow == WIN_5)
	{
		ScrollVar[0][0] = ui->P5_Set1_L->x();
		ScrollVar[0][1] = ui->P5_Set1_L->x() + ui->P5_Set1_L->width();
		ScrollVar[0][2] = ui->P5_Set1_L->y();
		ScrollVar[0][3] = ui->P5_Set1_L->y() + ui->P5_Set1_L->height();

		ScrollVar[1][0] = ui->P5_Set1_M->x();
		ScrollVar[1][1] = ui->P5_Set1_M->x() + ui->P5_Set1_M->width();
		ScrollVar[1][2] = ui->P5_Set1_M->y();
		ScrollVar[1][3] = ui->P5_Set1_M->y() + ui->P5_Set1_M->height();

		ScrollVar[2][0] = ui->P5_Set1_H->x();
		ScrollVar[2][1] = ui->P5_Set1_H->x() + ui->P5_Set1_H->width();
		ScrollVar[2][2] = ui->P5_Set1_H->y();
		ScrollVar[2][3] = ui->P5_Set1_H->y() + ui->P5_Set1_H->height();



		ScrollVar[3][0] = ui->P5_Set2_L->x();
		ScrollVar[3][1] = ui->P5_Set2_L->x() + ui->P5_Set2_L->width();
		ScrollVar[3][2] = ui->P5_Set2_L->y();
		ScrollVar[3][3] = ui->P5_Set2_L->y() + ui->P5_Set2_L->height();

		ScrollVar[4][0] = ui->P5_Set2_M->x();
		ScrollVar[4][1] = ui->P5_Set2_M->x() + ui->P5_Set2_M->width();
		ScrollVar[4][2] = ui->P5_Set2_M->y();
		ScrollVar[4][3] = ui->P5_Set2_M->y() + ui->P5_Set2_M->height();

		ScrollVar[5][0] = ui->P5_Set2_H->x();
		ScrollVar[5][1] = ui->P5_Set2_H->x() + ui->P5_Set2_H->width();
		ScrollVar[5][2] = ui->P5_Set2_H->y();
		ScrollVar[5][3] = ui->P5_Set2_H->y() + ui->P5_Set2_H->height();


		ScrollVar[6][0] = ui->P5_Set3_L->x();
		ScrollVar[6][1] = ui->P5_Set3_L->x() + ui->P5_Set3_L->width();
		ScrollVar[6][2] = ui->P5_Set3_L->y();
		ScrollVar[6][3] = ui->P5_Set3_L->y() + ui->P5_Set3_L->height();

		ScrollVar[7][0] = ui->P5_Set3_M->x();
		ScrollVar[7][1] = ui->P5_Set3_M->x() + ui->P5_Set3_M->width();
		ScrollVar[7][2] = ui->P5_Set3_M->y();
		ScrollVar[7][3] = ui->P5_Set3_M->y() + ui->P5_Set3_M->height();

		ScrollVar[8][0] = ui->P5_Set3_H->x();
		ScrollVar[8][1] = ui->P5_Set3_H->x() + ui->P5_Set3_H->width();
		ScrollVar[8][2] = ui->P5_Set3_H->y();
		ScrollVar[8][3] = ui->P5_Set3_H->y() + ui->P5_Set3_H->height();


		ScrollVar[9][0] = ui->P5_Set4_L->x();
		ScrollVar[9][1] = ui->P5_Set4_L->x() + ui->P5_Set4_L->width();
		ScrollVar[9][2] = ui->P5_Set4_L->y();
		ScrollVar[9][3] = ui->P5_Set4_L->y() + ui->P5_Set4_L->height();

		ScrollVar[10][0] = ui->P5_Set4_M->x();
		ScrollVar[10][1] = ui->P5_Set4_M->x() + ui->P5_Set4_M->width();
		ScrollVar[10][2] = ui->P5_Set4_M->y();
		ScrollVar[10][3] = ui->P5_Set4_M->y() + ui->P5_Set4_M->height();

		ScrollVar[11][0] = ui->P5_Set4_H->x();
		ScrollVar[11][1] = ui->P5_Set4_H->x() + ui->P5_Set4_H->width();
		ScrollVar[11][2] = ui->P5_Set4_H->y();
		ScrollVar[11][3] = ui->P5_Set4_H->y() + ui->P5_Set4_H->height();


		ScrollVar[12][0] = ui->P5_Set5_L->x();
		ScrollVar[12][1] = ui->P5_Set5_L->x() + ui->P5_Set5_L->width();
		ScrollVar[12][2] = ui->P5_Set5_L->y();
		ScrollVar[12][3] = ui->P5_Set5_L->y() + ui->P5_Set5_L->height();

		ScrollVar[13][0] = ui->P5_Set5_M->x();
		ScrollVar[13][1] = ui->P5_Set5_M->x() + ui->P5_Set5_M->width();
		ScrollVar[13][2] = ui->P5_Set5_M->y();
		ScrollVar[13][3] = ui->P5_Set5_M->y() + ui->P5_Set5_M->height();

		ScrollVar[14][0] = ui->P5_Set5_H->x();
		ScrollVar[14][1] = ui->P5_Set5_H->x() + ui->P5_Set5_H->width();
		ScrollVar[14][2] = ui->P5_Set5_H->y();
		ScrollVar[14][3] = ui->P5_Set5_H->y() + ui->P5_Set5_H->height();

	}
	else if(nNowWindow == WIN_6)
	{

		ScrollVar[0][0] = ui->P6_L1->x();
		ScrollVar[0][1] = ui->P6_L1->x() + ui->P6_L1->width();
		ScrollVar[0][2] = ui->P6_L1->y();
		ScrollVar[0][3] = ui->P6_L1->y() + ui->P6_L1->height();

		ScrollVar[1][0] = ui->P6_H1->x();
		ScrollVar[1][1] = ui->P6_H1->x() + ui->P6_H1->width();
		ScrollVar[1][2] = ui->P6_H1->y();
		ScrollVar[1][3] = ui->P6_H1->y() + ui->P6_H1->height();

		ScrollVar[2][0] = ui->P6_L2->x();
		ScrollVar[2][1] = ui->P6_L2->x() + ui->P6_L2->width();
		ScrollVar[2][2] = ui->P6_L2->y();
		ScrollVar[2][3] = ui->P6_L2->y() + ui->P6_L2->height();

		ScrollVar[3][0] = ui->P6_H2->x();
		ScrollVar[3][1] = ui->P6_H2->x() + ui->P6_H2->width();
		ScrollVar[3][2] = ui->P6_H2->y();
		ScrollVar[3][3] = ui->P6_H2->y() + ui->P6_H2->height();

		ScrollVar[4][0] = ui->P6_L3->x();
		ScrollVar[4][1] = ui->P6_L3->x() + ui->P6_L3->width();
		ScrollVar[4][2] = ui->P6_L3->y();
		ScrollVar[4][3] = ui->P6_L3->y() + ui->P6_L3->height();

		ScrollVar[5][0] = ui->P6_H3->x();
		ScrollVar[5][1] = ui->P6_H3->x() + ui->P6_H3->width();
		ScrollVar[5][2] = ui->P6_H3->y();
		ScrollVar[5][3] = ui->P6_H3->y() + ui->P6_H3->height();

		ScrollVar[6][0] = ui->P6_T1->x();
		ScrollVar[6][1] = ui->P6_T1->x() + ui->P6_T1->width();
		ScrollVar[6][2] = ui->P6_T1->y();
		ScrollVar[6][3] = ui->P6_T1->y() + ui->P6_T1->height();

		ScrollVar[7][0] = ui->P6_T2->x();
		ScrollVar[7][1] = ui->P6_T2->x() + ui->P6_T2->width();
		ScrollVar[7][2] = ui->P6_T2->y();
		ScrollVar[7][3] = ui->P6_T2->y() + ui->P6_T2->height();

		ScrollVar[8][0] = ui->P6_T3->x();
		ScrollVar[8][1] = ui->P6_T3->x() + ui->P6_T3->width();
		ScrollVar[8][2] = ui->P6_T3->y();
		ScrollVar[8][3] = ui->P6_T3->y() + ui->P6_T3->height();

		ScrollVar[9][0] = ui->P6_T4->x();
		ScrollVar[9][1] = ui->P6_T4->x() + ui->P6_T4->width();
		ScrollVar[9][2] = ui->P6_T4->y();
		ScrollVar[9][3] = ui->P6_T4->y() + ui->P6_T4->height();

		ScrollVar[10][0] = ui->P6_T5->x();
		ScrollVar[10][1] = ui->P6_T5->x() + ui->P6_T5->width();
		ScrollVar[10][2] = ui->P6_T5->y();
		ScrollVar[10][3] = ui->P6_T5->y() + ui->P6_T5->height();

	}
	else if(nNowWindow == WIN_7)
	{
		ScrollVar[0][0] = ui->P7_D1->x();
		ScrollVar[0][1] = ui->P7_D1->x() + ui->P7_D1->width();
		ScrollVar[0][2] = ui->P7_D1->y();
		ScrollVar[0][3] = ui->P7_D1->y() + ui->P7_D1->height();

		ScrollVar[1][0] = ui->P7_D2->x();
		ScrollVar[1][1] = ui->P7_D2->x() + ui->P7_D2->width();
		ScrollVar[1][2] = ui->P7_D2->y();
		ScrollVar[1][3] = ui->P7_D2->y() + ui->P7_D2->height();

		ScrollVar[2][0] = ui->P7_L1->x();
		ScrollVar[2][1] = ui->P7_L1->x() + ui->P7_L1->width();
		ScrollVar[2][2] = ui->P7_L1->y();
		ScrollVar[2][3] = ui->P7_L1->y() + ui->P7_L1->height();

		ScrollVar[3][0] = ui->P7_H1->x();
		ScrollVar[3][1] = ui->P7_H1->x() + ui->P7_H1->width();
		ScrollVar[3][2] = ui->P7_H1->y();
		ScrollVar[3][3] = ui->P7_H1->y() + ui->P7_H1->height();

	}

	QPoint qpMousePressedPoint = QCursor::pos();
	QPoint qpApploc = this->pos();
	iXdifferent = qpMousePressedPoint.x() - qpApploc.x();
	iYdifferent = qpMousePressedPoint.y() - qpApploc.y();
	QWidget::mousePressEvent(event);

}

void MainWindow::mouseReleaseEvent (QMouseEvent * event)
{
b_MousePressed = false;
QWidget::mouseReleaseEvent(event);

#if 0
// Click Test Code
QString mm;
mm.sprintf("%d, %d", iXdifferent, iYdifferent);
QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
#endif

switch(nNowWindow)
{
case WIN_1:
	TouchProcess_WIN1(iXdifferent,iYdifferent);
break;
case WIN_2:
	TouchProcess_WIN2(iXdifferent,iYdifferent);
break;
case WIN_3:
	TouchProcess_WIN3(iXdifferent,iYdifferent);
break;
case WIN_4:
	ui->frame_4->setHidden(false);
break;
case WIN_5:
	TouchProcess_WIN5(iXdifferent,iYdifferent);
break;
case WIN_6:
	TouchProcess_WIN6(iXdifferent,iYdifferent);
break;
case WIN_7:
	TouchProcess_WIN7(iXdifferent,iYdifferent);
break;
case WIN_8:
	TouchProcess_WIN8(iXdifferent,iYdifferent);
break;
case WIN_9:
	TouchProcess_WIN9(iXdifferent,iYdifferent);
break;
case WIN_10:
	TouchProcess_WIN10(iXdifferent,iYdifferent);
break;
case WIN_99:
	ui->frame_11->setHidden(false);
break;
}

}


void MainWindow::mouseMoveEvent ( QMouseEvent * event1 )
{

	if(b_MousePressed)
	{
		if(nNowWindow == WIN_4)
		{

		}
		else if(nNowWindow == WIN_5)
		{
			TouchMove_WIN5(iXdifferent,iYdifferent);
		}
		else if(nNowWindow == WIN_6)
		{
			TouchMove_WIN6(iXdifferent,iYdifferent);
		}
		else if(nNowWindow == WIN_7)
		{
			TouchMove_WIN7(iXdifferent,iYdifferent);
		}
	}
/*
	if(b_MousePressed)
{
QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) , (QCursor::pos().y() - iYdifferent) );
this->setProperty("pos", qpAppNewLoc);
}
QWidget::mouseMoveEvent(event);
*/
}


int MainWindow::Init_Serial(void)
{

	m_port = new QSerialPort(this);
	m_port->setPortName("COM6");
	m_port->setBaudRate(QSerialPort::Baud115200);
	m_port->setDataBits(QSerialPort::Data8);
	m_port->setParity(QSerialPort::NoParity);
	m_port->setStopBits(QSerialPort::OneStop);
	m_port->setFlowControl(QSerialPort::NoFlowControl);


	if (m_port->open(QSerialPort::ReadWrite))
	{
		m_rcv.clear();
		m_rcvIndex = CHK_START;
		m_rcvTimer.start();

		connect(m_port, &QSerialPort::readyRead, this, &MainWindow::on_readyRead);
		connect(m_port, &QSerialPort::errorOccurred, this, &MainWindow::breakCaught);
	}
	else
	{

		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", "Unable to connect to the radio.\n\nPlease check your connections\nand configuration and try again.");
		return 1;
	}

	return 0;
}

void MainWindow::breakCaught(void)
{

}

void MainWindow::on_readyRead(void)
{
	int i;
#if 0 // Test Code
	QString mm;

	m_rcv.append(m_port->readAll());
	//qDebug()<<"raw rxBtes"<<rxBytes;
	if(!m_rcv.contains("\r\n"))
	{
		return;
	}

	mm.sprintf("%s", m_rcv.data());
	QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	m_rcv.clear();
#endif

	if(m_rcvTimer.elapsed() > 200){
		// Receive Time is over 200ms
		m_rcvIndex = CHK_START;
	}
	m_rcvTimer.restart();

	m_rcv.append(m_port->readAll());

	for(i=0;i<m_rcv.size();i++){
		switch(m_rcvIndex)
		{
		case CHK_START:
			if(m_rcv.at(i) == DEF_STX){
				m_rcvIndex = CHK_HEADER;
			}
		break;
		case CHK_HEADER:
			i_rcvHeader = m_rcv.at(i);
			m_rcvIndex = CHK_LENGTH;
		break;
		case CHK_LENGTH:
			i_rcvCnt = 0;
			m_rcvData.clear();
			i_rcvDataCnt = m_rcv.at(i);
			m_rcvIndex = CHK_DATA;
		break;
		case CHK_DATA:
			i_rcvCnt++;
			m_rcvData.append(m_rcv.at(i));
			if(i_rcvCnt == i_rcvDataCnt){
				i_rcvCnt = 0;
				i_rcvCRC = 0;
				m_rcvIndex = CHK_CRC;
			}
		break;
		case CHK_CRC:
			i_rcvCnt++;
			i_rcvCRC = i_rcvCRC * 256;
			i_rcvCRC = i_rcvCRC + m_rcv.at(i);
			if(i_rcvCnt == 2){
				m_rcvIndex = CHK_END;
			}
		break;
		case CHK_END:
			m_rcvIndex = CHK_START;
			Display_UI_Value();
		break;
		}
	}
	m_rcv.clear();
}

void MainWindow::Display_UI_Value(void)
{
	int i, i_VarAddr;


	switch(i_rcvHeader){
	case 0x01:
		i_VarAddr = 0;
	break;
	case 0x02:
		i_VarAddr = 25;
	break;
	case 0x03:
		i_VarAddr = 50;
	break;
	case 0x04:
		i_VarAddr = 75;
	break;
	default:
		QMessageBox::critical(this, "Missmatch", "Commad not defined");
		return;
	}

	for(i=0;i<i_rcvDataCnt;i+=2){
		Motor_Var[(i/2) + i_VarAddr] = m_rcvData.at(i)*256 + m_rcvData.at(i+1);
	}
}


void MainWindow::Select_Window(WIN_VAR nSelWin)
{
	nNowWindow = nSelWin;

	ui->frame->setHidden(true);
	ui->frame_2->setHidden(true);
	ui->frame_3->setHidden(true);
	ui->frame_4->setHidden(true);
	ui->frame_5->setHidden(true);
	ui->frame_6->setHidden(true);
	ui->frame_7->setHidden(true);
	ui->frame_8->setHidden(true);
	ui->frame_9->setHidden(true);
	ui->frame_10->setHidden(true);
	ui->frame_11->setHidden(true);

	switch(nNowWindow)
	{
	case WIN_1:
		ChangeWindow_WIN1();
		ui->frame->setHidden(false);
	break;
	case WIN_2:
		ChangeWindow_WIN2();
		ui->frame_2->setHidden(false);
	break;
	case WIN_3:
		ChangeWindow_WIN3();
		ui->frame_3->setHidden(false);
	break;
	case WIN_4:
		ui->frame_4->setHidden(false);
	break;
	case WIN_5:
		ui->frame_5->setHidden(false);
	break;
	case WIN_6:
		ui->frame_6->setHidden(false);
	break;
	case WIN_7:
		ui->frame_7->setHidden(false);
	break;
	case WIN_8:
		ui->frame_8->setHidden(false);
	break;
	case WIN_9:
		ui->frame_9->setHidden(false);
	break;
	case WIN_10:
		ui->frame_10->setHidden(false);
	break;
	case WIN_99:
		ui->frame_11->setHidden(false);
	break;
	}
}

void MainWindow::on_CMD_SelUART_clicked()
{
	m_port = new QSerialPort(this);
	//m_port->setPortName(ui->comboBox->currentText().left(4));
	m_port->setPortName(ui->comboBox->currentText());
	m_port->setBaudRate(QSerialPort::Baud115200);
	m_port->setDataBits(QSerialPort::Data8);
	m_port->setParity(QSerialPort::NoParity);
	m_port->setStopBits(QSerialPort::OneStop);
	m_port->setFlowControl(QSerialPort::NoFlowControl);


	if (m_port->open(QSerialPort::ReadWrite))
	{
		m_rcv.clear();
		m_rcvIndex = CHK_START;
		m_rcvTimer.start();

		connect(m_port, &QSerialPort::readyRead, this, &MainWindow::on_readyRead);
		connect(m_port, &QSerialPort::errorOccurred, this, &MainWindow::breakCaught);

		Select_Window(WIN_1);
	}
	else
	{
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", "Unable to connect to the radio.\n\nPlease check your connections\nand configuration and try again.");
	}
}

void MainWindow::timer_Update(void)
{
	QString mm;
	count++;
	
	switch(nNowWindow)
	{
	case WIN_1:
		ChangeWindow_WIN1();
	break;
	case WIN_2:
		ChangeWindow_WIN2();
	break;
	case WIN_3:
		ChangeWindow_WIN3();
	break;
	case WIN_4:
	case WIN_5:
	case WIN_6:
	case WIN_7:
	case WIN_8:
	case WIN_9:
	case WIN_10:
	case WIN_99:
	break;
	}

	if(Motor_Var[PUMP_RUN] == SET_RUN)
	{	
		if(0/*DEFAULT_WINDOW_CHANGE_TIME < count*/)
		{
			count = 0;
			switch(nNowWindow)
			{
			case WIN_1:
				Select_Window(WIN_2);
			break;
			case WIN_2:
				Select_Window(WIN_3);
			break;
			case WIN_3:
				Select_Window(WIN_1);
			break;
			case WIN_4:
			case WIN_5:
			case WIN_6:
			case WIN_7:
			case WIN_8:
			case WIN_9:
			case WIN_10:
			case WIN_99:
			break;
			}
		}
	}
}

int MainWindow::TouchMatching(int val, int minimum, int maximum)
{
	if((val >= minimum) && (val <= maximum)) return 1;

	return 0;
}

void MainWindow::TouchProcess_WIN1(int x, int y)
{
#define P1_DEF_B1_X1	0
#define P1_DEF_B1_Y1	79
#define P1_DEF_B1_X2	73
#define P1_DEF_B1_Y2	155

#define P1_DEF_B2_X1	0
#define P1_DEF_B2_Y1	155
#define P1_DEF_B2_X2	73
#define P1_DEF_B2_Y2	228

#define P1_DEF_B3_X1	0
#define P1_DEF_B3_Y1	228
#define P1_DEF_B3_X2	73
#define P1_DEF_B3_Y2	303

#define P1_DEF_B4_X1	0
#define P1_DEF_B4_Y1	303
#define P1_DEF_B4_X2	73
#define P1_DEF_B4_Y2	378

#define P1_DEF_B5_X1	0
#define P1_DEF_B5_Y1	378
#define P1_DEF_B5_X2	73
#define P1_DEF_B5_Y2	440

#define P1_DEF_EXIT_X1	620
#define P1_DEF_EXIT_Y1	0
#define P1_DEF_EXIT_X2	800
#define P1_DEF_EXIT_Y2	59

#define P1_DEF_TEMPVIEW_X1	106
#define P1_DEF_TEMPVIEW_Y1	111
#define P1_DEF_TEMPVIEW_X2	(106+175)
#define P1_DEF_TEMPVIEW_Y2	(111+369)

#define P1_DEF_CURVIEW_X1	567
#define P1_DEF_CURVIEW_Y1	111
#define P1_DEF_CURVIEW_X2	(567+224)
#define P1_DEF_CURVIEW_Y2	(111+193)

	QString mm;
	char uc_temptemp[8] = {
        0x44,0x09,0x02,0x00,0x01,0x00,0x00,0x43
    };

	if(TouchMatching(x,P1_DEF_B1_X1,P1_DEF_B1_X2) && TouchMatching(y,P1_DEF_B1_Y1,P1_DEF_B1_Y2)){
		// �ڵ�����
		//mm.sprintf("Auto run");
		//QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
		if(Motor_Var[PUMP_RUN] == SET_RUN)
		{
			Motor_Var[PUMP_RUN] = SET_STOP;
	        uc_temptemp[3] = 0x01;
			uc_temptemp[4] = 0x01;

			m_send.clear();
			m_send.setRawData(uc_temptemp,8);

			m_port->write(m_send,m_send.size());
			m_port->waitForBytesWritten(1000);
		}
		else{
			Motor_Var[PUMP_RUN] = SET_RUN;
			uc_temptemp[3] = 0x00;
			uc_temptemp[4] = 0x00;

			m_send.clear();
			m_send.setRawData(uc_temptemp,8);

			m_port->write(m_send,m_send.size());
			m_port->waitForBytesWritten(1000);
		}
	}
	else if(TouchMatching(x,P1_DEF_B2_X1,P1_DEF_B2_X2) && TouchMatching(y,P1_DEF_B2_Y1,P1_DEF_B2_Y2)){
		// ��������
		mm.sprintf("Manual run");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P1_DEF_B3_X1,P1_DEF_B3_X2) && TouchMatching(y,P1_DEF_B3_Y1,P1_DEF_B3_Y2)){
		// ����ȭ��
		Select_Window(WIN_5);
	}
	else if(TouchMatching(x,P1_DEF_B4_X1,P1_DEF_B4_X2) && TouchMatching(y,P1_DEF_B4_Y1,P1_DEF_B4_Y2)){

		Select_Window(WIN_10);
	}
	else if(TouchMatching(x,P1_DEF_B5_X1,P1_DEF_B5_X2) && TouchMatching(y,P1_DEF_B5_Y1,P1_DEF_B5_Y2)){
		mm.sprintf("Init");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P1_DEF_B5_X1,P1_DEF_B5_X2) && TouchMatching(y,P1_DEF_B5_Y1,P1_DEF_B5_Y2)){
		mm.sprintf("Init");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P1_DEF_TEMPVIEW_X1,P1_DEF_TEMPVIEW_X2) && TouchMatching(y,P1_DEF_TEMPVIEW_Y1,P1_DEF_TEMPVIEW_Y2)){
		Select_Window(WIN_2);
	}
	else if(TouchMatching(x,P1_DEF_CURVIEW_X1,P1_DEF_CURVIEW_X2) && TouchMatching(y,P1_DEF_CURVIEW_Y1,P1_DEF_CURVIEW_Y2)){
		Select_Window(WIN_3);
	}
	else if(TouchMatching(x,P1_DEF_EXIT_X1,P1_DEF_EXIT_X2) && TouchMatching(y,P1_DEF_EXIT_Y1,P1_DEF_EXIT_Y2)){
		nExitCnt++;
		if(nExitCnt > 10) qApp->quit();
	}

}

void MainWindow::TouchProcess_WIN5(int x, int y)
{
#define P5_DEF_B1_X1	0
#define P5_DEF_B1_Y1	123
#define P5_DEF_B1_X2	100
#define P5_DEF_B1_Y2	153

#define P5_DEF_B2_X1	0
#define P5_DEF_B2_Y1	153
#define P5_DEF_B2_X2	100
#define P5_DEF_B2_Y2	183

#define P5_DEF_B3_X1	0
#define P5_DEF_B3_Y1	183
#define P5_DEF_B3_X2	100
#define P5_DEF_B3_Y2	213

#define P5_DEF_B4_X1	0
#define P5_DEF_B4_Y1	213
#define P5_DEF_B4_X2	100
#define P5_DEF_B4_Y2	243

#define P5_DEF_B5_X1	0
#define P5_DEF_B5_Y1	243
#define P5_DEF_B5_X2	100
#define P5_DEF_B5_Y2	273

#define P5_DEF_DEFAULT_X1	479
#define P5_DEF_DEFAULT_Y1	93
#define P5_DEF_DEFAULT_X2	623
#define P5_DEF_DEFAULT_Y2	118

#define P5_DEF_SAVE_X1	631
#define P5_DEF_SAVE_Y1	93
#define P5_DEF_SAVE_X2	706
#define P5_DEF_SAVE_Y2	118

#define P5_DEF_EXIT_X1	718
#define P5_DEF_EXIT_Y1	93
#define P5_DEF_EXIT_X2	790
#define P5_DEF_EXIT_Y2	118

	QString mm;
	if(TouchMatching(x,P5_DEF_B1_X1,P5_DEF_B1_X2) && TouchMatching(y,P5_DEF_B1_Y1,P5_DEF_B1_Y2)){
	}
	else if(TouchMatching(x,P5_DEF_B2_X1,P5_DEF_B2_X2) && TouchMatching(y,P5_DEF_B2_Y1,P5_DEF_B2_Y2)){
		Select_Window(WIN_6);
	}
	else if(TouchMatching(x,P5_DEF_B3_X1,P5_DEF_B3_X2) && TouchMatching(y,P5_DEF_B3_Y1,P5_DEF_B3_Y2)){
		Select_Window(WIN_7);
	}
	else if(TouchMatching(x,P5_DEF_B4_X1,P5_DEF_B4_X2) && TouchMatching(y,P5_DEF_B4_Y1,P5_DEF_B4_Y2)){
		Select_Window(WIN_8);
	}
	else if(TouchMatching(x,P5_DEF_B5_X1,P5_DEF_B5_X2) && TouchMatching(y,P5_DEF_B5_Y1,P5_DEF_B5_Y2)){
		Select_Window(WIN_9);
	}
	else if(TouchMatching(x,P5_DEF_DEFAULT_X1,P5_DEF_DEFAULT_X2) && TouchMatching(y,P5_DEF_DEFAULT_Y1,P5_DEF_DEFAULT_Y2)){
		mm.sprintf("Default");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P5_DEF_SAVE_X1,P5_DEF_SAVE_X2) && TouchMatching(y,P5_DEF_SAVE_Y1,P5_DEF_SAVE_Y2)){
		mm.sprintf("save");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P5_DEF_EXIT_X1,P5_DEF_EXIT_X2) && TouchMatching(y,P5_DEF_EXIT_Y1,P5_DEF_EXIT_Y2)){
		Select_Window(WIN_1);
	}

}

void MainWindow::TouchMove_WIN5(int orgX, int orgY)
{
	if(TouchMatching(orgX,ScrollVar[0][0],ScrollVar[0][1]) && TouchMatching(orgY,ScrollVar[0][2],ScrollVar[0][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) < 460 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) > ScrollVar[1][0]-(ui->P5_Set1_M->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] , ScrollVar[0][2] );
		ui->P5_Set1_L->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[1][0],ScrollVar[1][1]) && TouchMatching(orgY,ScrollVar[1][2],ScrollVar[1][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) < ScrollVar[0][1]-(ui->P5_Set1_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) > ScrollVar[2][0]-(ui->P5_Set1_H->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] , ScrollVar[1][2] );
		ui->P5_Set1_M->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[2][0],ScrollVar[2][1]) && TouchMatching(orgY,ScrollVar[2][2],ScrollVar[2][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) < ScrollVar[1][1]-(ui->P5_Set1_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) > 757 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] , ScrollVar[2][2] );
		ui->P5_Set1_H->setProperty("pos", qpAppNewLoc);
	}

	else if(TouchMatching(orgX,ScrollVar[3][0],ScrollVar[3][1]) && TouchMatching(orgY,ScrollVar[3][2],ScrollVar[3][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) < 460 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) > ScrollVar[4][0]-(ui->P5_Set2_M->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[3][0] , ScrollVar[3][2] );
		ui->P5_Set2_L->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[4][0],ScrollVar[4][1]) && TouchMatching(orgY,ScrollVar[4][2],ScrollVar[4][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[4][0]) < ScrollVar[3][1]-(ui->P5_Set2_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[4][0]) > ScrollVar[5][0]-(ui->P5_Set2_H->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[4][0] , ScrollVar[4][2] );
		ui->P5_Set2_M->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[5][0],ScrollVar[5][1]) && TouchMatching(orgY,ScrollVar[5][2],ScrollVar[5][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[5][0]) < ScrollVar[4][1]-(ui->P5_Set2_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[5][0]) > 757 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[5][0] , ScrollVar[5][2] );
		ui->P5_Set2_H->setProperty("pos", qpAppNewLoc);
	}


	else if(TouchMatching(orgX,ScrollVar[6][0],ScrollVar[6][1]) && TouchMatching(orgY,ScrollVar[6][2],ScrollVar[6][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[6][0]) < 460 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[6][0]) > ScrollVar[7][0]-(ui->P5_Set3_M->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[6][0] , ScrollVar[6][2] );
		ui->P5_Set3_L->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[7][0],ScrollVar[7][1]) && TouchMatching(orgY,ScrollVar[7][2],ScrollVar[7][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[7][0]) < ScrollVar[6][1]-(ui->P5_Set3_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[7][0]) > ScrollVar[8][0]-(ui->P5_Set3_H->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[7][0] , ScrollVar[7][2] );
		ui->P5_Set3_M->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[8][0],ScrollVar[8][1]) && TouchMatching(orgY,ScrollVar[8][2],ScrollVar[8][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[8][0]) < ScrollVar[7][1]-(ui->P5_Set3_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[8][0]) > 757 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[8][0] , ScrollVar[8][2] );
		ui->P5_Set3_H->setProperty("pos", qpAppNewLoc);
	}


	else if(TouchMatching(orgX,ScrollVar[9][0],ScrollVar[9][1]) && TouchMatching(orgY,ScrollVar[9][2],ScrollVar[9][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[9][0]) < 460 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[9][0]) > ScrollVar[10][0]-(ui->P5_Set4_M->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[9][0] , ScrollVar[9][2] );
		ui->P5_Set4_L->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[10][0],ScrollVar[10][1]) && TouchMatching(orgY,ScrollVar[10][2],ScrollVar[10][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[10][0]) < ScrollVar[9][1]-(ui->P5_Set4_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[10][0]) > ScrollVar[11][0]-(ui->P5_Set4_H->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[10][0] , ScrollVar[10][2] );
		ui->P5_Set4_M->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[11][0],ScrollVar[11][1]) && TouchMatching(orgY,ScrollVar[11][2],ScrollVar[11][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[11][0]) < ScrollVar[10][1]-(ui->P5_Set4_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[11][0]) > 757 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[11][0] , ScrollVar[11][2] );
		ui->P5_Set4_H->setProperty("pos", qpAppNewLoc);
	}


	else if(TouchMatching(orgX,ScrollVar[12][0],ScrollVar[12][1]) && TouchMatching(orgY,ScrollVar[12][2],ScrollVar[12][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[12][0]) < 460 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[12][0]) > ScrollVar[13][0]-(ui->P5_Set5_M->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[12][0] , ScrollVar[12][2] );
		ui->P5_Set5_L->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[13][0],ScrollVar[13][1]) && TouchMatching(orgY,ScrollVar[13][2],ScrollVar[13][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[13][0]) < ScrollVar[12][1]-(ui->P5_Set5_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[13][0]) > ScrollVar[14][0]-(ui->P5_Set5_H->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[13][0] , ScrollVar[13][2] );
		ui->P5_Set5_M->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[14][0],ScrollVar[14][1]) && TouchMatching(orgY,ScrollVar[14][2],ScrollVar[14][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[14][0]) < ScrollVar[13][1]-(ui->P5_Set5_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[14][0]) > 757 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[14][0] , ScrollVar[14][2] );
		ui->P5_Set5_H->setProperty("pos", qpAppNewLoc);
	}
}

void MainWindow::TouchProcess_WIN6(int x, int y)
{
#define P6_DEF_B1_X1	0
#define P6_DEF_B1_Y1	123
#define P6_DEF_B1_X2	100
#define P6_DEF_B1_Y2	153

#define P6_DEF_B2_X1	0
#define P6_DEF_B2_Y1	153
#define P6_DEF_B2_X2	100
#define P6_DEF_B2_Y2	183

#define P6_DEF_B3_X1	0
#define P6_DEF_B3_Y1	183
#define P6_DEF_B3_X2	100
#define P6_DEF_B3_Y2	213

#define P6_DEF_B4_X1	0
#define P6_DEF_B4_Y1	213
#define P6_DEF_B4_X2	100
#define P6_DEF_B4_Y2	243

#define P6_DEF_B5_X1	0
#define P6_DEF_B5_Y1	243
#define P6_DEF_B5_X2	100
#define P6_DEF_B5_Y2	273

#define P6_DEF_DEFAULT_X1	479
#define P6_DEF_DEFAULT_Y1	93
#define P6_DEF_DEFAULT_X2	623
#define P6_DEF_DEFAULT_Y2	118

#define P6_DEF_SAVE_X1	631
#define P6_DEF_SAVE_Y1	93
#define P6_DEF_SAVE_X2	706
#define P6_DEF_SAVE_Y2	118

#define P6_DEF_EXIT_X1	718
#define P6_DEF_EXIT_Y1	93
#define P6_DEF_EXIT_X2	790
#define P6_DEF_EXIT_Y2	118

	QString mm;
	if(TouchMatching(x,P6_DEF_B1_X1,P6_DEF_B1_X2) && TouchMatching(y,P6_DEF_B1_Y1,P6_DEF_B1_Y2)){
		Select_Window(WIN_5);
	}
	else if(TouchMatching(x,P6_DEF_B2_X1,P6_DEF_B2_X2) && TouchMatching(y,P6_DEF_B2_Y1,P6_DEF_B2_Y2)){
	}
	else if(TouchMatching(x,P6_DEF_B3_X1,P6_DEF_B3_X2) && TouchMatching(y,P6_DEF_B3_Y1,P6_DEF_B3_Y2)){
		Select_Window(WIN_7);
	}
	else if(TouchMatching(x,P6_DEF_B4_X1,P6_DEF_B4_X2) && TouchMatching(y,P6_DEF_B4_Y1,P6_DEF_B4_Y2)){
		Select_Window(WIN_8);
	}
	else if(TouchMatching(x,P6_DEF_B5_X1,P6_DEF_B5_X2) && TouchMatching(y,P6_DEF_B5_Y1,P6_DEF_B5_Y2)){
		Select_Window(WIN_9);
	}
	else if(TouchMatching(x,P6_DEF_DEFAULT_X1,P6_DEF_DEFAULT_X2) && TouchMatching(y,P6_DEF_DEFAULT_Y1,P6_DEF_DEFAULT_Y2)){
		mm.sprintf("Default");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P6_DEF_SAVE_X1,P6_DEF_SAVE_X2) && TouchMatching(y,P6_DEF_SAVE_Y1,P6_DEF_SAVE_Y2)){
		mm.sprintf("save");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P6_DEF_EXIT_X1,P6_DEF_EXIT_X2) && TouchMatching(y,P6_DEF_EXIT_Y1,P6_DEF_EXIT_Y2)){
		Select_Window(WIN_1);
	}

}


void MainWindow::TouchMove_WIN6(int orgX, int orgY)
{
	int nVal;
	QString mm;
	if(TouchMatching(orgX,ScrollVar[0][0],ScrollVar[0][1]) && TouchMatching(orgY,ScrollVar[0][2],ScrollVar[0][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) < 225 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) > ScrollVar[1][0]-(ui->P6_L1->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] , ScrollVar[0][2] );
		ui->P6_L1->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_L1->x() - 225;
		nVal = int((25*nVal/(375-225)));
		mm.sprintf("%d",nVal);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] + 2 , ScrollVar[0][2] - 15 );
		ui->P6_V1->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1->setText(mm);
	}
	else if(TouchMatching(orgX,ScrollVar[1][0],ScrollVar[1][1]) && TouchMatching(orgY,ScrollVar[1][2],ScrollVar[1][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) < ScrollVar[0][1]-(ui->P6_L1->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) > 375 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] , ScrollVar[1][2] );
		ui->P6_H1->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_H1->x() - 225;
		nVal = int((25*nVal/(375-225)));
		mm.sprintf("%d",nVal);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] + 2 , ScrollVar[1][2] - 15 );
		ui->P6_V1_2->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_2->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[2][0],ScrollVar[2][1]) && TouchMatching(orgY,ScrollVar[2][2],ScrollVar[2][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) < 225 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) > ScrollVar[3][0]-(ui->P6_L2->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] , ScrollVar[2][2] );
		ui->P6_L2->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_L2->x() - 225;
		nVal = int((25*nVal/(375-225)));
		mm.sprintf("%d",nVal);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] + 2 , ScrollVar[2][2] - 15 );
		ui->P6_V1_3->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_3->setText(mm);
	}
	else if(TouchMatching(orgX,ScrollVar[3][0],ScrollVar[3][1]) && TouchMatching(orgY,ScrollVar[3][2],ScrollVar[3][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) < ScrollVar[2][1]-(ui->P6_L2->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) > 375 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[3][0] , ScrollVar[3][2] );
		ui->P6_H2->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_H2->x() - 225;
		nVal = int((25*nVal/(375-225)));
		mm.sprintf("%d",nVal);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[3][0] + 2 , ScrollVar[3][2] - 15 );
		ui->P6_V1_4->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_4->setText(mm);
	}


	else if(TouchMatching(orgX,ScrollVar[4][0],ScrollVar[4][1]) && TouchMatching(orgY,ScrollVar[4][2],ScrollVar[4][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[4][0]) < 225 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[4][0]) > ScrollVar[5][0]-(ui->P6_L3->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[4][0] , ScrollVar[4][2] );
		ui->P6_L3->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_L3->x() - 225;
		nVal = int((25*nVal/(375-225)));
		mm.sprintf("%d",nVal);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[4][0] + 2 , ScrollVar[4][2] - 15 );
		ui->P6_V1_5->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_5->setText(mm);
	}
	else if(TouchMatching(orgX,ScrollVar[5][0],ScrollVar[5][1]) && TouchMatching(orgY,ScrollVar[5][2],ScrollVar[5][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[5][0]) < ScrollVar[4][1]-(ui->P6_L3->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[5][0]) > 375 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[5][0] , ScrollVar[5][2] );
		ui->P6_H3->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_H3->x() - 225;
		nVal = int((25*nVal/(375-225)));
		mm.sprintf("%d",nVal);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[5][0] + 2 , ScrollVar[5][2] - 15 );
		ui->P6_V1_6->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_6->setText(mm);
	}


	else if(TouchMatching(orgX,ScrollVar[6][0],ScrollVar[6][1]) && TouchMatching(orgY,ScrollVar[6][2],ScrollVar[6][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[6][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[6][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[6][0] , ScrollVar[6][2] );
		ui->P6_T1->setProperty("pos", qpAppNewLoc);
	}

	else if(TouchMatching(orgX,ScrollVar[7][0],ScrollVar[7][1]) && TouchMatching(orgY,ScrollVar[7][2],ScrollVar[7][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[7][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[7][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[7][0] , ScrollVar[7][2] );
		ui->P6_T2->setProperty("pos", qpAppNewLoc);
	}

	else if(TouchMatching(orgX,ScrollVar[8][0],ScrollVar[8][1]) && TouchMatching(orgY,ScrollVar[8][2],ScrollVar[8][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[8][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[8][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[8][0] , ScrollVar[8][2] );
		ui->P6_T3->setProperty("pos", qpAppNewLoc);
	}

	else if(TouchMatching(orgX,ScrollVar[9][0],ScrollVar[9][1]) && TouchMatching(orgY,ScrollVar[9][2],ScrollVar[9][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[9][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[9][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[9][0] , ScrollVar[9][2] );
		ui->P6_T4->setProperty("pos", qpAppNewLoc);
	}

	else if(TouchMatching(orgX,ScrollVar[10][0],ScrollVar[10][1]) && TouchMatching(orgY,ScrollVar[10][2],ScrollVar[10][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[10][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[10][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[10][0] , ScrollVar[10][2] );
		ui->P6_T5->setProperty("pos", qpAppNewLoc);
	}

}

void MainWindow::TouchProcess_WIN7(int x, int y)
{
#define P7_DEF_B1_X1	0
#define P7_DEF_B1_Y1	123
#define P7_DEF_B1_X2	100
#define P7_DEF_B1_Y2	153

#define P7_DEF_B2_X1	0
#define P7_DEF_B2_Y1	153
#define P7_DEF_B2_X2	100
#define P7_DEF_B2_Y2	183

#define P7_DEF_B3_X1	0
#define P7_DEF_B3_Y1	183
#define P7_DEF_B3_X2	100
#define P7_DEF_B3_Y2	213

#define P7_DEF_B4_X1	0
#define P7_DEF_B4_Y1	213
#define P7_DEF_B4_X2	100
#define P7_DEF_B4_Y2	243

#define P7_DEF_B5_X1	0
#define P7_DEF_B5_Y1	243
#define P7_DEF_B5_X2	100
#define P7_DEF_B5_Y2	273

#define P7_DEF_DEFAULT_X1	479
#define P7_DEF_DEFAULT_Y1	93
#define P7_DEF_DEFAULT_X2	623
#define P7_DEF_DEFAULT_Y2	118

#define P7_DEF_SAVE_X1	631
#define P7_DEF_SAVE_Y1	93
#define P7_DEF_SAVE_X2	706
#define P7_DEF_SAVE_Y2	118

#define P7_DEF_EXIT_X1	718
#define P7_DEF_EXIT_Y1	93
#define P7_DEF_EXIT_X2	790
#define P7_DEF_EXIT_Y2	118

	QString mm;
	if(TouchMatching(x,P7_DEF_B1_X1,P7_DEF_B1_X2) && TouchMatching(y,P7_DEF_B1_Y1,P7_DEF_B1_Y2)){
		Select_Window(WIN_5);
	}
	else if(TouchMatching(x,P7_DEF_B2_X1,P7_DEF_B2_X2) && TouchMatching(y,P7_DEF_B2_Y1,P7_DEF_B2_Y2)){
		Select_Window(WIN_6);
	}
	else if(TouchMatching(x,P7_DEF_B3_X1,P7_DEF_B3_X2) && TouchMatching(y,P7_DEF_B3_Y1,P7_DEF_B3_Y2)){
	}
	else if(TouchMatching(x,P7_DEF_B4_X1,P7_DEF_B4_X2) && TouchMatching(y,P7_DEF_B4_Y1,P7_DEF_B4_Y2)){
		Select_Window(WIN_8);
	}
	else if(TouchMatching(x,P7_DEF_B5_X1,P7_DEF_B5_X2) && TouchMatching(y,P7_DEF_B5_Y1,P7_DEF_B5_Y2)){
		Select_Window(WIN_9);
	}
	else if(TouchMatching(x,P7_DEF_DEFAULT_X1,P7_DEF_DEFAULT_X2) && TouchMatching(y,P7_DEF_DEFAULT_Y1,P7_DEF_DEFAULT_Y2)){
		mm.sprintf("Default");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P7_DEF_SAVE_X1,P7_DEF_SAVE_X2) && TouchMatching(y,P7_DEF_SAVE_Y1,P7_DEF_SAVE_Y2)){
		mm.sprintf("save");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P7_DEF_EXIT_X1,P7_DEF_EXIT_X2) && TouchMatching(y,P7_DEF_EXIT_Y1,P7_DEF_EXIT_Y2)){
		Select_Window(WIN_1);
	}

}

void MainWindow::TouchMove_WIN7(int orgX, int orgY)
{
	if(TouchMatching(orgX,ScrollVar[0][0],ScrollVar[0][1]) && TouchMatching(orgY,ScrollVar[0][2],ScrollVar[0][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) > 760 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] , ScrollVar[0][2] );
		ui->P7_D1->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[1][0],ScrollVar[1][1]) && TouchMatching(orgY,ScrollVar[1][2],ScrollVar[1][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) > 760 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] , ScrollVar[1][2] );
		ui->P7_D2->setProperty("pos", qpAppNewLoc);
	}

	else if(TouchMatching(orgX,ScrollVar[2][0],ScrollVar[2][1]) && TouchMatching(orgY,ScrollVar[2][2],ScrollVar[2][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) < 155 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) > ScrollVar[3][0]-(ui->P7_H1->width()/2+7) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] , ScrollVar[2][2] );
		ui->P7_L1->setProperty("pos", qpAppNewLoc);
	}
	else if(TouchMatching(orgX,ScrollVar[3][0],ScrollVar[3][1]) && TouchMatching(orgY,ScrollVar[3][2],ScrollVar[3][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) < ScrollVar[2][1]-(ui->P7_L1->width()/2-7) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) > 745 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[3][0] , ScrollVar[3][2] );
		ui->P7_H1->setProperty("pos", qpAppNewLoc);
	}

}

void MainWindow::TouchProcess_WIN8(int x, int y)
{
#define P8_DEF_B1_X1	0
#define P8_DEF_B1_Y1	123
#define P8_DEF_B1_X2	100
#define P8_DEF_B1_Y2	153

#define P8_DEF_B2_X1	0
#define P8_DEF_B2_Y1	153
#define P8_DEF_B2_X2	100
#define P8_DEF_B2_Y2	183

#define P8_DEF_B3_X1	0
#define P8_DEF_B3_Y1	183
#define P8_DEF_B3_X2	100
#define P8_DEF_B3_Y2	213

#define P8_DEF_B4_X1	0
#define P8_DEF_B4_Y1	213
#define P8_DEF_B4_X2	100
#define P8_DEF_B4_Y2	243

#define P8_DEF_B5_X1	0
#define P8_DEF_B5_Y1	243
#define P8_DEF_B5_X2	100
#define P8_DEF_B5_Y2	273

#define P8_DEF_DEFAULT_X1	479
#define P8_DEF_DEFAULT_Y1	93
#define P8_DEF_DEFAULT_X2	623
#define P8_DEF_DEFAULT_Y2	118

#define P8_DEF_SAVE_X1	631
#define P8_DEF_SAVE_Y1	93
#define P8_DEF_SAVE_X2	706
#define P8_DEF_SAVE_Y2	118

#define P8_DEF_EXIT_X1	718
#define P8_DEF_EXIT_Y1	93
#define P8_DEF_EXIT_X2	790
#define P8_DEF_EXIT_Y2	118

	QString mm;
	if(TouchMatching(x,P8_DEF_B1_X1,P8_DEF_B1_X2) && TouchMatching(y,P8_DEF_B1_Y1,P8_DEF_B1_Y2)){
		Select_Window(WIN_5);
	}
	else if(TouchMatching(x,P8_DEF_B2_X1,P8_DEF_B2_X2) && TouchMatching(y,P8_DEF_B2_Y1,P8_DEF_B2_Y2)){
		Select_Window(WIN_6);
	}
	else if(TouchMatching(x,P8_DEF_B3_X1,P8_DEF_B3_X2) && TouchMatching(y,P8_DEF_B3_Y1,P8_DEF_B3_Y2)){
		Select_Window(WIN_7);
	}
	else if(TouchMatching(x,P8_DEF_B4_X1,P8_DEF_B4_X2) && TouchMatching(y,P8_DEF_B4_Y1,P8_DEF_B4_Y2)){
	}
	else if(TouchMatching(x,P8_DEF_B5_X1,P8_DEF_B5_X2) && TouchMatching(y,P8_DEF_B5_Y1,P8_DEF_B5_Y2)){
		Select_Window(WIN_9);
	}
	else if(TouchMatching(x,P8_DEF_DEFAULT_X1,P8_DEF_DEFAULT_X2) && TouchMatching(y,P8_DEF_DEFAULT_Y1,P8_DEF_DEFAULT_Y2)){
		mm.sprintf("Default");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P8_DEF_SAVE_X1,P8_DEF_SAVE_X2) && TouchMatching(y,P8_DEF_SAVE_Y1,P8_DEF_SAVE_Y2)){
		mm.sprintf("save");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P8_DEF_EXIT_X1,P8_DEF_EXIT_X2) && TouchMatching(y,P8_DEF_EXIT_Y1,P8_DEF_EXIT_Y2)){
		Select_Window(WIN_1);
	}

}

void MainWindow::TouchProcess_WIN9(int x, int y)
{
#define P9_DEF_B1_X1	0
#define P9_DEF_B1_Y1	123
#define P9_DEF_B1_X2	100
#define P9_DEF_B1_Y2	153

#define P9_DEF_B2_X1	0
#define P9_DEF_B2_Y1	153
#define P9_DEF_B2_X2	100
#define P9_DEF_B2_Y2	183

#define P9_DEF_B3_X1	0
#define P9_DEF_B3_Y1	183
#define P9_DEF_B3_X2	100
#define P9_DEF_B3_Y2	213

#define P9_DEF_B4_X1	0
#define P9_DEF_B4_Y1	213
#define P9_DEF_B4_X2	100
#define P9_DEF_B4_Y2	243

#define P9_DEF_B5_X1	0
#define P9_DEF_B5_Y1	243
#define P9_DEF_B5_X2	100
#define P9_DEF_B5_Y2	273

#define P9_DEF_DEFAULT_X1	479
#define P9_DEF_DEFAULT_Y1	93
#define P9_DEF_DEFAULT_X2	623
#define P9_DEF_DEFAULT_Y2	118

#define P9_DEF_SAVE_X1	631
#define P9_DEF_SAVE_Y1	93
#define P9_DEF_SAVE_X2	706
#define P9_DEF_SAVE_Y2	118

#define P9_DEF_EXIT_X1	718
#define P9_DEF_EXIT_Y1	93
#define P9_DEF_EXIT_X2	790
#define P9_DEF_EXIT_Y2	118

	QString mm;
	if(TouchMatching(x,P9_DEF_B1_X1,P9_DEF_B1_X2) && TouchMatching(y,P9_DEF_B1_Y1,P9_DEF_B1_Y2)){
		Select_Window(WIN_5);
	}
	else if(TouchMatching(x,P9_DEF_B2_X1,P9_DEF_B2_X2) && TouchMatching(y,P9_DEF_B2_Y1,P9_DEF_B2_Y2)){
		Select_Window(WIN_6);
	}
	else if(TouchMatching(x,P9_DEF_B3_X1,P9_DEF_B3_X2) && TouchMatching(y,P9_DEF_B3_Y1,P9_DEF_B3_Y2)){
		Select_Window(WIN_7);
	}
	else if(TouchMatching(x,P9_DEF_B4_X1,P9_DEF_B4_X2) && TouchMatching(y,P9_DEF_B4_Y1,P9_DEF_B4_Y2)){
		Select_Window(WIN_8);
	}
	else if(TouchMatching(x,P9_DEF_B5_X1,P9_DEF_B5_X2) && TouchMatching(y,P9_DEF_B5_Y1,P9_DEF_B5_Y2)){
	}
	else if(TouchMatching(x,P9_DEF_DEFAULT_X1,P9_DEF_DEFAULT_X2) && TouchMatching(y,P9_DEF_DEFAULT_Y1,P9_DEF_DEFAULT_Y2)){
		mm.sprintf("Default");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P9_DEF_SAVE_X1,P9_DEF_SAVE_X2) && TouchMatching(y,P9_DEF_SAVE_Y1,P9_DEF_SAVE_Y2)){
		mm.sprintf("save");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P9_DEF_EXIT_X1,P9_DEF_EXIT_X2) && TouchMatching(y,P9_DEF_EXIT_Y1,P9_DEF_EXIT_Y2)){
		Select_Window(WIN_1);
	}

}

void MainWindow::TouchProcess_WIN10(int x, int y)
{
#define P10_DEF_B1_X1	0
#define P10_DEF_B1_Y1	87
#define P10_DEF_B1_X2	100
#define P10_DEF_B1_Y2	158

#define P10_DEF_B2_X1	0
#define P10_DEF_B2_Y1	162
#define P10_DEF_B2_X2	100
#define P10_DEF_B2_Y2	216

#define P10_DEF_B3_X1	0
#define P10_DEF_B3_Y1	221
#define P10_DEF_B3_X2	100
#define P10_DEF_B3_Y2	274


	QString mm;
	if(TouchMatching(x,P10_DEF_B1_X1,P10_DEF_B1_X2) && TouchMatching(y,P10_DEF_B1_Y1,P10_DEF_B1_Y2)){
		Select_Window(WIN_1);
	}
	else if(TouchMatching(x,P10_DEF_B2_X1,P10_DEF_B2_X2) && TouchMatching(y,P10_DEF_B2_Y1,P10_DEF_B2_Y2)){
		mm.sprintf("Prev page");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P10_DEF_B3_X1,P10_DEF_B3_X2) && TouchMatching(y,P10_DEF_B3_Y1,P10_DEF_B3_Y2)){
		mm.sprintf("Next page");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}

}

void MainWindow::TouchProcess_WIN2(int x, int y)
{
#define P2_DEF_B1_X1	0
#define P2_DEF_B1_Y1	87
#define P2_DEF_B1_X2	100
#define P2_DEF_B1_Y2	150

	if(TouchMatching(x,P2_DEF_B1_X1,P2_DEF_B1_X2) && TouchMatching(y,P2_DEF_B1_Y1,P2_DEF_B1_Y2)){
		Select_Window(WIN_1);
	}

}

void MainWindow::TouchProcess_WIN3(int x, int y)
{
#define P3_DEF_B1_X1	0
#define P3_DEF_B1_Y1	87
#define P3_DEF_B1_X2	100
#define P3_DEF_B1_Y2	150

	if(TouchMatching(x,P3_DEF_B1_X1,P3_DEF_B1_X2) && TouchMatching(y,P3_DEF_B1_Y1,P3_DEF_B1_Y2)){
		Select_Window(WIN_1);
	}

}

void MainWindow::ChangeWindow_WIN1(void)
{
	QString m;


	if(Motor_Var[PUMP_M1T] >= ERROR_TEMP_VAL) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M1T] >= WARNING_TEMP_VAL) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
	else ui->P1_ValMotor1->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M2T] >= ERROR_TEMP_VAL) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M2T] >= WARNING_TEMP_VAL) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
	else ui->P1_ValMotor2->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M3T] >= ERROR_TEMP_VAL) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M3T] >= WARNING_TEMP_VAL) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
	else ui->P1_ValMotor3->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M4T] >= ERROR_TEMP_VAL) ui->P1_ValBR1->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M4T] >= WARNING_TEMP_VAL) ui->P1_ValBR1->setStyleSheet("color:rgb(255,242,0)");
	else ui->P1_ValBR1->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M5T] >= ERROR_TEMP_VAL) ui->P1_ValBR2->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M5T] >= WARNING_TEMP_VAL) ui->P1_ValBR2->setStyleSheet("color:rgb(255,242,0)");
	else ui->P1_ValBR2->setStyleSheet("color:rgb(255,255,255)");


	if(Motor_Var[PUMP_M1C] >= ERROR_TEMP_VAL) ui->P1_ValRCur->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M1C] >= WARNING_TEMP_VAL) ui->P1_ValRCur->setStyleSheet("color:rgb(255,242,0)");
	else ui->P1_ValRCur->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M2C] >= ERROR_TEMP_VAL) ui->P1_ValSCur->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M2C] >= WARNING_TEMP_VAL) ui->P1_ValSCur->setStyleSheet("color:rgb(255,242,0)");
	else ui->P1_ValSCur->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M3C] >= ERROR_TEMP_VAL) ui->P1_ValTCur->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M3C] >= WARNING_TEMP_VAL) ui->P1_ValTCur->setStyleSheet("color:rgb(255,242,0)");
	else ui->P1_ValTCur->setStyleSheet("color:rgb(255,255,255)");

	m.sprintf("%d",Motor_Var[PUMP_M1T]);
    ui->P1_ValMotor1->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M2T]);
    ui->P1_ValMotor2->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M3T]);
    ui->P1_ValMotor3->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M4T]);
    ui->P1_ValBR1->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M5T]);
    ui->P1_ValBR2->setText(m);

    m.sprintf("%d",Motor_Var[PUMP_RPM]);
    ui->P1_ValRPM->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_RUNT]);
	ui->P1_ValOpTime->setText(m);

	m.sprintf("%d.%d",Motor_Var[PUMP_M1C]/10,Motor_Var[PUMP_M1C]%10);
    ui->P1_ValRCur->setText(m);
	m.sprintf("%d.%d",Motor_Var[PUMP_M2C]/10,Motor_Var[PUMP_M2C]%10);
    ui->P1_ValSCur->setText(m);
	m.sprintf("%d.%d",Motor_Var[PUMP_M3C]/10,Motor_Var[PUMP_M3C]%10);
    ui->P1_ValTCur->setText(m);

	m.sprintf("%d.%d",Motor_Var[PUMP_OC]/10,Motor_Var[PUMP_OC]%10);
    ui->P1_ValMaxCur->setText(m);
	m.sprintf("%d.%d",Motor_Var[PUMP_UC]/10,Motor_Var[PUMP_UC]%10);
    ui->P1_ValMinCur->setText(m);
	m.sprintf("%d.%d%d",Motor_Var[PUMP_UB]/100,(Motor_Var[PUMP_UB]%100)/10,Motor_Var[PUMP_UB]%10);
    ui->P1_ValBP->setText(m);



	QPixmap qp;
	int nTempValue;

	if(P1_RPM1_STRList.size() < 7){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_RPM] < MIN_RPM_VALUE){
		qp = QPixmap(P1_RPM1_STRList[0]);
	}
	else if(Motor_Var[PUMP_RPM] > MAX_RPM_VALUE){
		qp = QPixmap(P1_RPM1_STRList[6]);
	}
	else{
		nTempValue = int((((Motor_Var[PUMP_RPM] - MIN_RPM_VALUE)*100)/(MAX_RPM_VALUE-MIN_RPM_VALUE))/14.3);

		qp = QPixmap(P1_RPM1_STRList[nTempValue]);
	}
	ui->P1_RPM1->setPixmap(qp);


	if(P1_RPM2_STRList.size() < 16){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_RUN] == SET_RUN){
		mRPMIndex = (mRPMIndex+1)%16;


		qp = QPixmap(P1_RPM2_STRList[mRPMIndex]);
		ui->P1_RPM2->setPixmap(qp);
	}


	if(P1_MotorDir_STRList.size() < 2){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_DIR] == SET_CCW){
		qp = QPixmap(P1_MotorDir_STRList[1]);
	}
	else{
		qp = QPixmap(P1_MotorDir_STRList[0]);
	}
	ui->P1_MotorDir->setPixmap(qp);


	if(P1_WaterLevel_STRList.size() < 5){
		qApp->quit();
		return;
	}
	switch(Motor_Var[PUMP_WL]){
	case SET_LO:	qp = QPixmap(P1_WaterLevel_STRList[0]); break;
	case SET_LL:	qp = QPixmap(P1_WaterLevel_STRList[1]); break;
	case SET_L:		qp = QPixmap(P1_WaterLevel_STRList[2]); break;
	case SET_H:		qp = QPixmap(P1_WaterLevel_STRList[3]); break;
	case SET_HH:	qp = QPixmap(P1_WaterLevel_STRList[4]); break;
	}
	ui->P1_WaterLevel->setPixmap(qp);


	if(P1_MotorSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_FM] == SET_NORMAL){
		qp = QPixmap(P1_MotorSafe_STRList[0]);
	}
	else{
		qp = QPixmap(P1_MotorSafe_STRList[1]);
	}
	ui->P1_MotorSafe->setPixmap(qp);


	if(P1_OilSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_FO] == SET_NORMAL){
		qp = QPixmap(P1_OilSafe_STRList[0]);
	}
	else{
		qp = QPixmap(P1_OilSafe_STRList[1]);
	}
	ui->P1_OilSafe->setPixmap(qp);


	if(P1_ControlSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_FC] == SET_NORMAL){
		qp = QPixmap(P1_ControlSafe_STRList[0]);
	}
	else{
		qp = QPixmap(P1_ControlSafe_STRList[1]);
	}
	ui->P1_ControlSafe->setPixmap(qp);


	if(P1_AutoSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_ATYPE] != SET_RUNTYPE3){
		qp = QPixmap(P1_AutoSafe_STRList[1]);
	}
	else{
		qp = QPixmap(P1_AutoSafe_STRList[0]);
	}
	ui->P1_AutoSafe->setPixmap(qp);


	if(P1_SafeMecha_STRList.size() < 2){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_CHK_MECHA] == SET_NORMAL){
		qp = QPixmap(P1_SafeMecha_STRList[0]);
	}
	else{
		qp = QPixmap(P1_SafeMecha_STRList[1]);
	}
	ui->P1_SafeMecha->setPixmap(qp);


	if(P1_BRSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_CHK_BEARING] == SET_NORMAL){
		qp = QPixmap(P1_BRSafe_STRList[0]);
	}
	else{
		qp = QPixmap(P1_BRSafe_STRList[1]);
	}
	ui->P1_BRSafe->setPixmap(qp);


	if(P1_OilSafe_2_STRList.size() < 2){
		qApp->quit();
		return;
	}
	if(Motor_Var[PUMP_CHK_OIL] == SET_NORMAL){
		qp = QPixmap(P1_OilSafe_2_STRList[0]);
	}
	else{
		qp = QPixmap(P1_OilSafe_2_STRList[1]);
	}
	ui->P1_OilSafe_2->setPixmap(qp);

	// change scale.. temp 0 - 200 => range 0 - 144
	P1_M1Val = int(((Motor_Var[PUMP_M1T]*144)/MAX_TEMP_VAL));
	P1_M2Val = int(((Motor_Var[PUMP_M2T]*144)/MAX_TEMP_VAL));
	P1_M3Val = int(((Motor_Var[PUMP_M3T]*144)/MAX_TEMP_VAL));
	P1_M4Val = int(((Motor_Var[PUMP_M4T]*144)/MAX_TEMP_VAL));
	P1_M5Val = int(((Motor_Var[PUMP_M5T]*144)/MAX_TEMP_VAL));

	// range 0 - 100
	P1_RCVal = int(((Motor_Var[PUMP_M1C]*100)/MAX_CURRENT_VAL));
	P1_SCVal = int(((Motor_Var[PUMP_M2C]*100)/MAX_CURRENT_VAL));
	P1_TCVal = int(((Motor_Var[PUMP_M3C]*100)/MAX_CURRENT_VAL));

	ui->P1_Motor1->setStyleSheet("background:rgb(34,241,188)");
	ui->P1_Motor1->setFixedWidth(P1_M1Val);
	ui->P1_Motor1_2->move(100+P1_M1Val,165);

	ui->P1_Motor2->setStyleSheet("background:rgb(255,167,92)");
	ui->P1_Motor2->setFixedWidth(P1_M2Val);
	ui->P1_Motor2_2->move(100+P1_M2Val,233);

	ui->P1_Motor3->setStyleSheet("background:rgb(255,221,134)");
	ui->P1_Motor3->setFixedWidth(P1_M3Val);
	ui->P1_Motor3_2->move(100+P1_M3Val,300);

	ui->P1_Motor4->setStyleSheet("background:rgb(255,168,93)");
	ui->P1_Motor4->setFixedWidth(P1_M4Val);
	ui->P1_Motor4_2->move(100+P1_M4Val,366);

	ui->P1_Motor5->setStyleSheet("background:rgb(90,126,223)");
	ui->P1_Motor5->setFixedWidth(P1_M5Val);
	ui->P1_Motor5_2->move(100+P1_M5Val,433);

	ui->P1_RCurrent->setStyleSheet("background:rgb(34,241,188)");
	ui->P1_RCurrent->setFixedWidth(P1_RCVal);
	ui->P1_RCurrent_2->move(585+P1_RCVal,157);

	ui->P1_SCurrent->setStyleSheet("background:rgb(255,167,92)");
	ui->P1_SCurrent->setFixedWidth(P1_SCVal);
	ui->P1_SCurrent_2->move(585+P1_SCVal,211);

	ui->P1_TCurrent->setStyleSheet("background:rgb(255,221,134)");
	ui->P1_TCurrent->setFixedWidth(P1_TCVal);
	ui->P1_TCurrent_2->move(585+P1_TCVal,266);

}

void MainWindow::ChangeWindow_WIN2(void)
{
	QString m;

	if(Motor_Var[PUMP_M1T] >= ERROR_TEMP_VAL) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M1T] >= WARNING_TEMP_VAL) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
	else ui->P2_ValMotor1->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M2T] >= ERROR_TEMP_VAL) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M2T] >= WARNING_TEMP_VAL) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
	else ui->P2_ValMotor2->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M3T] >= ERROR_TEMP_VAL) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M3T] >= WARNING_TEMP_VAL) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
	else ui->P2_ValMotor3->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M4T] >= ERROR_TEMP_VAL) ui->P2_ValBR1->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M4T] >= WARNING_TEMP_VAL) ui->P2_ValBR1->setStyleSheet("color:rgb(255,242,0)");
	else ui->P2_ValBR1->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M5T] >= ERROR_TEMP_VAL) ui->P2_ValBR2->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M5T] >= WARNING_TEMP_VAL) ui->P2_ValBR2->setStyleSheet("color:rgb(255,242,0)");
	else ui->P2_ValBR2->setStyleSheet("color:rgb(255,255,255)");


    m.sprintf("%d",Motor_Var[PUMP_M1T]);
    ui->P2_ValMotor1->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M2T]);
    ui->P2_ValMotor2->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M3T]);
    ui->P2_ValMotor3->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M4T]);
    ui->P2_ValBR1->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M5T]);
    ui->P2_ValBR2->setText(m);


	// change scale.. temp 0 - 200 => range 0 - 144
	P1_M1Val = int(((Motor_Var[PUMP_M1T]*144)/MAX_TEMP_VAL));
	P1_M2Val = int(((Motor_Var[PUMP_M2T]*144)/MAX_TEMP_VAL));
	P1_M3Val = int(((Motor_Var[PUMP_M3T]*144)/MAX_TEMP_VAL));
	P1_M4Val = int(((Motor_Var[PUMP_M4T]*144)/MAX_TEMP_VAL));
	P1_M5Val = int(((Motor_Var[PUMP_M5T]*144)/MAX_TEMP_VAL));

	ui->P2_Motor1->setStyleSheet("background:rgb(34,241,188)");
	ui->P2_Motor1->setFixedWidth(P1_M1Val);
	ui->P2_Motor1_2->move(100+P1_M1Val,165);

	ui->P2_Motor2->setStyleSheet("background:rgb(255,167,92)");
	ui->P2_Motor2->setFixedWidth(P1_M2Val);
	ui->P2_Motor2_2->move(100+P1_M2Val,231);

	ui->P2_Motor3->setStyleSheet("background:rgb(255,221,134)");
	ui->P2_Motor3->setFixedWidth(P1_M3Val);
	ui->P2_Motor3_2->move(100+P1_M3Val,298);

	ui->P2_Motor4->setStyleSheet("background:rgb(255,168,93)");
	ui->P2_Motor4->setFixedWidth(P1_M4Val);
	ui->P2_Motor4_2->move(100+P1_M4Val,364);

	ui->P2_Motor5->setStyleSheet("background:rgb(90,126,223)");
	ui->P2_Motor5->setFixedWidth(P1_M5Val);
	ui->P2_Motor5_2->move(100+P1_M5Val,431);


}

void MainWindow::ChangeWindow_WIN3(void)
{
	QString m;



	if(Motor_Var[PUMP_M1C] >= ERROR_TEMP_VAL) ui->P3_ValR->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M1C] >= WARNING_TEMP_VAL) ui->P3_ValR->setStyleSheet("color:rgb(255,242,0)");
	else ui->P3_ValR->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M2C] >= ERROR_TEMP_VAL) ui->P3_ValS->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M2C] >= WARNING_TEMP_VAL) ui->P3_ValS->setStyleSheet("color:rgb(255,242,0)");
	else ui->P3_ValS->setStyleSheet("color:rgb(255,255,255)");

	if(Motor_Var[PUMP_M3C] >= ERROR_TEMP_VAL) ui->P3_ValT->setStyleSheet("color:rgb(255,0,0)");
	else if(Motor_Var[PUMP_M3C] >= WARNING_TEMP_VAL) ui->P3_ValT->setStyleSheet("color:rgb(255,242,0)");
	else ui->P3_ValT->setStyleSheet("color:rgb(255,255,255)");

    m.sprintf("%d",Motor_Var[PUMP_M1C]);
    ui->P3_ValR->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M2C]);
    ui->P3_ValS->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_M3C]);
    ui->P3_ValT->setText(m);
    m.sprintf("%d",Motor_Var[PUMP_UB]);
    ui->P3_ValBAL->setText(m);
}


void MainWindow::ChangeStringList(void)
{
	P1_RPM1_STRList = P1_RPM1_STR.split(",");
	P1_RPM2_STRList = P1_RPM2_STR.split(",");
	P1_MotorDir_STRList = P1_MotorDir_STR.split(",");
	P1_WaterLevel_STRList = P1_WaterLevel_STR.split(",");
	P1_MotorSafe_STRList = P1_MotorSafe_STR.split(",");
	P1_OilSafe_STRList = P1_OilSafe_STR.split(",");
	P1_ControlSafe_STRList = P1_ControlSafe_STR.split(",");
	P1_AutoSafe_STRList = P1_AutoSafe_STR.split(",");
	P1_SafeMecha_STRList = P1_SafeMecha_STR.split(",");
	P1_BRSafe_STRList = P1_BRSafe_STR.split(",");
	P1_OilSafe_2_STRList = P1_OilSafe_2_STR.split(",");
	P1_RPM1_STRCnt	=	 P1_RPM1_STRList.size();
	P1_RPM2_STRCnt	=	 P1_RPM2_STRList.size();
	P1_MotorDir_STRCnt	=	 P1_MotorDir_STRList.size();
	P1_WaterLevel_STRCnt	=	 P1_WaterLevel_STRList.size();
	P1_MotorSafe_STRCnt	=	 P1_MotorSafe_STRList.size();
	P1_OilSafe_STRCnt	=	 P1_OilSafe_STRList.size();
	P1_ControlSafe_STRCnt	=	 P1_ControlSafe_STRList.size();
	P1_AutoSafe_STRCnt	=	 P1_AutoSafe_STRList.size();
	P1_SafeMecha_STRCnt	=	 P1_SafeMecha_STRList.size();
	P1_BRSafe_STRCnt	=	 P1_BRSafe_STRList.size();
	P1_OilSafe_2_STRCnt	=	 P1_OilSafe_2_STRList.size();

	if(P1_RPM1_STRList.size() < 7){
		qApp->quit();
		return;
	}

	if(P1_RPM2_STRList.size() < 16){
		qApp->quit();
		return;
	}

	if(P1_MotorDir_STRList.size() < 3){
		qApp->quit();
		return;
	}

	if(P1_WaterLevel_STRList.size() < 2){
		qApp->quit();
		return;
	}

	if(P1_MotorSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}

	if(P1_OilSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}

	if(P1_ControlSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}

	if(P1_AutoSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}

	if(P1_SafeMecha_STRList.size() < 2){
		qApp->quit();
		return;
	}

	if(P1_BRSafe_STRList.size() < 2){
		qApp->quit();
		return;
	}

	if(P1_OilSafe_2_STRList.size() < 2){
		qApp->quit();
		return;
	}


}
