#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qstring.h>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	int i;


	for(i=0;i<MAX_PUMP_DEFINE;i++)
	{
		Motor_Var[i] = 0;//100;
	}
	for(i=0;i<MAX_SET_DEFINE;i++)
	{
		Setting_Var[i] = 0;
	}
	//Motor_Var[PUMP_RPM] = 1500;

	for(i=0;i<10;i++){
		historyTemp[0][i] = 0;
		historyTemp[1][i] = 0;
		historyTemp[2][i] = 0;
		historyTemp[3][i] = 0;
		historyTemp[4][i] = 0;
		
		historyCurrent[0][i] = 0;
		historyCurrent[1][i] = 0;
		historyCurrent[2][i] = 0;
		historyCurrent[3][i] = 0;
		historyCurrent[4][i] = 0;
	}


	rdFile = "";
	file.setFileName("ErrorList.txt");
	file.open(QFile::ReadOnly);//QIODevice::ReadWrite | QIODevice::Append | QFile::read);
	QTextStream stream(&file);
	while (!stream.atEnd()) { 
		rdFile.append(stream.readLine());
		rdFile.append("\r\n");
		P10_LineCnt = P10_LineCnt + 1;
	} 
	file.close();
	file.open(QFile::WriteOnly | QFile::Append );//QIODevice::ReadWrite | QIODevice::Append | QFile::read);

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


	ui->P1_LABEL1->setFont(QFont("Roboto",15));
	ui->P1_LABEL2->setFont(QFont("Roboto",15));
	ui->P2_LABEL1->setFont(QFont("Roboto",15));
	ui->P2_LABEL2->setFont(QFont("Roboto",15));
	ui->P3_LABEL1->setFont(QFont("Roboto",15));
	ui->P3_LABEL2->setFont(QFont("Roboto",15));
	ui->P4_LABEL1->setFont(QFont("Roboto",15));
	ui->P4_LABEL2->setFont(QFont("Roboto",15));
	ui->P5_LABEL1->setFont(QFont("Roboto",15));
	ui->P5_LABEL2->setFont(QFont("Roboto",15));
	ui->P6_LABEL1->setFont(QFont("Roboto",15));
	ui->P6_LABEL2->setFont(QFont("Roboto",15));
	ui->P7_LABEL1->setFont(QFont("Roboto",15));
	ui->P7_LABEL2->setFont(QFont("Roboto",15));
	ui->P8_LABEL1->setFont(QFont("Roboto",15));
	ui->P8_LABEL2->setFont(QFont("Roboto",15));
	ui->P9_LABEL1->setFont(QFont("Roboto",15));
	ui->P9_LABEL2->setFont(QFont("Roboto",15));
	ui->P10_LABEL1->setFont(QFont("Roboto",15));
	ui->P10_LABEL2->setFont(QFont("Roboto",15));


	i_BlinkTime = 0;


	//ui->label_204->installEventFilter(this);
	ui->P1_ValRPM->installEventFilter(this);

	SettingVar_Init();


	if(Init_Serial()){
		Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
			//ui->comboBox->addItem(port.portName() + "  " + port.description());
			ui->comboBox->addItem(port.portName());
		}

		Select_Window(WIN_99);
		//Select_Window(WIN_1);
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

void MainWindow::SettingVar_Init()
{
	Setting_Var[S_P5_V6]=1;
	Setting_Var[S_P5_V7]=100;
	Setting_Var[S_P5_V8]=200;
	Setting_Var[S_P5_V9]=1;
	Setting_Var[S_P5_V10]=100;
	Setting_Var[S_P5_V11]=200;
	Setting_Var[S_P5_V12]=1;
	Setting_Var[S_P5_V13]=100;
	Setting_Var[S_P5_V14]=200;
	Setting_Var[S_P5_V15]=1;
	Setting_Var[S_P5_V16]=100;
	Setting_Var[S_P5_V17]=200;
	Setting_Var[S_P5_V18]=1;
	Setting_Var[S_P5_V19]=100;
	Setting_Var[S_P5_V20]=200;

	Setting_Var[S_P6_V1]=1;
	Setting_Var[S_P6_V2]=25;
	Setting_Var[S_P6_V3]=25;
	Setting_Var[S_P6_V4]=1;
	Setting_Var[S_P6_V5]=1;
	Setting_Var[S_P6_V6]=25;

	Setting_Var[S_P6_V7]=0;
	Setting_Var[S_P6_V8]=0;
	Setting_Var[S_P6_V9]=0;
	Setting_Var[S_P6_V10]=0;
	Setting_Var[S_P6_V11]=0;

	Setting_Var[S_P7_V1]=0;
	Setting_Var[S_P7_V2]=1;
	Setting_Var[S_P7_V3]=1;
	Setting_Var[S_P7_V4]=3600;
	Setting_Var[S_P7_V5]=1;

	for(int i=S_P8_V1;i<=S_P8_V26;i++){
		Setting_Var[i] = 0;
	}

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
		ScrollVar[0][0] = ui->P4_Set1->x();
		ScrollVar[0][1] = ui->P4_Set1->x() + ui->P4_Set1->width();
		ScrollVar[0][2] = ui->P4_Set1->y();
		ScrollVar[0][3] = ui->P4_Set1->y() + ui->P4_Set1->height();
		
		ScrollVar[1][0] = ui->P4_Set2->x();
		ScrollVar[1][1] = ui->P4_Set2->x() + ui->P4_Set2->width();
		ScrollVar[1][2] = ui->P4_Set2->y();
		ScrollVar[1][3] = ui->P4_Set2->y() + ui->P4_Set2->height();

		ScrollVar[2][0] = ui->P4_Set3->x();
		ScrollVar[2][1] = ui->P4_Set3->x() + ui->P4_Set3->width();
		ScrollVar[2][2] = ui->P4_Set3->y();
		ScrollVar[2][3] = ui->P4_Set3->y() + ui->P4_Set3->height();

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

		ScrollVar[2][0] = ui->P7_H1->x();
		ScrollVar[2][1] = ui->P7_H1->x() + ui->P7_H1->width();
		ScrollVar[2][2] = ui->P7_H1->y();
		ScrollVar[2][3] = ui->P7_H1->y() + ui->P7_H1->height();

		ScrollVar[3][0] = ui->P7_L1->x();
		ScrollVar[3][1] = ui->P7_L1->x() + ui->P7_L1->width();
		ScrollVar[3][2] = ui->P7_L1->y();
		ScrollVar[3][3] = ui->P7_L1->y() + ui->P7_L1->height();

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
	TouchProcess_WIN4(iXdifferent,iYdifferent);
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
			TouchMove_WIN4(iXdifferent,iYdifferent);
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

int MainWindow::Check_Range(int nLeft, int nValue, int nRight)
{
	int ret;

	ret = 0;
	if (nValue >= nLeft)		ret = 1;
	else if(nValue <= nRight)	ret = 1;
	else ret = 0;

	return ret; 
}

void MainWindow::Display_UI_Value(void)
{
	int i, i_VarAddr;
	int nLeftVal,valueCheck,nRightVal;
	QString mm;


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
	case 0x35:
		i_VarAddr = 0;
		for(i=0;i<i_rcvDataCnt;i+=2){
			valueCheck = m_rcvData.at(i)*256 + m_rcvData.at(i+1);

			switch((i/2) + i_VarAddr){
				/////////////// Page 5
				case S_P5_V6:
				case S_P5_V9:
				case S_P5_V12:
				case S_P5_V15:
				case S_P5_V18:
					nLeftVal = 1; nRightVal = (m_rcvData.at(i+2)*256 + m_rcvData.at(i+3));	
				break;
				case S_P5_V7:
				case S_P5_V10:
				case S_P5_V13:
				case S_P5_V16:
				case S_P5_V19:	
					nLeftVal = (m_rcvData.at(i-2)*256 + m_rcvData.at(i-1)); nRightVal = (m_rcvData.at(i+2)*256 + m_rcvData.at(i+3));
				break;
				case S_P5_V8:
				case S_P5_V11:
				case S_P5_V14:
				case S_P5_V17:
				case S_P5_V20:	
					nLeftVal = (m_rcvData.at(i-2)*256 + m_rcvData.at(i-1)); nRightVal = 200;
				break;
				///////////////// Page 6
				case S_P6_V1:
				case S_P6_V3:
				case S_P6_V5:
					nLeftVal = 1; nRightVal = (m_rcvData.at(i+2)*256 + m_rcvData.at(i+3));
				break;
				case S_P6_V2:
				case S_P6_V4:	
					nLeftVal = (m_rcvData.at(i-2)*256 + m_rcvData.at(i-1)); nRightVal = 25;
				break;
				case S_P6_V6:
					nLeftVal = (m_rcvData.at(i-2)*256 + m_rcvData.at(i-1)); nRightVal = 100;
				break;
				case S_P6_V7:
					nLeftVal = 0; nRightVal = 200;
				break;
				case S_P6_V8:
				case S_P6_V9:
				case S_P6_V10:
					nLeftVal = 0; nRightVal = 20;
				break;
				case S_P6_V11:
					nLeftVal = 0; nRightVal = 1000;
				break;
				///////////////// Page 7
				case S_P7_V2:
				case S_P7_V3:
					nLeftVal = 1; nRightVal = 200;
				break;	
				case S_P7_V4:
					nLeftVal = 1; nRightVal = (m_rcvData.at(i+2)*256 + m_rcvData.at(i+3));
				break;	
				case S_P7_V5:
					nLeftVal = (m_rcvData.at(i-2)*256 + m_rcvData.at(i-1)); nRightVal = 3600;
				break;

			}
			if( Check_Range(nLeftVal,valueCheck,nRightVal) ) Setting_Var[(i/2) + i_VarAddr] = valueCheck;
		}
		return;
	case 0x36:
		i_VarAddr = 50;
		for(i=0;i<i_rcvDataCnt;i+=2){
			valueCheck = m_rcvData.at(i)*256 + m_rcvData.at(i+1);
			switch((i/2) + i_VarAddr){
				///////////////// Page 4
				case S_P4_V1:
				case S_P4_V2:
				case S_P4_V3:
					nLeftVal = 0; nRightVal = 30000;
				break;
			}
			if( Check_Range(nLeftVal,valueCheck,nRightVal) ) Setting_Var[(i/2) + i_VarAddr] = valueCheck;
		}
		return;
	case 0x10:
		switch(m_rcvData.at(1))
		{
		case ERROR_NO1:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,온도 모터1 경보\r\n"); break;
		case ERROR_NO2:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,온도 모터2 경보\r\n"); break;
		case ERROR_NO3:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,온도 모터3 경보\r\n"); break;
		case ERROR_NO4:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,온도 베어링 상 경보\r\n"); break;
		case ERROR_NO5:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,온도 베어링 하 경보\r\n"); break;
		case ERROR_NO6:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,온도 모터1 비상\r\n"); break;
		case ERROR_NO7:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,온도 모터2 비상\r\n"); break;
		case ERROR_NO8:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,온도 모터3 비상\r\n"); break;
		case ERROR_NO9:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,온도 베어링 상 비상\r\n"); break;
		case ERROR_NO10:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,온도 베어링 하 비상\r\n"); break;
		case ERROR_NO11:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,RPM 경보\r\n"); break;
		case ERROR_NO12:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,RPM 비상\r\n"); break;
		case ERROR_NO13:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,과전류 R상 경보\r\n"); break;
		case ERROR_NO14:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,과전류 S상 경보\r\n"); break;
		case ERROR_NO15:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,과전류 T상 경보\r\n"); break;
		case ERROR_NO16:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,과전류 R상 비상\r\n"); break;
		case ERROR_NO17:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,과전류 S상 비상\r\n"); break;
		case ERROR_NO18:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,과전류 T상 비상\r\n"); break;
		case ERROR_NO19:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,저전류 R상 경보\r\n"); break;
		case ERROR_NO20:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,저전류 S상 경보\r\n"); break;
		case ERROR_NO21:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,저전류 T상 경보\r\n"); break;
		case ERROR_NO22:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,저전류 R상 비상\r\n"); break;
		case ERROR_NO23:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,저전류 S상 비상\r\n"); break;
		case ERROR_NO24:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,저전류 T상 비상\r\n"); break;
		case ERROR_NO25:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,상전류 불평형 경보\r\n"); break;
		case ERROR_NO26:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,상전류 불평형 비상\r\n"); break;
		case ERROR_NO27:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,모터 누수 발생\r\n"); break;
		case ERROR_NO28:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,오일 누수 발생\r\n"); break;
		case ERROR_NO29:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("정지,제어 누수 발생\r\n"); break;
		case ERROR_NO30:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,메카니컬실 주기만료\r\n"); break;
		case ERROR_NO31:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,베어링 주기만료\r\n"); break;
		case ERROR_NO32:		mm.sprintf("20%02d-%02d-%02d  %02d:%02d:%02d,",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100)); mm.append("가동,오일 주기만료\r\n"); break;
		}

		rdFile.append(mm);
		file.write(mm.toLocal8Bit());
		P10_LineCnt++;
		return;
	default:
		QMessageBox::critical(this, "Missmatch", "Commad not defined");
		return;
	}

	for(i=0;i<i_rcvDataCnt;i+=2){
		Motor_Var[(i/2) + i_VarAddr] = m_rcvData.at(i)*256 + m_rcvData.at(i+1);
	}
	
	QString m;
	m.sprintf("20%02d. %d. %d  %d:%d:%d",int((Motor_Var[PUMP_TIME_YM])/100),int(Motor_Var[PUMP_TIME_YM]%100),int(Motor_Var[PUMP_TIME_DH]/100),int(Motor_Var[PUMP_TIME_DH]%100),int(Motor_Var[PUMP_TIME_MS]/100),int(Motor_Var[PUMP_TIME_MS]%100));
	ui->P1_ValTime->setText(m);
	ui->P2_ValTime->setText(m);
	ui->P3_ValTime->setText(m);
	ui->P4_ValTime->setText(m);
	ui->P5_ValTime->setText(m);
	ui->P6_ValTime->setText(m);
	ui->P7_ValTime->setText(m);
	ui->P8_ValTime->setText(m);
	ui->P9_ValTime->setText(m);
	ui->P10_ValTime->setText(m);

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
		ChangeWindow_WIN4();
		ui->frame_4->setHidden(false);
	break;
	case WIN_5:
		ChangeWindow_WIN5();
		ui->frame_5->setHidden(false);
	break;
	case WIN_6:
		ChangeWindow_WIN6();
		ui->frame_6->setHidden(false);
	break;
	case WIN_7:
		ChangeWindow_WIN7();
		ui->frame_7->setHidden(false);
	break;
	case WIN_8:
		ChangeWindow_WIN8();
		ui->frame_8->setHidden(false);
	break;
	case WIN_9:
		set_ym = Motor_Var[PUMP_TIME_YM];
		set_dh = Motor_Var[PUMP_TIME_DH];
		set_ms = Motor_Var[PUMP_TIME_MS];
		ui->frame_9->setHidden(false);
	break;
	case WIN_10:
		ShowEventPage();
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

QString MainWindow::toUniString(QString str)
{
	QTextCodec * codec = QTextCodec::codecForName("eucKR");
	QString localeStr = codec->toUnicode(str.toStdString().c_str());
	return (str.toLocal8Bit());
}

