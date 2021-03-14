#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meteo.h"
#include "prevision.h"
#include "pollution.h"
#include "indiceuv.h"

#include <QFont>
#include <QTimer>
#include <QStandardItem>
#include <QPixmap>
#include <QObject>
#include <QStandardItemModel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_meteo     = new meteo();
    m_pollution = new Pollution();
    m_indice    = new IndiceUV();
    m_prevision = new Prevision();

    item1 = new QStandardItem();
    item2 = new QStandardItem();
    item3 = new QStandardItem();
    item4 = new QStandardItem();
    item5 = new QStandardItem();
    item6 = new QStandardItem();
    item7 = new QStandardItem();

    connect(m_meteo,    SIGNAL(received()),this,SLOT(printHashmeteo()));
    connect(m_indice,   SIGNAL(received()),this,SLOT(printHashindice()));
    connect(m_prevision,SIGNAL(received()),this,SLOT(printHashprevision()));
    connect(m_pollution,SIGNAL(received()),this,SLOT(AQI()));
    connect(m_pollution,SIGNAL(received()),this,SLOT(Icon()));

    //Changer le background de la mainwindow

    /*QPixmap bkgnd ("/home/haissam/Pictures/meteo1.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background,bkgnd);
    this->setPalette(palette);*/

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_meteo;
    delete m_pollution;
    delete m_indice;
    delete m_prevision;

    delete item1;
    delete item2;
    delete item3;
    delete item4;
    delete item5;
    delete item6;
    delete item7;
}

void MainWindow::printHashmeteo()                              //création et remplissage du tableWidget xontenant les informations sur la météo du jours
{
    QHash <QString, QVariant>hash_meteo;
    hash_meteo = m_meteo->getHash();

    QString t = hash_meteo.value("temp").toString();
    ui->labelTemp->setText(QString ("%1 °C").arg(t));
    ui->labelCiel->setText(hash_meteo.value("main").toString());
    ui->labelDate->setText(QDateTime::currentDateTime().toString(("ddd d MMMM  hh:mm ")));
}

