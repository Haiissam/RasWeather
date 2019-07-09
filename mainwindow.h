#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <meteo.h>
#include <pollution.h>
#include <indiceuv.h>
#include <prevision.h>
#include <QTableWidgetItem>
#include <QGridLayout>
#include <QDialog>
#include <QtCharts/QChart>
#include <QStandardItem>
#include <QBarSet>
#include <QtCharts>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setvignette();


private:

    Ui::MainWindow *ui;

    meteo *m_meteo;
    Pollution *p_pollution;
    IndiceUV *i_indice;
    Prevision *pm_prevision;
    QStandardItemModel *table;
    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;
    QGridLayout* gridLayout;
    QStandardItem *item1 = new QStandardItem;
    QStandardItem *item2 = new QStandardItem;
    QStandardItem *item3 = new QStandardItem;
    QStandardItem *item4 = new QStandardItem;
    QStandardItem *item5 = new QStandardItem;
    QStandardItem *item6 = new QStandardItem;
    QStandardItem *item7 = new QStandardItem;



private slots:

    void printHashmeteo();
    void printHashprevision();
    QHash <QString, QVariant> printHashpollution();
    void printHashindice();
    void pollutionChart();
    void AQI();
    void Icon();


};

#endif // MAINWINDOW_H