void MainWindow::timer_Update(void)
{
	QString mm;
	int i;
	count++;
	i_BlinkTime++;
	

	if((count%UPDATE_CURRENT_HISTORY_TIME) == 0){
		for(i=9;i<1;i--){
			historyCurrent[0][i] = historyCurrent[0][i-1];
			historyCurrent[1][i] = historyCurrent[1][i-1];
			historyCurrent[2][i] = historyCurrent[2][i-1];
			historyCurrent[3][i] = historyCurrent[3][i-1];
			historyCurrent[4][i] = historyCurrent[4][i-1];
		}

		historyCurrent[0][0] = Motor_Var[PUMP_M1C];
		historyCurrent[1][0] = Motor_Var[PUMP_M2C];
		historyCurrent[2][0] = Motor_Var[PUMP_M3C];
		historyCurrent[3][0] = Motor_Var[PUMP_UB];
	}

	if((count%UPDATE_TEMP_HISTORY_TIME) == 0){
		for(i=9;i<1;i--){
			historyTemp[0][i] = historyTemp[0][i-1];
			historyTemp[1][i] = historyTemp[1][i-1];
			historyTemp[2][i] = historyTemp[2][i-1];
			historyTemp[3][i] = historyTemp[3][i-1];
			historyTemp[4][i] = historyTemp[4][i-1];
		}
		switch(Setting_Var[S_P5_V1]){
		case T_NONE	:
			historyTemp[0][0] = 0;
		break;
		case T_SET_M1 :
			historyTemp[0][0] = Motor_Var[PUMP_M1T];
		break;
		case T_SET_M2 :
			historyTemp[0][0] = Motor_Var[PUMP_M2T];
		break;
		case T_SET_M3 :
			historyTemp[0][0] = Motor_Var[PUMP_M3T];
		break;
		case T_SET_B1 :
			historyTemp[0][0] = Motor_Var[PUMP_M4T];
		break;
		case T_SET_B2 :
			historyTemp[0][0] = Motor_Var[PUMP_M5T];
		break;
		}	
		
		switch(Setting_Var[S_P5_V2]){
		case T_NONE	:
			historyTemp[1][0] = 0;
		break;
		case T_SET_M1 :
			historyTemp[1][0] = Motor_Var[PUMP_M1T];
		break;
		case T_SET_M2 :
			historyTemp[1][0] = Motor_Var[PUMP_M2T];
		break;
		case T_SET_M3 :
			historyTemp[1][0] = Motor_Var[PUMP_M3T];
		break;
		case T_SET_B1 :
			historyTemp[1][0] = Motor_Var[PUMP_M4T];
		break;
		case T_SET_B2 :
			historyTemp[1][0] = Motor_Var[PUMP_M5T];
		break;
		}	
		
		switch(Setting_Var[S_P5_V3]){
		case T_NONE	:
			historyTemp[2][0] = 0;
		break;
		case T_SET_M1 :
			historyTemp[2][0] = Motor_Var[PUMP_M1T];
		break;
		case T_SET_M2 :
			historyTemp[2][0] = Motor_Var[PUMP_M2T];
		break;
		case T_SET_M3 :
			historyTemp[2][0] = Motor_Var[PUMP_M3T];
		break;
		case T_SET_B1 :
			historyTemp[2][0] = Motor_Var[PUMP_M4T];
		break;
		case T_SET_B2 :
			historyTemp[2][0] = Motor_Var[PUMP_M5T];
		break;
		}	
		
		switch(Setting_Var[S_P5_V4]){
		case T_NONE	:
			historyTemp[3][0] = 0;
		break;
		case T_SET_M1 :
			historyTemp[3][0] = Motor_Var[PUMP_M1T];
		break;
		case T_SET_M2 :
			historyTemp[3][0] = Motor_Var[PUMP_M2T];
		break;
		case T_SET_M3 :
			historyTemp[3][0] = Motor_Var[PUMP_M3T];
		break;
		case T_SET_B1 :
			historyTemp[3][0] = Motor_Var[PUMP_M4T];
		break;
		case T_SET_B2 :
			historyTemp[3][0] = Motor_Var[PUMP_M5T];
		break;
		}	
		
		switch(Setting_Var[S_P5_V5]){
		case T_NONE	:
			historyTemp[4][0] = 0;
		break;
		case T_SET_M1 :
			historyTemp[4][0] = Motor_Var[PUMP_M1T];
		break;
		case T_SET_M2 :
			historyTemp[4][0] = Motor_Var[PUMP_M2T];
		break;
		case T_SET_M3 :
			historyTemp[4][0] = Motor_Var[PUMP_M3T];
		break;
		case T_SET_B1 :
			historyTemp[4][0] = Motor_Var[PUMP_M4T];
		break;
		case T_SET_B2 :
			historyTemp[4][0] = Motor_Var[PUMP_M5T];
		break;
		}	
	}
	
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
		if(0/*(DEFAULT_WINDOW_CHANGE_TIME % count) == 0*/)
		{
			//count = 0;
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

#define P1_DEF_HIDDEN1_X1	0
#define P1_DEF_HIDDEN1_Y1	0
#define P1_DEF_HIDDEN1_X2	50
#define P1_DEF_HIDDEN1_Y2	50

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
		//QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", toUniString(rdFile));
	}
	else if(TouchMatching(x,P1_DEF_B3_X1,P1_DEF_B3_X2) && TouchMatching(y,P1_DEF_B3_Y1,P1_DEF_B3_Y2)){
		// ����ȭ��
		for(int i=0;i<MAX_SET_DEFINE;i++){
			backSetting_Var[i] = Setting_Var[i];
		}
		Select_Window(WIN_5);
	}
	else if(TouchMatching(x,P1_DEF_B4_X1,P1_DEF_B4_X2) && TouchMatching(y,P1_DEF_B4_Y1,P1_DEF_B4_Y2)){

		Select_Window(WIN_10);
	}
	else if(TouchMatching(x,P1_DEF_B5_X1,P1_DEF_B5_X2) && TouchMatching(y,P1_DEF_B5_Y1,P1_DEF_B5_Y2)){
		mm.sprintf("Init"); 
		uc_temptemp[2] = 0x03;
		uc_temptemp[3] = 0x01;
		uc_temptemp[4] = 0x01;

		m_send.clear();
		m_send.setRawData(uc_temptemp,8);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);
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
	else if(TouchMatching(x,P1_DEF_HIDDEN1_X1,P1_DEF_HIDDEN1_X2) && TouchMatching(y,P1_DEF_HIDDEN1_Y1,P1_DEF_HIDDEN1_Y2)){
		Select_Window(WIN_4);
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


//
#define P5_S1_B1_X1	266
#define P5_S1_B1_Y1	214
#define P5_S1_B1_X2	303
#define P5_S1_B1_Y2	251
	
#define P5_S1_B2_X1	297
#define P5_S1_B2_Y1	214
#define P5_S1_B2_X2	334
#define P5_S1_B2_Y2	251
	
#define P5_S1_B3_X1	327
#define P5_S1_B3_Y1	214
#define P5_S1_B3_X2	364
#define P5_S1_B3_Y2	251
	
#define P5_S1_B4_X1	357
#define P5_S1_B4_Y1	214
#define P5_S1_B4_X2	394
#define P5_S1_B4_Y2	251
	
#define P5_S1_B5_X1	386
#define P5_S1_B5_Y1	214
#define P5_S1_B5_X2	423
#define P5_S1_B5_Y2	251
	
#define P5_S1_B6_X1	416
#define P5_S1_B6_Y1	214
#define P5_S1_B6_X2	453
#define P5_S1_B6_Y2	251

#define P5_S2_B1_X1	266
#define P5_S2_B1_Y1	263
#define P5_S2_B1_X2	303
#define P5_S2_B1_Y2	300
	
#define P5_S2_B2_X1	297
#define P5_S2_B2_Y1	263
#define P5_S2_B2_X2	334
#define P5_S2_B2_Y2	300
	
#define P5_S2_B3_X1	327
#define P5_S2_B3_Y1	263
#define P5_S2_B3_X2	364
#define P5_S2_B3_Y2	300
	
#define P5_S2_B4_X1	357
#define P5_S2_B4_Y1	263
#define P5_S2_B4_X2	394
#define P5_S2_B4_Y2	300
	
#define P5_S2_B5_X1	386
#define P5_S2_B5_Y1	263
#define P5_S2_B5_X2	423
#define P5_S2_B5_Y2	300
	
#define P5_S2_B6_X1	416
#define P5_S2_B6_Y1	263
#define P5_S2_B6_X2	453
#define P5_S2_B6_Y2	300

#define P5_S3_B1_X1	266
#define P5_S3_B1_Y1	313
#define P5_S3_B1_X2	303
#define P5_S3_B1_Y2	350
	
#define P5_S3_B2_X1	297
#define P5_S3_B2_Y1	313
#define P5_S3_B2_X2	334
#define P5_S3_B2_Y2	350
	
#define P5_S3_B3_X1	327
#define P5_S3_B3_Y1	313
#define P5_S3_B3_X2	364
#define P5_S3_B3_Y2	350
	
#define P5_S3_B4_X1	357
#define P5_S3_B4_Y1	313
#define P5_S3_B4_X2	394
#define P5_S3_B4_Y2	350
	
#define P5_S3_B5_X1	386
#define P5_S3_B5_Y1	313
#define P5_S3_B5_X2	423
#define P5_S3_B5_Y2	350
	
#define P5_S3_B6_X1	416
#define P5_S3_B6_Y1	313
#define P5_S3_B6_X2	453
#define P5_S3_B6_Y2	350

#define P5_S4_B1_X1	266
#define P5_S4_B1_Y1	362
#define P5_S4_B1_X2	303
#define P5_S4_B1_Y2	399
	
#define P5_S4_B2_X1	297
#define P5_S4_B2_Y1	362
#define P5_S4_B2_X2	334
#define P5_S4_B2_Y2	399
	
#define P5_S4_B3_X1	327
#define P5_S4_B3_Y1	362
#define P5_S4_B3_X2	364
#define P5_S4_B3_Y2	399
	
#define P5_S4_B4_X1	357
#define P5_S4_B4_Y1	362
#define P5_S4_B4_X2	394
#define P5_S4_B4_Y2	399
	
#define P5_S4_B5_X1	386
#define P5_S4_B5_Y1	362
#define P5_S4_B5_X2	423
#define P5_S4_B5_Y2	399
	
#define P5_S4_B6_X1	416
#define P5_S4_B6_Y1	362
#define P5_S4_B6_X2	453
#define P5_S4_B6_Y2	399

#define P5_S5_B1_X1	266
#define P5_S5_B1_Y1	412
#define P5_S5_B1_X2	303
#define P5_S5_B1_Y2	449
	
#define P5_S5_B2_X1	297
#define P5_S5_B2_Y1	412
#define P5_S5_B2_X2	334
#define P5_S5_B2_Y2	449
	
#define P5_S5_B3_X1	327
#define P5_S5_B3_Y1	412
#define P5_S5_B3_X2	364
#define P5_S5_B3_Y2	449
	
#define P5_S5_B4_X1	357
#define P5_S5_B4_Y1	412
#define P5_S5_B4_X2	394
#define P5_S5_B4_Y2	449
	
#define P5_S5_B5_X1	386
#define P5_S5_B5_Y1	412
#define P5_S5_B5_X2	423
#define P5_S5_B5_Y2	449
	
#define P5_S5_B6_X1	416
#define P5_S5_B6_Y1	412
#define P5_S5_B6_X2	453
#define P5_S5_B6_Y2	449

//

	QString mm;
	QPixmap qp;

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
		char uc_temptemp[108] = {
				0x44,0x33,0x02,0x00,0x01,0x00,0x00,0x43
			};
		uint i, scnt;
		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x33;
		uc_temptemp[scnt++] = 100;
		for(i=0;i<50;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x34;
		uc_temptemp[scnt++] = 100;
		for(i=50;i<100;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);
		
		Select_Window(WIN_1);
	}
	else if(TouchMatching(x,P5_DEF_EXIT_X1,P5_DEF_EXIT_X2) && TouchMatching(y,P5_DEF_EXIT_Y1,P5_DEF_EXIT_Y2)){
		for(int i=0;i<MAX_SET_DEFINE;i++){
			Setting_Var[i] = backSetting_Var[i];
		}
		Select_Window(WIN_1);
	}


	
	else if(TouchMatching(x,P5_S1_B1_X1,P5_S1_B1_X2) && TouchMatching(y,P5_S1_B1_Y1,P5_S1_B1_Y2)){
		Setting_Var[S_P5_V1] = T_NONE;

		qp = QPixmap(P5_TempSel_STRList[1]); // 0,1
		ui->P5_S1_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S1_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S1_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S1_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S1_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S1_6->setPixmap(qp);
		
		mm.sprintf("사용안함");
		ui->P5_S1_0->setText(mm);
		ui->P5_S1_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S1_B2_X1,P5_S1_B2_X2) && TouchMatching(y,P5_S1_B2_Y1,P5_S1_B2_Y2)){
		Setting_Var[S_P5_V1] = T_SET_M1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S1_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[3]); // 2,3
		ui->P5_S1_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S1_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S1_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S1_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S1_6->setPixmap(qp);
		
		mm.sprintf("모터1");
		ui->P5_S1_0->setText(mm);
		ui->P5_S1_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S1_B3_X1,P5_S1_B3_X2) && TouchMatching(y,P5_S1_B3_Y1,P5_S1_B3_Y2)){
		Setting_Var[S_P5_V1] = T_SET_M2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S1_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S1_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[5]); // 4,5
		ui->P5_S1_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S1_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S1_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S1_6->setPixmap(qp);
		
		mm.sprintf("모터2");
		ui->P5_S1_0->setText(mm);
		ui->P5_S1_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S1_B4_X1,P5_S1_B4_X2) && TouchMatching(y,P5_S1_B4_Y1,P5_S1_B4_Y2)){
		Setting_Var[S_P5_V1] = T_SET_M3;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S1_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S1_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S1_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[7]); // 6,7
		ui->P5_S1_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S1_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S1_6->setPixmap(qp);
		
		mm.sprintf("모터3");
		ui->P5_S1_0->setText(mm);
		ui->P5_S1_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S1_B5_X1,P5_S1_B5_X2) && TouchMatching(y,P5_S1_B5_Y1,P5_S1_B5_Y2)){
		Setting_Var[S_P5_V1] = T_SET_B1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S1_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S1_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S1_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S1_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[9]); // 8,9
		ui->P5_S1_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S1_6->setPixmap(qp);
		
		mm.sprintf("베어링 상");
		ui->P5_S1_0->setText(mm);
		ui->P5_S1_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S1_B6_X1,P5_S1_B6_X2) && TouchMatching(y,P5_S1_B6_Y1,P5_S1_B6_Y2)){
		Setting_Var[S_P5_V1] = T_SET_B2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S1_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S1_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S1_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S1_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S1_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[11]); // 10,11
		ui->P5_S1_6->setPixmap(qp);
		
		mm.sprintf("베어링 하");
		ui->P5_S1_0->setText(mm);
		ui->P5_S1_0->setStyleSheet("color:rgb(255,255,255)");
	}
	

	else if(TouchMatching(x,P5_S2_B1_X1,P5_S2_B1_X2) && TouchMatching(y,P5_S2_B1_Y1,P5_S2_B1_Y2)){
		Setting_Var[S_P5_V2] = T_NONE;

		qp = QPixmap(P5_TempSel_STRList[1]); // 0,1
		ui->P5_S2_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S2_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S2_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S2_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S2_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S2_6->setPixmap(qp);
		
		mm.sprintf("사용안함");
		ui->P5_S2_0->setText(mm);
		ui->P5_S2_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S2_B2_X1,P5_S2_B2_X2) && TouchMatching(y,P5_S2_B2_Y1,P5_S2_B2_Y2)){
		Setting_Var[S_P5_V2] = T_SET_M1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S2_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[3]); // 2,3
		ui->P5_S2_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S2_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S2_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S2_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S2_6->setPixmap(qp);
		
		mm.sprintf("모터1");
		ui->P5_S2_0->setText(mm);
		ui->P5_S2_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S2_B3_X1,P5_S2_B3_X2) && TouchMatching(y,P5_S2_B3_Y1,P5_S2_B3_Y2)){
		Setting_Var[S_P5_V2] = T_SET_M2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S2_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S2_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[5]); // 4,5
		ui->P5_S2_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S2_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S2_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S2_6->setPixmap(qp);
		
		mm.sprintf("모터2");
		ui->P5_S2_0->setText(mm);
		ui->P5_S2_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S2_B4_X1,P5_S2_B4_X2) && TouchMatching(y,P5_S2_B4_Y1,P5_S2_B4_Y2)){
		Setting_Var[S_P5_V2] = T_SET_M3;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S2_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S2_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S2_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[7]); // 6,7
		ui->P5_S2_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S2_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S2_6->setPixmap(qp);
		
		mm.sprintf("모터3");
		ui->P5_S2_0->setText(mm);
		ui->P5_S2_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S2_B5_X1,P5_S2_B5_X2) && TouchMatching(y,P5_S2_B5_Y1,P5_S2_B5_Y2)){
		Setting_Var[S_P5_V2] = T_SET_B1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S2_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S2_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S2_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S2_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[9]); // 8,9
		ui->P5_S2_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S2_6->setPixmap(qp);
		
		mm.sprintf("베어링 상");
		ui->P5_S2_0->setText(mm);
		ui->P5_S2_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S2_B6_X1,P5_S2_B6_X2) && TouchMatching(y,P5_S2_B6_Y1,P5_S2_B6_Y2)){
		Setting_Var[S_P5_V2] = T_SET_B2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S2_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S2_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S2_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S2_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S2_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[11]); // 10,11
		ui->P5_S2_6->setPixmap(qp);
		
		mm.sprintf("베어링 하");
		ui->P5_S2_0->setText(mm);
		ui->P5_S2_0->setStyleSheet("color:rgb(255,255,255)");
	}
	
	else if(TouchMatching(x,P5_S3_B1_X1,P5_S3_B1_X2) && TouchMatching(y,P5_S3_B1_Y1,P5_S3_B1_Y2)){
		Setting_Var[S_P5_V3] = T_NONE;

		qp = QPixmap(P5_TempSel_STRList[1]); // 0,1
		ui->P5_S3_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S3_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S3_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S3_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S3_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S3_6->setPixmap(qp);
		
		mm.sprintf("사용안함");
		ui->P5_S3_0->setText(mm);
		ui->P5_S3_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S3_B2_X1,P5_S3_B2_X2) && TouchMatching(y,P5_S3_B2_Y1,P5_S3_B2_Y2)){
		Setting_Var[S_P5_V3] = T_SET_M1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S3_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[3]); // 2,3
		ui->P5_S3_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S3_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S3_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S3_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S3_6->setPixmap(qp);
		
		mm.sprintf("모터1");
		ui->P5_S3_0->setText(mm);
		ui->P5_S3_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S3_B3_X1,P5_S3_B3_X2) && TouchMatching(y,P5_S3_B3_Y1,P5_S3_B3_Y2)){
		Setting_Var[S_P5_V3] = T_SET_M2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S3_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S3_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[5]); // 4,5
		ui->P5_S3_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S3_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S3_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S3_6->setPixmap(qp);
		
		mm.sprintf("모터2");
		ui->P5_S3_0->setText(mm);
		ui->P5_S3_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S3_B4_X1,P5_S3_B4_X2) && TouchMatching(y,P5_S3_B4_Y1,P5_S3_B4_Y2)){
		Setting_Var[S_P5_V3] = T_SET_M3;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S3_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S3_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S3_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[7]); // 6,7
		ui->P5_S3_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S3_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S3_6->setPixmap(qp);
		
		mm.sprintf("모터3");
		ui->P5_S3_0->setText(mm);
		ui->P5_S3_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S3_B5_X1,P5_S3_B5_X2) && TouchMatching(y,P5_S3_B5_Y1,P5_S3_B5_Y2)){
		Setting_Var[S_P5_V3] = T_SET_B1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S3_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S3_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S3_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S3_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[9]); // 8,9
		ui->P5_S3_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S3_6->setPixmap(qp);
		
		mm.sprintf("베어링 상");
		ui->P5_S3_0->setText(mm);
		ui->P5_S3_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S3_B6_X1,P5_S3_B6_X2) && TouchMatching(y,P5_S3_B6_Y1,P5_S3_B6_Y2)){
		Setting_Var[S_P5_V3] = T_SET_B2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S3_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S3_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S3_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S3_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S3_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[11]); // 10,11
		ui->P5_S3_6->setPixmap(qp);
		
		mm.sprintf("베어링 하");
		ui->P5_S3_0->setText(mm);
		ui->P5_S3_0->setStyleSheet("color:rgb(255,255,255)");
	}
	
	else if(TouchMatching(x,P5_S4_B1_X1,P5_S4_B1_X2) && TouchMatching(y,P5_S4_B1_Y1,P5_S4_B1_Y2)){
		Setting_Var[S_P5_V4] = T_NONE;

		qp = QPixmap(P5_TempSel_STRList[1]); // 0,1
		ui->P5_S4_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S4_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S4_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S4_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S4_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S4_6->setPixmap(qp);
		
		mm.sprintf("사용안함");
		ui->P5_S4_0->setText(mm);
		ui->P5_S4_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S4_B2_X1,P5_S4_B2_X2) && TouchMatching(y,P5_S4_B2_Y1,P5_S4_B2_Y2)){
		Setting_Var[S_P5_V4] = T_SET_M1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S4_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[3]); // 2,3
		ui->P5_S4_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S4_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S4_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S4_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S4_6->setPixmap(qp);
		
		mm.sprintf("모터1");
		ui->P5_S4_0->setText(mm);
		ui->P5_S4_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S4_B3_X1,P5_S4_B3_X2) && TouchMatching(y,P5_S4_B3_Y1,P5_S4_B3_Y2)){
		Setting_Var[S_P5_V4] = T_SET_M2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S4_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S4_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[5]); // 4,5
		ui->P5_S4_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S4_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S4_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S4_6->setPixmap(qp);
		
		mm.sprintf("모터2");
		ui->P5_S4_0->setText(mm);
		ui->P5_S4_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S4_B4_X1,P5_S4_B4_X2) && TouchMatching(y,P5_S4_B4_Y1,P5_S4_B4_Y2)){
		Setting_Var[S_P5_V4] = T_SET_M3;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S4_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S4_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S4_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[7]); // 6,7
		ui->P5_S4_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S4_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S4_6->setPixmap(qp);
		
		mm.sprintf("모터3");
		ui->P5_S4_0->setText(mm);
		ui->P5_S4_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S4_B5_X1,P5_S4_B5_X2) && TouchMatching(y,P5_S4_B5_Y1,P5_S4_B5_Y2)){
		Setting_Var[S_P5_V4] = T_SET_B1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S4_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S4_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S4_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S4_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[9]); // 8,9
		ui->P5_S4_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S4_6->setPixmap(qp);
		
		mm.sprintf("베어링 상");
		ui->P5_S4_0->setText(mm);
		ui->P5_S4_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S4_B6_X1,P5_S4_B6_X2) && TouchMatching(y,P5_S4_B6_Y1,P5_S4_B6_Y2)){
		Setting_Var[S_P5_V4] = T_SET_B2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S4_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S4_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S4_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S4_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S4_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[11]); // 10,11
		ui->P5_S4_6->setPixmap(qp);
		
		mm.sprintf("베어링 하");
		ui->P5_S4_0->setText(mm);
		ui->P5_S4_0->setStyleSheet("color:rgb(255,255,255)");
	}
	
	else if(TouchMatching(x,P5_S5_B1_X1,P5_S5_B1_X2) && TouchMatching(y,P5_S5_B1_Y1,P5_S5_B1_Y2)){
		Setting_Var[S_P5_V5] = T_NONE;

		qp = QPixmap(P5_TempSel_STRList[1]); // 0,1
		ui->P5_S5_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S5_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S5_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S5_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S5_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S5_6->setPixmap(qp);
		
		mm.sprintf("사용안함");
		ui->P5_S5_0->setText(mm);
		ui->P5_S5_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S5_B2_X1,P5_S5_B2_X2) && TouchMatching(y,P5_S5_B2_Y1,P5_S5_B2_Y2)){
		Setting_Var[S_P5_V5] = T_SET_M1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S5_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[3]); // 2,3
		ui->P5_S5_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S5_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S5_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S5_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S5_6->setPixmap(qp);
		
		mm.sprintf("모터1");
		ui->P5_S5_0->setText(mm);
		ui->P5_S5_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S5_B3_X1,P5_S5_B3_X2) && TouchMatching(y,P5_S5_B3_Y1,P5_S5_B3_Y2)){
		Setting_Var[S_P5_V5] = T_SET_M2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S5_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S5_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[5]); // 4,5
		ui->P5_S5_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S5_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S5_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S5_6->setPixmap(qp);
		
		mm.sprintf("모터2");
		ui->P5_S5_0->setText(mm);
		ui->P5_S5_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S5_B4_X1,P5_S5_B4_X2) && TouchMatching(y,P5_S5_B4_Y1,P5_S5_B4_Y2)){
		Setting_Var[S_P5_V5] = T_SET_M3;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S5_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S5_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S5_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[7]); // 6,7
		ui->P5_S5_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S5_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S5_6->setPixmap(qp);
		
		mm.sprintf("모터3");
		ui->P5_S5_0->setText(mm);
		ui->P5_S5_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S5_B5_X1,P5_S5_B5_X2) && TouchMatching(y,P5_S5_B5_Y1,P5_S5_B5_Y2)){
		Setting_Var[S_P5_V5] = T_SET_B1;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S5_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S5_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S5_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S5_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[9]); // 8,9
		ui->P5_S5_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[10]); // 10,11
		ui->P5_S5_6->setPixmap(qp);
		
		mm.sprintf("베어링 상");
		ui->P5_S5_0->setText(mm);
		ui->P5_S5_0->setStyleSheet("color:rgb(255,255,255)");
	}
	else if(TouchMatching(x,P5_S5_B6_X1,P5_S5_B6_X2) && TouchMatching(y,P5_S5_B6_Y1,P5_S5_B6_Y2)){
		Setting_Var[S_P5_V5] = T_SET_B2;

		qp = QPixmap(P5_TempSel_STRList[0]); // 0,1
		ui->P5_S5_1->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[2]); // 2,3
		ui->P5_S5_2->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[4]); // 4,5
		ui->P5_S5_3->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[6]); // 6,7
		ui->P5_S5_4->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[8]); // 8,9
		ui->P5_S5_5->setPixmap(qp);
		qp = QPixmap(P5_TempSel_STRList[11]); // 10,11
		ui->P5_S5_6->setPixmap(qp);
		
		mm.sprintf("베어링 하");
		ui->P5_S5_0->setText(mm);
		ui->P5_S5_0->setStyleSheet("color:rgb(255,255,255)");
	}

}

