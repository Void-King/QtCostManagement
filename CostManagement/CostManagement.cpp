#include <sstream>
#include <string>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMouseEvent>
#include <QProcess>

#include "CostManagement.h"

CostManagement::CostManagement(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	uiConfig();
	eventConnect();

	eatFilterInit();
	costInit();
	costDataInit();
	// costDataInitFromPython();
}

CostManagement::~CostManagement()
{

}

void CostManagement::eatFilterInit()
{
	QString path = "./resource/EatFilter.json";
	QFile file(path);
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
		fileOpenError();
	}
	else {
		qDebug() << "File open!";
	}

	QByteArray inData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument inputDoc = QJsonDocument::fromJson(inData, &jsonError);
	QJsonObject eatFilter = inputDoc.object();
	QJsonArray eatFilterArray = eatFilter.value("eatFilter").toArray();
	for (auto itr : eatFilterArray)
	{
		m_eatPattern.push_back(itr.toString());
	}
}
void CostManagement::uiConfig()
{
	QIcon wIcon("./resource/CostManagement.png");
	this->setWindowIcon(wIcon);

	/*this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());*/
	this->setMinimumWidth(800);
	this->setMinimumHeight(700);

	QWidget::setTabOrder(ui.newCostInput, ui.newCostDescription);
	ui.costTable->setFocusPolicy(Qt::NoFocus);
	ui.curRemain->setFocusPolicy(Qt::NoFocus);
	ui.weekCost->setFocusPolicy(Qt::NoFocus);
	ui.weekEat->setFocusPolicy(Qt::NoFocus);
	ui.monthCost->setFocusPolicy(Qt::NoFocus);
	ui.monthEat->setFocusPolicy(Qt::NoFocus);
	ui.monthOther->setFocusPolicy(Qt::NoFocus);
	ui.buttonAdd->setFocusPolicy(Qt::NoFocus);
	ui.buttonDelete->setFocusPolicy(Qt::NoFocus);
	ui.buttonExit->setFocusPolicy(Qt::NoFocus);
	ui.buttonFolder->setFocusPolicy(Qt::NoFocus);
	ui.buttonMinimize->setFocusPolicy(Qt::NoFocus);

	ui.curRemain->setEnabled(false);
	ui.weekCost->setEnabled(false);
	ui.weekEat->setEnabled(false);
	ui.monthCost->setEnabled(false);
	ui.monthEat->setEnabled(false);
	ui.monthOther->setEnabled(false);
}

bool CostManagement::CheckExit()
{
	return m_directExit;
}

void CostManagement::closeEvent(QCloseEvent *e)
{
	if (m_directExit)
	{
		e->accept();
		return;
	}

	QMessageBox tips;
	tips.setText("\n 提示：\n\n 正在关闭窗口，是否保存数据？\t\n");
	tips.setStandardButtons(
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

	tips.setButtonText(QMessageBox::Yes, " 保存并退出 ");
	tips.setButtonText(QMessageBox::No, " 退出 ");
	tips.setButtonText(QMessageBox::Cancel, " 取消 ");

	int res = tips.exec();
	if (res == QMessageBox::Cancel)
	{
		e->ignore();
		return;
	}
	else if (res == QMessageBox::Yes)
	{
		saveData();
		e->accept();
		return;
	}
	else
	{
		e->accept();
		return;
	}
}

void CostManagement::eventConnect()
{
	connect(ui.buttonExit, SIGNAL(clicked()), this, SLOT(ClickButtonExit()));
	connect(ui.buttonMinimize,
		SIGNAL(clicked()), this, SLOT(ClickButtonMinimize()));
	connect(ui.buttonAdd,
		SIGNAL(clicked()), this, SLOT(ClickButtonAdd()));
	connect(ui.buttonDelete,
		SIGNAL(clicked()), this, SLOT(ClickButtonDelete()));
	connect(ui.buttonFolder,
		SIGNAL(clicked()), this, SLOT(ClickButtonFolder()));
}


void CostManagement::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key_Return:
		ClickButtonAdd();
		break;
	case Qt::Key_Enter:
		ClickButtonAdd();
		break;
	case Qt::Key_D:
		if (e->modifiers() == Qt::ControlModifier)
		{
			ClickButtonDelete();
		}
		break;
	case Qt::Key_Escape:
		this->close();
		break;
	default:
		break;
	}
}

