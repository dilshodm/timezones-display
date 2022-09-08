/****************************************************************************
 *
 * @author Dilshod Mukhtarov <dilshodm(at)gmail.com>
 * Jul 2022
 *
 ****************************************************************************/

#pragma once

#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>
#include <QDate>

class TimeTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    static QTimeZone timeZone(int col);

public:
    explicit TimeTable(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QString name(int col) const;

public slots:
    void setDate(const QDate &date, int column);

private:
    QVector<QStringList> m_data;
};