void MainWindow::TouchMove_WIN4(int orgX, int orgY)
{
	int nVal;
	QString mm;

	if(TouchMatching(orgX,ScrollVar[0][0],ScrollVar[0][1]) && TouchMatching(orgY,ScrollVar[0][2],ScrollVar[0][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) < 590 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) > 745 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] , ScrollVar[0][2] );
		ui->P4_Set1->setProperty("pos", qpAppNewLoc);

		nVal = ui->P4_Set1->x() - 590;
		nVal = int((30000*nVal/(745-590)));

		Setting_Var[S_P4_V1] = nVal;
		mm.sprintf("%d",Setting_Var[S_P4_V1]);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] - 30 , ScrollVar[0][2] - 20 );
		ui->P4_Set1_T->setProperty("pos", qpAppNewLoc1);
		ui->P4_Set1_T->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[1][0],ScrollVar[1][1]) && TouchMatching(orgY,ScrollVar[1][2],ScrollVar[1][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) < 590 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) > 745 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] , ScrollVar[1][2] );
		ui->P4_Set2->setProperty("pos", qpAppNewLoc);

		nVal = ui->P4_Set2->x() - 590;
		nVal = int((30000*nVal/(745-590)));

		Setting_Var[S_P4_V2] = nVal;
		mm.sprintf("%d",Setting_Var[S_P4_V2]);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] - 30 , ScrollVar[1][2] - 20 );
		ui->P4_Set2_T->setProperty("pos", qpAppNewLoc1);
		ui->P4_Set2_T->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[2][0],ScrollVar[2][1]) && TouchMatching(orgY,ScrollVar[2][2],ScrollVar[2][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) < 590 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) > 745 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] , ScrollVar[2][2] );
		ui->P4_Set3->setProperty("pos", qpAppNewLoc);

		nVal = ui->P4_Set3->x() - 590;
		nVal = int((30000*nVal/(745-590)));

		Setting_Var[S_P4_V3] = nVal;
		mm.sprintf("%d",Setting_Var[S_P4_V3]);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] - 30 , ScrollVar[2][2] - 20 );
		ui->P4_Set3_T->setProperty("pos", qpAppNewLoc1);
		ui->P4_Set3_T->setText(mm);
	}

}

void MainWindow::TouchMove_WIN5(int orgX, int orgY)
{
	int nVal;
	QString mm;

	if(TouchMatching(orgX,ScrollVar[0][0],ScrollVar[0][1]) && TouchMatching(orgY,ScrollVar[0][2],ScrollVar[0][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) < 460 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) > ScrollVar[1][0]-(ui->P5_Set1_M->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] , ScrollVar[0][2] );
		ui->P5_Set1_L->setProperty("pos", qpAppNewLoc);

		nVal = ui->P5_Set1_L->x() - 460;
		nVal = int((199*nVal/(757-460))+1);

		Setting_Var[S_P5_V6] = nVal;
		mm.sprintf("%d",Setting_Var[S_P5_V6]);

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] + 2 , ScrollVar[0][2] - 10 );
		ui->P5_Set1_L_txt->setProperty("pos", qpAppNewLoc1);
		ui->P5_Set1_L_txt->setText(mm);
	}
	else if(TouchMatching(orgX,ScrollVar[1][0],ScrollVar[1][1]) && TouchMatching(orgY,ScrollVar[1][2],ScrollVar[1][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) < ScrollVar[0][1]-(ui->P5_Set1_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) > ScrollVar[2][0]-(ui->P5_Set1_H->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] , ScrollVar[1][2] );
		ui->P5_Set1_M->setProperty("pos", qpAppNewLoc);

		nVal = ui->P5_Set1_M->x() - 460;
		nVal = int((199*nVal/(757-460))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P5_V7] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] + 2 , ScrollVar[1][2] - 10 );
		ui->P5_Set1_M_txt->setProperty("pos", qpAppNewLoc1);
		ui->P5_Set1_M_txt->setText(mm);
	}
	else if(TouchMatching(orgX,ScrollVar[2][0],ScrollVar[2][1]) && TouchMatching(orgY,ScrollVar[2][2],ScrollVar[2][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) < ScrollVar[1][1]-(ui->P5_Set1_L->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) > 757 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] , ScrollVar[2][2] );
		ui->P5_Set1_H->setProperty("pos", qpAppNewLoc);

		nVal = ui->P5_Set1_H->x() - 460;
		nVal = int((199*nVal/(757-460))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P5_V8] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] + 2 , ScrollVar[2][2] - 10 );
		ui->P5_Set1_H_txt->setProperty("pos", qpAppNewLoc1);
		ui->P5_Set1_H_txt->setText(mm);
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
		char uc_temptemp[108] = {
						0x44,0x33,0x02,0x00,0x01,0x00,0x00,0x43
					};
		uint i, scnt;
		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x33;
		uc_temptemp[scnt++] = 100;
		for(i=0;i<50;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x34;
		uc_temptemp[scnt++] = 100;
		for(i=50;i<100;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);
		
		Select_Window(WIN_1);
	}
	else if(TouchMatching(x,P6_DEF_EXIT_X1,P6_DEF_EXIT_X2) && TouchMatching(y,P6_DEF_EXIT_Y1,P6_DEF_EXIT_Y2)){
		for(int i=0;i<MAX_SET_DEFINE;i++){
			Setting_Var[i] = backSetting_Var[i];
		}
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
		nVal = int((24*nVal/(375-225))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V1] = nVal;

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
		nVal = int((24*nVal/(375-225))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V2] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] + 2 , ScrollVar[1][2] - 15 );
		ui->P6_V1_2->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_2->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[2][0],ScrollVar[2][1]) && TouchMatching(orgY,ScrollVar[2][2],ScrollVar[2][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) < ScrollVar[3][1]-(ui->P6_H2->width()/2) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) > 375 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] , ScrollVar[2][2] );
		ui->P6_L2->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_L2->x() - 225;
		nVal = int((24*nVal/(375-225))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V3] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] + 2 , ScrollVar[2][2] - 15 );
		ui->P6_V1_3->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_3->setText(mm);
	}
	else if(TouchMatching(orgX,ScrollVar[3][0],ScrollVar[3][1]) && TouchMatching(orgY,ScrollVar[3][2],ScrollVar[3][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) < 225 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) > ScrollVar[2][0]-(ui->P6_H2->width()/2) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[3][0] , ScrollVar[3][2] );
		ui->P6_H2->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_H2->x() - 225;
		nVal = int((24*nVal/(375-225))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V4] = nVal;

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
		nVal = int((100*nVal/(375-225))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V5] = nVal;

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
		nVal = int((100*nVal/(375-225)));
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V6] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[5][0] + 2 , ScrollVar[5][2] - 15 );
		ui->P6_V1_6->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_6->setText(mm);
	}


	else if(TouchMatching(orgX,ScrollVar[6][0],ScrollVar[6][1]) && TouchMatching(orgY,ScrollVar[6][2],ScrollVar[6][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[6][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[6][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[6][0] , ScrollVar[6][2] );
		ui->P6_T1->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_T1->x() - 500;
		nVal = int((200*nVal/(750-500)));
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V7] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[6][0] + 2 , ScrollVar[6][2] - 15 );
		ui->P6_V1_7->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_7->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[7][0],ScrollVar[7][1]) && TouchMatching(orgY,ScrollVar[7][2],ScrollVar[7][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[7][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[7][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[7][0] , ScrollVar[7][2] );
		ui->P6_T2->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_T2->x() - 500;
		nVal = int((20*nVal/(750-500)));
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V8] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[7][0] + 2 , ScrollVar[7][2] - 15 );
		ui->P6_V1_8->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_8->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[8][0],ScrollVar[8][1]) && TouchMatching(orgY,ScrollVar[8][2],ScrollVar[8][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[8][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[8][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[8][0] , ScrollVar[8][2] );
		ui->P6_T3->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_T3->x() - 500;
		nVal = int((20*nVal/(750-500)));
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V9] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[8][0] + 2 , ScrollVar[8][2] - 15 );
		ui->P6_V1_9->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_9->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[9][0],ScrollVar[9][1]) && TouchMatching(orgY,ScrollVar[9][2],ScrollVar[9][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[9][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[9][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[9][0] , ScrollVar[9][2] );
		ui->P6_T4->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_T4->x() - 500;
		nVal = int((20*nVal/(750-500)));
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V10] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[9][0] + 2 , ScrollVar[9][2] - 15 );
		ui->P6_V1_10->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_10->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[10][0],ScrollVar[10][1]) && TouchMatching(orgY,ScrollVar[10][2],ScrollVar[10][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[10][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[10][0]) > 750 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[10][0] , ScrollVar[10][2] );
		ui->P6_T5->setProperty("pos", qpAppNewLoc);

		nVal = ui->P6_T5->x() - 500;
		nVal = int((1000*nVal/(750-500)));
		mm.sprintf("%d",nVal);
		Setting_Var[S_P6_V11] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[10][0] - 2 , ScrollVar[10][2] - 15 );
		ui->P6_V1_11->setProperty("pos", qpAppNewLoc1);
		ui->P6_V1_11->setText(mm);
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

#define P7_DEF_B6_X1	165
#define P7_DEF_B6_Y1	227
#define P7_DEF_B6_X2	205
#define P7_DEF_B6_Y2	267

#define P7_DEF_B7_X1	285
#define P7_DEF_B7_Y1	227
#define P7_DEF_B7_X2	325
#define P7_DEF_B7_Y2	267

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

	QPixmap qp;
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
		char uc_temptemp[108] = {
						0x44,0x33,0x02,0x00,0x01,0x00,0x00,0x43
					};
		uint i, scnt;
		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x33;
		uc_temptemp[scnt++] = 100;
		for(i=0;i<50;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x34;
		uc_temptemp[scnt++] = 100;
		for(i=50;i<100;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		Select_Window(WIN_1);
	}
	else if(TouchMatching(x,P7_DEF_EXIT_X1,P7_DEF_EXIT_X2) && TouchMatching(y,P7_DEF_EXIT_Y1,P7_DEF_EXIT_Y2)){
		for(int i=0;i<MAX_SET_DEFINE;i++){
			Setting_Var[i] = backSetting_Var[i];
		}
		Select_Window(WIN_1);
	}
	else if(TouchMatching(x,P7_DEF_B6_X1,P7_DEF_B6_X2) && TouchMatching(y,P7_DEF_B6_Y1,P7_DEF_B6_Y2)){
		qp = QPixmap(":/new/7P/UIUX/7p/TempInfo/7P_Group2 (5).png");
		ui->P7_B1->setPixmap(qp);
		Setting_Var[S_P7_V1] = 0;
	}
	else if(TouchMatching(x,P7_DEF_B7_X1,P7_DEF_B7_X2) && TouchMatching(y,P7_DEF_B7_Y1,P7_DEF_B7_Y2)){
		qp = QPixmap(":/new/7P/UIUX/7p/TempInfo/7P_Group2 (3).png");
		ui->P7_B1->setPixmap(qp);
		Setting_Var[S_P7_V1] = 1;
	}

}

void MainWindow::TouchMove_WIN7(int orgX, int orgY)
{
	int nVal;
	QString mm;

	if(TouchMatching(orgX,ScrollVar[0][0],ScrollVar[0][1]) && TouchMatching(orgY,ScrollVar[0][2],ScrollVar[0][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[0][0]) > 760 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] , ScrollVar[0][2] );
		ui->P7_D1->setProperty("pos", qpAppNewLoc);

		nVal = ui->P7_D1->x() - 500;
		nVal = int((199*nVal/(760-500))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P7_V2] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[0][0] + 2 , ScrollVar[0][2] - 15 );
		ui->P7_V1_1->setProperty("pos", qpAppNewLoc1);
		ui->P7_V1_1->setText(mm);

	}
	else if(TouchMatching(orgX,ScrollVar[1][0],ScrollVar[1][1]) && TouchMatching(orgY,ScrollVar[1][2],ScrollVar[1][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) < 500 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[1][0]) > 760 ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] , ScrollVar[1][2] );
		ui->P7_D2->setProperty("pos", qpAppNewLoc);

		nVal = ui->P7_D2->x() - 500;
		nVal = int((199*nVal/(760-500))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P7_V3] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[1][0] + 2 , ScrollVar[1][2] - 15 );
		ui->P7_V1_2->setProperty("pos", qpAppNewLoc1);
		ui->P7_V1_2->setText(mm);
	}

	else if(TouchMatching(orgX,ScrollVar[2][0],ScrollVar[2][1]) && TouchMatching(orgY,ScrollVar[2][2],ScrollVar[2][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) > ScrollVar[3][0]-(ui->P7_L1->width()/2+7) ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[2][0]) < 155 ) return;
		

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] , ScrollVar[2][2] );
		ui->P7_H1->setProperty("pos", qpAppNewLoc);

		nVal = ui->P7_H1->x() - 155;
		nVal = int((3599*nVal/(745-155))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P7_V5] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[2][0] - 10 , ScrollVar[2][2] - 18 );
		ui->P7_V1_4->setProperty("pos", qpAppNewLoc1);
		ui->P7_V1_4->setText(mm);
	}
	else if(TouchMatching(orgX,ScrollVar[3][0],ScrollVar[3][1]) && TouchMatching(orgY,ScrollVar[3][2],ScrollVar[3][3])){
		if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) > 745 ) return;
		else if( ((QCursor::pos().x() - iXdifferent) + ScrollVar[3][0]) < ScrollVar[2][1]-(ui->P7_H1->width()/2-7) ) return;

		QPoint qpAppNewLoc( (QCursor::pos().x() - iXdifferent) + ScrollVar[3][0] , ScrollVar[3][2] );
		ui->P7_L1->setProperty("pos", qpAppNewLoc);

		nVal = ui->P7_L1->x() - 155;
		nVal = int((3599*nVal/(745-155))+1);
		mm.sprintf("%d",nVal);
		Setting_Var[S_P7_V4] = nVal;

		QPoint qpAppNewLoc1( (QCursor::pos().x() - iXdifferent) + ScrollVar[3][0] - 10 , ScrollVar[3][2] - 18 );
		ui->P7_V1_3->setProperty("pos", qpAppNewLoc1);
		ui->P7_V1_3->setText(mm);
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

#define P8_DEF_V1_X1	170
#define P8_DEF_V1_Y1	170
#define P8_DEF_V1_X2	370
#define P8_DEF_V1_Y2	230

#define P8_DEF_V2_X1	170
#define P8_DEF_V2_Y1	245
#define P8_DEF_V2_X2	370
#define P8_DEF_V2_Y2	305

#define P8_DEF_V3_X1	170
#define P8_DEF_V3_Y1	320
#define P8_DEF_V3_X2	370
#define P8_DEF_V3_Y2	380

#define P8_DEF_V4_X1	170
#define P8_DEF_V4_Y1	400
#define P8_DEF_V4_X2	370
#define P8_DEF_V4_Y2	460

#define P8_DEF_V5_X1	560
#define P8_DEF_V5_Y1	187
#define P8_DEF_V5_X2	610
#define P8_DEF_V5_Y2	217

#define P8_DEF_V6_X1	618
#define P8_DEF_V6_Y1	187
#define P8_DEF_V6_X2	668
#define P8_DEF_V6_Y2	217

#define P8_DEF_V7_X1	672
#define P8_DEF_V7_Y1	187
#define P8_DEF_V7_X2	722
#define P8_DEF_V7_Y2	217

#define P8_DEF_V8_X1	724
#define P8_DEF_V8_Y1	187
#define P8_DEF_V8_X2	774
#define P8_DEF_V8_Y2	217

#define P8_DEF_V9_X1	564
#define P8_DEF_V9_Y1	250
#define P8_DEF_V9_X2	604
#define P8_DEF_V9_Y2	280

#define P8_DEF_V10_X1	620
#define P8_DEF_V10_Y1	250
#define P8_DEF_V10_X2	660
#define P8_DEF_V10_Y2	280

#define P8_DEF_V11_X1	672
#define P8_DEF_V11_Y1	250
#define P8_DEF_V11_X2	712
#define P8_DEF_V11_Y2	280

#define P8_DEF_V12_X1	725
#define P8_DEF_V12_Y1	250
#define P8_DEF_V12_X2	765
#define P8_DEF_V12_Y2	280

#define P8_DEF_V13_X1	532
#define P8_DEF_V13_Y1	340
#define P8_DEF_V13_X2	572
#define P8_DEF_V13_Y2	370

#define P8_DEF_V14_X1	582
#define P8_DEF_V14_Y1	340
#define P8_DEF_V14_X2	622
#define P8_DEF_V14_Y2	370

#define P8_DEF_V15_X1	632
#define P8_DEF_V15_Y1	340
#define P8_DEF_V15_X2	672
#define P8_DEF_V15_Y2	370

#define P8_DEF_V16_X1	682
#define P8_DEF_V16_Y1	340
#define P8_DEF_V16_X2	722
#define P8_DEF_V16_Y2	370

#define P8_DEF_V17_X1	732
#define P8_DEF_V17_Y1	340
#define P8_DEF_V17_X2	772
#define P8_DEF_V17_Y2	370

#define P8_DEF_V18_X1	532
#define P8_DEF_V18_Y1	370
#define P8_DEF_V18_X2	572
#define P8_DEF_V18_Y2	400

#define P8_DEF_V19_X1	582
#define P8_DEF_V19_Y1	370
#define P8_DEF_V19_X2	622
#define P8_DEF_V19_Y2	400

#define P8_DEF_V20_X1	632
#define P8_DEF_V20_Y1	370
#define P8_DEF_V20_X2	672
#define P8_DEF_V20_Y2	400

#define P8_DEF_V21_X1	682
#define P8_DEF_V21_Y1	370
#define P8_DEF_V21_X2	722
#define P8_DEF_V21_Y2	400

#define P8_DEF_V22_X1	732
#define P8_DEF_V22_Y1	370
#define P8_DEF_V22_X2	772
#define P8_DEF_V22_Y2	400

#define P8_DEF_V23_X1	564
#define P8_DEF_V23_Y1	430
#define P8_DEF_V23_X2	604
#define P8_DEF_V23_Y2	460

#define P8_DEF_V24_X1	623
#define P8_DEF_V24_Y1	430
#define P8_DEF_V24_X2	663
#define P8_DEF_V24_Y2	460

#define P8_DEF_V25_X1	675
#define P8_DEF_V25_Y1	430
#define P8_DEF_V25_X2	715
#define P8_DEF_V25_Y2	460