void CostManagement::costInit()
{
	// ui.costTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringList header;
	header << "日期" << "金额" << "描述";
	ui.costTable->setHorizontalHeaderLabels(header);
	ui.costTable->horizontalHeader()->setDefaultAlignment(
		Qt::AlignLeft | Qt::AlignVCenter);
	ui.costTable->horizontalHeader()->
		setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
	ui.costTable->horizontalHeader()->
		setSectionResizeMode(0, QHeaderView::Interactive);
	ui.costTable->setColumnWidth(0, 240);
	ui.costTable->horizontalHeader()->
		setSectionResizeMode(1, QHeaderView::Interactive);
	ui.costTable->setColumnWidth(1, 100);
}

void CostManagement::costDataInitFromPython()
{
	QString path = "./cost_local.ini";
	QFile file(path);
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
		fileOpenError();
	}
	else {
		qDebug() << "File open!";
	}

	QJsonArray jsonArray;
	for (int i = 0; i < 739; ++i)
	{
		QString dataStr = file.readLine();
		dataStr.remove(QChar('\r'), Qt::CaseInsensitive);
		dataStr.remove(QChar('\n'), Qt::CaseInsensitive);
		QString costStr = file.readLine();
		costStr.remove(QChar('\r'), Qt::CaseInsensitive);
		costStr.remove(QChar('\n'), Qt::CaseInsensitive);
		QString descriptionStr = file.readLine();
		descriptionStr.remove(QChar('\r'), Qt::CaseInsensitive);
		descriptionStr.remove(QChar('\n'), Qt::CaseInsensitive);
		QJsonObject jsonObj;
		jsonObj.insert("date", dataStr);
		jsonObj.insert("cost", costStr);
		jsonObj.insert("decription", descriptionStr);
		jsonArray.append(jsonObj);
	}
	file.close();

	m_directExit = true;

	path = "./CostDebug.ini";
	QFile fileSec(path);
	if (!fileSec.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
		fileOpenError();
	}
	else {
		qDebug() << "File open!";
	}
	QJsonObject jsonCost;
	jsonCost.insert("allCost", jsonArray);
	QJsonDocument outputDoc;
	outputDoc.setObject(jsonCost);
	fileSec.resize(0);
	fileSec.write(outputDoc.toJson());
	fileSec.close();

	costDataInit();
}

void CostManagement::costAnalyze(int& rowID, QDateTime& date,
	double& cost, QString& description, bool positiveAddin)
{
	curRemain(cost);

	if ((cost > 0 && !positiveAddin) ||
		(cost < 0 && positiveAddin))
	{
		cost = 0;
	}

	if (monthCost(date, cost))
	{
		ui.costTable->item(rowID, 0)->setBackgroundColor(m_monthBackColor);
		ui.costTable->item(rowID, 1)->setBackgroundColor(m_monthBackColor);
		ui.costTable->item(rowID, 2)->setBackgroundColor(m_monthBackColor);

		if (!monthEat(cost, description))
		{
			monthOther(cost);
		}
	}

	if (weekCost(date, cost))
	{
		ui.costTable->item(rowID, 0)->setBackgroundColor(m_weekBackColor);
		ui.costTable->item(rowID, 1)->setBackgroundColor(m_weekBackColor);
		ui.costTable->item(rowID, 2)->setBackgroundColor(m_weekBackColor);
		weekEat(cost, description);
	}
}

void CostManagement::curRemain(double& cost)
{
	double curRemainNumber = ui.curRemain->value();
	curRemainNumber += cost;
	ui.curRemain->setValue(curRemainNumber);
}

