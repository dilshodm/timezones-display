/****************************************************************************
 *
 * @author Dilshod Mukhtarov <dilshodm(at)gmail.com>
 * Sep 2022
 *
 ****************************************************************************/

#include <QTimer>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "timetable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_model {new TimeTable(this)}
{
    ui->setupUi(this);
    setWindowTitle(tr("Timezones Display v%1").arg(qApp->applicationVersion()));
    setWindowIcon(QIcon{":/time-zone.png"});

    ui->tableView->setModel(m_model);

    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &MainWindow::displayTimes);
    ui->dateEdit->setDate(QDateTime::currentDateTime().date());

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, this,
            [this](int section) {
                m_column = section;
                displayTimes();
            });

    ui->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tableView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    ui->timestampConvertedLineEdit->setReadOnly(true);

    connect(ui->timestampSpinBox, &QSpinBox::valueChanged, this,
            &MainWindow::displayConvertedTimestamp);

    connect(ui->currentTimestampPushButton, &QPushButton::clicked, this,
            &MainWindow::onShowCurrentTimestamp);

    onShowCurrentTimestamp();
    QTimer::singleShot(0, this, [this]() { adjustSize(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayTimes()
{
    const auto date = ui->dateEdit->date();
    m_model->setDate(date, m_column);
}

void MainWindow::displayConvertedTimestamp()
{
    const auto timestamp = ui->timestampSpinBox->value();
    const auto dt = QDateTime::fromSecsSinceEpoch(timestamp);
    ui->timestampConvertedLineEdit->setText(dt.toString("yyyy-MM-dd hh:mm:ss"));
}

void MainWindow::onShowCurrentTimestamp()
{
    const auto timestamp = QDateTime::currentSecsSinceEpoch();
    ui->timestampSpinBox->setValue(timestamp);
}