#define P8_DEF_V26_X1	726
#define P8_DEF_V26_Y1	430
#define P8_DEF_V26_X2	766
#define P8_DEF_V26_Y2	460

	QPixmap qp;
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
		char uc_temptemp[108] = {
						0x44,0x33,0x02,0x00,0x01,0x00,0x00,0x43
					};
		uint i, scnt;
		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x33;
		uc_temptemp[scnt++] = 100;
		for(i=0;i<50;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x34;
		uc_temptemp[scnt++] = 100;
		for(i=50;i<100;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		Select_Window(WIN_1);
	}
	else if(TouchMatching(x,P8_DEF_EXIT_X1,P8_DEF_EXIT_X2) && TouchMatching(y,P8_DEF_EXIT_Y1,P8_DEF_EXIT_Y2)){
		for(int i=0;i<MAX_SET_DEFINE;i++){
			Setting_Var[i] = backSetting_Var[i];
		}
		Select_Window(WIN_1);
	}

	else if(TouchMatching(x,P8_DEF_V1_X1,P8_DEF_V1_X2) && TouchMatching(y,P8_DEF_V1_Y1,P8_DEF_V1_Y2)){
		if(Setting_Var[S_P8_V1]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B1->setPixmap(qp);

		if(Setting_Var[S_P8_V1]) qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (11)");  // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (12)"); // ���
		ui->P8_B1_V2->setPixmap(qp);

		Setting_Var[S_P8_V1] = (Setting_Var[S_P8_V1] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V2_X1,P8_DEF_V2_X2) && TouchMatching(y,P8_DEF_V2_Y1,P8_DEF_V2_Y2)){
		if(Setting_Var[S_P8_V2]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B2->setPixmap(qp);

		if(Setting_Var[S_P8_V2]) qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (11)");  // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (12)"); // ���
		ui->P8_B2_V2->setPixmap(qp);

		Setting_Var[S_P8_V2] = (Setting_Var[S_P8_V2] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V3_X1,P8_DEF_V3_X2) && TouchMatching(y,P8_DEF_V3_Y1,P8_DEF_V3_Y2)){
		if(Setting_Var[S_P8_V3]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B3->setPixmap(qp);

		if(Setting_Var[S_P8_V3]) qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (11)");  // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (12)"); // ���
		ui->P8_B3_V2->setPixmap(qp);

		Setting_Var[S_P8_V3] = (Setting_Var[S_P8_V3] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V4_X1,P8_DEF_V4_X2) && TouchMatching(y,P8_DEF_V4_Y1,P8_DEF_V4_Y2)){
		if(Setting_Var[S_P8_V4]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B4->setPixmap(qp);

		if(Setting_Var[S_P8_V4]) qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (11)");  // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (12)"); // ���
		ui->P8_B4_V2->setPixmap(qp);

		Setting_Var[S_P8_V4] = (Setting_Var[S_P8_V4] + 1) % 2;
	}


	else if(TouchMatching(x,P8_DEF_V5_X1,P8_DEF_V5_X2) && TouchMatching(y,P8_DEF_V5_Y1,P8_DEF_V5_Y2)){
		
		Setting_Var[S_P8_V5] = SET_ENABLE;
		Setting_Var[S_P8_V6] = SET_DISABLE;
		Setting_Var[S_P8_V7] = SET_DISABLE;
		Setting_Var[S_P8_V8] = SET_DISABLE;
		
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ������
		ui->P8_B5->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B6->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B7->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B8->setPixmap(qp);

	}
	else if(TouchMatching(x,P8_DEF_V6_X1,P8_DEF_V6_X2) && TouchMatching(y,P8_DEF_V6_Y1,P8_DEF_V6_Y2)){
		
		Setting_Var[S_P8_V5] = SET_DISABLE;
		Setting_Var[S_P8_V6] = SET_ENABLE;
		Setting_Var[S_P8_V7] = SET_DISABLE;
		Setting_Var[S_P8_V8] = SET_DISABLE;
		
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B5->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ������
		ui->P8_B6->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B7->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B8->setPixmap(qp);
	}
	else if(TouchMatching(x,P8_DEF_V7_X1,P8_DEF_V7_X2) && TouchMatching(y,P8_DEF_V7_Y1,P8_DEF_V7_Y2)){
		
		Setting_Var[S_P8_V5] = SET_DISABLE;
		Setting_Var[S_P8_V6] = SET_DISABLE;
		Setting_Var[S_P8_V7] = SET_ENABLE;
		Setting_Var[S_P8_V8] = SET_DISABLE;
		
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B5->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B6->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ������
		ui->P8_B7->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B8->setPixmap(qp);
	}
	else if(TouchMatching(x,P8_DEF_V8_X1,P8_DEF_V8_X2) && TouchMatching(y,P8_DEF_V8_Y1,P8_DEF_V8_Y2)){
		
		Setting_Var[S_P8_V5] = SET_DISABLE;
		Setting_Var[S_P8_V6] = SET_DISABLE;
		Setting_Var[S_P8_V7] = SET_DISABLE;
		Setting_Var[S_P8_V8] = SET_ENABLE;
		
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B5->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B6->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		ui->P8_B7->setPixmap(qp);
		qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ������
		ui->P8_B8->setPixmap(qp);
	}

	else if(TouchMatching(x,P8_DEF_V9_X1,P8_DEF_V9_X2) && TouchMatching(y,P8_DEF_V9_Y1,P8_DEF_V9_Y2)){
		if(!Setting_Var[S_P8_V9]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (11).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (22).png"); // Dis
		ui->P8_B19->setPixmap(qp);

		Setting_Var[S_P8_V9] = (Setting_Var[S_P8_V9] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V10_X1,P8_DEF_V10_X2) && TouchMatching(y,P8_DEF_V10_Y1,P8_DEF_V10_Y2)){
		if(!Setting_Var[S_P8_V10]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (23).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (24).png"); // Dis
		ui->P8_B20->setPixmap(qp);

		Setting_Var[S_P8_V10] = (Setting_Var[S_P8_V10] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V11_X1,P8_DEF_V11_X2) && TouchMatching(y,P8_DEF_V11_Y1,P8_DEF_V11_Y2)){
		if(!Setting_Var[S_P8_V11]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (10).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (26).png"); // Dis
		ui->P8_B21->setPixmap(qp);

		Setting_Var[S_P8_V11] = (Setting_Var[S_P8_V11] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V12_X1,P8_DEF_V12_X2) && TouchMatching(y,P8_DEF_V12_Y1,P8_DEF_V12_Y2)){
		if(!Setting_Var[S_P8_V12]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (9).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (25).png"); // Dis
		ui->P8_B22->setPixmap(qp);

		Setting_Var[S_P8_V12] = (Setting_Var[S_P8_V12] + 1) % 2;
	}

	else if(TouchMatching(x,P8_DEF_V13_X1,P8_DEF_V13_X2) && TouchMatching(y,P8_DEF_V13_Y1,P8_DEF_V13_Y2)){
		if(!Setting_Var[S_P8_V13]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (12).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (31).png"); // Dis
		ui->P8_B9_V2->setPixmap(qp);

		Setting_Var[S_P8_V13] = (Setting_Var[S_P8_V13] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V14_X1,P8_DEF_V14_X2) && TouchMatching(y,P8_DEF_V14_Y1,P8_DEF_V14_Y2)){
		if(!Setting_Var[S_P8_V14]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (13).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (27).png"); // Dis
		ui->P8_B10_V2->setPixmap(qp);

		Setting_Var[S_P8_V14] = (Setting_Var[S_P8_V14] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V15_X1,P8_DEF_V15_X2) && TouchMatching(y,P8_DEF_V15_Y1,P8_DEF_V15_Y2)){
		if(!Setting_Var[S_P8_V15]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (33).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (37).png"); // Dis
		ui->P8_B11_V2->setPixmap(qp);

		Setting_Var[S_P8_V15] = (Setting_Var[S_P8_V15] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V16_X1,P8_DEF_V16_X2) && TouchMatching(y,P8_DEF_V16_Y1,P8_DEF_V16_Y2)){
		if(!Setting_Var[S_P8_V16]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (19).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (36).png"); // Dis
		ui->P8_B12_V2->setPixmap(qp);

		Setting_Var[S_P8_V16] = (Setting_Var[S_P8_V16] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V17_X1,P8_DEF_V17_X2) && TouchMatching(y,P8_DEF_V17_Y1,P8_DEF_V17_Y2)){
		if(!Setting_Var[S_P8_V17]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (21).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (35).png"); // Dis
		ui->P8_B13_V2->setPixmap(qp);

		Setting_Var[S_P8_V17] = (Setting_Var[S_P8_V17] + 1) % 2;
	}

	else if(TouchMatching(x,P8_DEF_V18_X1,P8_DEF_V18_X2) && TouchMatching(y,P8_DEF_V18_Y1,P8_DEF_V18_Y2)){
		if(Setting_Var[S_P8_V18]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B9->setPixmap(qp);

		if(Setting_Var[S_P8_V18]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
		ui->P8_B9_V1->setPixmap(qp);

		Setting_Var[S_P8_V18] = (Setting_Var[S_P8_V18] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V19_X1,P8_DEF_V19_X2) && TouchMatching(y,P8_DEF_V19_Y1,P8_DEF_V19_Y2)){
		if(Setting_Var[S_P8_V19]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B10->setPixmap(qp);

		if(Setting_Var[S_P8_V19]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
		ui->P8_B10_V1->setPixmap(qp);

		Setting_Var[S_P8_V19] = (Setting_Var[S_P8_V19] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V20_X1,P8_DEF_V20_X2) && TouchMatching(y,P8_DEF_V20_Y1,P8_DEF_V20_Y2)){
		if(Setting_Var[S_P8_V20]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B11->setPixmap(qp);

		if(Setting_Var[S_P8_V20]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
		ui->P8_B11_V1->setPixmap(qp);

		Setting_Var[S_P8_V20] = (Setting_Var[S_P8_V20] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V21_X1,P8_DEF_V21_X2) && TouchMatching(y,P8_DEF_V21_Y1,P8_DEF_V21_Y2)){
		if(Setting_Var[S_P8_V21]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B12->setPixmap(qp);

		if(Setting_Var[S_P8_V21]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
		ui->P8_B12_V1->setPixmap(qp);

		Setting_Var[S_P8_V21] = (Setting_Var[S_P8_V21] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V22_X1,P8_DEF_V22_X2) && TouchMatching(y,P8_DEF_V22_Y1,P8_DEF_V22_Y2)){
		if(Setting_Var[S_P8_V22]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
		ui->P8_B13->setPixmap(qp);

		if(Setting_Var[S_P8_V22]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
		ui->P8_B13_V1->setPixmap(qp);

		Setting_Var[S_P8_V22] = (Setting_Var[S_P8_V22] + 1) % 2;
	}

	else if(TouchMatching(x,P8_DEF_V23_X1,P8_DEF_V23_X2) && TouchMatching(y,P8_DEF_V23_Y1,P8_DEF_V23_Y2)){
		if(!Setting_Var[S_P8_V23]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (34).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (38).png"); // Dis
		ui->P8_B15->setPixmap(qp);

		Setting_Var[S_P8_V23] = (Setting_Var[S_P8_V23] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V24_X1,P8_DEF_V24_X2) && TouchMatching(y,P8_DEF_V24_Y1,P8_DEF_V24_Y2)){
		if(!Setting_Var[S_P8_V24]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (33).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (28).png"); // Dis
		ui->P8_B16->setPixmap(qp);

		Setting_Var[S_P8_V24] = (Setting_Var[S_P8_V24] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V25_X1,P8_DEF_V25_X2) && TouchMatching(y,P8_DEF_V25_Y1,P8_DEF_V25_Y2)){
		if(!Setting_Var[S_P8_V25]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (32).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (29).png"); // Dis
		ui->P8_B17->setPixmap(qp);

		Setting_Var[S_P8_V25] = (Setting_Var[S_P8_V25] + 1) % 2;
	}
	else if(TouchMatching(x,P8_DEF_V26_X1,P8_DEF_V26_X2) && TouchMatching(y,P8_DEF_V26_Y1,P8_DEF_V26_Y2)){
		if(!Setting_Var[S_P8_V26]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (20).png"); // En
		else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (30).png"); // Dis
		ui->P8_B18->setPixmap(qp);

		Setting_Var[S_P8_V26] = (Setting_Var[S_P8_V26] + 1) % 2;
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

#define P9_B1_X1	170
#define P9_B1_Y1	160
#define P9_B1_X2	220
#define P9_B1_Y2	250

#define P9_B2_X1	370
#define P9_B2_Y1	160
#define P9_B2_X2	420
#define P9_B2_Y2	250

#define P9_B3_X1	170
#define P9_B3_Y1	260
#define P9_B3_X2	220
#define P9_B3_Y2	350

#define P9_B4_X1	370
#define P9_B4_Y1	260
#define P9_B4_X2	420
#define P9_B4_Y2	350

#define P9_B5_X1	170
#define P9_B5_Y1	360
#define P9_B5_X2	220
#define P9_B5_Y2	450

#define P9_B6_X1	370
#define P9_B6_Y1	360
#define P9_B6_X2	420
#define P9_B6_Y2	450

#define P9_B7_X1	480
#define P9_B7_Y1	160
#define P9_B7_X2	530
#define P9_B7_Y2	250

#define P9_B8_X1	680
#define P9_B8_Y1	160
#define P9_B8_X2	730
#define P9_B8_Y2	250

#define P9_B9_X1	480
#define P9_B9_Y1	260
#define P9_B9_X2	530
#define P9_B9_Y2	350

#define P9_B10_X1	680
#define P9_B10_Y1	260
#define P9_B10_X2	730
#define P9_B10_Y2	350

#define P9_B11_X1	480
#define P9_B11_Y1	360
#define P9_B11_X2	530
#define P9_B11_Y2	450

#define P9_B12_X1	680
#define P9_B12_Y1	360
#define P9_B12_X2	730
#define P9_B12_Y2	450


	QString mm;
	int tempN;
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
		char uc_temptemp[108] = {
						0x44,0x33,0x02,0x00,0x01,0x00,0x00,0x43
					};
		uint i, scnt;
		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x33;
		uc_temptemp[scnt++] = 100;
		for(i=0;i<50;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x34;
		uc_temptemp[scnt++] = 100;
		for(i=50;i<100;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		Select_Window(WIN_1);
	}
	else if(TouchMatching(x,P9_DEF_EXIT_X1,P9_DEF_EXIT_X2) && TouchMatching(y,P9_DEF_EXIT_Y1,P9_DEF_EXIT_Y2)){
		for(int i=0;i<MAX_SET_DEFINE;i++){
			Setting_Var[i] = backSetting_Var[i];
		}
		Select_Window(WIN_1);
	}

	
	
	else if(TouchMatching(x,P9_B1_X1,P9_B1_X2) && TouchMatching(y,P9_B1_Y1,P9_B1_Y2)){
		tempN = set_ym/100;
		if((tempN-1) <= 1) tempN = 1;
		
		set_ym = (tempN*100) + (set_ym%100);
		mm.sprintf("20%d",tempN);
		ui->P9_ValYear->setText(mm);
	}
	else if(TouchMatching(x,P9_B2_X1,P9_B2_X2) && TouchMatching(y,P9_B2_Y1,P9_B2_Y2)){
		tempN = set_ym/100;
		if((tempN+1) >= 100) tempN = 99;
		
		set_ym = (tempN*100) + (set_ym%100);
		mm.sprintf("20%d",tempN);
		ui->P9_ValYear->setText(mm);
	}

	else if(TouchMatching(x,P9_B3_X1,P9_B3_X2) && TouchMatching(y,P9_B3_Y1,P9_B3_Y2)){
		tempN = set_ym%100;
		if((tempN-1) <= 1) tempN = 1;
		
		set_ym = ((set_ym/100)*100) + (tempN%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValMonth->setText(mm);
	}
	else if(TouchMatching(x,P9_B4_X1,P9_B4_X2) && TouchMatching(y,P9_B4_Y1,P9_B4_Y2)){
		tempN = set_ym%100;
		if((tempN+1) >= 12) tempN = 12;
		
		set_ym = ((set_ym/100)*100) + (tempN%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValMonth->setText(mm);
	}

	else if(TouchMatching(x,P9_B5_X1,P9_B5_X2) && TouchMatching(y,P9_B5_Y1,P9_B5_Y2)){
		tempN = set_dh/100;
		if((tempN-1) <= 1) tempN = 1;
		
		set_dh = (tempN*100) + (set_dh%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValDay->setText(mm);
	}
	else if(TouchMatching(x,P9_B6_X1,P9_B6_X2) && TouchMatching(y,P9_B6_Y1,P9_B6_Y2)){
		tempN = set_dh/100;
		if((tempN+1) >= 31) tempN = 31;
		
		set_dh = (tempN*100) + (set_dh%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValDay->setText(mm);
	}


	

	else if(TouchMatching(x,P9_B7_X1,P9_B7_X2) && TouchMatching(y,P9_B7_Y1,P9_B7_Y2)){
		tempN = set_dh%100;
		if((tempN-1) <= 0) tempN = 0;
		
		set_dh = ((set_dh/100)*100) + (tempN%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValHour->setText(mm);
	}
	else if(TouchMatching(x,P9_B8_X1,P9_B8_X2) && TouchMatching(y,P9_B8_Y1,P9_B8_Y2)){
		tempN = set_dh%100;
		if((tempN+1) >= 23) tempN = 23;
		
		set_dh = ((set_dh/100)*100) + (tempN%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValHour->setText(mm);
	}

	else if(TouchMatching(x,P9_B9_X1,P9_B9_X2) && TouchMatching(y,P9_B9_Y1,P9_B9_Y2)){
		tempN = set_ms/100;
		if((tempN-1) <= 0) tempN = 0;
		
		set_ms = (tempN*100) + (set_ms%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValMinute->setText(mm);
	}
	else if(TouchMatching(x,P9_B10_X1,P9_B10_X2) && TouchMatching(y,P9_B10_Y1,P9_B10_Y2)){
		tempN = set_ms/100;
		if((tempN+1) >= 59) tempN = 59;
		
		set_ms = (tempN*100) + (set_ms%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValMinute->setText(mm);
	}
	else if(TouchMatching(x,P9_B11_X1,P9_B11_X2) && TouchMatching(y,P9_B11_Y1,P9_B11_Y2)){
		tempN = set_ms%100;
		if((tempN-1) <= 0) tempN = 0;
		
		set_ms = ((set_ms/100)*100) + (tempN%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValSecond->setText(mm);
	}
	else if(TouchMatching(x,P9_B12_X1,P9_B12_X2) && TouchMatching(y,P9_B12_Y1,P9_B12_Y2)){
		tempN = set_ms%100;
		if((tempN+1) >= 59) tempN = 59;
		
		set_ms = ((set_ms/100)*100) + (tempN%100);
		mm.sprintf("%d",tempN);
		ui->P9_ValSecond->setText(mm);
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
		//mm.sprintf("Prev page");
		//QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
		if(P10_PageIndex > 0){
			P10_PageIndex--;

			ShowEventPage();
		}
	}
	else if(TouchMatching(x,P10_DEF_B3_X1,P10_DEF_B3_X2) && TouchMatching(y,P10_DEF_B3_Y1,P10_DEF_B3_Y2)){
		//mm.sprintf("Next page");
		//QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
		if(((P10_LineCnt/9)) > P10_PageIndex){
			if((((P10_LineCnt%9) == 0)) && ((P10_LineCnt/9) == (P10_PageIndex+1))) P10_PageIndex--;
			P10_PageIndex++;

			ShowEventPage();
		} 
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

void MainWindow::TouchProcess_WIN4(int x, int y)
{
#define P4_DEF_B1_X1	100
#define P4_DEF_B1_Y1	170
#define P4_DEF_B1_X2	(P4_DEF_B1_X1+60)
#define P4_DEF_B1_Y2	(P4_DEF_B1_Y1+22)

#define P4_DEF_B2_X1	190
#define P4_DEF_B2_Y1	170
#define P4_DEF_B2_X2	(P4_DEF_B2_X1+60)
#define P4_DEF_B2_Y2	(P4_DEF_B2_Y1+22)

#define P4_DEF_B3_X1	280
#define P4_DEF_B3_Y1	170
#define P4_DEF_B3_X2	(P4_DEF_B3_X1+60)
#define P4_DEF_B3_Y2	(P4_DEF_B3_Y1+22)

#define P4_DEF_B4_X1	100
#define P4_DEF_B4_Y1	204
#define P4_DEF_B4_X2	(P4_DEF_B4_X1+60)
#define P4_DEF_B4_Y2	(P4_DEF_B4_Y1+22)

#define P4_DEF_B5_X1	190
#define P4_DEF_B5_Y1	204
#define P4_DEF_B5_X2	(P4_DEF_B5_X1+60)
#define P4_DEF_B5_Y2	(P4_DEF_B5_Y1+22)

#define P4_DEF_B6_X1	280
#define P4_DEF_B6_Y1	204
#define P4_DEF_B6_X2	(P4_DEF_B6_X1+60)
#define P4_DEF_B6_Y2	(P4_DEF_B6_Y1+22)

#define P4_DEF_B7_X1	100
#define P4_DEF_B7_Y1	239
#define P4_DEF_B7_X2	(P4_DEF_B7_X1+60)
#define P4_DEF_B7_Y2	(P4_DEF_B7_Y1+22)

#define P4_DEF_B8_X1	190
#define P4_DEF_B8_Y1	239
#define P4_DEF_B8_X2	(P4_DEF_B8_X1+60)
#define P4_DEF_B8_Y2	(P4_DEF_B8_Y1+22)

#define P4_DEF_B9_X1	280
#define P4_DEF_B9_Y1	239
#define P4_DEF_B9_X2	(P4_DEF_B9_X1+60)
#define P4_DEF_B9_Y2	(P4_DEF_B9_Y1+22)



#define P4_DEF_B10_X1	80
#define P4_DEF_B10_Y1	297
#define P4_DEF_B10_X2	(P4_DEF_B10_X1+60)
#define P4_DEF_B10_Y2	(P4_DEF_B10_Y1+22)

#define P4_DEF_B11_X1	150
#define P4_DEF_B11_Y1	297
#define P4_DEF_B11_X2	(P4_DEF_B11_X1+60)
#define P4_DEF_B11_Y2	(P4_DEF_B11_Y1+22)

#define P4_DEF_B12_X1	220
#define P4_DEF_B12_Y1	297
#define P4_DEF_B12_X2	(P4_DEF_B12_X1+60)
#define P4_DEF_B12_Y2	(P4_DEF_B12_Y1+22)

#define P4_DEF_B13_X1	290
#define P4_DEF_B13_Y1	297
#define P4_DEF_B13_X2	(P4_DEF_B13_X1+60)
#define P4_DEF_B13_Y2	(P4_DEF_B13_Y1+22)

#define P4_DEF_B14_X1	80
#define P4_DEF_B14_Y1	337
#define P4_DEF_B14_X2	(P4_DEF_B14_X1+60)
#define P4_DEF_B14_Y2	(P4_DEF_B14_Y1+22)

#define P4_DEF_B15_X1	150
#define P4_DEF_B15_Y1	337
#define P4_DEF_B15_X2	(P4_DEF_B15_X1+60)
#define P4_DEF_B15_Y2	(P4_DEF_B15_Y1+22)

#define P4_DEF_B16_X1	220
#define P4_DEF_B16_Y1	337
#define P4_DEF_B16_X2	(P4_DEF_B16_X1+60)
#define P4_DEF_B16_Y2	(P4_DEF_B16_Y1+22)

#define P4_DEF_B17_X1	290
#define P4_DEF_B17_Y1	337
#define P4_DEF_B17_X2	(P4_DEF_B17_X1+60)
#define P4_DEF_B17_Y2	(P4_DEF_B17_Y1+22)

#define P4_DEF_B18_X1	80
#define P4_DEF_B18_Y1	377
#define P4_DEF_B18_X2	(P4_DEF_B18_X1+60)
#define P4_DEF_B18_Y2	(P4_DEF_B18_Y1+22)

#define P4_DEF_B19_X1	150
#define P4_DEF_B19_Y1	377
#define P4_DEF_B19_X2	(P4_DEF_B19_X1+60)
#define P4_DEF_B19_Y2	(P4_DEF_B19_Y1+22)

#define P4_DEF_B20_X1	220
#define P4_DEF_B20_Y1	377
#define P4_DEF_B20_X2	(P4_DEF_B20_X1+60)
#define P4_DEF_B20_Y2	(P4_DEF_B20_Y1+22)

#define P4_DEF_B21_X1	290
#define P4_DEF_B21_Y1	377
#define P4_DEF_B21_X2	(P4_DEF_B21_X1+60)
#define P4_DEF_B21_Y2	(P4_DEF_B21_Y1+22)

#define P4_DEF_B22_X1	80
#define P4_DEF_B22_Y1	417
#define P4_DEF_B22_X2	(P4_DEF_B22_X1+60)
#define P4_DEF_B22_Y2	(P4_DEF_B22_Y1+22)

#define P4_DEF_B23_X1	150
#define P4_DEF_B23_Y1	417
#define P4_DEF_B23_X2	(P4_DEF_B23_X1+60)
#define P4_DEF_B23_Y2	(P4_DEF_B23_Y1+22)

#define P4_DEF_B24_X1	220
#define P4_DEF_B24_Y1	417
#define P4_DEF_B24_X2	(P4_DEF_B24_X1+60)
#define P4_DEF_B24_Y2	(P4_DEF_B24_Y1+22)

#define P4_DEF_B25_X1	290
#define P4_DEF_B25_Y1	417
#define P4_DEF_B25_X2	(P4_DEF_B25_X1+60)
#define P4_DEF_B25_Y2	(P4_DEF_B25_Y1+22)



#define P4_DEF_B26_X1	500
#define P4_DEF_B26_Y1	166
#define P4_DEF_B26_X2	(P4_DEF_B26_X1+82)
#define P4_DEF_B26_Y2	(P4_DEF_B26_Y1+42)

#define P4_DEF_B27_X1	500
#define P4_DEF_B27_Y1	270
#define P4_DEF_B27_X2	(P4_DEF_B27_X1+82)
#define P4_DEF_B27_Y2	(P4_DEF_B27_Y1+42)

#define P4_DEF_B28_X1	500
#define P4_DEF_B28_Y1	370
#define P4_DEF_B28_X2	(P4_DEF_B28_X1+82)
#define P4_DEF_B28_Y2	(P4_DEF_B28_Y1+42)



#define P4_DEF_DEFAULT_X1	520
#define P4_DEF_DEFAULT_Y1	93
#define P4_DEF_DEFAULT_X2	623
#define P4_DEF_DEFAULT_Y2	118

#define P4_DEF_SAVE_X1	631
#define P4_DEF_SAVE_Y1	93
#define P4_DEF_SAVE_X2	706
#define P4_DEF_SAVE_Y2	118

#define P4_DEF_EXIT_X1	718
#define P4_DEF_EXIT_Y1	93
#define P4_DEF_EXIT_X2	790
#define P4_DEF_EXIT_Y2	118

	int nVal;
	int nVal2;
	QString mm;
	QPoint qpAppNewLoc;

	if(TouchMatching(x,P4_DEF_B1_X1,P4_DEF_B1_X2) && TouchMatching(y,P4_DEF_B1_Y1,P4_DEF_B1_Y2)){
		Setting_Var[S_P4_V4] = 0;
	}
	else if(TouchMatching(x,P4_DEF_B2_X1,P4_DEF_B2_X2) && TouchMatching(y,P4_DEF_B2_Y1,P4_DEF_B2_Y2)){
		Setting_Var[S_P4_V4] = 1;
	}
	else if(TouchMatching(x,P4_DEF_B3_X1,P4_DEF_B3_X2) && TouchMatching(y,P4_DEF_B3_Y1,P4_DEF_B3_Y2)){
		Setting_Var[S_P4_V4] = 2;
	}
	else if(TouchMatching(x,P4_DEF_B4_X1,P4_DEF_B4_X2) && TouchMatching(y,P4_DEF_B4_Y1,P4_DEF_B4_Y2)){
		Setting_Var[S_P4_V4] = 3;
	}
	else if(TouchMatching(x,P4_DEF_B5_X1,P4_DEF_B5_X2) && TouchMatching(y,P4_DEF_B5_Y1,P4_DEF_B5_Y2)){
		Setting_Var[S_P4_V4] = 4;
	}
	else if(TouchMatching(x,P4_DEF_B6_X1,P4_DEF_B6_X2) && TouchMatching(y,P4_DEF_B6_Y1,P4_DEF_B6_Y2)){
		Setting_Var[S_P4_V4] = 5;
	}
	else if(TouchMatching(x,P4_DEF_B7_X1,P4_DEF_B7_X2) && TouchMatching(y,P4_DEF_B7_Y1,P4_DEF_B7_Y2)){
		Setting_Var[S_P4_V4] = 6;
	}
	else if(TouchMatching(x,P4_DEF_B8_X1,P4_DEF_B8_X2) && TouchMatching(y,P4_DEF_B8_Y1,P4_DEF_B8_Y2)){
		Setting_Var[S_P4_V4] = 7;
	}
	else if(TouchMatching(x,P4_DEF_B9_X1,P4_DEF_B9_X2) && TouchMatching(y,P4_DEF_B9_Y1,P4_DEF_B9_Y2)){
		Setting_Var[S_P4_V4] = 8;
	}

	else if(TouchMatching(x,P4_DEF_B10_X1,P4_DEF_B10_X2) && TouchMatching(y,P4_DEF_B10_Y1,P4_DEF_B10_Y2)){
		Setting_Var[S_P4_V5] = 0;
	}
	else if(TouchMatching(x,P4_DEF_B11_X1,P4_DEF_B11_X2) && TouchMatching(y,P4_DEF_B11_Y1,P4_DEF_B11_Y2)){
		Setting_Var[S_P4_V5] = 1;
	}
	else if(TouchMatching(x,P4_DEF_B12_X1,P4_DEF_B12_X2) && TouchMatching(y,P4_DEF_B12_Y1,P4_DEF_B12_Y2)){
		Setting_Var[S_P4_V5] = 2;
	}
	else if(TouchMatching(x,P4_DEF_B13_X1,P4_DEF_B13_X2) && TouchMatching(y,P4_DEF_B13_Y1,P4_DEF_B13_Y2)){
		Setting_Var[S_P4_V5] = 3;
	}
	else if(TouchMatching(x,P4_DEF_B14_X1,P4_DEF_B14_X2) && TouchMatching(y,P4_DEF_B14_Y1,P4_DEF_B14_Y2)){
		Setting_Var[S_P4_V5] = 4;
	}
	else if(TouchMatching(x,P4_DEF_B15_X1,P4_DEF_B15_X2) && TouchMatching(y,P4_DEF_B15_Y1,P4_DEF_B15_Y2)){
		Setting_Var[S_P4_V5] = 5;
	}
	else if(TouchMatching(x,P4_DEF_B16_X1,P4_DEF_B16_X2) && TouchMatching(y,P4_DEF_B16_Y1,P4_DEF_B16_Y2)){
		Setting_Var[S_P4_V5] = 6;
	}
	else if(TouchMatching(x,P4_DEF_B17_X1,P4_DEF_B17_X2) && TouchMatching(y,P4_DEF_B17_Y1,P4_DEF_B17_Y2)){
		Setting_Var[S_P4_V5] = 7;
	}
	else if(TouchMatching(x,P4_DEF_B18_X1,P4_DEF_B18_X2) && TouchMatching(y,P4_DEF_B18_Y1,P4_DEF_B18_Y2)){
		Setting_Var[S_P4_V5] = 8;
	}
	else if(TouchMatching(x,P4_DEF_B19_X1,P4_DEF_B19_X2) && TouchMatching(y,P4_DEF_B19_Y1,P4_DEF_B19_Y2)){
		Setting_Var[S_P4_V5] = 9;
	}
	else if(TouchMatching(x,P4_DEF_B20_X1,P4_DEF_B20_X2) && TouchMatching(y,P4_DEF_B20_Y1,P4_DEF_B20_Y2)){
		Setting_Var[S_P4_V5] = 10;
	}
	else if(TouchMatching(x,P4_DEF_B21_X1,P4_DEF_B21_X2) && TouchMatching(y,P4_DEF_B21_Y1,P4_DEF_B21_Y2)){
		Setting_Var[S_P4_V5] = 11;
	}
	else if(TouchMatching(x,P4_DEF_B22_X1,P4_DEF_B22_X2) && TouchMatching(y,P4_DEF_B22_Y1,P4_DEF_B22_Y2)){
		Setting_Var[S_P4_V5] = 12;
	}
	else if(TouchMatching(x,P4_DEF_B23_X1,P4_DEF_B23_X2) && TouchMatching(y,P4_DEF_B23_Y1,P4_DEF_B23_Y2)){
		Setting_Var[S_P4_V5] = 13;
	}
	else if(TouchMatching(x,P4_DEF_B24_X1,P4_DEF_B24_X2) && TouchMatching(y,P4_DEF_B24_Y1,P4_DEF_B24_Y2)){
		Setting_Var[S_P4_V5] = 14;
	}
	else if(TouchMatching(x,P4_DEF_B25_X1,P4_DEF_B25_X2) && TouchMatching(y,P4_DEF_B25_Y1,P4_DEF_B25_Y2)){
		Setting_Var[S_P4_V5] = 15;
	}

	
	else if(TouchMatching(x,P4_DEF_B26_X1,P4_DEF_B26_X2) && TouchMatching(y,P4_DEF_B26_Y1,P4_DEF_B26_Y2)){
		Setting_Var[S_P4_V1] = 30000;
		nVal = int(((Setting_Var[S_P4_V1])*(745-590))/30000+590);
		nVal2 = ui->P4_Set1->y();
		qpAppNewLoc.setX(nVal);
		qpAppNewLoc.setY(nVal2);
		ui->P4_Set1->setProperty("pos", qpAppNewLoc);
		mm.sprintf("%d",Setting_Var[S_P4_V1]);
		qpAppNewLoc.setX(nVal-30);
		qpAppNewLoc.setY(nVal2-20);
		ui->P4_Set1_T->setProperty("pos", qpAppNewLoc);
		ui->P4_Set1_T->setText(mm);

	}
	else if(TouchMatching(x,P4_DEF_B27_X1,P4_DEF_B27_X2) && TouchMatching(y,P4_DEF_B27_Y1,P4_DEF_B27_Y2)){
		Setting_Var[S_P4_V2] = 30000;
		nVal = int(((Setting_Var[S_P4_V2])*(745-590))/30000+590);
		nVal2 = ui->P4_Set2->y();
		qpAppNewLoc.setX(nVal);
		qpAppNewLoc.setY(nVal2);
		ui->P4_Set2->setProperty("pos", qpAppNewLoc);
		mm.sprintf("%d",Setting_Var[S_P4_V2]);
		qpAppNewLoc.setX(nVal-30);
		qpAppNewLoc.setY(nVal2-20);
		ui->P4_Set2_T->setProperty("pos", qpAppNewLoc);
		ui->P4_Set2_T->setText(mm);

	}
	else if(TouchMatching(x,P4_DEF_B28_X1,P4_DEF_B28_X2) && TouchMatching(y,P4_DEF_B28_Y1,P4_DEF_B28_Y2)){
		Setting_Var[S_P4_V3] = 30000;
		nVal = int(((Setting_Var[S_P4_V3])*(745-590))/30000+590);
		nVal2 = ui->P4_Set3->y();
		qpAppNewLoc.setX(nVal);
		qpAppNewLoc.setY(nVal2);
		ui->P4_Set3->setProperty("pos", qpAppNewLoc);
		mm.sprintf("%d",Setting_Var[S_P4_V3]);
		qpAppNewLoc.setX(nVal-30);
		qpAppNewLoc.setY(nVal2-20);
		ui->P4_Set3_T->setProperty("pos", qpAppNewLoc);
		ui->P4_Set3_T->setText(mm);
	}

	
	else if(TouchMatching(x,P4_DEF_DEFAULT_X1,P4_DEF_DEFAULT_X2) && TouchMatching(y,P4_DEF_DEFAULT_Y1,P4_DEF_DEFAULT_Y2)){
		mm.sprintf("Default");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
	}
	else if(TouchMatching(x,P4_DEF_SAVE_X1,P4_DEF_SAVE_X2) && TouchMatching(y,P4_DEF_SAVE_Y1,P4_DEF_SAVE_Y2)){
		mm.sprintf("save");
		QMessageBox::critical(this, "SERIAL PORT NOT CONNECTED", mm);
		char uc_temptemp[108] = {
				0x44,0x33,0x02,0x00,0x01,0x00,0x00,0x43
			};
		uint i, scnt;
		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x33;
		uc_temptemp[scnt++] = 100;
		for(i=0;i<50;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);

		scnt = 0;
		uc_temptemp[scnt++] = 0x44;
		uc_temptemp[scnt++] = 0x34;
		uc_temptemp[scnt++] = 100;
		for(i=50;i<100;i++){
			uc_temptemp[scnt++] = Setting_Var[i]/256;
			uc_temptemp[scnt++] = Setting_Var[i]%256;
		}
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0;
		uc_temptemp[scnt++] = 0x43;

		m_send.clear();
		m_send.setRawData(uc_temptemp,scnt);

		m_port->write(m_send,m_send.size());
		m_port->waitForBytesWritten(1000);
		
		Select_Window(WIN_1);
	}
	else if(TouchMatching(x,P4_DEF_EXIT_X1,P4_DEF_EXIT_X2) && TouchMatching(y,P4_DEF_EXIT_Y1,P4_DEF_EXIT_Y2)){
		for(int i=0;i<MAX_SET_DEFINE;i++){
			Setting_Var[i] = backSetting_Var[i];
		}
		Select_Window(WIN_1);
	}

	

	QPixmap qp;

	qp = QPixmap(P4_V_STRList[0]);
	ui->P4_BT_1->setPixmap(qp);
	qp = QPixmap(P4_V_STRList[2]);
	ui->P4_BT_2->setPixmap(qp);
	qp = QPixmap(P4_V_STRList[4]);
	ui->P4_BT_3->setPixmap(qp);
	qp = QPixmap(P4_V_STRList[6]);
	ui->P4_BT_4->setPixmap(qp);
	qp = QPixmap(P4_V_STRList[8]);
	ui->P4_BT_5->setPixmap(qp);
	qp = QPixmap(P4_V_STRList[10]);
	ui->P4_BT_6->setPixmap(qp);
	qp = QPixmap(P4_V_STRList[12]);
	ui->P4_BT_7->setPixmap(qp);
	qp = QPixmap(P4_V_STRList[14]);
	ui->P4_BT_8->setPixmap(qp);
	qp = QPixmap(P4_V_STRList[16]);
	ui->P4_BT_9->setPixmap(qp);

	switch(Setting_Var[S_P4_V4]){
	case 0:
		qp = QPixmap(P4_V_STRList[1]);
		ui->P4_BT_1->setPixmap(qp);
	break;
	case 1:
		qp = QPixmap(P4_V_STRList[3]);
		ui->P4_BT_2->setPixmap(qp);
	break;
	case 2:
		qp = QPixmap(P4_V_STRList[5]);
		ui->P4_BT_3->setPixmap(qp);
	break;
	case 3:
		qp = QPixmap(P4_V_STRList[7]);
		ui->P4_BT_4->setPixmap(qp);
	break;
	case 4:
		qp = QPixmap(P4_V_STRList[9]);
		ui->P4_BT_5->setPixmap(qp);
	break;
	case 5:
		qp = QPixmap(P4_V_STRList[11]);
		ui->P4_BT_6->setPixmap(qp);
	break;
	case 6:
		qp = QPixmap(P4_V_STRList[13]);
		ui->P4_BT_7->setPixmap(qp);
	break;
	case 7:
		qp = QPixmap(P4_V_STRList[15]);
		ui->P4_BT_8->setPixmap(qp);
	break;
	case 8:
		qp = QPixmap(P4_V_STRList[17]);
		ui->P4_BT_9->setPixmap(qp);
	break;
	}


	qp = QPixmap(P4_KW_STRList[0]);
	ui->P4_BT2_1->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[2]);
	ui->P4_BT2_2->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[4]);
	ui->P4_BT2_3->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[6]);
	ui->P4_BT2_4->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[0]);
	ui->P4_BT3_1->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[2]);
	ui->P4_BT3_2->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[4]);
	ui->P4_BT3_3->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[6]);
	ui->P4_BT3_4->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[0]);
	ui->P4_BT4_1->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[2]);
	ui->P4_BT4_2->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[4]);
	ui->P4_BT4_3->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[6]);
	ui->P4_BT4_4->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[0]);
	ui->P4_BT5_1->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[2]);
	ui->P4_BT5_2->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[4]);
	ui->P4_BT5_3->setPixmap(qp);
	qp = QPixmap(P4_KW_STRList[6]);
	ui->P4_BT5_4->setPixmap(qp);

	switch(Setting_Var[S_P4_V5]){
	case 0:
		qp = QPixmap(P4_KW_STRList[1]);
		ui->P4_BT2_1->setPixmap(qp);
	break;
	case 1:
		qp = QPixmap(P4_KW_STRList[3]);
		ui->P4_BT2_2->setPixmap(qp);
	break;
	case 2:
		qp = QPixmap(P4_KW_STRList[5]);
		ui->P4_BT2_3->setPixmap(qp);
	break;
	case 3:
		qp = QPixmap(P4_KW_STRList[7]);
		ui->P4_BT2_4->setPixmap(qp);
	break;
	case 4:
		qp = QPixmap(P4_KW_STRList[1]);
		ui->P4_BT3_1->setPixmap(qp);
	break;
	case 5:
		qp = QPixmap(P4_KW_STRList[3]);
		ui->P4_BT3_2->setPixmap(qp);
	break;
	case 6:
		qp = QPixmap(P4_KW_STRList[5]);
		ui->P4_BT3_3->setPixmap(qp);
	break;
	case 7:
		qp = QPixmap(P4_KW_STRList[7]);
		ui->P4_BT3_4->setPixmap(qp);
	break;
	case 8:
		qp = QPixmap(P4_KW_STRList[1]);
		ui->P4_BT4_1->setPixmap(qp);
	break;
	case 9:
		qp = QPixmap(P4_KW_STRList[3]);
		ui->P4_BT4_2->setPixmap(qp);
	break;
	case 10:
		qp = QPixmap(P4_KW_STRList[5]);
		ui->P4_BT4_3->setPixmap(qp);
	break;
	case 11:
		qp = QPixmap(P4_KW_STRList[7]);
		ui->P4_BT4_4->setPixmap(qp);
	break;
	case 12:
		qp = QPixmap(P4_KW_STRList[1]);
		ui->P4_BT5_1->setPixmap(qp);
	break;
	case 13:
		qp = QPixmap(P4_KW_STRList[3]);
		ui->P4_BT5_2->setPixmap(qp);
	break;
	case 14:
		qp = QPixmap(P4_KW_STRList[5]);
		ui->P4_BT5_3->setPixmap(qp);
	break;
	case 15:
		qp = QPixmap(P4_KW_STRList[7]);
		ui->P4_BT5_4->setPixmap(qp);
	break;
	}

}

void MainWindow::ChangeWindow_WIN1(void)
{
	QString m;

	// change scale.. temp 0 - 200 => range 0 - 144


	switch(Setting_Var[S_P5_V1]){
	case T_NONE	:
		ui->P1_ValMotor1_2->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P1_ValMotor1_2->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V8]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V7]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P1_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V8]));
		ui->P1_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P1_Motor1->setFixedWidth(P1_M1Val);
		ui->P1_Motor1_2->move(100+P1_M1Val,165);
		ui->P1_ValMotor1_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P1_ValMotor1_2->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V8]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V7]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P1_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V8]));
		ui->P1_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P1_Motor1->setFixedWidth(P1_M1Val);
		ui->P1_Motor1_2->move(100+P1_M1Val,165);

		ui->P1_ValMotor1_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P1_ValMotor1_2->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V8]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V7]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P1_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V8]));
		ui->P1_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P1_Motor1->setFixedWidth(P1_M1Val);
		ui->P1_Motor1_2->move(100+P1_M1Val,165);

		ui->P1_ValMotor1_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P1_ValMotor1_2->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V8]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V7]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P1_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V8]));
		ui->P1_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P1_Motor1->setFixedWidth(P1_M1Val);
		ui->P1_Motor1_2->move(100+P1_M1Val,165);

		ui->P1_ValMotor1_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P1_ValMotor1_2->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V8]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V7]) ui->P1_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P1_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V8]));
		ui->P1_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P1_Motor1->setFixedWidth(P1_M1Val);
		ui->P1_Motor1_2->move(100+P1_M1Val,165);
		
		ui->P1_ValMotor1_1->setText("베어링 하");
	break;
	}

	
	switch(Setting_Var[S_P5_V2]){
	case T_NONE	:
		ui->P1_ValMotor2_2->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P1_ValMotor2_2->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V11]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V10]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P1_ValMotor2->setText(m);
		
		P1_M2Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V11]));
		ui->P1_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P1_Motor2->setFixedWidth(P1_M2Val);
		ui->P1_Motor2_2->move(100+P1_M2Val,233);

		ui->P1_ValMotor2_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P1_ValMotor2_2->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V11]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V10]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P1_ValMotor2->setText(m);
		
		P1_M2Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V11]));
		ui->P1_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P1_Motor2->setFixedWidth(P1_M2Val);
		ui->P1_Motor2_2->move(100+P1_M2Val,233);

		ui->P1_ValMotor2_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P1_ValMotor2_2->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V11]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V10]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P1_ValMotor2->setText(m);
		
		P1_M2Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V11]));
		ui->P1_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P1_Motor2->setFixedWidth(P1_M2Val);
		ui->P1_Motor2_2->move(100+P1_M2Val,233);

		ui->P1_ValMotor2_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P1_ValMotor2_2->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V11]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V10]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P1_ValMotor2->setText(m);
		
		P1_M2Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V11]));
		ui->P1_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P1_Motor2->setFixedWidth(P1_M2Val);
		ui->P1_Motor2_2->move(100+P1_M2Val,233);

		ui->P1_ValMotor2_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P1_ValMotor2_2->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V11]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V10]) ui->P1_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P1_ValMotor2->setText(m);
		
		P1_M2Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V11]));
		ui->P1_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P1_Motor2->setFixedWidth(P1_M2Val);
		ui->P1_Motor2_2->move(100+P1_M2Val,233);

		ui->P1_ValMotor2_1->setText("베어링 하");
	break;
	}

	
	switch(Setting_Var[S_P5_V3]){
	case T_NONE	:
		ui->P1_ValMotor3_2->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P1_ValMotor3_2->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V14]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V13]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P1_ValMotor3->setText(m);
		
		P1_M3Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V14]));
		ui->P1_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P1_Motor3->setFixedWidth(P1_M3Val);
		ui->P1_Motor3_2->move(100+P1_M3Val,300);

		ui->P1_ValMotor3_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P1_ValMotor3_2->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V14]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V13]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P1_ValMotor3->setText(m);
		
		P1_M3Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V14]));
		ui->P1_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P1_Motor3->setFixedWidth(P1_M3Val);
		ui->P1_Motor3_2->move(100+P1_M3Val,300);

		ui->P1_ValMotor3_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P1_ValMotor3_2->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V14]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V13]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P1_ValMotor3->setText(m);
		
		P1_M3Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V14]));
		ui->P1_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P1_Motor3->setFixedWidth(P1_M3Val);
		ui->P1_Motor3_2->move(100+P1_M3Val,300);

		ui->P1_ValMotor3_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P1_ValMotor3_2->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V14]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V13]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P1_ValMotor3->setText(m);
		
		P1_M3Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V14]));
		ui->P1_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P1_Motor3->setFixedWidth(P1_M3Val);
		ui->P1_Motor3_2->move(100+P1_M3Val,300);

		ui->P1_ValMotor3_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P1_ValMotor3_2->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V14]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V13]) ui->P1_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P1_ValMotor3->setText(m);
		
		P1_M3Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V14]));
		ui->P1_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P1_Motor3->setFixedWidth(P1_M3Val);
		ui->P1_Motor3_2->move(100+P1_M3Val,300);

		ui->P1_ValMotor3_1->setText("베어링 하");
	break;
	}

	
	switch(Setting_Var[S_P5_V4]){
	case T_NONE	:
		ui->P1_ValBR1_2->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P1_ValBR1_2->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V17]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V16]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P1_ValBR1->setText(m);
		
		P1_M4Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V17]));
		ui->P1_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P1_Motor4->setFixedWidth(P1_M4Val);
		ui->P1_Motor4_2->move(100+P1_M4Val,366);

		ui->P1_ValBR1_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P1_ValBR1_2->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V17]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V16]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P1_ValBR1->setText(m);
		
		P1_M4Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V17]));
		ui->P1_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P1_Motor4->setFixedWidth(P1_M4Val);
		ui->P1_Motor4_2->move(100+P1_M4Val,366);

		ui->P1_ValBR1_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P1_ValBR1_2->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V17]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V16]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P1_ValBR1->setText(m);
		
		P1_M4Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V17]));
		ui->P1_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P1_Motor4->setFixedWidth(P1_M4Val);
		ui->P1_Motor4_2->move(100+P1_M4Val,366);

		ui->P1_ValBR1_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P1_ValBR1_2->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V17]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V16]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P1_ValBR1->setText(m);
		
		P1_M4Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V17]));
		ui->P1_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P1_Motor4->setFixedWidth(P1_M4Val);
		ui->P1_Motor4_2->move(100+P1_M4Val,366);

		ui->P1_ValBR1_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P1_ValBR1_2->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V17]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V16]) ui->P1_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P1_ValBR1->setText(m);
		
		P1_M4Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V17]));
		ui->P1_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P1_Motor4->setFixedWidth(P1_M4Val);
		ui->P1_Motor4_2->move(100+P1_M4Val,366);

		ui->P1_ValBR1_1->setText("베어링 하");
	break;
	}

	
	switch(Setting_Var[S_P5_V5]){
	case T_NONE	:
		ui->P1_ValBR2_2->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P1_ValBR2_2->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V20]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V19]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P1_ValBR2->setText(m);
		
		P1_M5Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V20]));
		ui->P1_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P1_Motor5->setFixedWidth(P1_M5Val);
		ui->P1_Motor5_2->move(100+P1_M5Val,433);

		ui->P1_ValBR2_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P1_ValBR2_2->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V20]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V19]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P1_ValBR2->setText(m);
		
		P1_M5Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V20]));
		ui->P1_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P1_Motor5->setFixedWidth(P1_M5Val);
		ui->P1_Motor5_2->move(100+P1_M5Val,433);

		ui->P1_ValBR2_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P1_ValBR2_2->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V20]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V19]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P1_ValBR2->setText(m);
		
		P1_M5Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V20]));
		ui->P1_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P1_Motor5->setFixedWidth(P1_M5Val);
		ui->P1_Motor5_2->move(100+P1_M5Val,433);

		ui->P1_ValBR2_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P1_ValBR2_2->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V20]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V19]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P1_ValBR2->setText(m);
		
		P1_M5Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V20]));
		ui->P1_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P1_Motor5->setFixedWidth(P1_M5Val);
		ui->P1_Motor5_2->move(100+P1_M5Val,433);

		ui->P1_ValBR2_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P1_ValBR2_2->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V20]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V19]) ui->P1_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P1_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P1_ValBR2->setText(m);
		
		P1_M5Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V20]));
		ui->P1_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P1_Motor5->setFixedWidth(P1_M5Val);
		ui->P1_Motor5_2->move(100+P1_M5Val,433);

		ui->P1_ValBR2_1->setText("베어링 하");
	break;
	}






	if( ((Setting_Var[S_P6_V2]*10) < Motor_Var[PUMP_M1C]) || ((Setting_Var[S_P6_V4]*10) > Motor_Var[PUMP_M1C]) ){	// 과전류,저전류 ERROR
		ui->P1_ValRCur->setStyleSheet("color:rgb(255,0,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValRCur->setVisible(true);
		}
		else{
			ui->P1_ValRCur->setVisible(false);
		}
	}
	else if( ((Setting_Var[S_P6_V1]*10) < Motor_Var[PUMP_M1C]) || ((Setting_Var[S_P6_V3]*10) > Motor_Var[PUMP_M1C]) ){	// 과전류,저전류 Warning
		ui->P1_ValRCur->setStyleSheet("color:rgb(255,242,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValRCur->setVisible(true);
		}
		else{
			ui->P1_ValRCur->setVisible(false);
		}
	}
	else{
		ui->P1_ValRCur->setVisible(true);
		ui->P1_ValRCur->setStyleSheet("color:rgb(255,255,255)");
	}
	

	if( ((Setting_Var[S_P6_V2]*10) < Motor_Var[PUMP_M2C]) || ((Setting_Var[S_P6_V4]*10) > Motor_Var[PUMP_M2C]) ){	// 과전류,저전류 ERROR
		ui->P1_ValSCur->setStyleSheet("color:rgb(255,0,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValSCur->setVisible(true);
		}
		else{
			ui->P1_ValSCur->setVisible(false);
		}
	}
	else if( ((Setting_Var[S_P6_V1]*10) < Motor_Var[PUMP_M2C]) || ((Setting_Var[S_P6_V3]*10) > Motor_Var[PUMP_M2C]) ){	// 과전류,저전류 Warning
		ui->P1_ValSCur->setStyleSheet("color:rgb(255,242,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValSCur->setVisible(true);
		}
		else{
			ui->P1_ValSCur->setVisible(false);
		}
	}
	else{
		ui->P1_ValSCur->setVisible(true);
		ui->P1_ValSCur->setStyleSheet("color:rgb(255,255,255)");
	}

	
	if( ((Setting_Var[S_P6_V2]*10) < Motor_Var[PUMP_M3C]) || ((Setting_Var[S_P6_V4]*10) > Motor_Var[PUMP_M3C]) ){	// 과전류,저전류 ERROR
		ui->P1_ValTCur->setStyleSheet("color:rgb(255,0,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValTCur->setVisible(true);
		}
		else{
			ui->P1_ValTCur->setVisible(false);
		}
	}
	else if( ((Setting_Var[S_P6_V1]*10) < Motor_Var[PUMP_M3C]) || ((Setting_Var[S_P6_V3]*10) > Motor_Var[PUMP_M3C]) ){	// 과전류,저전류 Warning
		ui->P1_ValTCur->setStyleSheet("color:rgb(255,242,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValTCur->setVisible(true);
		}
		else{
			ui->P1_ValTCur->setVisible(false);
		}
	}
	else{
		ui->P1_ValTCur->setVisible(true);
		ui->P1_ValTCur->setStyleSheet("color:rgb(255,255,255)");
	}
	
	
	if((Setting_Var[S_P6_V2]*10) < Motor_Var[PUMP_OC]){	// 과전류 ERROR
		ui->P1_ValMaxCur->setStyleSheet("color:rgb(255,0,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValMaxCur->setVisible(true);
		}
		else{
			ui->P1_ValMaxCur->setVisible(false);
		}
	}
	else if((Setting_Var[S_P6_V1]*10) < Motor_Var[PUMP_OC]) {	// 과전류 Warning
		ui->P1_ValMaxCur->setStyleSheet("color:rgb(255,242,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValMaxCur->setVisible(true);
		}
		else{
			ui->P1_ValMaxCur->setVisible(false);
		}
	}
	else{
		ui->P1_ValMaxCur->setVisible(true);
		ui->P1_ValMaxCur->setStyleSheet("color:rgb(255,255,255)");
	}
	
	
	if((Setting_Var[S_P6_V4]*10) > Motor_Var[PUMP_UC]){	// 저전류 ERROR
		ui->P1_ValMinCur->setStyleSheet("color:rgb(255,0,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValMinCur->setVisible(true);
		}
		else{
			ui->P1_ValMinCur->setVisible(false);
		}
	}
	else if((Setting_Var[S_P6_V3]*10) > Motor_Var[PUMP_UC]) {	// 저전류 Warning
		ui->P1_ValMinCur->setStyleSheet("color:rgb(255,242,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValMinCur->setVisible(true);
		}
		else{
			ui->P1_ValMinCur->setVisible(false);
		}
	}
	else{
		ui->P1_ValMinCur->setVisible(true);
		ui->P1_ValMinCur->setStyleSheet("color:rgb(255,255,255)");
	}
	
	
	if((Setting_Var[S_P6_V6]*100) < Motor_Var[PUMP_UB]){	// 불평형 ERROR
		ui->P1_ValBP->setStyleSheet("color:rgb(255,0,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValBP->setVisible(true);
		}
		else{
			ui->P1_ValBP->setVisible(false);
		}
	}
	else if((Setting_Var[S_P6_V5]*100) < Motor_Var[PUMP_UC]) {	// 불평형 Warning
		ui->P1_ValBP->setStyleSheet("color:rgb(255,242,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValBP->setVisible(true);
		}
		else{
			ui->P1_ValBP->setVisible(false);
		}
	}
	else{
		ui->P1_ValBP->setVisible(true);
		ui->P1_ValBP->setStyleSheet("color:rgb(255,255,255)");
	}

	if((Setting_Var[S_P7_V5]) > Motor_Var[PUMP_RPM]){	// RPM ERROR
		ui->P1_ValRPM->setStyleSheet("color:rgb(255,0,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValRPM->setVisible(true);
		}
		else{
			ui->P1_ValRPM->setVisible(false);
		}
	}
	else if((Setting_Var[S_P7_V4]) > Motor_Var[PUMP_RPM]) {	// RPM Warning
		ui->P1_ValRPM->setStyleSheet("color:rgb(255,242,0)");
		if((i_BlinkTime%FONT_BLINKING_TIME) != 0 ){
			ui->P1_ValRPM->setVisible(true);
		}
		else{
			ui->P1_ValRPM->setVisible(false);
		}
	}
	else{
		ui->P1_ValRPM->setVisible(true);
		ui->P1_ValRPM->setStyleSheet("color:rgb(255,255,255)");
	}


    m.sprintf("%d",Motor_Var[PUMP_RPM]);
    ui->P1_ValRPM->setText(m);
    m.sprintf("%dh",Motor_Var[PUMP_RUNT]);
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

	// range 0 - 100
	P1_RCVal = int(((Motor_Var[PUMP_M1C]*100)/(Setting_Var[S_P6_V2]*10)));
	P1_SCVal = int(((Motor_Var[PUMP_M2C]*100)/(Setting_Var[S_P6_V2]*10)));
	P1_TCVal = int(((Motor_Var[PUMP_M3C]*100)/(Setting_Var[S_P6_V2]*10)));

	ui->P1_RCurrent->setStyleSheet("background:rgb(34,241,188)");
	ui->P1_RCurrent->setFixedWidth(P1_RCVal);
	ui->P1_RCurrent_2->move(585+P1_RCVal,157);

	ui->P1_SCurrent->setStyleSheet("background:rgb(255,167,92)");
	ui->P1_SCurrent->setFixedWidth(P1_SCVal);
	ui->P1_SCurrent_2->move(585+P1_SCVal,211);

	ui->P1_TCurrent->setStyleSheet("background:rgb(255,221,134)");
	ui->P1_TCurrent->setFixedWidth(P1_TCVal);
	ui->P1_TCurrent_2->move(585+P1_TCVal,266);



	if(Motor_Var[PUMP_YD_Master] == SET_NOTCONN){
		qp = QPixmap(P1_DeviceConn_STRList[0]);
	}
	else{
		qp = QPixmap(P1_DeviceConn_STRList[1]);
	}
	ui->P1_Master->setPixmap(qp);

	if(Motor_Var[PUMP_YD_Sub1] == SET_NOTCONN){
		qp = QPixmap(P1_DeviceConn_STRList[2]);
	}
	else{
		qp = QPixmap(P1_DeviceConn_STRList[3]);
	}
	ui->P1_Slave1->setPixmap(qp);

	if(Motor_Var[PUMP_YD_Sub2] == SET_NOTCONN){
		qp = QPixmap(P1_DeviceConn_STRList[4]);
	}
	else{
		qp = QPixmap(P1_DeviceConn_STRList[5]);
	}
	ui->P1_Slave2->setPixmap(qp);

	if(Motor_Var[PUMP_YD_Sub3] == SET_NOTCONN){
		qp = QPixmap(P1_DeviceConn_STRList[6]);
	}
	else{
		qp = QPixmap(P1_DeviceConn_STRList[7]);
	}
	ui->P1_Slave3->setPixmap(qp);


	QString mm;

	switch(Setting_Var[S_P4_V4]){
	case 0:
		mm.sprintf("SWHP ");
	break;
	case 1:
		mm.sprintf("SWVP ");
	break;
	case 2:
		mm.sprintf("SWSC ");
	break;
	case 3:
		mm.sprintf("SWBP ");
	break;
	case 4:
		mm.sprintf("SWDP ");
	break;
	case 5:
		mm.sprintf("SWDT ");
	break;
	case 6:
		mm.sprintf("SWGP ");
	break;
	case 7:
		mm.sprintf("SGPN ");
	break;
	case 8:
		mm.sprintf("SMX ");
	break;
	}
	
	switch(Setting_Var[S_P4_V5]){
	case 0:
		mm.append("2P 3.7KW");
	break;
	case 1:
		mm.append("2P 4.5KW");
	break;
	case 2:
		mm.append("2P 5.5KW");
	break;
	case 3:
		mm.append("2P 7.5KW");
	break;
	
	case 4:
		mm.append("4P 3.7KW");
	break;
	case 5:
		mm.append("4P 4.5KW");
	break;
	case 6:
		mm.append("4P 5.5KW");
	break;
	case 7:
		mm.append("4P 7.5KW");
	break;
	
	case 8:
		mm.append("6P 3.7KW");
	break;
	case 9:
		mm.append("6P 4.5KW");
	break;
	case 10:
		mm.append("6P 5.5KW");
	break;
	case 11:
		mm.append("6P 7.5KW");
	break;
	
	case 12:
		mm.append("8P 3.7KW");
	break;
	case 13:
		mm.append("8P 4.5KW");
	break;
	case 14:
		mm.append("8P 5.5KW");
	break;
	case 15:
		mm.append("8P 7.5KW");
	break;
	}
	ui->P1_LABEL1->setText(mm);
	ui->P2_LABEL1->setText(mm);
	ui->P3_LABEL1->setText(mm);
	ui->P4_LABEL1->setText(mm);
	ui->P5_LABEL1->setText(mm);
	ui->P6_LABEL1->setText(mm);
	ui->P7_LABEL1->setText(mm);
	ui->P8_LABEL1->setText(mm);
	ui->P9_LABEL1->setText(mm);
	ui->P10_LABEL1->setText(mm);
	
	mm = "";
	if(Setting_Var[S_P8_V5]) mm.sprintf("PUMP MASTER");
	else if(Setting_Var[S_P8_V6]) mm.sprintf("PUMP 1P");
	else if(Setting_Var[S_P8_V7]) mm.sprintf("PUMP 2P");
	else if(Setting_Var[S_P8_V8]) mm.sprintf("PUMP 3P");
	else mm.sprintf("PUMP MASTER");
	
	ui->P1_LABEL2->setText(mm);
	ui->P2_LABEL2->setText(mm);
	ui->P3_LABEL2->setText(mm);
	ui->P4_LABEL2->setText(mm);
	ui->P5_LABEL2->setText(mm);
	ui->P6_LABEL2->setText(mm);
	ui->P7_LABEL2->setText(mm);
	ui->P8_LABEL2->setText(mm);
	ui->P9_LABEL2->setText(mm);
	ui->P10_LABEL2->setText(mm);
}