bool CostManagement::weekCost(QDateTime& date, double& cost)
{
	bool check = false;

	QDateTime now = QDateTime::currentDateTime();
	int nowYear = now.date().year();
	int nowMonth = now.date().month();
	int nowDayOfMonth = now.date().day();
	int nowDayOfWeek = now.date().dayOfWeek();
	// 今天是周日
	if (nowDayOfWeek == 7)
	{
		QDate thisSunDate = now.date();
		QDate recordDate = date.date();
		if (recordDate >= thisSunDate)
		{
			check = true;
		}
	}
	else // 上周日及之后
	{
		QDate lastSunDate = now.date().addDays(-nowDayOfWeek);
		QDate recordDate = date.date();
		if (recordDate >= lastSunDate)
		{
			check = true;
		}
	}

	if (check)
	{
		double curCost = ui.weekCost->value();
		curCost += cost;
		ui.weekCost->setValue(curCost);
	}

	return check;
}

void CostManagement::weekEat(double& cost, QString& description)
{
	bool check = false;

	for (auto singlePattern : m_eatPattern)
	{
		if (description.contains(singlePattern))
		{
			check = true;
			break;
		}
	}

	if (check)
	{
		double curCost = ui.weekEat->value();
		curCost += cost;
		ui.weekEat->setValue(curCost);
	}
}

bool CostManagement::monthCost(QDateTime& date, double cost)
{
	bool check = false;

	QDateTime now = QDateTime::currentDateTime();
	int nowYear = now.date().year();
	int nowMonth = now.date().month();
	int nowDayOfMonth = now.date().day();

	int recordYear = date.date().year();
	int recordMonth = date.date().month();
	int recordDayOfMonth = date.date().day();

	// 本月20号及之后的时间
	if (nowDayOfMonth >= 20)
	{
		QDate thisMonth20Date = QDate(nowYear, nowMonth, 20);
		QDate recordDate = date.date();
		if (recordDate >= thisMonth20Date)
		{
			check = true;
		}
	}
	else // 上月20号之后的时间
	{
		QDate lastMonth20Date;
		QDate recordDate = date.date();
		if (nowMonth == 1)
		{
			lastMonth20Date = QDate(nowYear - 1, 12, 20);
		}
		else
		{
			lastMonth20Date = QDate(nowYear, nowMonth - 1, 20);;
		}

		if (recordDate >= lastMonth20Date)
		{
			check = true;
		}
	}

	if (check)
	{
		double curCost = ui.monthCost->value();
		curCost += cost;
		ui.monthCost->setValue(curCost);
	}

	return check;
}

bool CostManagement::monthEat(double cost, QString& description)
{
	bool check = false;

	for (auto singlePattern : m_eatPattern)
	{
		if (description.contains(singlePattern))
		{
			check = true;
			break;
		}
	}

	if (check)
	{
		double curCost = ui.monthEat->value();
		curCost += cost;
		ui.monthEat->setValue(curCost);
	}

	return check;
}

void CostManagement::monthOther(double cost)
{
	double curCost = ui.monthOther->value();
	curCost += cost;
	ui.monthOther->setValue(curCost);
}

void CostManagement::fileOpenError()
{
	QMessageBox tips;
	tips.setText("\n 提示：\n\n 文件读取错误！\t\n");
	tips.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	tips.setButtonText(QMessageBox::Yes, " 打开文件夹 ");
	tips.setButtonText(QMessageBox::No, " 退出 ");

	m_directExit = true;
	if (tips.exec() == QMessageBox::Yes)
	{
		ClickButtonFolder();
	}
	this->close();
}

