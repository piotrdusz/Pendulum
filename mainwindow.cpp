#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

int zmienna=1;

float E;float E_poprz;float E_poprz_poprz;

float f1[3];
float f2[3];
float f1z;float f2z;

float Tp=0.005;
float dt=0.0017;

bool ok=false;
bool trajektoria=false;

QColor link(100,100,100,255);

QColor blue(0,100,255,255);
QColor green(0,255,0,255);
QColor red(255,0,0,255);


QBrush bblue(blue);
QColor white(255,255,255,255);

QBrush bwhite(white);
//------------------------------------------
float pom1;float pom2;
int iter2=100;

float tlumienie_wozka=0.1;
float tlumienie_wahadla=0.2;

int iter=0;
float a=500;
float i=0;
int esize=14;

float g=9.8;
float m1=0.2;
float m2=0.2;
float l1=0.3;float l2=0.3;
float F;
float b0=0.1;float b1=0;float b2=0;
float IA=0.006;float IB=0.006;
float m0=0.5;
float r=0;
float mA=0.1;
float mB=0.1;

double fi1;
double fi2;
double x0;
double ddfi1;
double ddfi2;
double ddx0;
double dfi1;
double dfi2;
double dx0;
double fi_poprz;
double x_poprz;
double dfi1_poprz;
double dfi2_poprz;
double dx_poprz;
double ddfi1_poprz;
double ddfi2_poprz;
double ddx_poprz;

int xo=675;
int yo=500;


float kat;
float pozycja;
float pozycja_zadana=2;

