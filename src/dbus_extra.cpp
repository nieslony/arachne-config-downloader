#include "dbus_extra.h"

#include <QDBusArgument>
#include <QDBusInterface>

QDBusArgument &operator<<(QDBusArgument &argument, const StringMap &map)
{
    argument.beginMap(qMetaTypeId<QString>(), qMetaTypeId<QString>());
    QMapIterator<QString,QString> it(map);
    while (it.hasNext()) {
        it.next();
        argument.beginMapEntry();
        argument << it.key() << it.value();
        argument.endMapEntry();
    }
    argument.endMap();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, StringMap &map)
{
    argument.beginMap();
    map.clear();
     while (!argument.atEnd()) {
         QString key;
         QString value;
         argument.beginMapEntry();
         argument >> key >> value;
         argument.endMapEntry();
         map.insert(key, value);
     }
    argument.endMap();
    return argument;
}
