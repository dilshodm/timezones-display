/****************************************************************************
 *
 * @author Dilshod Mukhtarov <dilshodm(at)gmail.com>
 * Jul 2022
 *
 ****************************************************************************/

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TimeTable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void displayTimes();
    void displayConvertedTimestamp();
    void onShowCurrentTimestamp();

private:
    Ui::MainWindow *ui;
    TimeTable *m_model;

    int m_column {0};
};
