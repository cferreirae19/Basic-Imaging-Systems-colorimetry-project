#ifndef PROGRAMASI_H
#define PROGRAMASI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ProgramaSI; }
QT_END_NAMESPACE

class ProgramaSI : public QMainWindow
{
    Q_OBJECT

public:
    ProgramaSI(QWidget *parent = nullptr);
    ~ProgramaSI();

    float a[2048];
    float x[90];
    float z[90];
    float y[90];
    float w0[90];
    float w1[2048];
    int b;
    float Xvalue;
    float Yvalue;
    float Zvalue;
    float rescale;
    float Xori;
    float Yori;
    float Zori;
    float pseudoRvalue;
    float pseudoGvalue;
    float pseudoBvalue;

private slots:
    void on_RealColor_Screen_linkActivated(const QString &link);

    void on_PseudoColor_Screen_linkActivated(const QString &link);

    void on_BFile_clicked();

    void Load(int lines);

    float lerp(float x0, float y0, float x1, float y1, float x);

    void on_BrightnessSlider_valueChanged(int value);

    void on_RGBvalues_linkActivated(const QString &link);

    void on_PseudoR_Slider_valueChanged(int value);

    void on_PseudoG_Slider_valueChanged(int value);

    void on_PseudoB_Slider_valueChanged(int value);

private:
    Ui::ProgramaSI *ui;

    QString Path;

    QPixmap Dib1, Dib2;
};
#endif // PROGRAMASI_H
