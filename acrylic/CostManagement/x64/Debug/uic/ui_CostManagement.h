/********************************************************************************
** Form generated from reading UI file 'CostManagement.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COSTMANAGEMENT_H
#define UI_COSTMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CostManagementClass
{
public:
    QWidget *centralWidget;
    QPushButton *buttonAdd;
    QPushButton *buttonFolder;
    QPushButton *buttonDelete;
    QPushButton *buttonExit;
    QPushButton *buttonMinimize;
    QLabel *label;
    QLabel *appTitle;
    QTableWidget *costTable;
    QDoubleSpinBox *newCostInput;
    QLineEdit *newCostDescription;
    QDoubleSpinBox *curRemain;
    QDoubleSpinBox *weekCost;
    QDoubleSpinBox *monthCost;
    QDoubleSpinBox *weekEat;
    QDoubleSpinBox *monthEat;
    QDoubleSpinBox *monthOther;
    QLabel *curRemainLabel;
    QLabel *newCostLable;
    QLabel *newCostDescriptionLable;
    QLabel *weekCostLabel;
    QLabel *monthCostLabel;
    QLabel *weekEatLabel;
    QLabel *monthEatLabel;
    QLabel *monthOtherLabel;
    QLabel *labelBackground;

    void setupUi(QMainWindow *CostManagementClass)
    {
        if (CostManagementClass->objectName().isEmpty())
            CostManagementClass->setObjectName(QStringLiteral("CostManagementClass"));
        CostManagementClass->resize(800, 700);
        centralWidget = new QWidget(CostManagementClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        buttonAdd = new QPushButton(centralWidget);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));
        buttonAdd->setGeometry(QRect(700, 550, 71, 41));
        buttonAdd->setMaximumSize(QSize(240, 120));
        buttonFolder = new QPushButton(centralWidget);
        buttonFolder->setObjectName(QStringLiteral("buttonFolder"));
        buttonFolder->setGeometry(QRect(700, 630, 71, 41));
        buttonFolder->setMaximumSize(QSize(240, 120));
        buttonDelete = new QPushButton(centralWidget);
        buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
        buttonDelete->setGeometry(QRect(700, 590, 71, 41));
        buttonDelete->setMaximumSize(QSize(240, 120));
        buttonExit = new QPushButton(centralWidget);
        buttonExit->setObjectName(QStringLiteral("buttonExit"));
        buttonExit->setGeometry(QRect(760, 30, 24, 24));
        buttonExit->setMinimumSize(QSize(24, 24));
        buttonExit->setMaximumSize(QSize(24, 24));
        buttonMinimize = new QPushButton(centralWidget);
        buttonMinimize->setObjectName(QStringLiteral("buttonMinimize"));
        buttonMinimize->setGeometry(QRect(730, 30, 24, 24));
        buttonMinimize->setMinimumSize(QSize(24, 24));
        buttonMinimize->setMaximumSize(QSize(24, 24));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(16, 20, 20, 20));
        label->setMinimumSize(QSize(20, 20));
        label->setMaximumSize(QSize(20, 20));
        label->setStyleSheet(QStringLiteral("image:url(:/CostManagement/resource/CostManagement.png);"));
        appTitle = new QLabel(centralWidget);
        appTitle->setObjectName(QStringLiteral("appTitle"));
        appTitle->setGeometry(QRect(46, 24, 54, 12));
        costTable = new QTableWidget(centralWidget);
        if (costTable->columnCount() < 3)
            costTable->setColumnCount(3);
        costTable->setObjectName(QStringLiteral("costTable"));
        costTable->setGeometry(QRect(30, 70, 741, 351));
        costTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        costTable->setRowCount(0);
        costTable->setColumnCount(3);
        costTable->horizontalHeader()->setVisible(true);
        costTable->horizontalHeader()->setCascadingSectionResizes(false);
        costTable->verticalHeader()->setVisible(false);
        costTable->verticalHeader()->setCascadingSectionResizes(false);
        newCostInput = new QDoubleSpinBox(centralWidget);
        newCostInput->setObjectName(QStringLiteral("newCostInput"));
        newCostInput->setGeometry(QRect(290, 560, 101, 31));
        newCostInput->setMinimum(-1e+6);
        newCostInput->setMaximum(1e+6);
        newCostDescription = new QLineEdit(centralWidget);
        newCostDescription->setObjectName(QStringLiteral("newCostDescription"));
        newCostDescription->setGeometry(QRect(500, 560, 151, 31));
        curRemain = new QDoubleSpinBox(centralWidget);
        curRemain->setObjectName(QStringLiteral("curRemain"));
        curRemain->setGeometry(QRect(80, 560, 101, 31));
        curRemain->setMinimum(-1e+6);
        curRemain->setMaximum(1e+6);
        weekCost = new QDoubleSpinBox(centralWidget);
        weekCost->setObjectName(QStringLiteral("weekCost"));
        weekCost->setGeometry(QRect(80, 600, 101, 31));
        weekCost->setMinimum(-1e+6);
        weekCost->setMaximum(1e+6);
        monthCost = new QDoubleSpinBox(centralWidget);
        monthCost->setObjectName(QStringLiteral("monthCost"));
        monthCost->setGeometry(QRect(290, 600, 91, 31));
        monthCost->setMinimum(-1e+6);
        monthCost->setMaximum(1e+6);
        weekEat = new QDoubleSpinBox(centralWidget);
        weekEat->setObjectName(QStringLiteral("weekEat"));
        weekEat->setGeometry(QRect(80, 640, 101, 31));
        weekEat->setMinimum(-1e+6);
        weekEat->setMaximum(1e+6);
        monthEat = new QDoubleSpinBox(centralWidget);
        monthEat->setObjectName(QStringLiteral("monthEat"));
        monthEat->setGeometry(QRect(290, 640, 91, 31));
        monthEat->setMinimum(-1e+6);
        monthEat->setMaximum(1e+6);
        monthOther = new QDoubleSpinBox(centralWidget);
        monthOther->setObjectName(QStringLiteral("monthOther"));
        monthOther->setGeometry(QRect(500, 640, 81, 31));
        monthOther->setMinimum(-1e+6);
        monthOther->setValue(0);
        curRemainLabel = new QLabel(centralWidget);
        curRemainLabel->setObjectName(QStringLiteral("curRemainLabel"));
        curRemainLabel->setGeometry(QRect(10, 570, 54, 12));
        newCostLable = new QLabel(centralWidget);
        newCostLable->setObjectName(QStringLiteral("newCostLable"));
        newCostLable->setGeometry(QRect(210, 570, 54, 12));
        newCostDescriptionLable = new QLabel(centralWidget);
        newCostDescriptionLable->setObjectName(QStringLiteral("newCostDescriptionLable"));
        newCostDescriptionLable->setGeometry(QRect(430, 570, 54, 12));
        weekCostLabel = new QLabel(centralWidget);
        weekCostLabel->setObjectName(QStringLiteral("weekCostLabel"));
        weekCostLabel->setGeometry(QRect(10, 610, 71, 16));
        monthCostLabel = new QLabel(centralWidget);
        monthCostLabel->setObjectName(QStringLiteral("monthCostLabel"));
        monthCostLabel->setGeometry(QRect(193, 610, 71, 20));
        weekEatLabel = new QLabel(centralWidget);
        weekEatLabel->setObjectName(QStringLiteral("weekEatLabel"));
        weekEatLabel->setGeometry(QRect(13, 650, 61, 20));
        monthEatLabel = new QLabel(centralWidget);
        monthEatLabel->setObjectName(QStringLiteral("monthEatLabel"));
        monthEatLabel->setGeometry(QRect(203, 640, 61, 20));
        monthOtherLabel = new QLabel(centralWidget);
        monthOtherLabel->setObjectName(QStringLiteral("monthOtherLabel"));
        monthOtherLabel->setGeometry(QRect(420, 650, 54, 12));
        labelBackground = new QLabel(centralWidget);
        labelBackground->setObjectName(QStringLiteral("labelBackground"));
        labelBackground->setGeometry(QRect(0, -10, 811, 711));
        CostManagementClass->setCentralWidget(centralWidget);
        labelBackground->raise();
        buttonAdd->raise();
        buttonFolder->raise();
        buttonDelete->raise();
        buttonExit->raise();
        buttonMinimize->raise();
        label->raise();
        appTitle->raise();
        costTable->raise();
        newCostInput->raise();
        newCostDescription->raise();
        curRemain->raise();
        weekCost->raise();
        monthCost->raise();
        weekEat->raise();
        monthEat->raise();
        monthOther->raise();
        curRemainLabel->raise();
        newCostLable->raise();
        newCostDescriptionLable->raise();
        weekCostLabel->raise();
        monthCostLabel->raise();
        weekEatLabel->raise();
        monthEatLabel->raise();
        monthOtherLabel->raise();

        retranslateUi(CostManagementClass);

        QMetaObject::connectSlotsByName(CostManagementClass);
    } // setupUi

    void retranslateUi(QMainWindow *CostManagementClass)
    {
        CostManagementClass->setWindowTitle(QApplication::translate("CostManagementClass", "CostManagementClass", Q_NULLPTR));
        buttonAdd->setText(QApplication::translate("CostManagementClass", "\346\226\260\345\242\236", Q_NULLPTR));
        buttonFolder->setText(QApplication::translate("CostManagementClass", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        buttonDelete->setText(QApplication::translate("CostManagementClass", "\345\210\240\351\231\244", Q_NULLPTR));
        buttonExit->setText(QApplication::translate("CostManagementClass", "\303\227", Q_NULLPTR));
        buttonMinimize->setText(QApplication::translate("CostManagementClass", "-", Q_NULLPTR));
        label->setText(QString());
        appTitle->setText(QApplication::translate("CostManagementClass", "\350\212\261\351\224\200\347\256\241\347\220\206", Q_NULLPTR));
        curRemainLabel->setText(QApplication::translate("CostManagementClass", "\345\211\251\344\275\231\351\207\221\351\242\235\357\274\232", Q_NULLPTR));
        newCostLable->setText(QApplication::translate("CostManagementClass", "\351\207\221\351\242\235\357\274\232", Q_NULLPTR));
        newCostDescriptionLable->setText(QApplication::translate("CostManagementClass", "\346\217\217\350\277\260\357\274\232", Q_NULLPTR));
        weekCostLabel->setText(QApplication::translate("CostManagementClass", "\346\234\254\345\221\250\346\200\273\350\212\261\351\224\200\357\274\232", Q_NULLPTR));
        monthCostLabel->setText(QApplication::translate("CostManagementClass", "\346\234\254\346\234\210\346\200\273\350\212\261\351\224\200\357\274\232", Q_NULLPTR));
        weekEatLabel->setText(QApplication::translate("CostManagementClass", "\346\234\254\345\221\250\351\245\256\351\243\237\357\274\232", Q_NULLPTR));
        monthEatLabel->setText(QApplication::translate("CostManagementClass", "\346\234\254\346\234\210\351\245\256\351\243\237\357\274\232", Q_NULLPTR));
        monthOtherLabel->setText(QApplication::translate("CostManagementClass", "\346\234\254\346\234\210\345\205\266\344\273\226\357\274\232", Q_NULLPTR));
        labelBackground->setText(QApplication::translate("CostManagementClass", "sdfad", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CostManagementClass: public Ui_CostManagementClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COSTMANAGEMENT_H