void MainWindow::ChangeWindow_WIN2(void)
{
	QString m;

	
	switch(Setting_Var[S_P5_V1]){
	case T_NONE	:
		ui->P2_ValMotor1_2->setVisible(true);
		ui->P2_ValMotor1_3->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P2_ValMotor1_2->setVisible(false);
		ui->P2_ValMotor1_3->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V8]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V7]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P2_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V8]));
		ui->P2_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P2_Motor1->setFixedWidth(P1_M1Val);
		ui->P2_Motor1_2->move(100+P1_M1Val,165);
		ui->P2_ValMotor1_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P2_ValMotor1_2->setVisible(false);
		ui->P2_ValMotor1_3->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V8]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V7]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P2_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V8]));
		ui->P2_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P2_Motor1->setFixedWidth(P1_M1Val);
		ui->P2_Motor1_2->move(100+P1_M1Val,165);

		ui->P2_ValMotor1_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P2_ValMotor1_2->setVisible(false);
		ui->P2_ValMotor1_3->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V8]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V7]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P2_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V8]));
		ui->P2_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P2_Motor1->setFixedWidth(P1_M1Val);
		ui->P2_Motor1_2->move(100+P1_M1Val,165);

		ui->P2_ValMotor1_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P2_ValMotor1_2->setVisible(false);
		ui->P2_ValMotor1_3->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V8]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V7]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P2_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V8]));
		ui->P2_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P2_Motor1->setFixedWidth(P1_M1Val);
		ui->P2_Motor1_2->move(100+P1_M1Val,165);

		ui->P2_ValMotor1_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P2_ValMotor1_2->setVisible(false);
		ui->P2_ValMotor1_3->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V8]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V7]) ui->P2_ValMotor1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor1->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P2_ValMotor1->setText(m);

		P1_M1Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V8]));
		ui->P2_Motor1->setStyleSheet("background:rgb(34,241,188)");
		ui->P2_Motor1->setFixedWidth(P1_M1Val);
		ui->P2_Motor1_2->move(100+P1_M1Val,165);
		
		ui->P2_ValMotor1_1->setText("베어링 하");
	break;
	}

	
	switch(Setting_Var[S_P5_V2]){
	case T_NONE	:
		ui->P2_ValMotor2_2->setVisible(true);
		ui->P2_ValMotor2_3->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P2_ValMotor2_2->setVisible(false);
		ui->P2_ValMotor2_3->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V11]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V10]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P2_ValMotor2->setText(m);
		
		P2_M2Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V11]));
		ui->P2_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P2_Motor2->setFixedWidth(P2_M2Val);
		ui->P2_Motor2_2->move(100+P2_M2Val,233);

		ui->P2_ValMotor2_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P2_ValMotor2_2->setVisible(false);
		ui->P2_ValMotor2_3->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V11]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V10]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P2_ValMotor2->setText(m);
		
		P2_M2Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V11]));
		ui->P2_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P2_Motor2->setFixedWidth(P2_M2Val);
		ui->P2_Motor2_2->move(100+P2_M2Val,233);

		ui->P2_ValMotor2_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P2_ValMotor2_2->setVisible(false);
		ui->P2_ValMotor2_3->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V11]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V10]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P2_ValMotor2->setText(m);
		
		P2_M2Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V11]));
		ui->P2_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P2_Motor2->setFixedWidth(P2_M2Val);
		ui->P2_Motor2_2->move(100+P2_M2Val,233);

		ui->P2_ValMotor2_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P2_ValMotor2_2->setVisible(false);
		ui->P2_ValMotor2_3->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V11]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V10]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P2_ValMotor2->setText(m);
		
		P2_M2Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V11]));
		ui->P2_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P2_Motor2->setFixedWidth(P2_M2Val);
		ui->P2_Motor2_2->move(100+P2_M2Val,233);

		ui->P2_ValMotor2_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P2_ValMotor2_2->setVisible(false);
		ui->P2_ValMotor2_3->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V11]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V10]) ui->P2_ValMotor2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor2->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P2_ValMotor2->setText(m);
		
		P2_M2Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V11]));
		ui->P2_Motor2->setStyleSheet("background:rgb(255,167,92)");
		ui->P2_Motor2->setFixedWidth(P2_M2Val);
		ui->P2_Motor2_2->move(100+P2_M2Val,233);

		ui->P2_ValMotor2_1->setText("베어링 하");
	break;
	}

	
	switch(Setting_Var[S_P5_V3]){
	case T_NONE	:
		ui->P2_ValMotor3_2->setVisible(true);
		ui->P2_ValMotor3_3->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P2_ValMotor3_2->setVisible(false);
		ui->P2_ValMotor3_3->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V14]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V13]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P2_ValMotor3->setText(m);
		
		P2_M3Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V14]));
		ui->P2_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P2_Motor3->setFixedWidth(P2_M3Val);
		ui->P2_Motor3_2->move(100+P2_M3Val,300);

		ui->P2_ValMotor3_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P2_ValMotor3_2->setVisible(false);
		ui->P2_ValMotor3_3->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V14]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V13]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P2_ValMotor3->setText(m);
		
		P2_M3Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V14]));
		ui->P2_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P2_Motor3->setFixedWidth(P2_M3Val);
		ui->P2_Motor3_2->move(100+P2_M3Val,300);

		ui->P2_ValMotor3_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P2_ValMotor3_2->setVisible(false);
		ui->P2_ValMotor3_3->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V14]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V13]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P2_ValMotor3->setText(m);
		
		P2_M3Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V14]));
		ui->P2_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P2_Motor3->setFixedWidth(P2_M3Val);
		ui->P2_Motor3_2->move(100+P2_M3Val,300);

		ui->P2_ValMotor3_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P2_ValMotor3_2->setVisible(false);
		ui->P2_ValMotor3_3->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V14]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V13]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P2_ValMotor3->setText(m);
		
		P2_M3Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V14]));
		ui->P2_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P2_Motor3->setFixedWidth(P2_M3Val);
		ui->P2_Motor3_2->move(100+P2_M3Val,300);

		ui->P2_ValMotor3_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P2_ValMotor3_2->setVisible(false);
		ui->P2_ValMotor3_3->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V14]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V13]) ui->P2_ValMotor3->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValMotor3->setStyleSheet("color:rgb(255,255,255)");
		
		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P2_ValMotor3->setText(m);
		
		P2_M3Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V14]));
		ui->P2_Motor3->setStyleSheet("background:rgb(255,221,134)");
		ui->P2_Motor3->setFixedWidth(P2_M3Val);
		ui->P2_Motor3_2->move(100+P2_M3Val,300);

		ui->P2_ValMotor3_1->setText("베어링 하");
	break;
	}

	
	switch(Setting_Var[S_P5_V4]){
	case T_NONE	:
		ui->P2_ValBR1_2->setVisible(true);
		ui->P2_ValBR1_3->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P2_ValBR1_2->setVisible(false);
		ui->P2_ValBR1_3->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V17]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V16]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P2_ValBR1->setText(m);
		
		P2_M4Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V17]));
		ui->P2_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P2_Motor4->setFixedWidth(P2_M4Val);
		ui->P2_Motor4_2->move(100+P2_M4Val,366);

		ui->P2_ValBR1_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P2_ValBR1_2->setVisible(false);
		ui->P2_ValBR1_3->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V17]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V16]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P2_ValBR1->setText(m);
		
		P2_M4Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V17]));
		ui->P2_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P2_Motor4->setFixedWidth(P2_M4Val);
		ui->P2_Motor4_2->move(100+P2_M4Val,366);

		ui->P2_ValBR1_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P2_ValBR1_2->setVisible(false);
		ui->P2_ValBR1_3->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V17]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V16]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P2_ValBR1->setText(m);
		
		P2_M4Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V17]));
		ui->P2_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P2_Motor4->setFixedWidth(P2_M4Val);
		ui->P2_Motor4_2->move(100+P2_M4Val,366);

		ui->P2_ValBR1_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P2_ValBR1_2->setVisible(false);
		ui->P2_ValBR1_3->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V17]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V16]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P2_ValBR1->setText(m);
		
		P2_M4Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V17]));
		ui->P2_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P2_Motor4->setFixedWidth(P2_M4Val);
		ui->P2_Motor4_2->move(100+P2_M4Val,366);

		ui->P2_ValBR1_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P2_ValBR1_2->setVisible(false);
		ui->P2_ValBR1_3->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V17]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V16]) ui->P2_ValBR1->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR1->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P2_ValBR1->setText(m);
		
		P2_M4Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V17]));
		ui->P2_Motor4->setStyleSheet("background:rgb(255,168,93)");
		ui->P2_Motor4->setFixedWidth(P2_M4Val);
		ui->P2_Motor4_2->move(100+P2_M4Val,366);

		ui->P2_ValBR1_1->setText("베어링 하");
	break;
	}

	
	switch(Setting_Var[S_P5_V5]){
	case T_NONE	:
		ui->P2_ValBR2_2->setVisible(true);
		ui->P2_ValBR2_3->setVisible(true);
	break;
	case T_SET_M1 :
		ui->P2_ValBR2_2->setVisible(false);
		ui->P2_ValBR2_3->setVisible(false);
		if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V20]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M1T] >= Setting_Var[S_P5_V19]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M1T]);
		ui->P2_ValBR2->setText(m);
		
		P2_M5Val = int(((Motor_Var[PUMP_M1T]*144)/Setting_Var[S_P5_V20]));
		ui->P2_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P2_Motor5->setFixedWidth(P2_M5Val);
		ui->P2_Motor5_2->move(100+P2_M5Val,433);

		ui->P2_ValBR2_1->setText("모터 1");
	break;
	case T_SET_M2 :
		ui->P2_ValBR2_2->setVisible(false);
		ui->P2_ValBR2_3->setVisible(false);
		if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V20]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M2T] >= Setting_Var[S_P5_V19]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M2T]);
		ui->P2_ValBR2->setText(m);
		
		P2_M5Val = int(((Motor_Var[PUMP_M2T]*144)/Setting_Var[S_P5_V20]));
		ui->P2_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P2_Motor5->setFixedWidth(P2_M5Val);
		ui->P2_Motor5_2->move(100+P2_M5Val,433);

		ui->P2_ValBR2_1->setText("모터 2");
	break;
	case T_SET_M3 :
		ui->P2_ValBR2_2->setVisible(false);
		ui->P2_ValBR2_3->setVisible(false);
		if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V20]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M3T] >= Setting_Var[S_P5_V19]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M3T]);
		ui->P2_ValBR2->setText(m);
		
		P2_M5Val = int(((Motor_Var[PUMP_M3T]*144)/Setting_Var[S_P5_V20]));
		ui->P2_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P2_Motor5->setFixedWidth(P2_M5Val);
		ui->P2_Motor5_2->move(100+P2_M5Val,433);

		ui->P2_ValBR2_1->setText("모터 3");
	break;
	case T_SET_B1 :
		ui->P2_ValBR2_2->setVisible(false);
		ui->P2_ValBR2_3->setVisible(false);
		if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V20]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M4T] >= Setting_Var[S_P5_V19]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M4T]);
		ui->P2_ValBR2->setText(m);
		
		P2_M5Val = int(((Motor_Var[PUMP_M4T]*144)/Setting_Var[S_P5_V20]));
		ui->P2_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P2_Motor5->setFixedWidth(P2_M5Val);
		ui->P2_Motor5_2->move(100+P2_M5Val,433);

		ui->P2_ValBR2_1->setText("베어링 상");
	break;
	case T_SET_B2 :
		ui->P2_ValBR2_2->setVisible(false);
		ui->P2_ValBR2_3->setVisible(false);
		if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V20]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,0,0)");
		else if(Motor_Var[PUMP_M5T] >= Setting_Var[S_P5_V19]) ui->P2_ValBR2->setStyleSheet("color:rgb(255,242,0)");
		else ui->P2_ValBR2->setStyleSheet("color:rgb(255,255,255)");

		m.sprintf("%d",Motor_Var[PUMP_M5T]);
		ui->P2_ValBR2->setText(m);
		
		P2_M5Val = int(((Motor_Var[PUMP_M5T]*144)/Setting_Var[S_P5_V20]));
		ui->P2_Motor5->setStyleSheet("background:rgb(90,126,223)");
		ui->P2_Motor5->setFixedWidth(P2_M5Val);
		ui->P2_Motor5_2->move(100+P2_M5Val,433);

		ui->P2_ValBR2_1->setText("베어링 하");
	break;
	}


	

	m.sprintf("%d",historyTemp[0][0]);
	ui->P2_Temp1->setText(m);
	m.sprintf("%d",historyTemp[0][1]);
	ui->P2_Temp1_2->setText(m);
	m.sprintf("%d",historyTemp[0][2]);
	ui->P2_Temp1_3->setText(m);
	m.sprintf("%d",historyTemp[0][3]);
	ui->P2_Temp1_4->setText(m);
	m.sprintf("%d",historyTemp[0][4]);
	ui->P2_Temp1_5->setText(m);
	m.sprintf("%d",historyTemp[0][5]);
	ui->P2_Temp1_6->setText(m);
	m.sprintf("%d",historyTemp[0][6]);
	ui->P2_Temp1_7->setText(m);
	m.sprintf("%d",historyTemp[0][7]);
	ui->P2_Temp1_8->setText(m);
	m.sprintf("%d",historyTemp[0][8]);
	ui->P2_Temp1_9->setText(m);
	m.sprintf("%d",historyTemp[0][9]);
	ui->P2_Temp1_10->setText(m);
	

	m.sprintf("%d",historyTemp[1][0]);
	ui->P2_Temp2->setText(m);
	m.sprintf("%d",historyTemp[1][1]);
	ui->P2_Temp2_2->setText(m);
	m.sprintf("%d",historyTemp[1][2]);
	ui->P2_Temp2_3->setText(m);
	m.sprintf("%d",historyTemp[1][3]);
	ui->P2_Temp2_4->setText(m);
	m.sprintf("%d",historyTemp[1][4]);
	ui->P2_Temp2_5->setText(m);
	m.sprintf("%d",historyTemp[1][5]);
	ui->P2_Temp2_6->setText(m);
	m.sprintf("%d",historyTemp[1][6]);
	ui->P2_Temp2_7->setText(m);
	m.sprintf("%d",historyTemp[1][7]);
	ui->P2_Temp2_8->setText(m);
	m.sprintf("%d",historyTemp[1][8]);
	ui->P2_Temp2_9->setText(m);
	m.sprintf("%d",historyTemp[1][9]);
	ui->P2_Temp2_10->setText(m);
	

	m.sprintf("%d",historyTemp[2][0]);
	ui->P2_Temp3->setText(m);
	m.sprintf("%d",historyTemp[2][1]);
	ui->P2_Temp3_2->setText(m);
	m.sprintf("%d",historyTemp[2][2]);
	ui->P2_Temp3_3->setText(m);
	m.sprintf("%d",historyTemp[2][3]);
	ui->P2_Temp3_4->setText(m);
	m.sprintf("%d",historyTemp[2][4]);
	ui->P2_Temp3_5->setText(m);
	m.sprintf("%d",historyTemp[2][5]);
	ui->P2_Temp3_6->setText(m);
	m.sprintf("%d",historyTemp[2][6]);
	ui->P2_Temp3_7->setText(m);
	m.sprintf("%d",historyTemp[2][7]);
	ui->P2_Temp3_8->setText(m);
	m.sprintf("%d",historyTemp[2][8]);
	ui->P2_Temp3_9->setText(m);
	m.sprintf("%d",historyTemp[2][9]);
	ui->P2_Temp3_10->setText(m);
	

	m.sprintf("%d",historyTemp[3][0]);
	ui->P2_Temp4->setText(m);
	m.sprintf("%d",historyTemp[3][1]);
	ui->P2_Temp4_2->setText(m);
	m.sprintf("%d",historyTemp[3][2]);
	ui->P2_Temp4_3->setText(m);
	m.sprintf("%d",historyTemp[3][3]);
	ui->P2_Temp4_4->setText(m);
	m.sprintf("%d",historyTemp[3][4]);
	ui->P2_Temp4_5->setText(m);
	m.sprintf("%d",historyTemp[3][5]);
	ui->P2_Temp4_6->setText(m);
	m.sprintf("%d",historyTemp[3][6]);
	ui->P2_Temp4_7->setText(m);
	m.sprintf("%d",historyTemp[3][7]);
	ui->P2_Temp4_8->setText(m);
	m.sprintf("%d",historyTemp[3][8]);
	ui->P2_Temp4_9->setText(m);
	m.sprintf("%d",historyTemp[3][9]);
	ui->P2_Temp4_10->setText(m);
	

	m.sprintf("%d",historyTemp[4][0]);
	ui->P2_Temp5->setText(m);
	m.sprintf("%d",historyTemp[4][1]);
	ui->P2_Temp5_2->setText(m);
	m.sprintf("%d",historyTemp[4][2]);
	ui->P2_Temp5_3->setText(m);
	m.sprintf("%d",historyTemp[4][3]);
	ui->P2_Temp5_4->setText(m);
	m.sprintf("%d",historyTemp[4][4]);
	ui->P2_Temp5_5->setText(m);
	m.sprintf("%d",historyTemp[4][5]);
	ui->P2_Temp5_6->setText(m);
	m.sprintf("%d",historyTemp[4][6]);
	ui->P2_Temp5_7->setText(m);
	m.sprintf("%d",historyTemp[4][7]);
	ui->P2_Temp5_8->setText(m);
	m.sprintf("%d",historyTemp[4][8]);
	ui->P2_Temp5_9->setText(m);
	m.sprintf("%d",historyTemp[4][9]);
	ui->P2_Temp5_10->setText(m);

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


	m.sprintf("%d",historyCurrent[0][0]);
	ui->P3_CurrentR->setText(m);
	m.sprintf("%d",historyCurrent[0][1]);
	ui->P3_CurrentR_2->setText(m);
	m.sprintf("%d",historyCurrent[0][2]);
	ui->P3_CurrentR_3->setText(m);
	m.sprintf("%d",historyCurrent[0][3]);
	ui->P3_CurrentR_4->setText(m);
	m.sprintf("%d",historyCurrent[0][4]);
	ui->P3_CurrentR_5->setText(m);
	m.sprintf("%d",historyCurrent[0][5]);
	ui->P3_CurrentR_6->setText(m);
	m.sprintf("%d",historyCurrent[0][6]);
	ui->P3_CurrentR_7->setText(m);
	m.sprintf("%d",historyCurrent[0][7]);
	ui->P3_CurrentR_8->setText(m);
	m.sprintf("%d",historyCurrent[0][8]);
	ui->P3_CurrentR_9->setText(m);
	m.sprintf("%d",historyCurrent[0][9]);
	ui->P3_CurrentR_10->setText(m);

	m.sprintf("%d",historyCurrent[1][0]);
	ui->P3_CurrentS->setText(m);
	m.sprintf("%d",historyCurrent[1][1]);
	ui->P3_CurrentS_2->setText(m);
	m.sprintf("%d",historyCurrent[1][2]);
	ui->P3_CurrentS_3->setText(m);
	m.sprintf("%d",historyCurrent[1][3]);
	ui->P3_CurrentS_4->setText(m);
	m.sprintf("%d",historyCurrent[1][4]);
	ui->P3_CurrentS_5->setText(m);
	m.sprintf("%d",historyCurrent[1][5]);
	ui->P3_CurrentS_6->setText(m);
	m.sprintf("%d",historyCurrent[1][6]);
	ui->P3_CurrentS_7->setText(m);
	m.sprintf("%d",historyCurrent[1][7]);
	ui->P3_CurrentS_8->setText(m);
	m.sprintf("%d",historyCurrent[1][8]);
	ui->P3_CurrentS_9->setText(m);
	m.sprintf("%d",historyCurrent[1][9]);
	ui->P3_CurrentS_10->setText(m);

	m.sprintf("%d",historyCurrent[2][0]);
	ui->P3_CurrentT->setText(m);
	m.sprintf("%d",historyCurrent[2][1]);
	ui->P3_CurrentT_2->setText(m);
	m.sprintf("%d",historyCurrent[2][2]);
	ui->P3_CurrentT_3->setText(m);
	m.sprintf("%d",historyCurrent[2][3]);
	ui->P3_CurrentT_4->setText(m);
	m.sprintf("%d",historyCurrent[2][4]);
	ui->P3_CurrentT_5->setText(m);
	m.sprintf("%d",historyCurrent[2][5]);
	ui->P3_CurrentT_6->setText(m);
	m.sprintf("%d",historyCurrent[2][6]);
	ui->P3_CurrentT_7->setText(m);
	m.sprintf("%d",historyCurrent[2][7]);
	ui->P3_CurrentT_8->setText(m);
	m.sprintf("%d",historyCurrent[2][8]);
	ui->P3_CurrentT_9->setText(m);
	m.sprintf("%d",historyCurrent[2][9]);
	ui->P3_CurrentT_10->setText(m);

	m.sprintf("%d",historyCurrent[3][0]);
	ui->P3_CurrentUB->setText(m);
	m.sprintf("%d",historyCurrent[3][1]);
	ui->P3_CurrentUB_2->setText(m);
	m.sprintf("%d",historyCurrent[3][2]);
	ui->P3_CurrentUB_3->setText(m);
	m.sprintf("%d",historyCurrent[3][3]);
	ui->P3_CurrentUB_4->setText(m);
	m.sprintf("%d",historyCurrent[3][4]);
	ui->P3_CurrentUB_5->setText(m);
	m.sprintf("%d",historyCurrent[3][5]);
	ui->P3_CurrentUB_6->setText(m);
	m.sprintf("%d",historyCurrent[3][6]);
	ui->P3_CurrentUB_7->setText(m);
	m.sprintf("%d",historyCurrent[3][7]);
	ui->P3_CurrentUB_8->setText(m);
	m.sprintf("%d",historyCurrent[3][8]);
	ui->P3_CurrentUB_9->setText(m);
	m.sprintf("%d",historyCurrent[3][9]);
	ui->P3_CurrentUB_10->setText(m);


}
void MainWindow::ChangeWindow_WIN4(void)
{
	int nVal,nVal2;
	QString mm;
	QPoint qpAppNewLoc;


	nVal = int(((Setting_Var[S_P4_V1])*(745-590))/30000+590);
	nVal2 = ui->P4_Set1->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P4_Set1->setProperty("pos", qpAppNewLoc);
	mm.sprintf("%d",Setting_Var[S_P4_V1]);
	qpAppNewLoc.setX(nVal-30);
	qpAppNewLoc.setY(nVal2-20);
	ui->P4_Set1_T->setProperty("pos", qpAppNewLoc);
	ui->P4_Set1_T->setText(mm);

	nVal = int(((Setting_Var[S_P4_V2])*(745-590))/30000+590);
	nVal2 = ui->P4_Set2->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P4_Set2->setProperty("pos", qpAppNewLoc);
	mm.sprintf("%d",Setting_Var[S_P4_V2]);
	qpAppNewLoc.setX(nVal-30);
	qpAppNewLoc.setY(nVal2-20);
	ui->P4_Set2_T->setProperty("pos", qpAppNewLoc);
	ui->P4_Set2_T->setText(mm);

	nVal = int(((Setting_Var[S_P4_V3])*(745-590))/30000+590);
	nVal2 = ui->P4_Set3->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P4_Set3->setProperty("pos", qpAppNewLoc);
	mm.sprintf("%d",Setting_Var[S_P4_V3]);
	qpAppNewLoc.setX(nVal-30);
	qpAppNewLoc.setY(nVal2-20);
	ui->P4_Set3_T->setProperty("pos", qpAppNewLoc);
	ui->P4_Set3_T->setText(mm);

}

