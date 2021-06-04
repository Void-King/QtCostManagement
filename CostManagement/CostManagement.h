#pragma once

#pragma execution_character_set("utf-8")

#include <set>

#include <QtWidgets/QMainWindow>
#include <QMessageBox>

#include "ui_CostManagement.h"

class AcrylicMessageBox : public QMessageBox
{
public:
	AcrylicMessageBox();

protected:
	void paintEvent(QPaintEvent *e);

	QLabel* labelBackground = nullptr;
};

class DoubleWidgetItem : public QTableWidgetItem
{
public:
	DoubleWidgetItem(const QString& text) :
		QTableWidgetItem(text)
	{
	}

	bool operator <(const QTableWidgetItem &other) const
	{
		return text().toFloat() < other.text().toFloat();
	}
};

class CostManagement : public QMainWindow
{
    Q_OBJECT

public:
    CostManagement(QWidget *parent = Q_NULLPTR);
	~CostManagement();

	bool CheckExit();

protected:
	/*void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseDoubleClickEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent*  e);*/
	void moveEvent(QMoveEvent* e);
	void resizeEvent(QResizeEvent* e);
	void closeEvent(QCloseEvent* e);
	void keyPressEvent(QKeyEvent* e);
	void paintEvent(QPaintEvent *e);

	void costInit();
	void costDataInit();
	void costDataInitFromPython();

	void eventConnect();

	void getSelectionRowsAndCols(
		QList<QTableWidgetItem*>& selection,
		std::set<int, std::greater<int>>& rowIDs,
		std::set<int, std::greater<int>>& colIDs);

	void saveData();

	void costAnalyze(
		int& rowID, QDateTime& date, double& cost,
		QString& description, bool positiveAddin = false);

	void curRemain(double& cost);
	void allCostCount(double& cost);
	bool weekCost(QDateTime& date, double& cost);
	void weekEat(double& cost, QString& description);
	bool monthCost(QDateTime& date, double cost);
	bool monthEat(double cost, QString& description);
	void monthOther(double cost);

	void uiConfig();

	void eatFilterInit();

	void fileOpenError();

protected slots:
	void ClickButtonExit();
	void ClickButtonMinimize();
	void ClickButtonAdd();
	void ClickButtonDelete();
	void ClickButtonFolder();

private:
    Ui::CostManagementClass ui;

	std::list<QString> m_eatPattern;

	QString m_costFile = "";
	bool m_directExit = false;
	QColor m_monthBackColor = QColor(0, 60, 40, 140);
	QColor m_weekBackColor = QColor(0, 120, 80, 140);
};