//Affichage de l'indice UV et de l'icon correspondante
void MainWindow::printHashindice()
{
    QHash <QString, QVariant>indice;
    indice = m_indice->getHash();
    int indice_value = indice.value("UV").toInt();
    QString ind=tr("Indice UV ");

    if (indice_value>=0 && indice_value<=2)
    {
        ui->label_DUV->setText(QString ("<font color=\"#0fc133\">%0 %1</font>").arg(tr("Faible: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#0fc133\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#0fc133\">%1</font>").arg(ind));
    }

    else if (indice_value>=3 && indice_value<=5)
    {
        ui->label_DUV->setText(QString ("<font color=\"#f9eb25\">%0 %1</font>").arg(tr("Moyen: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#f9eb25\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#f9eb25\">%1</font>").arg(ind));
    }

    else if (indice_value>=6 && indice_value<=7)
    {
        ui->label_DUV->setText(QString ("<font color=\"#ff9011\">%0 %1</font>").arg(tr("Élevé!: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#ff9011\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#ff9011\">%1</font>").arg(ind));
    }

    else if (indice_value>=8 && indice_value<=10)
    {
        ui->label_DUV->setText(QString ("<font color=\"#e00f0f\">%0 %1</font>").arg(tr("Très Élevé!!: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#e00f0f\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#e00f0f\">%1</font>").arg(ind));
    }

    else
    {
        ui->label_DUV->setText(QString ("<font color=\"#c669e5\">%0 %1</font>").arg(tr("Extreme!!!: ")).arg(indice_value));
        ui->label_indUV->setText("<font color=\"#c669e5\">UV</font>");
        ui->label_TUV->setText(QString("<font color=\"#c669e5\">%1</font>").arg(ind));
    }

    ui->label_DUV->setFont(QFont("Ubuntu",16,QFont::Bold));
}

//Affichage des prévisions pour les prochaines 24h (par intervalles de 3h), onglet prévision
void MainWindow::printHashprevision()
{

    QHash <QString, QVariant>hash_prevision;
    hash_prevision = m_prevision->getHash();

    QPixmap ic;
    QString icon;
    double t1,t2,t3,t4,t5;
    QDateTime dh1,dh2,dh3,dh4,dh5,dh6;
    QString h1,h2,h3,h4,h5,h6;

    /*Affichage des icones météo*/

    icon=hash_prevision.value("Icon1").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon1->setPixmap(ic);

    icon=hash_prevision.value("Icon2").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon2->setPixmap(ic);

    icon=hash_prevision.value("Icon3").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon3->setPixmap(ic);

    icon=hash_prevision.value("Icon4").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon4->setPixmap(ic);

    icon=hash_prevision.value("Icon5").toString();
    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->label_icon5->setPixmap(ic);

    /*Affichage des températures dans l'onglet prévision*/

    t1 = hash_prevision.value("Temp1").toDouble();
    ui->label_value1->setText(QString ("%1 °C").arg(t1));

    t2 = hash_prevision.value("Temp2").toDouble();
    ui->label_value2->setText(QString ("%1 °C").arg(t2));

    t3 = hash_prevision.value("Temp3").toDouble();
    ui->label_value3->setText(QString ("%1 °C").arg(t3));

    t4 = hash_prevision.value("Temp4").toDouble();
    ui->label_value4->setText(QString ("%1 °C").arg(t4));

    t5 = hash_prevision.value("Temp5").toDouble();
    ui->label_value5->setText(QString ("%1 °C").arg(t5));

    /*Affichage des dates météo*/
    dh1 = hash_prevision.value("Date_heure1").toDateTime();
    h1 = dh1.toString("hh:mm");
    ui->label_date1->setText(h1);

    dh2 = hash_prevision.value("Date_heure2").toDateTime();
    h2 = dh2.toString("hh:mm");
    ui->label_date2->setText(h2);

    dh3 = hash_prevision.value("Date_heure3").toDateTime();
    h3 = dh3.toString("hh:mm");
    ui->label_date3->setText(h3);

    dh4 = hash_prevision.value("Date_heure4").toDateTime();
    h4 = dh4.toString("hh:mm");
    ui->label_date4->setText(h4);

    dh5 = hash_prevision.value("Date_heure5").toDateTime();
    h5 = dh5.toString("hh:mm");
    ui->label_date5->setText(h5);
}

//affichage de l'AQI et l'icone correspondante
void MainWindow::AQI()
{
    QPixmap fondPlan;
    QHash <QString, QVariant> aqi = m_pollution->getHash();
    int aqi_value = aqi.value("AQI").toInt();
    QString aq =  tr("Indice Qualité Air ");

    if (aqi_value>=0 && aqi_value<=50)
    {
        ui->label_DAQI->setText(QString ("<font color=\"#39962e\">%0 %1</font>").arg(tr("Bon: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_g.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#39962e\">%1</font>").arg(aq));
    }

    else if (aqi_value>=51 && aqi_value<=100)
    {
        ui->label_DAQI->setText(QString ("<font color=\"#eded2d\">%0 %1</font>").arg(tr("Modéré: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_m.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#eded2d\">%1</font>").arg(aq));
    }

    else if (aqi_value>=101 && aqi_value<=150)
    {
        ui->label_DAQI->setText(QString ("<font color=\"#f99c2a\">%0 %1</font>").arg(tr("Malsain pour sensible: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_u1.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#f99c2a\">%1</font>").arg(aq));
    }

    else if (aqi_value>=151 && aqi_value<=200)
    {
        ui->label_DAQI->setText(QString("<font color=\"#ef2121\">%0 %1</font>").arg(tr("Malsain: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_u2.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#ef2121\">%1</font>").arg(aq));
    }

    else if (aqi_value>=201 && aqi_value<=300)
    {
        ui->label_DAQI->setText(QString ("<font color=\"#9920ef\">%0 %1</font>").arg(tr("Très Malsain!: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_vu.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#9920ef\">%1</font>").arg(aq));
    }

    else
    {
        ui->label_DAQI->setText(QString ("<font color=\"#c11b1b\">%0 %1</font>").arg(tr("Risqué!!: ")).arg(aqi_value));
        fondPlan.load(":/Icons_meteo/aqi_h.png");
        ui->label_IAQI->setPixmap(fondPlan);
        ui->label->setText(QString ("<font color=\"#c11b1b\">%1</font>").arg(aq));
    }
}

//affichage de l'icone meteo dans l'onglet Météo
void MainWindow::Icon()
{
    QHash <QString, QVariant>hash_meteo;
    hash_meteo = m_meteo->getHash();
    QString icon = hash_meteo.value("icon").toString();
    QPixmap ic;

    ic.load(QString(":/Icons_meteo/%1.png").arg(icon));
    ui->labelIcon->setPixmap(ic);
}














