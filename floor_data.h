#ifndef FLOOR_DATA_H
#define FLOOR_DATA_H
#include <QObject>
#include <QMap>
#include <QVector>

class floor_data : public QObject
{
    Q_OBJECT
public:
    explicit floor_data(QObject *parent = 0);

public:

    QMap<int, QVector< QVector<int> > >Floor;
signals:

public slots:

};

#endif // FLOOR_DATA_H
