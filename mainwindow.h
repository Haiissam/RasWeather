#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <meteo.h>
#include <pollution.h>
#include <indiceuv.h>
#include <prevision.h>
#include <QStandardItem>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:

    Ui::MainWindow *ui;

    meteo     *m_meteo;
    Pollution *m_pollution;
    IndiceUV  *m_indice;
    Prevision *m_prevision;

    QStandardItem *item1;
    QStandardItem *item2;
    QStandardItem *item3;
    QStandardItem *item4;
    QStandardItem *item5;
    QStandardItem *item6;
    QStandardItem *item7;



private slots:

    void printHashmeteo();
    void printHashprevision();
    void printHashindice();
    void AQI();
    void Icon();
};

#endif // MAINWINDOW_H
