/********************************************************************************
** Form generated from reading UI file 'programasi.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMASI_H
#define UI_PROGRAMASI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgramaSI
{
public:
    QWidget *centralwidget;
    QLabel *RealColor_Screen;
    QLabel *PseudoColor_Screen;
    QPushButton *BFile;
    QSlider *BrightnessSlider;
    QLabel *RGBvalues;
    QSlider *PseudoG_Slider;
    QSlider *PseudoR_Slider;
    QSlider *PseudoB_Slider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProgramaSI)
    {
        if (ProgramaSI->objectName().isEmpty())
            ProgramaSI->setObjectName("ProgramaSI");
        ProgramaSI->resize(800, 600);
        centralwidget = new QWidget(ProgramaSI);
        centralwidget->setObjectName("centralwidget");
        RealColor_Screen = new QLabel(centralwidget);
        RealColor_Screen->setObjectName("RealColor_Screen");
        RealColor_Screen->setGeometry(QRect(130, 120, 211, 81));
        RealColor_Screen->setAlignment(Qt::AlignCenter);
        PseudoColor_Screen = new QLabel(centralwidget);
        PseudoColor_Screen->setObjectName("PseudoColor_Screen");
        PseudoColor_Screen->setGeometry(QRect(430, 120, 211, 81));
        PseudoColor_Screen->setAlignment(Qt::AlignCenter);
        BFile = new QPushButton(centralwidget);
        BFile->setObjectName("BFile");
        BFile->setGeometry(QRect(350, 330, 80, 24));
        BrightnessSlider = new QSlider(centralwidget);
        BrightnessSlider->setObjectName("BrightnessSlider");
        BrightnessSlider->setGeometry(QRect(150, 390, 171, 16));
        QFont font;
        font.setBold(false);
        BrightnessSlider->setFont(font);
        BrightnessSlider->setAutoFillBackground(false);
        BrightnessSlider->setMaximum(255);
        BrightnessSlider->setValue(127);
        BrightnessSlider->setSliderPosition(127);
        BrightnessSlider->setOrientation(Qt::Horizontal);
        RGBvalues = new QLabel(centralwidget);
        RGBvalues->setObjectName("RGBvalues");
        RGBvalues->setGeometry(QRect(290, 420, 161, 81));
        RGBvalues->setAlignment(Qt::AlignCenter);
        PseudoG_Slider = new QSlider(centralwidget);
        PseudoG_Slider->setObjectName("PseudoG_Slider");
        PseudoG_Slider->setGeometry(QRect(460, 390, 171, 16));
        PseudoG_Slider->setMinimum(500);
        PseudoG_Slider->setMaximum(600);
        PseudoG_Slider->setValue(550);
        PseudoG_Slider->setOrientation(Qt::Horizontal);
        PseudoR_Slider = new QSlider(centralwidget);
        PseudoR_Slider->setObjectName("PseudoR_Slider");
        PseudoR_Slider->setGeometry(QRect(460, 350, 171, 16));
        PseudoR_Slider->setMinimum(600);
        PseudoR_Slider->setMaximum(700);
        PseudoR_Slider->setValue(650);
        PseudoR_Slider->setOrientation(Qt::Horizontal);
        PseudoB_Slider = new QSlider(centralwidget);
        PseudoB_Slider->setObjectName("PseudoB_Slider");
        PseudoB_Slider->setGeometry(QRect(460, 430, 171, 16));
        PseudoB_Slider->setMinimum(400);
        PseudoB_Slider->setMaximum(500);
        PseudoB_Slider->setValue(450);
        PseudoB_Slider->setOrientation(Qt::Horizontal);
        ProgramaSI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ProgramaSI);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ProgramaSI->setMenuBar(menubar);
        statusbar = new QStatusBar(ProgramaSI);
        statusbar->setObjectName("statusbar");
        ProgramaSI->setStatusBar(statusbar);

        retranslateUi(ProgramaSI);

        QMetaObject::connectSlotsByName(ProgramaSI);
    } // setupUi

    void retranslateUi(QMainWindow *ProgramaSI)
    {
        ProgramaSI->setWindowTitle(QCoreApplication::translate("ProgramaSI", "ProgramaSI", nullptr));
        RealColor_Screen->setText(QCoreApplication::translate("ProgramaSI", "RealColor", nullptr));
        PseudoColor_Screen->setText(QCoreApplication::translate("ProgramaSI", "PseudoColor", nullptr));
        BFile->setText(QCoreApplication::translate("ProgramaSI", "Load File", nullptr));
        RGBvalues->setText(QCoreApplication::translate("ProgramaSI", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProgramaSI: public Ui_ProgramaSI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMASI_H