int pox;
int poy;
int pl;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer = new QTimer;
    m_timer->setInterval(10);   //1
    connect(m_timer, SIGNAL(timeout()), this, SLOT(glowna_funkcja()));
    m_timer->start();

    fi1=0;
    fi2=0;
    x0=0;
    pozycja=0;

    fi1=0;
    fi2=0;

    F=3;

    for(int i=0;i<3;i++){f1[i]=0;f2[i]=0;}


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::glowna_funkcja()
{
    i=i+0.01;
iter=iter+1;

if(trajektoria==true){
if(iter==0&&zmienna==1)r=0;
if(iter==100&&zmienna==1){r=-0.5;zmienna=2;}
if(zmienna==2&&iter==600){r=0.5;zmienna=3;}
if(zmienna==3&&fi1<-0.13){r=0.8;zmienna=4;}
if(zmienna==4&&iter==1200){r=-0.2;zmienna=5;}
if(zmienna==5&&fi1>0.13){r=-0.5;zmienna=6;}
if(zmienna==6&&iter==1500){r=-0.5;zmienna=7;}
if(zmienna==7&&iter==1700){zmienna=2;iter=400;}
}
else
    r=0;

if(ok==false)
{F=-( 54.7723 *(x0-r)+43.8986*dx0+257.5083*fi1+5.7595*dfi1 -439.5554*fi2 -67.6810*dfi2);}
else
F=0;

   ddx0 = (F*IA*IB+F*(l1*l1)*(l2*l2)*(m2*m2)+F*IB*(l1*l1)*m1+F*IA*(l2*l2)*m2+F*IB*(l1*l1)*m2-IA*IB*b0*dx0+F*(l1*l1)*(l2*l2)*m1*m2-F*(l1*l1)*(l2*l2)*(m2*m2)*pow(cos(fi1-fi2),2.0)-(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*(m2*m2*m2)*sin(fi1)-(dfi2*dfi2)*(l1*l1)*(l2*l2*l2)*(m2*m2*m2)*sin(fi2)-b0*dx0*(l1*l1)*(l2*l2)*(m2*m2)-IB*b0*dx0*(l1*l1)*m1-IA*b0*dx0*(l2*l2)*m2-IB*b0*dx0*(l1*l1)*m2-IB*(dfi1*dfi1)*(l1*l1*l1)*(m1*m1)*sin(fi1)-IB*(dfi1*dfi1)*(l1*l1*l1)*(m2*m2)*sin(fi1)-IA*(dfi2*dfi2)*(l2*l2*l2)*(m2*m2)*sin(fi2)-IB*b1*dfi1*l1*m1*cos(fi1)-IB*b1*dfi1*l1*m2*cos(fi1)-IA*b2*dfi2*l2*m2*cos(fi2)-IA*(dfi1*dfi1)*l1*(l2*l2)*(m2*m2)*sin(fi1)-IB*(dfi2*dfi2)*(l1*l1)*l2*(m2*m2)*sin(fi2)+IB*g*(l1*l1)*(m1*m1)*cos(fi1)*sin(fi1)+IB*g*(l1*l1)*(m2*m2)*cos(fi1)*sin(fi1)+IA*g*(l2*l2)*(m2*m2)*cos(fi2)*sin(fi2)-(dfi2*dfi2)*(l1*l1)*(l2*l2*l2)*(m2*m2*m2)*cos(fi1)*sin(fi1-fi2)+(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi2)*sin(fi1-fi2)-IA*IB*(dfi1*dfi1)*l1*m1*sin(fi1)-IA*IB*(dfi1*dfi1)*l1*m2*sin(fi1)-IA*IB*(dfi2*dfi2)*l2*m2*sin(fi2)-b0*dx0*(l1*l1)*(l2*l2)*m1*m2+(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*(m2*m2*m2)*sin(fi1)*pow(cos(fi1-fi2),2.0)+(dfi2*dfi2)*(l1*l1)*(l2*l2*l2)*(m2*m2*m2)*sin(fi2)*pow(cos(fi1-fi2),2.0)+g*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*sin(fi1)+g*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi2)*sin(fi2)-(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*m1*(m2*m2)*sin(fi1)*2.0-(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*(m1*m1)*m2*sin(fi1)-(dfi2*dfi2)*(l1*l1)*(l2*l2*l2)*m1*(m2*m2)*sin(fi2)+b0*dx0*(l1*l1)*(l2*l2)*(m2*m2)*pow(cos(fi1-fi2),2.0)-IB*(dfi1*dfi1)*(l1*l1*l1)*m1*m2*sin(fi1)*2.0-b1*dfi1*l1*(l2*l2)*(m2*m2)*cos(fi1)-b2*dfi2*(l1*l1)*l2*(m2*m2)*cos(fi2)-b1*dfi1*l1*(l2*l2)*m1*m2*cos(fi1)-b2*dfi2*(l1*l1)*l2*m1*m2*cos(fi2)+(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*m1*(m2*m2)*sin(fi1)*pow(cos(fi1-fi2),2.0)+IA*(dfi1*dfi1)*l1*(l2*l2)*(m2*m2)*cos(fi2)*sin(fi1-fi2)-IB*(dfi2*dfi2)*(l1*l1)*l2*(m2*m2)*cos(fi1)*sin(fi1-fi2)+g*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*sin(fi1)*2.0+g*(l1*l1)*(l2*l2)*(m1*m1)*m2*cos(fi1)*sin(fi1)+g*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi2)*sin(fi2)+g*(l1*l1)*(l2*l2)*(m2*m2)*mA*cos(fi1)*sin(fi1)*(3.0/2.0)+g*(l1*l1)*(l2*l2)*(m2*m2)*mA*cos(fi2)*sin(fi2)*(1.0/2.0)-(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*cos(fi1-fi2)*sin(fi1-fi2)+(dfi2*dfi2)*(l1*l1)*(l2*l2*l2)*(m2*m2*m2)*cos(fi2)*cos(fi1-fi2)*sin(fi1-fi2)-IA*(dfi1*dfi1)*l1*(l2*l2)*m1*m2*sin(fi1)-IB*(dfi2*dfi2)*(l1*l1)*l2*m1*m2*sin(fi2)+IB*g*(l1*l1)*m1*m2*cos(fi1)*sin(fi1)*2.0+IB*g*(l1*l1)*m1*mA*cos(fi1)*sin(fi1)*(3.0/2.0)+IB*g*(l1*l1)*m2*mA*cos(fi1)*sin(fi1)*(3.0/2.0)+IA*g*(l2*l2)*m2*mA*cos(fi2)*sin(fi2)*(1.0/2.0)-g*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*sin(fi2)*cos(fi1-fi2)-g*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi2)*sin(fi1)*cos(fi1-fi2)-(dfi2*dfi2)*(l1*l1)*(l2*l2*l2)*m1*(m2*m2)*cos(fi1)*sin(fi1-fi2)+(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi2)*sin(fi1-fi2)+b1*dfi1*l1*(l2*l2)*(m2*m2)*cos(fi2)*cos(fi1-fi2)+b2*dfi2*(l1*l1)*l2*(m2*m2)*cos(fi1)*cos(fi1-fi2)-g*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*sin(fi2)*cos(fi1-fi2)-g*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi2)*sin(fi1)*cos(fi1-fi2)-g*(l1*l1)*(l2*l2)*(m2*m2)*mA*cos(fi1)*sin(fi2)*cos(fi1-fi2)*(1.0/2.0)-g*(l1*l1)*(l2*l2)*(m2*m2)*mA*cos(fi2)*sin(fi1)*cos(fi1-fi2)*(3.0/2.0)-IB*(dfi2*dfi2)*(l1*l1)*l2*m1*m2*cos(fi1)*sin(fi1-fi2)+g*(l1*l1)*(l2*l2)*m1*m2*mA*cos(fi1)*sin(fi1)*(3.0/2.0)+g*(l1*l1)*(l2*l2)*m1*m2*mA*cos(fi2)*sin(fi2)*(1.0/2.0)-(dfi1*dfi1)*(l1*l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*cos(fi1-fi2)*sin(fi1-fi2)+b2*dfi2*(l1*l1)*l2*m1*m2*cos(fi1)*cos(fi1-fi2)-g*(l1*l1)*(l2*l2)*m1*m2*mA*cos(fi1)*sin(fi2)*cos(fi1-fi2)*(1.0/2.0))/(IB*(l1*l1)*(m1*m1)+IA*(l2*l2)*(m2*m2)+IB*(l1*l1)*(m2*m2)+IA*IB*m0+IA*IB*m1+IA*IB*m2+(l1*l1)*(l2*l2)*(m2*m2*m2)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi1-fi2),2.0)+(l1*l1)*(l2*l2)*m0*(m2*m2)+(l1*l1)*(l2*l2)*m1*(m2*m2)*2.0+(l1*l1)*(l2*l2)*(m1*m1)*m2+IB*(l1*l1)*m0*m1+IA*(l2*l2)*m0*m2+IB*(l1*l1)*m0*m2+IA*(l2*l2)*m1*m2+IB*(l1*l1)*m1*m2*2.0-IB*(l1*l1)*(m1*m1)*pow(cos(fi1),2.0)-IB*(l1*l1)*(m2*m2)*pow(cos(fi1),2.0)-IA*(l2*l2)*(m2*m2)*pow(cos(fi2),2.0)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi1),2.0)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi2),2.0)+(l1*l1)*(l2*l2)*m0*m1*m2-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi1),2.0)*2.0-(l1*l1)*(l2*l2)*(m1*m1)*m2*pow(cos(fi1),2.0)-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi2),2.0)-IB*(l1*l1)*m1*m2*pow(cos(fi1),2.0)*2.0-(l1*l1)*(l2*l2)*m0*(m2*m2)*pow(cos(fi1-fi2),2.0)-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi1-fi2),2.0)+(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*cos(fi2)*cos(fi1-fi2)*2.0+(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*cos(fi2)*cos(fi1-fi2)*2.0);
   ddfi1 = (-b1*dfi1*(l2*l2)*(m2*m2)-IB*b1*dfi1*m0-IB*b1*dfi1*m1-IB*b1*dfi1*m2+IB*g*l1*(m1*m1)*sin(fi1)+IB*g*l1*(m2*m2)*sin(fi1)-(dfi2*dfi2)*l1*(l2*l2*l2)*(m2*m2*m2)*sin(fi1-fi2)+F*l1*(l2*l2)*(m2*m2)*cos(fi1)+F*IB*l1*m1*cos(fi1)+F*IB*l1*m2*cos(fi1)+g*l1*(l2*l2)*(m2*m2*m2)*sin(fi1)-b1*dfi1*(l2*l2)*m0*m2-b1*dfi1*(l2*l2)*m1*m2+b1*dfi1*(l2*l2)*(m2*m2)*pow(cos(fi2),2.0)-IB*(dfi2*dfi2)*l1*l2*(m2*m2)*sin(fi1-fi2)+g*l1*(l2*l2)*m0*(m2*m2)*sin(fi1)+g*l1*(l2*l2)*m1*(m2*m2)*sin(fi1)*2.0+g*l1*(l2*l2)*(m1*m1)*m2*sin(fi1)+g*l1*(l2*l2)*(m2*m2)*mA*sin(fi1)*(3.0/2.0)-IB*b0*dx0*l1*m1*cos(fi1)-IB*b0*dx0*l1*m2*cos(fi1)-(dfi1*dfi1)*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*sin(fi1)+IB*g*l1*m0*m1*sin(fi1)+IB*g*l1*m0*m2*sin(fi1)+IB*g*l1*m1*m2*sin(fi1)*2.0+IB*g*l1*m0*mA*sin(fi1)*(3.0/2.0)+IB*g*l1*m1*mA*sin(fi1)*(3.0/2.0)+IB*g*l1*m2*mA*sin(fi1)*(3.0/2.0)+(dfi2*dfi2)*l1*(l2*l2*l2)*(m2*m2*m2)*pow(cos(fi2),2.0)*sin(fi1-fi2)-F*l1*(l2*l2)*(m2*m2)*cos(fi2)*cos(fi1-fi2)-(dfi1*dfi1)*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1-fi2)*sin(fi1-fi2)+F*l1*(l2*l2)*m1*m2*cos(fi1)-g*l1*(l2*l2)*(m2*m2*m2)*sin(fi2)*cos(fi1-fi2)-(dfi2*dfi2)*l1*(l2*l2*l2)*m0*(m2*m2)*sin(fi1-fi2)-(dfi2*dfi2)*l1*(l2*l2*l2)*m1*(m2*m2)*sin(fi1-fi2)-IB*(dfi1*dfi1)*(l1*l1)*(m1*m1)*cos(fi1)*sin(fi1)-IB*(dfi1*dfi1)*(l1*l1)*(m2*m2)*cos(fi1)*sin(fi1)+b2*dfi2*l1*l2*(m2*m2)*cos(fi1-fi2)-(dfi2*dfi2)*l1*(l2*l2*l2)*(m2*m2*m2)*cos(fi1)*sin(fi2)-g*l1*(l2*l2)*(m2*m2*m2)*pow(cos(fi2),2.0)*sin(fi1)-b0*dx0*l1*(l2*l2)*(m2*m2)*cos(fi1)-g*l1*(l2*l2)*m0*(m2*m2)*sin(fi2)*cos(fi1-fi2)-g*l1*(l2*l2)*m1*(m2*m2)*sin(fi2)*cos(fi1-fi2)-g*l1*(l2*l2)*(m2*m2)*mA*sin(fi2)*cos(fi1-fi2)*(1.0/2.0)-b0*dx0*l1*(l2*l2)*m1*m2*cos(fi1)+(dfi1*dfi1)*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*cos(fi2)*sin(fi1-fi2)+(dfi1*dfi1)*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi2)*sin(fi1)*cos(fi1-fi2)-IB*(dfi2*dfi2)*l1*l2*m0*m2*sin(fi1-fi2)-IB*(dfi2*dfi2)*l1*l2*m1*m2*sin(fi1-fi2)+g*l1*(l2*l2)*m0*m1*m2*sin(fi1)+g*l1*(l2*l2)*m0*m2*mA*sin(fi1)*(3.0/2.0)+g*l1*(l2*l2)*m1*m2*mA*sin(fi1)*(3.0/2.0)+g*l1*(l2*l2)*(m2*m2*m2)*cos(fi1)*cos(fi2)*sin(fi2)-(dfi2*dfi2)*l1*(l2*l2*l2)*m1*(m2*m2)*cos(fi1)*sin(fi2)-g*l1*(l2*l2)*m1*(m2*m2)*pow(cos(fi2),2.0)*sin(fi1)-g*l1*(l2*l2)*(m2*m2)*mA*pow(cos(fi2),2.0)*sin(fi1)*(3.0/2.0)-b2*dfi2*l1*l2*(m2*m2)*cos(fi1)*cos(fi2)-(dfi1*dfi1)*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*sin(fi1)*2.0-(dfi1*dfi1)*(l1*l1)*(l2*l2)*(m1*m1)*m2*cos(fi1)*sin(fi1)-IB*(dfi2*dfi2)*l1*l2*(m2*m2)*cos(fi1)*sin(fi2)-IB*(dfi1*dfi1)*(l1*l1)*m1*m2*cos(fi1)*sin(fi1)*2.0+(dfi2*dfi2)*l1*(l2*l2*l2)*(m2*m2*m2)*cos(fi2)*sin(fi2)*cos(fi1-fi2)+b2*dfi2*l1*l2*m0*m2*cos(fi1-fi2)+b2*dfi2*l1*l2*m1*m2*cos(fi1-fi2)-(dfi1*dfi1)*(l1*l1)*(l2*l2)*m0*(m2*m2)*cos(fi1-fi2)*sin(fi1-fi2)-(dfi1*dfi1)*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1-fi2)*sin(fi1-fi2)+b0*dx0*l1*(l2*l2)*(m2*m2)*cos(fi2)*cos(fi1-fi2)-g*l1*(l2*l2)*m0*m2*mA*sin(fi2)*cos(fi1-fi2)*(1.0/2.0)-g*l1*(l2*l2)*m1*m2*mA*sin(fi2)*cos(fi1-fi2)*(1.0/2.0)-b2*dfi2*l1*l2*m1*m2*cos(fi1)*cos(fi2)+(dfi1*dfi1)*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*cos(fi2)*sin(fi1-fi2)+(dfi1*dfi1)*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi2)*sin(fi1)*cos(fi1-fi2)+g*l1*(l2*l2)*m1*(m2*m2)*cos(fi1)*cos(fi2)*sin(fi2)+g*l1*(l2*l2)*(m2*m2)*mA*cos(fi1)*cos(fi2)*sin(fi2)*(1.0/2.0)-IB*(dfi2*dfi2)*l1*l2*m1*m2*cos(fi1)*sin(fi2)+g*l1*(l2*l2)*m1*m2*mA*cos(fi1)*cos(fi2)*sin(fi2)*(1.0/2.0))/(IB*(l1*l1)*(m1*m1)+IA*(l2*l2)*(m2*m2)+IB*(l1*l1)*(m2*m2)+IA*IB*m0+IA*IB*m1+IA*IB*m2+(l1*l1)*(l2*l2)*(m2*m2*m2)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi1-fi2),2.0)+(l1*l1)*(l2*l2)*m0*(m2*m2)+(l1*l1)*(l2*l2)*m1*(m2*m2)*2.0+(l1*l1)*(l2*l2)*(m1*m1)*m2+IB*(l1*l1)*m0*m1+IA*(l2*l2)*m0*m2+IB*(l1*l1)*m0*m2+IA*(l2*l2)*m1*m2+IB*(l1*l1)*m1*m2*2.0-IB*(l1*l1)*(m1*m1)*pow(cos(fi1),2.0)-IB*(l1*l1)*(m2*m2)*pow(cos(fi1),2.0)-IA*(l2*l2)*(m2*m2)*pow(cos(fi2),2.0)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi1),2.0)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi2),2.0)+(l1*l1)*(l2*l2)*m0*m1*m2-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi1),2.0)*2.0-(l1*l1)*(l2*l2)*(m1*m1)*m2*pow(cos(fi1),2.0)-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi2),2.0)-IB*(l1*l1)*m1*m2*pow(cos(fi1),2.0)*2.0-(l1*l1)*(l2*l2)*m0*(m2*m2)*pow(cos(fi1-fi2),2.0)-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi1-fi2),2.0)+(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*cos(fi2)*cos(fi1-fi2)*2.0+(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*cos(fi2)*cos(fi1-fi2)*2.0);
   ddfi2 = (-b2*dfi2*(l1*l1)*(m1*m1)-b2*dfi2*(l1*l1)*(m2*m2)-IA*b2*dfi2*m0-IA*b2*dfi2*m1-IA*b2*dfi2*m2+IA*g*l2*(m2*m2)*sin(fi2)+(dfi1*dfi1)*(l1*l1*l1)*l2*(m2*m2*m2)*sin(fi1-fi2)+F*(l1*l1)*l2*(m2*m2)*cos(fi2)+F*IA*l2*m2*cos(fi2)+g*(l1*l1)*l2*(m2*m2*m2)*sin(fi2)-b2*dfi2*(l1*l1)*m0*m1-b2*dfi2*(l1*l1)*m0*m2-b2*dfi2*(l1*l1)*m1*m2*2.0+b2*dfi2*(l1*l1)*(m1*m1)*pow(cos(fi1),2.0)+b2*dfi2*(l1*l1)*(m2*m2)*pow(cos(fi1),2.0)+IA*(dfi1*dfi1)*l1*l2*(m2*m2)*sin(fi1-fi2)+g*(l1*l1)*l2*m0*(m2*m2)*sin(fi2)+g*(l1*l1)*l2*m1*(m2*m2)*sin(fi2)*2.0+g*(l1*l1)*l2*(m1*m1)*m2*sin(fi2)+g*(l1*l1)*l2*(m1*m1)*mA*sin(fi2)*(1.0/2.0)+g*(l1*l1)*l2*(m2*m2)*mA*sin(fi2)*(1.0/2.0)-IA*b0*dx0*l2*m2*cos(fi2)-(dfi2*dfi2)*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi2)*sin(fi2)+IA*g*l2*m0*m2*sin(fi2)+IA*g*l2*m1*m2*sin(fi2)+IA*g*l2*m0*mA*sin(fi2)*(1.0/2.0)+IA*g*l2*m1*mA*sin(fi2)*(1.0/2.0)+IA*g*l2*m2*mA*sin(fi2)*(1.0/2.0)-(dfi1*dfi1)*(l1*l1*l1)*l2*(m2*m2*m2)*pow(cos(fi1),2.0)*sin(fi1-fi2)-F*(l1*l1)*l2*(m2*m2)*cos(fi1)*cos(fi1-fi2)+(dfi2*dfi2)*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1-fi2)*sin(fi1-fi2)+F*(l1*l1)*l2*m1*m2*cos(fi2)-g*(l1*l1)*l2*(m2*m2*m2)*sin(fi1)*cos(fi1-fi2)+(dfi1*dfi1)*(l1*l1*l1)*l2*m0*(m2*m2)*sin(fi1-fi2)+(dfi1*dfi1)*(l1*l1*l1)*l2*m1*(m2*m2)*sin(fi1-fi2)*2.0+(dfi1*dfi1)*(l1*l1*l1)*l2*(m1*m1)*m2*sin(fi1-fi2)-IA*(dfi2*dfi2)*(l2*l2)*(m2*m2)*cos(fi2)*sin(fi2)+b1*dfi1*l1*l2*(m2*m2)*cos(fi1-fi2)-(dfi1*dfi1)*(l1*l1*l1)*l2*(m2*m2*m2)*cos(fi2)*sin(fi1)-g*(l1*l1)*l2*(m2*m2*m2)*pow(cos(fi1),2.0)*sin(fi2)-b0*dx0*(l1*l1)*l2*(m2*m2)*cos(fi2)+b2*dfi2*(l1*l1)*m1*m2*pow(cos(fi1),2.0)*2.0-g*(l1*l1)*l2*m0*(m2*m2)*sin(fi1)*cos(fi1-fi2)-g*(l1*l1)*l2*m1*(m2*m2)*sin(fi1)*cos(fi1-fi2)*2.0-g*(l1*l1)*l2*(m1*m1)*m2*sin(fi1)*cos(fi1-fi2)-g*(l1*l1)*l2*(m2*m2)*mA*sin(fi1)*cos(fi1-fi2)*(3.0/2.0)-b0*dx0*(l1*l1)*l2*m1*m2*cos(fi2)-(dfi2*dfi2)*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*cos(fi2)*sin(fi1-fi2)+(dfi2*dfi2)*(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*sin(fi2)*cos(fi1-fi2)+IA*(dfi1*dfi1)*l1*l2*m0*m2*sin(fi1-fi2)+IA*(dfi1*dfi1)*l1*l2*m1*m2*sin(fi1-fi2)+g*(l1*l1)*l2*m0*m1*m2*sin(fi2)+g*(l1*l1)*l2*m0*m1*mA*sin(fi2)*(1.0/2.0)+g*(l1*l1)*l2*m0*m2*mA*sin(fi2)*(1.0/2.0)+g*(l1*l1)*l2*m1*m2*mA*sin(fi2)+g*(l1*l1)*l2*(m2*m2*m2)*cos(fi1)*cos(fi2)*sin(fi1)-(dfi1*dfi1)*(l1*l1*l1)*l2*m1*(m2*m2)*cos(fi2)*sin(fi1)*2.0-(dfi1*dfi1)*(l1*l1*l1)*l2*(m1*m1)*m2*cos(fi2)*sin(fi1)-g*(l1*l1)*l2*m1*(m2*m2)*pow(cos(fi1),2.0)*sin(fi2)*2.0-g*(l1*l1)*l2*(m1*m1)*m2*pow(cos(fi1),2.0)*sin(fi2)-g*(l1*l1)*l2*(m1*m1)*mA*pow(cos(fi1),2.0)*sin(fi2)*(1.0/2.0)-g*(l1*l1)*l2*(m2*m2)*mA*pow(cos(fi1),2.0)*sin(fi2)*(1.0/2.0)-b1*dfi1*l1*l2*(m2*m2)*cos(fi1)*cos(fi2)-F*(l1*l1)*l2*m1*m2*cos(fi1)*cos(fi1-fi2)-(dfi2*dfi2)*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi2)*sin(fi2)+(dfi1*dfi1)*(l1*l1*l1)*l2*m0*m1*m2*sin(fi1-fi2)-IA*(dfi1*dfi1)*l1*l2*(m2*m2)*cos(fi2)*sin(fi1)+(dfi1*dfi1)*(l1*l1*l1)*l2*(m2*m2*m2)*cos(fi1)*sin(fi1)*cos(fi1-fi2)-(dfi1*dfi1)*(l1*l1*l1)*l2*m1*(m2*m2)*pow(cos(fi1),2.0)*sin(fi1-fi2)*2.0-(dfi1*dfi1)*(l1*l1*l1)*l2*(m1*m1)*m2*pow(cos(fi1),2.0)*sin(fi1-fi2)+b1*dfi1*l1*l2*m0*m2*cos(fi1-fi2)+b1*dfi1*l1*l2*m1*m2*cos(fi1-fi2)+(dfi2*dfi2)*(l1*l1)*(l2*l2)*m0*(m2*m2)*cos(fi1-fi2)*sin(fi1-fi2)+(dfi2*dfi2)*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1-fi2)*sin(fi1-fi2)+b0*dx0*(l1*l1)*l2*(m2*m2)*cos(fi1)*cos(fi1-fi2)-g*(l1*l1)*l2*m0*m1*m2*sin(fi1)*cos(fi1-fi2)-g*(l1*l1)*l2*m0*m2*mA*sin(fi1)*cos(fi1-fi2)*(3.0/2.0)-g*(l1*l1)*l2*m1*m2*mA*sin(fi1)*cos(fi1-fi2)*(3.0/2.0)+(dfi1*dfi1)*(l1*l1*l1)*l2*m1*(m2*m2)*cos(fi1)*sin(fi1)*cos(fi1-fi2)*2.0+(dfi1*dfi1)*(l1*l1*l1)*l2*(m1*m1)*m2*cos(fi1)*sin(fi1)*cos(fi1-fi2)-g*(l1*l1)*l2*m1*m2*mA*pow(cos(fi1),2.0)*sin(fi2)-b1*dfi1*l1*l2*m1*m2*cos(fi1)*cos(fi2)-(dfi2*dfi2)*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*cos(fi2)*sin(fi1-fi2)+(dfi2*dfi2)*(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*sin(fi2)*cos(fi1-fi2)+g*(l1*l1)*l2*m1*(m2*m2)*cos(fi1)*cos(fi2)*sin(fi1)*2.0+g*(l1*l1)*l2*(m1*m1)*m2*cos(fi1)*cos(fi2)*sin(fi1)+g*(l1*l1)*l2*(m2*m2)*mA*cos(fi1)*cos(fi2)*sin(fi1)*(3.0/2.0)-IA*(dfi1*dfi1)*l1*l2*m1*m2*cos(fi2)*sin(fi1)+b0*dx0*(l1*l1)*l2*m1*m2*cos(fi1)*cos(fi1-fi2)+g*(l1*l1)*l2*m1*m2*mA*cos(fi1)*cos(fi2)*sin(fi1)*(3.0/2.0))/(IB*(l1*l1)*(m1*m1)+IA*(l2*l2)*(m2*m2)+IB*(l1*l1)*(m2*m2)+IA*IB*m0+IA*IB*m1+IA*IB*m2+(l1*l1)*(l2*l2)*(m2*m2*m2)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi1-fi2),2.0)+(l1*l1)*(l2*l2)*m0*(m2*m2)+(l1*l1)*(l2*l2)*m1*(m2*m2)*2.0+(l1*l1)*(l2*l2)*(m1*m1)*m2+IB*(l1*l1)*m0*m1+IA*(l2*l2)*m0*m2+IB*(l1*l1)*m0*m2+IA*(l2*l2)*m1*m2+IB*(l1*l1)*m1*m2*2.0-IB*(l1*l1)*(m1*m1)*pow(cos(fi1),2.0)-IB*(l1*l1)*(m2*m2)*pow(cos(fi1),2.0)-IA*(l2*l2)*(m2*m2)*pow(cos(fi2),2.0)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi1),2.0)-(l1*l1)*(l2*l2)*(m2*m2*m2)*pow(cos(fi2),2.0)+(l1*l1)*(l2*l2)*m0*m1*m2-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi1),2.0)*2.0-(l1*l1)*(l2*l2)*(m1*m1)*m2*pow(cos(fi1),2.0)-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi2),2.0)-IB*(l1*l1)*m1*m2*pow(cos(fi1),2.0)*2.0-(l1*l1)*(l2*l2)*m0*(m2*m2)*pow(cos(fi1-fi2),2.0)-(l1*l1)*(l2*l2)*m1*(m2*m2)*pow(cos(fi1-fi2),2.0)+(l1*l1)*(l2*l2)*(m2*m2*m2)*cos(fi1)*cos(fi2)*cos(fi1-fi2)*2.0+(l1*l1)*(l2*l2)*m1*(m2*m2)*cos(fi1)*cos(fi2)*cos(fi1-fi2)*2.0);


       dfi1=dfi1+(ddfi1+ddfi1_poprz)*dt;
       fi1=fi1+(dfi1+dfi1_poprz)*dt;

       dfi2=dfi2+(ddfi2+ddfi2_poprz)*dt;
       fi2=fi2+(dfi2+dfi2_poprz)*dt;

       dx0=dx0+(ddx0+ddx_poprz)*dt;
       x0=x0+(dx0+dx_poprz)*dt;

       dx_poprz=dx0;
       ddx_poprz=ddx0;

       dfi1_poprz=dfi1;
       ddfi1_poprz=ddfi1;

        dfi2_poprz=dfi2;
        ddfi2_poprz=ddfi2;

        pozycja=x0;

   update();
}

