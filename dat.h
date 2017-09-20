#ifndef DAT_H
#define DAT_H

#include <QHash>
class Dat
{
public:
    static QHash<int,QStringList> idPlayListHash;
    static QHash<QString,QStringList> idListHash;
    static int currentId;
};

#endif // DAT_H