void CostManagement::costDataInit()
{
#ifdef _DEBUG
	m_costFile = "./CostDebug.ini";
#elif _RELEASE
	m_costFile = "./Cost.ini";
#else
	m_costFile = "./CostTemp.ini";
#endif
	QFile file(m_costFile);
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
	}
	else {
		qDebug() << "File open!";
	}

	QByteArray inData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument inputDoc = QJsonDocument::fromJson(inData, &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		fileOpenError();
	}

	QJsonObject jsonCost = inputDoc.object();
	QJsonArray jsonArray = jsonCost.value("allCost").toArray();

	for (auto single = jsonArray.begin(); single != jsonArray.end(); ++single)
	{
		QJsonObject singleObj = single->toObject();

		QString col0Str = singleObj.value("date").toString();
		QString col1Str = singleObj.value("cost").toString();
		QString col2Str = singleObj.value("decription").toString();

		QDateTime recordDate =
			QDateTime::fromString(col0Str, "yyyy-MM-dd hh:mm:ss  ddd");
		double recordCost = col1Str.toDouble();

		int RowCont = 0;
		RowCont = ui.costTable->rowCount();
		ui.costTable->insertRow(RowCont);//增加一行
		ui.costTable->setItem(RowCont, 0, new QTableWidgetItem(col0Str));
		ui.costTable->setItem(RowCont, 1, new QTableWidgetItem(col1Str));
		ui.costTable->setItem(RowCont, 2, new QTableWidgetItem(col2Str));

		QTableWidgetItem* pItem = ui.costTable->item(RowCont, 0);
		pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
		pItem->setTextColor("white");
		pItem = ui.costTable->item(RowCont, 1);
		pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
		pItem->setTextColor("white");
		pItem = ui.costTable->item(RowCont, 2);
		pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
		pItem->setTextColor("white");

		costAnalyze(RowCont, recordDate, recordCost, col2Str);
	}
}

void CostManagement::saveData()
{
	QFile file(m_costFile);
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
		fileOpenError();
	}
	else {
		qDebug() << "File open!";
	}

	QJsonObject jsonCost;
	QJsonArray jsonArray;

	for (int i = 0; i < ui.costTable->rowCount(); ++i)
	{
		QJsonObject singleObj;

		singleObj.insert("date", ui.costTable->item(i, 0)->text());
		singleObj.insert("cost", ui.costTable->item(i, 1)->text());
		singleObj.insert("decription", ui.costTable->item(i, 2)->text());

		jsonArray.append(singleObj);
	}
	jsonCost.insert("allCost", jsonArray);
	QJsonDocument outputDoc;
	outputDoc.setObject(jsonCost);
	file.resize(0);
	file.write(outputDoc.toJson());
	file.close();
}
//void CostManagement::mouseDoubleClickEvent(QMouseEvent* e)
//{
//	int wWidth = this->width();
//	int wHeight = this->height();
//	int wX = this->x();
//	int wY = this->y();
//	int mX = e->x();
//	int mY = e->y();
//	if (mX < wWidth && mY < 50)
//	{
//		if (!fullFlag)
//		{
//			this->showFullScreen();
//			fullFlag = true;
//		}
//		else
//		{
//			this->showNormal();
//			fullFlag = false;
//		}
//	}
//}
//
//void CostManagement::mousePressEvent(QMouseEvent* e)
//{//仅对鼠标左键响应，右键留着使用菜单功能
//	int wWidth = this->width();
//	int wHeight = this->height();
//	int wX = this->x();
//	int wY = this->y();
//	int mX = e->x();
//	int mY = e->y();
//	if (mX < wWidth && mY < 50)
//	{
//		m_oldSize.first = wWidth;
//		m_oldSize.second = wHeight;
//		moveFlag = true;
//		if (e->button() == Qt::LeftButton)
//		{
//			pos = e->globalPos();
//			m_oldPos.first = wX;
//			m_oldPos.second = wY;
//		}
//	}
//}
//void CostManagement::mouseMoveEvent(QMouseEvent* e)
//{//仅对鼠标左键响应，右键留着使用菜单功能
//	int wWidth = this->width();
//	int wHeight = this->height();
//	if (moveFlag)
//	{
//		if (m_oldSize.first != wWidth || m_oldSize.second != wHeight)
//		{
//			m_oldSize.first = wWidth;
//			m_oldSize.second = wHeight;
//			return;
//		}
//		if (!e->buttons().testFlag(Qt::LeftButton))
//			return;
//		int dx = e->globalX() - pos.x();
//		int dy = e->globalY() - pos.y();
//		pos = e->globalPos();
//
//		this->showNormal();
//		fullFlag = false;
//
//		move(m_oldPos.first + dx, m_oldPos.second + dy);
//		m_oldPos.first = x();
//		m_oldPos.second = y();
//	}
//	else
//	{
//		m_oldSize.first = wWidth;
//		m_oldSize.second = wHeight;
//	}
//}
//
//void AppTest::mouseReleaseEvent(QMouseEvent*  e)
//{
//	moveFlag = false;
//}

