/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout;
    OpenGLWidget *openGLWidget;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_4;
    QLabel *label_fpsCounter;
    QGroupBox *groupBox_5;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QPushButton *pushButton;
    QGroupBox *groupBox_12;
    QLabel *label_4;
    QLabel *label_6;
    QGroupBox *groupBox_13;
    QLabel *label_5;
    QLabel *label_7;
    QGroupBox *groupBox_14;
    QLabel *label_8;
    QLabel *label_9;
    QGroupBox *groupBox_4;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QWidget *tab;
    QGroupBox *groupBox_3;
    QSlider *horizontalSlider;
    QLabel *label;
    QLabel *label_2;
    QSlider *horizontalSlider_2;
    QLabel *label_3;
    QSlider *horizontalSlider_3;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_10;
    QGroupBox *groupBox_9;
    QRadioButton *radioButton_12;
    QRadioButton *radioButton_11;
    QSlider *horizontalSlider_4;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QWidget *tab_2;
    QGroupBox *groupBox_10;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_13;
    QRadioButton *radioButton_14;
    QRadioButton *radioButton_15;
    QRadioButton *radioButton_16;
    QRadioButton *radioButton_17;
    QGroupBox *groupBox_11;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_18;
    QRadioButton *radioButton_19;
    QGroupBox *groupBox;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_1;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(1104, 667);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        groupBox_6->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border: 0px;\n"
"}"));
        verticalLayout = new QVBoxLayout(groupBox_6);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        openGLWidget = new OpenGLWidget(groupBox_6);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy1);
        openGLWidget->setCursor(QCursor(Qt::OpenHandCursor));

        verticalLayout->addWidget(openGLWidget);

        groupBox_7 = new QGroupBox(groupBox_6);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setMinimumSize(QSize(0, 48));
        groupBox_7->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border: 0px;\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_7);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_8 = new QGroupBox(groupBox_7);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_8);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_2 = new QPushButton(groupBox_8);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy2);
        pushButton_2->setMinimumSize(QSize(0, 0));
        pushButton_2->setFocusPolicy(Qt::NoFocus);
        pushButton_2->setStyleSheet(QLatin1String("QPushButton {\n"
"	padding: 3px 10px;\n"
"}"));

        horizontalLayout_4->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(groupBox_8);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(100, 0));
        pushButton_3->setFocusPolicy(Qt::NoFocus);
        pushButton_3->setStyleSheet(QLatin1String("QPushButton {\n"
"	padding: 3px 10px;\n"
"}"));

        horizontalLayout_4->addWidget(pushButton_3);

        label_10 = new QLabel(groupBox_8);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_4->addWidget(label_10);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_4 = new QPushButton(groupBox_8);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setFocusPolicy(Qt::NoFocus);
        pushButton_4->setStyleSheet(QLatin1String("QPushButton {\n"
"	padding: 3px 10px;\n"
"}"));

        horizontalLayout_4->addWidget(pushButton_4);


        horizontalLayout_3->addWidget(groupBox_8);

        label_fpsCounter = new QLabel(groupBox_7);
        label_fpsCounter->setObjectName(QStringLiteral("label_fpsCounter"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_fpsCounter->sizePolicy().hasHeightForWidth());
        label_fpsCounter->setSizePolicy(sizePolicy3);
        label_fpsCounter->setMinimumSize(QSize(100, 0));
        label_fpsCounter->setLayoutDirection(Qt::LeftToRight);
        label_fpsCounter->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_fpsCounter);


        verticalLayout->addWidget(groupBox_7);


        horizontalLayout_2->addWidget(groupBox_6);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy4);
        groupBox_5->setMinimumSize(QSize(280, 0));
        groupBox_5->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border: 0px;\n"