void MainWindow::ChangeWindow_WIN5(void)
{
	int nVal,nVal2;
	QString mm;
	QPoint qpAppNewLoc;


	nVal = int(((Setting_Var[S_P5_V6]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set1_L->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set1_L->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V6]);

	nVal = int(((Setting_Var[S_P5_V6]/2)*(757-460)/100)+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set1_L_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set1_L_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V7]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set1_M->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set1_M->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V7]);
	nVal = int(((Setting_Var[S_P5_V7]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set1_M_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set1_M_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V8]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set1_H->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set1_H->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V8]);
	nVal = int(((Setting_Var[S_P5_V8]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set1_H_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set1_H_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V9]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set2_L->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set2_L->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V9]);
	nVal = int(((Setting_Var[S_P5_V9]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set2_L_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set2_L_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V10]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set2_M->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set2_M->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V10]);
	nVal = int(((Setting_Var[S_P5_V10]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set2_M_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set2_M_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V11]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set2_H->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set2_H->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V11]);
	nVal = int(((Setting_Var[S_P5_V11]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set2_H_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set2_H_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V12]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set3_L->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set3_L->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V12]);
	nVal = int(((Setting_Var[S_P5_V12]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set3_L_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set3_L_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V13]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set3_M->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set3_M->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V13]);
	nVal = int(((Setting_Var[S_P5_V13]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set3_M_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set3_M_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V14]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set3_H->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set3_H->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V14]);
	nVal = int(((Setting_Var[S_P5_V14]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set3_H_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set3_H_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V15]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set4_L->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set4_L->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V15]);
	nVal = int(((Setting_Var[S_P5_V15]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set4_L_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set4_L_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V16]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set4_M->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set4_M->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V16]);
	nVal = int(((Setting_Var[S_P5_V16]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set4_M_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set4_M_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V17]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set4_H->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set4_H->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V17]);
	nVal = int(((Setting_Var[S_P5_V17]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set4_H_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set4_H_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V18]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set5_L->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set5_L->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V18]);
	nVal = int(((Setting_Var[S_P5_V18]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set5_L_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set5_L_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V19]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set5_M->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set5_M->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V19]);
	nVal = int(((Setting_Var[S_P5_V19]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set5_M_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set5_M_txt->setText(mm);


	nVal = int(((Setting_Var[S_P5_V20]/2)*(757-460))/100+460);
	nVal2 = ui->P5_Set5_H->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P5_Set5_H->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P5_V20]);
	nVal = int(((Setting_Var[S_P5_V20]/2)*(757-460))/100+460);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-10);
	ui->P5_Set5_H_txt->setProperty("pos", qpAppNewLoc);
	ui->P5_Set5_H_txt->setText(mm);

}

