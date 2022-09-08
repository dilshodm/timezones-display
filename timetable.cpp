/****************************************************************************
 *
 * @author Dilshod Mukhtarov <dilshodm(at)gmail.com>
 * Sep 2022
 *
 ****************************************************************************/

#include <QTimeZone>
#include "timetable.h"

const QVector<QTimeZone> &timeZonesArr()
{
    static const auto dt = QDateTime::currentDateTime();
    static QVector<QTimeZone> tz {
            dt.timeZone(), // local
            QTimeZone::utc(),
            QTimeZone {"America/Los_Angeles"},
    };

    return tz;
}

constexpr auto HOURS {24};
const auto TIMEZONES {timeZonesArr().size()};

QTimeZone TimeTable::timeZone(int col)
{
    if (col < 0 || col >= timeZonesArr().size())
        col = 0;

    return timeZonesArr()[col];
}

TimeTable::TimeTable(QObject *parent)
    : QAbstractTableModel {parent}
    , m_data {TIMEZONES, QStringList{HOURS}}
{
}

int TimeTable::rowCount(const QModelIndex &) const
{
    if (m_data.isEmpty())
        return 0;

    return m_data.first().size();
}

int TimeTable::columnCount(const QModelIndex &) const
{
    return m_data.size();
}

QVariant TimeTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant {};

    switch (role) {
    case Qt::DisplayRole:
        return m_data[index.column()][index.row()];

    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;

    default:
        break;
    }

    return QVariant {};
}

QVariant TimeTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        switch (role) {
        case Qt::DisplayRole:
            return name(section);
        }
    } else {
        switch (role) {
        case Qt::DisplayRole:
            return QString::number(section + 1);
        }
    }

    return QVariant {};
}

QString TimeTable::name(int col) const
{
    return timeZone(col).displayName(QDateTime::currentDateTime());
}

void TimeTable::setDate(const QDate &date, int column)
{
    auto dt = QDateTime {date, QTime {0, 0}, timeZone(column)};
    for (auto row = 0; row < rowCount(); ++row) {
        for (auto col = 0; col < columnCount(); ++col) {
            m_data[col][row] = dt.toTimeZone(timeZone(col)).toString("yyyy-MM-dd hh:mm");
        }
        dt = dt.addSecs(1 * 60 * 60);
    }

    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}