void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);


    //tu jest ta wymagana bardzo duża skala, aby było widać ruchy
    xo=pozycja*650+580;
yo=400;



    pen.setColor(blue);
     pen.setWidth(18);
    painter.setPen(pen);
    painter.drawLine(0,yo,1400,yo);

    // painter.drawEllipse(r*500+600-5,50-5,10,10);

    pen.setColor(white);
    pen.setWidth(6);
    painter.setPen(pen);
    painter.setBrush(bwhite);
    painter.drawRect(xo-50,yo-20,100,40);



        x[0]=-l1*a*sin(fi1)+xo;
        y[0]=-l1*a*cos(fi1)+yo;

        x[1]=-l2*a*sin(fi2)+x[0];
        y[1]=-l2*a*cos(fi2)+y[0];


        pen.setColor(link);

        pen.setWidth(6);
         painter.setBrush(bwhite);
       painter.setPen(pen);

       pen.setColor(red);
      painter.setPen(pen);
        painter.drawLine(x[0],y[0],xo,yo);
        pen.setColor(green);
       painter.setPen(pen);
        painter.drawLine(x[0],y[0],x[1],y[1]);
        pen.setColor(link);
       painter.setPen(pen);

        pen.setWidth(4);

       painter.setPen(pen);

        painter.drawEllipse(xo-esize/2,yo-esize/2,esize,esize);


        painter.drawEllipse(x[0]-esize/2,y[0]-esize/2,esize,esize);
        painter.drawEllipse(x[1]-esize/2,y[1]-esize/2,esize,esize);

/*
        if(iter2<15){


            pen.setColor(blue);


             painter.setBrush(bblue);
           painter.setPen(pen);

       painter.drawEllipse(pox-esize/2,poy-10-esize/2,esize,esize);
iter2=iter2+1;
        }

*/
}



void MainWindow::mousePressEvent(QMouseEvent * ev)
{

    if(ev->y()<y[0]){
    if(ev->x()>x[0])
    dfi2=dfi2+0.2;

    if(ev->x()<x[0])
    dfi2=dfi2-0.2;
    }

    if(ev->y()>=y[0]){
    if(ev->x()>x[0])
    dfi1=dfi1+0.2;

    if(ev->x()<x[0])
    dfi1=dfi1-0.2;
    }

iter2=0;
    pox=ev->x();poy=ev->y();
}



void MainWindow::on_checkBox_clicked(bool checked)
{
    ok=checked;
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    iter=0;i=0;
    trajektoria=checked;
}