void CostManagement::moveEvent(QMoveEvent* e)
{
	return;
}

void CostManagement::resizeEvent(QResizeEvent* e)
{
	int wWidth = this->width();
	int wHeight = this->height();
	int wX = this->x();
	int wY = this->y();

	// grid position
	ui.costTable->move(20, 60);

	QSize sizeTable;
	sizeTable.setWidth(wWidth - 40);
	sizeTable.setHeight(wHeight - 240);
	ui.costTable->resize(sizeTable);

	// system menu position
	ui.buttonExit->move(wWidth - 40, 20);
	ui.buttonMinimize->move(wWidth - 74, 20);

	// row position
	int row0 = wHeight - 160;
	int row1 = wHeight - 110;
	int row2 = wHeight - 60;

	// three button position
	QSize sizeButton;
	sizeButton.setHeight(30);
	sizeButton.setWidth(70);
	int buttonCol = wWidth - 100;
	ui.buttonAdd->resize(sizeButton);
	ui.buttonAdd->move(buttonCol, row0);
	ui.buttonDelete->resize(sizeButton);
	ui.buttonDelete->move(buttonCol, row1);
	ui.buttonFolder->resize(sizeButton);
	ui.buttonFolder->move(buttonCol, row2);

	// col description and month other
	int dataRightBound = wWidth - 130;
	int dataLeftBound = 20;
	int dataLeftBoundTemp = 20;

	int widthOfDataVector = (dataRightBound - dataLeftBound) / 7;

	QSize sizeDataVector;
	sizeDataVector.setHeight(30);
	sizeDataVector.setWidth(100);

	/*QSize sizeDiscription;
	sizeDiscription.setHeight(30);
	sizeDiscription.setWidth(92);*/

	int col0 = dataLeftBoundTemp;
	dataLeftBoundTemp += 80;
	ui.curRemainLabel->resize(sizeDataVector);
	ui.curRemainLabel->move(col0, row0);
	ui.weekCostLabel->resize(sizeDataVector);
	ui.weekCostLabel->move(col0, row1);
	ui.weekEatLabel->resize(sizeDataVector);
	ui.weekEatLabel->move(col0, row2);


	int col1 = dataLeftBoundTemp;
	dataLeftBoundTemp += 120;
	ui.curRemain->resize(sizeDataVector);
	ui.curRemain->move(col1, row0);
	ui.weekCost->resize(sizeDataVector);
	ui.weekCost->move(col1, row1);
	ui.weekEat->resize(sizeDataVector);
	ui.weekEat->move(col1, row2);

	int col2 = dataLeftBoundTemp;
	dataLeftBoundTemp += 80;
	ui.newCostLable->resize(sizeDataVector);
	ui.newCostLable->move(col2, row0);
	ui.monthCostLabel->resize(sizeDataVector);
	ui.monthCostLabel->move(col2, row1);
	ui.monthEatLabel->resize(sizeDataVector);
	ui.monthEatLabel->move(col2, row2);

	int col3 = dataLeftBoundTemp;
	dataLeftBoundTemp += 120;
	ui.newCostInput->resize(sizeDataVector);
	ui.newCostInput->move(col3, row0);
	ui.monthCost->resize(sizeDataVector);
	ui.monthCost->move(col3, row1);
	ui.monthEat->resize(sizeDataVector);
	ui.monthEat->move(col3, row2);

	int col4 = dataLeftBoundTemp;
	dataLeftBoundTemp += 80;
	ui.newCostDescriptionLable->resize(sizeDataVector);
	ui.newCostDescriptionLable->move(col4, row0);
	ui.monthOtherLabel->resize(sizeDataVector);
	ui.monthOtherLabel->move(col4, row2);

	QSize sizeDescription;
	sizeDescription.setHeight(30);
	sizeDescription.setWidth(dataRightBound - dataLeftBoundTemp - 10);

	int col5 = dataLeftBoundTemp;
	ui.newCostDescription->resize(sizeDescription);
	ui.newCostDescription->move(col5, row0);
	ui.monthOther->resize(sizeDataVector);
	ui.monthOther->move(col5, row2);

	return;
}

