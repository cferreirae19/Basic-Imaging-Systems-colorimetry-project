#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include "programasi.h"
#include "./ui_programasi.h"

ProgramaSI::ProgramaSI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProgramaSI)
{
    ui->setupUi(this);
    b = 127;
}

ProgramaSI::~ProgramaSI()
{
    delete ui;
}


void ProgramaSI::on_RealColor_Screen_linkActivated(const QString &link)
{

}


void ProgramaSI::on_PseudoColor_Screen_linkActivated(const QString &link)
{

}


//--------------------------------------------------------------------------------------------------------------------------------------
//----------- Halla valores X,Y,Z multiplicando las componentes de nuestra imagen por las componentes de las curvas estándar -----------
//--------------------------------------------------------------------------------------------------------------------------------------
void ProgramaSI::on_BFile_clicked()
{
    // Cargamos las curvas estándar
        Load(90);
        // Llamada a la función Load() para seleccionar el archivo con los datos que vamos a utilizar
        Load(2048);

        //TESTING
        //qDebug()<<x[0]<<x[1]<<x[2]<<a[0]<<a[1]<<a[2];

        // Iteramos a través del array para poder eliminar aquellos valores por debajo de 380 nm (UV) y por encima de 825 nm (IR)
        int minIndex;
        int maxIndex;
        for (int k=0;k<(sizeof(w1)/sizeof(float));k++) {
            if (w1[k] >= w0[0]) {
                minIndex = k;
                break;
            }
        }
        for (int j=0;j<(sizeof(w1)/sizeof(float));j++) {
            if (w1[j] <= w0[89]) {
                maxIndex = j;
            }
        }

        //Arrays en los que se almacenarán los resultados de la multiplicación
        float xMult[(maxIndex-minIndex+1)];
        float yMult[(maxIndex-minIndex+1)];
        float zMult[(maxIndex-minIndex+1)];

        //Valores "finales" de XYZ (pre-reescalado)
        Xvalue = 0;
        Yvalue = 0;
        Zvalue = 0;

        //Variables para la interpolación
        float ampX;
        float ampY;
        float ampZ;

        //Límites inferior y superior de longitud de onda
        int lowerBound = 380;
        int upperBound = 385;

        //Multiplicamos las curvas estándar X,Y,Z por la componente de nuestra imagen
        for (int n=minIndex;n<maxIndex;n++) {   //Iteramos entre la 380nm (minIndex) y 825nm (maxIndex)

            if (w1[n] > upperBound) {  //Si la longitud de onda es mayor que el límite superior
                lowerBound = upperBound;    //Redefinimos el límite superior como límite inferior
                upperBound += 5;    //El límite superior siempre será 5 unidades mayor que el inferior
            }

            // Interpolamos
            ampX = lerp(lowerBound,x[(lowerBound-380)/5],upperBound,x[(upperBound-380)/5],w1[n]);
            ampY = lerp(lowerBound,y[(lowerBound-380)/5],upperBound,y[(upperBound-380)/5],w1[n]);
            ampZ = lerp(lowerBound,z[(lowerBound-380)/5],upperBound,z[(upperBound-380)/5],w1[n]);

            //TESTING
//            if (n>=minIndex && n<=minIndex+2) {
//                qDebug()<<ampX<<ampY<<ampZ;
//            }

            //Multiplicamos el valor de las curvas estándar obtenido mediante interpolación por el valor de amplitud de la fila n-ésima de nuestro fichero
            xMult[n-minIndex] = ampX*a[n];
            yMult[n-minIndex] = ampY*a[n];
            zMult[n-minIndex] = ampZ*a[n];

            //TESTING
//            if (n>=minIndex && n<=minIndex+2) {
//                        qDebug()<<xMult[n-minIndex];
//            }

            //Sumamos todas los elementos de cada array para obtener 3 valores "finales" (aún debemos reescalarlos)
            Xvalue += xMult[n-minIndex];
            Yvalue += yMult[n-minIndex];
            Zvalue += zMult[n-minIndex];
        }

        //TESTING
        //qDebug()<<Xvalue<<Yvalue<<Zvalue;

        //TESTING
        //qDebug()<<rescale<<b;

        Xori = Xvalue;
        Yori = Yvalue;
        Zori = Zvalue;

        //TESTING
        //qDebug()<<Xvalue<<Yvalue<<Zvalue;

        on_BrightnessSlider_valueChanged(ui->BrightnessSlider->value());

        // Iteramos a través del array para poder eliminar aquellos valores por debajo de 380 nm (UV) y por encima de 825 nm (IR)
        for (int k=0;k<(sizeof(w1)/sizeof(float));k++) {
            if (w1[k] >= 400) {
                minIndexB = k;
                break;
            }
        }
        for (int j=0;j<(sizeof(w1)/sizeof(float));j++) {
            if (w1[j] <= 500) {
                maxIndexB = j;
            }
        }
        // Iteramos a través del array para poder eliminar aquellos valores por debajo de 380 nm (UV) y por encima de 825 nm (IR)
        for (int k=0;k<(sizeof(w1)/sizeof(float));k++) {
            if (w1[k] >= 500) {
                minIndexG = k;
                break;
            }
        }
        for (int j=0;j<(sizeof(w1)/sizeof(float));j++) {
            if (w1[j] <= 600) {
                maxIndexG = j;
            }
        }
        // Iteramos a través del array para poder eliminar aquellos valores por debajo de 380 nm (UV) y por encima de 825 nm (IR)
        for (int k=0;k<(sizeof(w1)/sizeof(float));k++) {
            if (w1[k] >= 600) {
                minIndexR = k;
                break;
            }
        }
        for (int j=0;j<(sizeof(w1)/sizeof(float));j++) {
            if (w1[j] <= 700) {
                maxIndexR = j;
            }
        }
}