void MainWindow::ChangeWindow_WIN6(void)
{
	int nVal, nVal2;
	QString mm;
	QPoint qpAppNewLoc;

	nVal = int((double(Setting_Var[S_P6_V1]/25.0)*(375-225))+225);
	nVal2 = ui->P6_L1->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_L1->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V1]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1->setProperty("pos", qpAppNewLoc);
	ui->P6_V1->setText(mm);

	nVal = int(((Setting_Var[S_P6_V2]/25.0)*(375-225))+225);
	nVal2 = ui->P6_H1->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_H1->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V2]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_2->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_2->setText(mm);


	nVal = int(((Setting_Var[S_P6_V3]/25.0)*(375-225))+225);
	nVal2 = ui->P6_L2->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_L2->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V3]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_3->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_3->setText(mm);

	nVal = int(((Setting_Var[S_P6_V4]/25.0)*(375-225))+225);
	nVal2 = ui->P6_H2->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_H2->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V4]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_4->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_4->setText(mm);


	nVal = int(((Setting_Var[S_P6_V5]/100.0)*(375-225))+225);
	nVal2 = ui->P6_L3->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_L3->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V5]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_5->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_5->setText(mm);

	nVal = int(((Setting_Var[S_P6_V6]/100.0)*(375-225))+225);
	nVal2 = ui->P6_H3->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_H3->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V6]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_6->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_6->setText(mm);



	nVal = int(((Setting_Var[S_P6_V7]/200.0)*(750-500))+500);
	nVal2 = ui->P6_T1->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_T1->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V7]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_7->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_7->setText(mm);

	nVal = int(((Setting_Var[S_P6_V8]/20.0)*(750-500))+500);
	nVal2 = ui->P6_T2->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_T2->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V8]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_8->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_8->setText(mm);

	nVal = int(((Setting_Var[S_P6_V9]/20.0)*(750-500))+500);
	nVal2 = ui->P6_T3->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_T3->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V9]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_9->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_9->setText(mm);

	nVal = int(((Setting_Var[S_P6_V10]/20.0)*(750-500))+500);
	nVal2 = ui->P6_T4->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_T4->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V10]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_10->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_10->setText(mm);

	nVal = int(((Setting_Var[S_P6_V11]/1000.0)*(750-500))+500);
	nVal2 = ui->P6_T5->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P6_T5->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P6_V11]);
	qpAppNewLoc.setX(nVal-2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P6_V1_11->setProperty("pos", qpAppNewLoc);
	ui->P6_V1_11->setText(mm);

}

