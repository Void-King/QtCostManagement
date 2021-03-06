
#include <QtWidgets/QApplication>
#include <QFile>

#include "CostManagement.h"
#include "WinMsgFilter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QFile file("./qss/MaterialDark.qss");
	if (file.open(QFile::ReadOnly))
	{
		a.setStyleSheet(file.readAll());
		file.close();
	}

	WinMsgFilter wfm;
	a.installNativeEventFilter(&wfm);

    CostManagement w;
	
	if (w.CheckExit())
	{
		return 0;
	}

    w.show();
    return a.exec();
}