//-------------------------------------------------
//----------- Carga una imagen de disco -----------
//-------------------------------------------------
void ProgramaSI::Load(int lines)
{
    ui->BrightnessSlider->setValue(127);

    // Para el archivo "ciexyzjv.txt"
    if (lines == 90) {
        QString file = "ciexyzjv.txt";
        // Si no escogió nada, nos vamos
        if(file.isEmpty()) return;
        //Leemos el archivo con nombre "file"
        QFile In(file);
        // Archivo con texto para lectura
        if (In.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream sIn(&In);
            for(int i=0;i<lines;i++)  sIn>>w0[i]>>x[i]>>y[i]>>z[i];
            In.close();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Couldn't load the file");
            msgBox.exec();
        }
    }
    // Para el resto de archivos
    else {
    // Permite al usuario escoger un fichero de imagen
    QString file = QFileDialog::getOpenFileName(this,tr("Open file"),Path,tr("Image Files (*.txt)"));
    // Si no escogió nada, nos vamos
    if(file.isEmpty()) return;
    //Leemos el archivo con nombre "file"
    QFile In(file);
    // Archivo con texto para lectura
    if (In.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream sIn(&In);
        for(int i=0;i<lines;i++)  sIn>>w1[i]>>a[i];
        In.close();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Couldn't load the file");
        msgBox.exec();
    }
    }
}


//--------------------------------------------
//----------- Interpolación linear -----------
//--------------------------------------------
float ProgramaSI::lerp(float x0, float y0, float x1, float y1, float x) {

  return (y0*((x1-x)/(x1-x0))+y1*((x-x0)/(x1-x0)));

}


//--------------------------------------------
//------------- Cambio de brillo -------------
//--------------------------------------------
void ProgramaSI::on_BrightnessSlider_valueChanged(int value)
{
    b = value;

    // Código copìado de la función principal para que se vuelva a ejecutar cada vez que se cambie el slider de luminancia
    Xvalue = (Xori/Yori)*b;
    Yvalue = b;
    Zvalue = (Zori/Yori)*b;

    //TESTING
    //qDebug()<<Xvalue<<Yvalue<<Zvalue;

    //Conversión XYZ -> RGB
    int Rvalue = (3.240749*Xvalue-1.53715*Yvalue-0.498535*Zvalue);//>255?255:(3.240749*Xvalue-1.53715*Yvalue-0.498535*Zvalue)<0?0:(3.240749*Xvalue-1.53715*Yvalue-0.498535*Zvalue);
    int Gvalue = (-0.969256*Xvalue+1.875992*Yvalue+0.041556*Zvalue);//>255?255:(-0.969256*Xvalue+1.875992*Yvalue+0.041556*Zvalue)<0?0:(-0.969256*Xvalue+1.875992*Yvalue+0.041556*Zvalue);
    int Bvalue = (0.055648*Xvalue-0.204043*Yvalue+1.057311*Zvalue);//>255?255:(0.055648*Xvalue-0.204043*Yvalue+1.057311*Zvalue)<0?0:(0.055648*Xvalue-0.204043*Yvalue+1.057311*Zvalue);
    uchar R = Rvalue>255?255:Rvalue<0?0:Rvalue;
    uchar G = Gvalue>255?255:Gvalue<0?0:Gvalue;
    uchar B = Bvalue>255?255:Bvalue<0?0:Bvalue;

    //TESTING
    qDebug()<<Rvalue<<Gvalue<<Bvalue;

    // Inicializamos a negro los lienzos (QPixmap) y los asociamos a las "pantallas" gráficas (QLabel)
    //   Le damos tamaño
    Dib1=QPixmap(256,100);
    //   Lo pintamos de negro
    Dib1.fill(QColor::fromRgb(R,G,B));
    //   Lo asignamos a un QLabel
    ui->RealColor_Screen->setPixmap(Dib1);

    // Mostramos valores de RGB (antes y después del recorte) en una label
    QString s = QString::number(Rvalue);
    QString sRa = QString::number(R);
    QString sGb = QString::number(Gvalue);
    QString sGa = QString::number(G);
    QString sBb = QString::number(Bvalue);
    QString sBa = QString::number(B);
    s = s + " " + sGb + " " + sBb + "\n" + sRa + " " + sGa + " " + sBa;
    ui->RGBvalues->setText(s);
}



void ProgramaSI::on_RGBvalues_linkActivated(const QString &link)
{

}



void ProgramaSI::on_PseudoR_Slider_valueChanged(int value)
{
    int i = 0;
    while ((value-w1[++i])<0.5);
    pseudoRvalue = w1[i];
}



void ProgramaSI::on_PseudoG_Slider_valueChanged(int value)
{
    int i = 0;
    while ((value-w1[++i])<0.5);
    pseudoGvalue = w1[i];
}



void ProgramaSI::on_PseudoB_Slider_valueChanged(int value)
{
    int i = 0;
    while ((value-w1[++i])<0.5);
    pseudoBvalue = w1[i];
}


//--------------------------------------------------
//------------- Cálculo de pseudocolor -------------
//--------------------------------------------------
void ProgramaSI::ObtainPseudoColor() {
    // Calcular luminancia para reescalado
    float y = 0.2125*pseudoRvalue + 0.7154*pseudoGvalue + 0.0721*pseudoBvalue;

    // TO DO
    // Reescalado -> Multiplicar por valor de slider de brillo para pseudocolor (hay que añadir), y dividir por luminancia (ya calculada)
    //Mostrar componentes ya reescaladas, que forman un color (R,G,B)
}