void CostManagement::ClickButtonExit()
{
	this->close();
}

void CostManagement::ClickButtonMinimize()
{
	this->showMinimized();
}

void CostManagement::ClickButtonAdd()
{
	QDateTime curTime = QDateTime::currentDateTime();
	QString date = curTime.toString("yyyy-MM-dd hh:mm:ss  ddd");
	QString description = ui.newCostDescription->text();

	double costInput = ui.newCostInput->value();

	int rowID = 0;
	ui.costTable->insertRow(rowID);//增加一行
	ui.costTable->setItem(rowID, 0, new QTableWidgetItem(date));
	ui.costTable->setItem(rowID, 1,
		new QTableWidgetItem(QString::number(costInput, 10, 2)));
	ui.costTable->setItem(rowID, 2, new QTableWidgetItem(description));

	QTableWidgetItem* pItem = ui.costTable->item(rowID, 0);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextColor("white");

	pItem = ui.costTable->item(rowID, 1);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextColor("white");

	pItem = ui.costTable->item(rowID, 2);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextColor("white");

	costAnalyze(rowID, curTime, costInput, description);
}

void CostManagement::getSelectionRowsAndCols(
	QList<QTableWidgetItem*>& selection,
	std::set<int, std::greater<int>>& rowIDs,
	std::set<int, std::greater<int>>& colIDs)
{
	for (auto itr : selection)
	{
		rowIDs.insert(itr->row());
		colIDs.insert(itr->column());
	}
}

void CostManagement::ClickButtonDelete()
{
	QList<QTableWidgetItem*> selection = ui.costTable->selectedItems();
	std::set<int, std::greater<int>> rowIDs;
	std::set<int, std::greater<int>> colIDs;
	getSelectionRowsAndCols(selection, rowIDs, colIDs);

	if (rowIDs.empty())
	{
		rowIDs.insert(0);
	}

	for (auto itr : rowIDs)
	{

		QString col0Str = ui.costTable->item(itr, 0)->text();
		QString col1Str = ui.costTable->item(itr, 1)->text();
		QString col2Str = ui.costTable->item(itr, 2)->text();

		QDateTime recordDate =
			QDateTime::fromString(col0Str, "yyyy-MM-dd hh:mm:ss  ddd");
		double recordCost = -col1Str.toDouble();

		costAnalyze(itr, recordDate, recordCost, col2Str, true);

		ui.costTable->removeRow(itr);
	}
}

void CostManagement::ClickButtonFolder()
{
	QString fileName = QDir::currentPath();
	// QString fileNameSec = QCoreApplication::applicationDirPath();
	// explorer.exe E:\qt\pythonToQt\CostManagement\CostManagement
	QProcess p;

	QString fileNameFormat = "";
	for (int i = 0; i < fileName.size(); ++i)
	{
		if (fileName.at(i) == '/')
		{
			fileNameFormat.append('\\');
		}
		else
		{
			fileNameFormat.append(fileName.at(i));
		}
	}

	QString command = "explorer.exe /e, /root, ";
	command.append(fileNameFormat);

	p.startDetached(command);

	return;
}