void MainWindow::ChangeWindow_WIN7(void)
{
	int nVal, nVal2;
	QString mm;
	QPoint qpAppNewLoc;
	QPixmap qp;

	if(Setting_Var[S_P7_V1]){
		qp = QPixmap(":/new/7P/UIUX/7p/TempInfo/7P_Group2 (3).png");
	}
	else{
		qp = QPixmap(":/new/7P/UIUX/7p/TempInfo/7P_Group2 (5).png");
	}
	ui->P7_B1->setPixmap(qp);

	nVal = int((double(Setting_Var[S_P7_V2]/200.0)*(760-500))+500);
	nVal2 = ui->P7_D1->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P7_D1->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P7_V2]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P7_V1_1->setProperty("pos", qpAppNewLoc);
	ui->P7_V1_1->setText(mm);

	nVal = int((double(Setting_Var[S_P7_V3]/200.0)*(760-500))+500);
	nVal2 = ui->P7_D2->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P7_D2->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P7_V3]);
	qpAppNewLoc.setX(nVal+2);
	qpAppNewLoc.setY(nVal2-15);
	ui->P7_V1_2->setProperty("pos", qpAppNewLoc);
	ui->P7_V1_2->setText(mm);



	nVal = int((double(Setting_Var[S_P7_V4]/3600.0)*(745-155))+155);
	nVal2 = ui->P7_L1->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P7_L1->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P7_V4]);
	qpAppNewLoc.setX(nVal-10);
	qpAppNewLoc.setY(nVal2-18);
	ui->P7_V1_3->setProperty("pos", qpAppNewLoc);
	ui->P7_V1_3->setText(mm);

	nVal = int((double(Setting_Var[S_P7_V5]/3600.0)*(745-155))+155);
	nVal2 = ui->P7_H1->y();
	qpAppNewLoc.setX(nVal);
	qpAppNewLoc.setY(nVal2);
	ui->P7_H1->setProperty("pos", qpAppNewLoc);

	mm.sprintf("%d",Setting_Var[S_P7_V5]);
	qpAppNewLoc.setX(nVal-10);
	qpAppNewLoc.setY(nVal2-18);
	ui->P7_V1_4->setProperty("pos", qpAppNewLoc);
	ui->P7_V1_4->setText(mm);

}

void MainWindow::ChangeWindow_WIN8(void)
{
	QPixmap qp;

	if(!Setting_Var[S_P8_V1]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B1->setPixmap(qp);

	if(!Setting_Var[S_P8_V1]) qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (11)");  // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (12)"); // ���
	ui->P8_B1_V2->setPixmap(qp);


	if(!Setting_Var[S_P8_V2]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B2->setPixmap(qp);

	if(!Setting_Var[S_P8_V2]) qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (11)");  // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (12)"); // ���
	ui->P8_B2_V2->setPixmap(qp);

	if(!Setting_Var[S_P8_V3]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B3->setPixmap(qp);

	if(!Setting_Var[S_P8_V3]) qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (11)");  // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (12)"); // ���
	ui->P8_B3_V2->setPixmap(qp);


	if(!Setting_Var[S_P8_V4]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B4->setPixmap(qp);

	if(!Setting_Var[S_P8_V4]) qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (11)");  // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SetSafety/9P_Group2 (12)"); // ���
	ui->P8_B4_V2->setPixmap(qp);


	if(!Setting_Var[S_P8_V5]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B5->setPixmap(qp);

	if(!Setting_Var[S_P8_V6]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B6->setPixmap(qp);


	if(!Setting_Var[S_P8_V7]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B7->setPixmap(qp);


	if(!Setting_Var[S_P8_V8]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B8->setPixmap(qp);


	if(Setting_Var[S_P8_V9]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (11).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (22).png"); // Dis
	ui->P8_B19->setPixmap(qp);


	if(Setting_Var[S_P8_V10]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (23).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (24).png"); // Dis
	ui->P8_B20->setPixmap(qp);


	if(Setting_Var[S_P8_V11]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (10).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (26).png"); // Dis
	ui->P8_B21->setPixmap(qp);


	if(Setting_Var[S_P8_V12]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (9).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (25).png"); // Dis
	ui->P8_B22->setPixmap(qp);


	if(Setting_Var[S_P8_V13]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (12).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (31).png"); // Dis
	ui->P8_B9_V2->setPixmap(qp);


	if(Setting_Var[S_P8_V14]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (13).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (27).png"); // Dis
	ui->P8_B10_V2->setPixmap(qp);


	if(Setting_Var[S_P8_V15]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (33).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (37).png"); // Dis
	ui->P8_B11_V2->setPixmap(qp);


	if(Setting_Var[S_P8_V16]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (19).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (36).png"); // Dis
	ui->P8_B12_V2->setPixmap(qp);


	if(Setting_Var[S_P8_V17]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (21).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (35).png"); // Dis
	ui->P8_B13_V2->setPixmap(qp);


	if(!Setting_Var[S_P8_V18]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B9->setPixmap(qp);

	if(!Setting_Var[S_P8_V18]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
	ui->P8_B9_V1->setPixmap(qp);


	if(!Setting_Var[S_P8_V19]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B10->setPixmap(qp);

	if(!Setting_Var[S_P8_V19]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
	ui->P8_B10_V1->setPixmap(qp);


	if(!Setting_Var[S_P8_V20]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B11->setPixmap(qp);

	if(!Setting_Var[S_P8_V20]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
	ui->P8_B11_V1->setPixmap(qp);


	if(!Setting_Var[S_P8_V21]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B12->setPixmap(qp);

	if(!Setting_Var[S_P8_V21]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
	ui->P8_B12_V1->setPixmap(qp);


	if(!Setting_Var[S_P8_V22]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (2).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (1).png"); // ���
	ui->P8_B13->setPixmap(qp);

	if(!Setting_Var[S_P8_V22]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (46).png"); // ������
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (8).png"); // ���
	ui->P8_B13_V1->setPixmap(qp);


	if(Setting_Var[S_P8_V23]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (34).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (38).png"); // Dis
	ui->P8_B15->setPixmap(qp);


	if(Setting_Var[S_P8_V24]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (33).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (28).png"); // Dis
	ui->P8_B16->setPixmap(qp);


	if(Setting_Var[S_P8_V25]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (32).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (29).png"); // Dis
	ui->P8_B17->setPixmap(qp);


	if(Setting_Var[S_P8_V26]) qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (20).png"); // En
	else qp = QPixmap(":/new/8P/UIUX/8p/SelMonitoringTemp/8P_Group1 (30).png"); // Dis
	ui->P8_B18->setPixmap(qp);
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
	P1_DeviceConn_STRList = P1_DeviceConn_STR.split(",");
	P5_TempSel_STRList = P5_TempSel_STR.split(",");
	P4_V_STRList =  P4_V_STR.split(",");
	P4_KW_STRList =  P4_KW_STR.split(",");

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
	P1_DeviceConn_STRCnt	=	 P1_DeviceConn_STRList.size();
	P5_TempSel_STRCnt	=	 P5_TempSel_STRList.size();
	P4_V_STRCnt =  P4_V_STRList.size();
	P4_KW_STRCnt =  P4_KW_STRList.size();
	

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

	if(P1_DeviceConn_STRList.size() < 8){
		qApp->quit();
		return;
	}

	if(P5_TempSel_STRList.size() < 12){
		qApp->quit();
		return;
	}

	if(P4_V_STRList.size() < 18){
		qApp->quit();
		return;
	}

	if(P4_KW_STRList.size() < 8){
		qApp->quit();
		return;
	}
	
}

void MainWindow::ShowEventPage(void)
{
	QString mm;
	QStringList strlist1,strlist2;
	int lineCnt;
	
	strlist1 = rdFile.split("\n");

	for(lineCnt=P10_PageIndex*9;lineCnt<(P10_PageIndex*9)+9;lineCnt++){
		if(lineCnt >= P10_LineCnt){

			switch(lineCnt%9){
			case 0:
				ui->P10_index_0->setVisible(false);
				ui->P10_time_0->setVisible(false);
				ui->P10_process_0->setVisible(false);
				ui->P10_info_0->setVisible(false);
			break;
			case 1:
				ui->P10_index_1->setVisible(false);
				ui->P10_time_1->setVisible(false);
				ui->P10_process_1->setVisible(false);
				ui->P10_info_1->setVisible(false);
			break;
			case 2:
				ui->P10_index_2->setVisible(false);
				ui->P10_time_2->setVisible(false);
				ui->P10_process_2->setVisible(false);
				ui->P10_info_2->setVisible(false);
			break;
			case 3:
				ui->P10_index_3->setVisible(false);
				ui->P10_time_3->setVisible(false);
				ui->P10_process_3->setVisible(false);
				ui->P10_info_3->setVisible(false);
			break;
			case 4:
				ui->P10_index_4->setVisible(false);
				ui->P10_time_4->setVisible(false);
				ui->P10_process_4->setVisible(false);
				ui->P10_info_4->setVisible(false);
			break;
			case 5:
				ui->P10_index_5->setVisible(false);
				ui->P10_time_5->setVisible(false);
				ui->P10_process_5->setVisible(false);
				ui->P10_info_5->setVisible(false);
			break;
			case 6:
				ui->P10_index_6->setVisible(false);
				ui->P10_time_6->setVisible(false);
				ui->P10_process_6->setVisible(false);
				ui->P10_info_6->setVisible(false);
			break;
			case 7:
				ui->P10_index_7->setVisible(false);
				ui->P10_time_7->setVisible(false);
				ui->P10_process_7->setVisible(false);
				ui->P10_info_7->setVisible(false);
			break;
			case 8:
				ui->P10_index_8->setVisible(false);
				ui->P10_time_8->setVisible(false);
				ui->P10_process_8->setVisible(false);
				ui->P10_info_8->setVisible(false);
			break;
			}
		}
		else{
			switch(lineCnt%9){
			case 0:
				ui->P10_index_0->setVisible(true);
				ui->P10_time_0->setVisible(true);
				ui->P10_process_0->setVisible(true);
				ui->P10_info_0->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_0->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_0->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_0->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_0->setText(mm);
			break;
			case 1:
				ui->P10_index_1->setVisible(true);
				ui->P10_time_1->setVisible(true);
				ui->P10_process_1->setVisible(true);
				ui->P10_info_1->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_1->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_1->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_1->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_1->setText(mm);
			break;
			case 2:
				ui->P10_index_2->setVisible(true);
				ui->P10_time_2->setVisible(true);
				ui->P10_process_2->setVisible(true);
				ui->P10_info_2->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_2->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_2->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_2->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_2->setText(mm);
			break;
			case 3:
				ui->P10_index_3->setVisible(true);
				ui->P10_time_3->setVisible(true);
				ui->P10_process_3->setVisible(true);
				ui->P10_info_3->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_3->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_3->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_3->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_3->setText(mm);
			break;
			case 4:
				ui->P10_index_4->setVisible(true);
				ui->P10_time_4->setVisible(true);
				ui->P10_process_4->setVisible(true);
				ui->P10_info_4->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_4->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_4->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_4->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_4->setText(mm);
			break;
			case 5:
				ui->P10_index_5->setVisible(true);
				ui->P10_time_5->setVisible(true);
				ui->P10_process_5->setVisible(true);
				ui->P10_info_5->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_5->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_5->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_5->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_5->setText(mm);
			break;
			case 6:
				ui->P10_index_6->setVisible(true);
				ui->P10_time_6->setVisible(true);
				ui->P10_process_6->setVisible(true);
				ui->P10_info_6->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_6->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_6->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_6->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_6->setText(mm);
			break;
			case 7:
				ui->P10_index_7->setVisible(true);
				ui->P10_time_7->setVisible(true);
				ui->P10_process_7->setVisible(true);
				ui->P10_info_7->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_7->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_7->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_7->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_7->setText(mm);
			break;
			case 8:
				ui->P10_index_8->setVisible(true);
				ui->P10_time_8->setVisible(true);
				ui->P10_process_8->setVisible(true);
				ui->P10_info_8->setVisible(true);

				mm.sprintf("%d",lineCnt+1);
				ui->P10_index_8->setText(mm);
				mm = strlist1[lineCnt];
				strlist2 = mm.split(",");
				mm = strlist2[0].toUtf8();
				ui->P10_time_8->setText(mm);
				mm = strlist2[1].toUtf8();
				ui->P10_process_8->setText(mm);
				mm = strlist2[2].toUtf8();
				ui->P10_info_8->setText(mm);
			break;
			}
		}
	}
}
