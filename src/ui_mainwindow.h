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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    OpenGLWidget *openGLWidget;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QGroupBox *groupBox_3;
    QSlider *horizontalSlider;
    QLabel *label;
    QLabel *label_2;
    QSlider *horizontalSlider_2;
    QLabel *label_3;
    QSlider *horizontalSlider_3;
    QLabel *label_fpsCounter;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QGroupBox *groupBox_4;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(600, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openGLWidget = new OpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 600, 400));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 410, 120, 91));
        groupBox->setAutoFillBackground(false);
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(0, 60, 112, 26));
        radioButton->setChecked(false);
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(0, 30, 112, 26));
        radioButton_2->setChecked(true);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(180, 410, 131, 121));
        groupBox_2->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        groupBox_2->setCheckable(false);
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(0, 30, 131, 26));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(0, 60, 131, 26));
        radioButton_4->setChecked(true);
        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(0, 90, 131, 26));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(340, 410, 221, 121));
        groupBox_3->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        horizontalSlider = new QSlider(groupBox_3);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(70, 30, 151, 21));
        horizontalSlider->setMaximum(10);
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
        horizontalSlider_2->setMaximum(10);
        horizontalSlider_2->setPageStep(2);
        horizontalSlider_2->setSliderPosition(5);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 90, 66, 21));
        horizontalSlider_3 = new QSlider(groupBox_3);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(70, 90, 151, 21));
        horizontalSlider_3->setMaximum(10);
        horizontalSlider_3->setPageStep(2);
        horizontalSlider_3->setSliderPosition(8);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        label_fpsCounter = new QLabel(centralWidget);
        label_fpsCounter->setObjectName(QStringLiteral("label_fpsCounter"));
        label_fpsCounter->setGeometry(QRect(430, 550, 131, 21));
        label_fpsCounter->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(340, 550, 95, 26));
        checkBox->setChecked(true);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(180, 550, 121, 31));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(40, 500, 120, 91));
        groupBox_4->setStyleSheet(QLatin1String("QGroupBox {\n"
"	font-weight: bold;\n"
"	border: 0px;\n"
"}"));
        radioButton_6 = new QRadioButton(groupBox_4);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(0, 30, 112, 26));
        radioButton_6->setChecked(true);
        radioButton_7 = new QRadioButton(groupBox_4);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(0, 60, 112, 26));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(radioButton, SIGNAL(clicked()), openGLWidget, SLOT(switchToWireframe()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), openGLWidget, SLOT(switchToSolid()));
        QObject::connect(pushButton, SIGNAL(clicked()), openGLWidget, SLOT(reset()));
        QObject::connect(radioButton_3, SIGNAL(clicked()), openGLWidget, SLOT(switchToNoShading()));
        QObject::connect(radioButton_4, SIGNAL(clicked()), openGLWidget, SLOT(switchToFlatShading()));
        QObject::connect(radioButton_5, SIGNAL(clicked()), openGLWidget, SLOT(switchToPhongShading()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), openGLWidget, SLOT(tuneAmbientLight(int)));
        QObject::connect(horizontalSlider_2, SIGNAL(valueChanged(int)), openGLWidget, SLOT(tuneDiffuseLight(int)));
        QObject::connect(horizontalSlider_3, SIGNAL(valueChanged(int)), openGLWidget, SLOT(tuneSpecularLight(int)));
        QObject::connect(openGLWidget, SIGNAL(fpsChanged(QString)), label_fpsCounter, SLOT(setText(QString)));
        QObject::connect(checkBox, SIGNAL(clicked()), openGLWidget, SLOT(toggleCulling()));
        QObject::connect(radioButton_6, SIGNAL(clicked()), openGLWidget, SLOT(switchToOrthogonal()));
        QObject::connect(radioButton_7, SIGNAL(clicked()), openGLWidget, SLOT(switchToPerspective()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "3D Graphics Engine", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Mode", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Wireframe", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Solid", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Shading", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "Off", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "Flat Shading", 0));
        radioButton_5->setText(QApplication::translate("MainWindow", "Phong Shading", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Lighting", 0));
        label->setText(QApplication::translate("MainWindow", "Ambient", 0));
        label_2->setText(QApplication::translate("MainWindow", "Diffuse", 0));
        label_3->setText(QApplication::translate("MainWindow", "Specular", 0));
        label_fpsCounter->setText(QApplication::translate("MainWindow", "Frame per second", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Culling", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Reset Position", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "View", 0));
        radioButton_6->setText(QApplication::translate("MainWindow", "Orthogonal", 0));
        radioButton_7->setText(QApplication::translate("MainWindow", "Perspective", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