"}"));
        tabWidget = new QTabWidget(groupBox_5);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 261, 511));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 390, 81, 31));
        pushButton->setMinimumSize(QSize(0, 0));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QLatin1String("QPushButton {\n"
"	padding: 3px 10px;\n"
"}"));
        groupBox_12 = new QGroupBox(tab_3);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(10, 290, 231, 81));
        groupBox_12->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        label_4 = new QLabel(groupBox_12);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 30, 141, 21));
        label_6 = new QLabel(groupBox_12);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 60, 141, 21));
        groupBox_13 = new QGroupBox(tab_3);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setGeometry(QRect(10, 110, 231, 81));
        groupBox_13->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        label_5 = new QLabel(groupBox_13);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 30, 141, 21));
        label_7 = new QLabel(groupBox_13);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 60, 81, 21));
        groupBox_14 = new QGroupBox(tab_3);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        groupBox_14->setGeometry(QRect(10, 200, 231, 101));
        groupBox_14->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        label_8 = new QLabel(groupBox_14);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 30, 101, 21));
        label_9 = new QLabel(groupBox_14);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 60, 71, 21));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 10, 231, 91));
        groupBox_4->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        radioButton_6 = new QRadioButton(groupBox_4);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(0, 30, 112, 26));
        radioButton_6->setFocusPolicy(Qt::NoFocus);
        radioButton_6->setChecked(true);
        radioButton_7 = new QRadioButton(groupBox_4);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(0, 60, 112, 26));
        radioButton_7->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 190, 221, 121));
        groupBox_3->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        horizontalSlider = new QSlider(groupBox_3);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(70, 30, 151, 21));
        horizontalSlider->setFocusPolicy(Qt::NoFocus);
        horizontalSlider->setMaximum(12);
        horizontalSlider->setPageStep(2);
        horizontalSlider->setSliderPosition(2);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 30, 66, 21));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 60, 66, 21));
        horizontalSlider_2 = new QSlider(groupBox_3);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(70, 60, 151, 21));
        horizontalSlider_2->setFocusPolicy(Qt::NoFocus);
        horizontalSlider_2->setMaximum(16);
        horizontalSlider_2->setPageStep(2);
        horizontalSlider_2->setSliderPosition(10);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 90, 66, 21));
        horizontalSlider_3 = new QSlider(groupBox_3);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(70, 90, 151, 21));
        horizontalSlider_3->setFocusPolicy(Qt::NoFocus);
        horizontalSlider_3->setMaximum(12);
        horizontalSlider_3->setPageStep(2);
        horizontalSlider_3->setSliderPosition(2);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 231, 181));
        groupBox_2->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        groupBox_2->setCheckable(false);
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(0, 60, 131, 26));
        radioButton_4->setFocusPolicy(Qt::NoFocus);
        radioButton_4->setChecked(true);
        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(0, 90, 131, 26));
        radioButton_5->setFocusPolicy(Qt::NoFocus);
        radioButton_5->setChecked(false);
        radioButton_8 = new QRadioButton(groupBox_2);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        radioButton_8->setGeometry(QRect(0, 30, 131, 26));
        radioButton_8->setFocusPolicy(Qt::NoFocus);
        radioButton_9 = new QRadioButton(groupBox_2);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));
        radioButton_9->setGeometry(QRect(0, 120, 112, 26));
        radioButton_9->setFocusPolicy(Qt::NoFocus);
        radioButton_10 = new QRadioButton(groupBox_2);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));
        radioButton_10->setGeometry(QRect(0, 150, 112, 26));
        radioButton_10->setFocusPolicy(Qt::NoFocus);
        groupBox_9 = new QGroupBox(tab);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setGeometry(QRect(10, 310, 231, 151));
        groupBox_9->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        radioButton_12 = new QRadioButton(groupBox_9);
        radioButton_12->setObjectName(QStringLiteral("radioButton_12"));
        radioButton_12->setGeometry(QRect(0, 30, 151, 26));
        radioButton_12->setFocusPolicy(Qt::NoFocus);
        radioButton_11 = new QRadioButton(groupBox_9);
        radioButton_11->setObjectName(QStringLiteral("radioButton_11"));
        radioButton_11->setGeometry(QRect(0, 60, 241, 26));
        radioButton_11->setFocusPolicy(Qt::NoFocus);
        radioButton_11->setChecked(true);
        horizontalSlider_4 = new QSlider(groupBox_9);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setGeometry(QRect(120, 90, 101, 20));
        horizontalSlider_4->setFocusPolicy(Qt::NoFocus);
        horizontalSlider_4->setMinimum(980);
        horizontalSlider_4->setMaximum(999);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        checkBox_4 = new QCheckBox(groupBox_9);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setGeometry(QRect(20, 80, 95, 41));
        checkBox_4->setFocusPolicy(Qt::NoFocus);
        checkBox_5 = new QCheckBox(groupBox_9);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setGeometry(QRect(20, 110, 95, 31));
        checkBox_5->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox_10 = new QGroupBox(tab_2);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(10, 10, 241, 441));
        groupBox_10->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        radioButton = new QRadioButton(groupBox_10);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(0, 30, 112, 26));
        radioButton->setFocusPolicy(Qt::NoFocus);
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(groupBox_10);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(0, 60, 191, 26));
        radioButton_2->setFocusPolicy(Qt::NoFocus);
        radioButton_13 = new QRadioButton(groupBox_10);
        radioButton_13->setObjectName(QStringLiteral("radioButton_13"));
        radioButton_13->setGeometry(QRect(0, 210, 171, 26));
        radioButton_13->setFocusPolicy(Qt::NoFocus);
        radioButton_13->setChecked(false);
        radioButton_14 = new QRadioButton(groupBox_10);
        radioButton_14->setObjectName(QStringLiteral("radioButton_14"));
        radioButton_14->setGeometry(QRect(0, 90, 201, 26));
        radioButton_14->setFocusPolicy(Qt::NoFocus);
        radioButton_15 = new QRadioButton(groupBox_10);
        radioButton_15->setObjectName(QStringLiteral("radioButton_15"));
        radioButton_15->setGeometry(QRect(0, 120, 191, 26));
        radioButton_15->setFocusPolicy(Qt::NoFocus);
        radioButton_16 = new QRadioButton(groupBox_10);
        radioButton_16->setObjectName(QStringLiteral("radioButton_16"));
        radioButton_16->setGeometry(QRect(0, 150, 191, 26));
        radioButton_16->setFocusPolicy(Qt::NoFocus);
        radioButton_17 = new QRadioButton(groupBox_10);
        radioButton_17->setObjectName(QStringLiteral("radioButton_17"));
        radioButton_17->setGeometry(QRect(0, 180, 241, 26));
        radioButton_17->setFocusPolicy(Qt::NoFocus);
        groupBox_11 = new QGroupBox(groupBox_10);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setGeometry(QRect(0, 240, 241, 181));
        groupBox_11->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        radioButton_3 = new QRadioButton(groupBox_11);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(0, 30, 151, 26));
        radioButton_3->setFocusPolicy(Qt::NoFocus);
        radioButton_3->setChecked(true);
        radioButton_18 = new QRadioButton(groupBox_11);
        radioButton_18->setObjectName(QStringLiteral("radioButton_18"));
        radioButton_18->setGeometry(QRect(0, 60, 151, 26));
        radioButton_18->setFocusPolicy(Qt::NoFocus);
        radioButton_19 = new QRadioButton(groupBox_11);
        radioButton_19->setObjectName(QStringLiteral("radioButton_19"));
        radioButton_19->setGeometry(QRect(0, 90, 151, 26));
        radioButton_19->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_2, QString());
        groupBox = new QGroupBox(groupBox_5);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 540, 271, 101));
        groupBox->setAutoFillBackground(false);
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        checkBox_1 = new QCheckBox(groupBox);
        checkBox_1->setObjectName(QStringLiteral("checkBox_1"));
        checkBox_1->setGeometry(QRect(80, 30, 101, 26));
        checkBox_1->setFocusPolicy(Qt::NoFocus);
        checkBox_1->setChecked(false);
        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(0, 30, 61, 26));
        checkBox_2->setFocusPolicy(Qt::NoFocus);
        checkBox_2->setChecked(true);
        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(180, 30, 81, 26));
        checkBox_3->setFocusPolicy(Qt::NoFocus);
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(90, 70, 61, 31));
        pushButton_6->setFocusPolicy(Qt::NoFocus);
        pushButton_6->setStyleSheet(QLatin1String("QPushButton {\n"
"	padding: 3px 10px;\n"
"}"));
        pushButton_6->setCheckable(true);
        pushButton_6->setChecked(false);
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(160, 70, 103, 31));
        pushButton_5->setFocusPolicy(Qt::NoFocus);
        pushButton_5->setStyleSheet(QLatin1String("QPushButton {\n"
"	padding: 3px 10px;\n"
"}"));
        pushButton_5->setCheckable(true);
        pushButton_1 = new QPushButton(groupBox);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(0, 70, 81, 31));
        pushButton_1->setFocusPolicy(Qt::NoFocus);
        pushButton_1->setStyleSheet(QLatin1String("QPushButton {\n"
"	padding: 3px 10px;\n"
"}"));
        pushButton_1->setCheckable(true);
        pushButton_1->setChecked(true);

        horizontalLayout_2->addWidget(groupBox_5);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), openGLWidget, SLOT(reset()));
        QObject::connect(openGLWidget, SIGNAL(fpsChanged(QString)), label_fpsCounter, SLOT(setText(QString)));
        QObject::connect(radioButton_6, SIGNAL(clicked()), openGLWidget, SLOT(switchToOrthogonal()));
        QObject::connect(radioButton_7, SIGNAL(clicked()), openGLWidget, SLOT(switchToPerspective()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), openGLWidget, SLOT(selectPrevModel()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), openGLWidget, SLOT(selectNextModel()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), openGLWidget, SLOT(toggleBackground()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), openGLWidget, SLOT(saveAsImage()));
        QObject::connect(checkBox_2, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToSolid(bool)));
        QObject::connect(checkBox_1, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToWireframe(bool)));
        QObject::connect(checkBox_3, SIGNAL(toggled(bool)), openGLWidget, SLOT(addNormalDisplay(bool)));
        QObject::connect(horizontalSlider_2, SIGNAL(valueChanged(int)), openGLWidget, SLOT(tuneDiffuseLight(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), openGLWidget, SLOT(tuneAmbientLight(int)));
        QObject::connect(radioButton_8, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToZShading(bool)));
        QObject::connect(horizontalSlider_3, SIGNAL(valueChanged(int)), openGLWidget, SLOT(tuneSpecularLight(int)));
        QObject::connect(radioButton_5, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToPhongShading(bool)));
        QObject::connect(radioButton_10, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToNormalShading(bool)));
        QObject::connect(radioButton_9, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToCellShading(bool)));
        QObject::connect(radioButton_4, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToFlatShading(bool)));
        QObject::connect(radioButton_12, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToDirectionalLight(bool)));
        QObject::connect(checkBox_5, SIGNAL(toggled(bool)), openGLWidget, SLOT(toggleShadow(bool)));
        QObject::connect(radioButton_17, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureLML(bool)));
        QObject::connect(radioButton_16, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureNML(bool)));
        QObject::connect(checkBox_4, SIGNAL(toggled(bool)), openGLWidget, SLOT(turnOnSpotlight(bool)));
        QObject::connect(radioButton_2, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureLinear(bool)));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureNearest(bool)));
        QObject::connect(radioButton_11, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToPointLight(bool)));
        QObject::connect(horizontalSlider_4, SIGNAL(valueChanged(int)), openGLWidget, SLOT(changeSpotlightAngle(int)));
        QObject::connect(radioButton_13, SIGNAL(toggled(bool)), openGLWidget, SLOT(turnOffTexture(bool)));
        QObject::connect(radioButton_14, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureNMN(bool)));
        QObject::connect(radioButton_15, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureLMN(bool)));
        QObject::connect(radioButton_3, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureWrapping(bool)));
        QObject::connect(radioButton_18, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureMirroring(bool)));
        QObject::connect(radioButton_19, SIGNAL(toggled(bool)), openGLWidget, SLOT(switchToTextureClamping(bool)));
        QObject::connect(pushButton_1, SIGNAL(toggled(bool)), openGLWidget, SLOT(toggleCulling(bool)));
        QObject::connect(pushButton_6, SIGNAL(toggled(bool)), openGLWidget, SLOT(toggleShowAxes(bool)));
        QObject::connect(openGLWidget, SIGNAL(modelChanged(QString)), label_10, SLOT(setText(QString)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "3D Graphics Engine", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\342\227\200 Last Model", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Next Model \342\226\266", 0));
        label_10->setText(QApplication::translate("MainWindow", "Model", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "\342\244\223 Save Image", 0));
        label_fpsCounter->setText(QApplication::translate("MainWindow", "fps", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\342\206\272 Reset", 0));
        groupBox_12->setTitle(QApplication::translate("MainWindow", "Translation", 0));
        label_4->setText(QApplication::translate("MainWindow", "Shift + Mouse Drag", 0));
        label_6->setText(QApplication::translate("MainWindow", "Shift + Key A/D/S/W", 0));
        groupBox_13->setTitle(QApplication::translate("MainWindow", "Rotation", 0));
        label_5->setText(QApplication::translate("MainWindow", "Mouse Drag", 0));
        label_7->setText(QApplication::translate("MainWindow", "Arrow Keys", 0));
        groupBox_14->setTitle(QApplication::translate("MainWindow", "Scaling", 0));
        label_8->setText(QApplication::translate("MainWindow", "Mouse Wheel", 0));
        label_9->setText(QApplication::translate("MainWindow", "Key - / +", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Projection", 0));
        radioButton_6->setText(QApplication::translate("MainWindow", "Orthogonal", 0));
        radioButton_7->setText(QApplication::translate("MainWindow", "Perspective", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Transform", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Lighting", 0));
        label->setText(QApplication::translate("MainWindow", "Ambient", 0));
        label_2->setText(QApplication::translate("MainWindow", "Diffuse", 0));
        label_3->setText(QApplication::translate("MainWindow", "Specular", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Shading", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "Flat Shading", 0));
        radioButton_5->setText(QApplication::translate("MainWindow", "Phong Shading", 0));
        radioButton_8->setText(QApplication::translate("MainWindow", "Depth Shading", 0));
        radioButton_9->setText(QApplication::translate("MainWindow", "Cell Shading", 0));
        radioButton_10->setText(QApplication::translate("MainWindow", "Normal Map", 0));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "Light Source", 0));
        radioButton_12->setText(QApplication::translate("MainWindow", "Directional Light", 0));
        radioButton_11->setText(QApplication::translate("MainWindow", "Point Light (Right Click)", 0));
        checkBox_4->setText(QApplication::translate("MainWindow", "Spotlight", 0));
        checkBox_5->setText(QApplication::translate("MainWindow", "Shadow", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Lighting", 0));
        groupBox_10->setTitle(QApplication::translate("MainWindow", "Texture Mapping", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Nearest", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Linear (Bilinear)", 0));
        radioButton_13->setText(QApplication::translate("MainWindow", "Off", 0));
        radioButton_14->setText(QApplication::translate("MainWindow", "Nearest-Mipmap-Nearest", 0));
        radioButton_15->setText(QApplication::translate("MainWindow", "Linear-Mipmap-Nearest", 0));
        radioButton_16->setText(QApplication::translate("MainWindow", "Nearest-Mipmap-Linear", 0));
        radioButton_17->setText(QApplication::translate("MainWindow", "Linear-Mipmap-Linear (Trilinear)", 0));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "Texture Addressing", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "Wrapping", 0));
        radioButton_18->setText(QApplication::translate("MainWindow", "Mirroring", 0));
        radioButton_19->setText(QApplication::translate("MainWindow", "Clamping", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Texture", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Rendering", 0));
        checkBox_1->setText(QApplication::translate("MainWindow", "Wireframe", 0));
        checkBox_2->setText(QApplication::translate("MainWindow", "Solid", 0));
        checkBox_3->setText(QApplication::translate("MainWindow", "Normals", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "Axes", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Background", 0));
        pushButton_1->setText(QApplication::translate("MainWindow", "Culling", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
