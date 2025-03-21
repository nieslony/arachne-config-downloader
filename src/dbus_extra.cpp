#include "dbus_extra.h"

#include <QDBusArgument>
#include <QDBusInterface>
#include <QDebug>

QDebug operator<<(QDebug dbg, const Uint32List&l) {
    dbg << "[";
    for (quint32 u: l)
        dbg << u;
    dbg << "]";

    return dbg;
}

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

QDBusArgument &operator<<(QDBusArgument &argument, const Uint32List &l)
{
    argument.beginArray(qMetaTypeId<quint32>());
    for (quint32 ui: l)
         argument << ui;
    argument.endArray();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Uint32List &l)
{
    argument.beginArray();
    while (!argument.atEnd()) {
         quint32 value;
         argument >> value;
         l.append(value);
    }
    argument.endArray();

    return argument;
}

QVariant dbus_property(
    const QString &service,
    const QString &path,
    const QString &interface,
    const char* propertyName
    )
{
    QDBusConnection con = QDBusConnection::systemBus();
    if (!con.isConnected())
        throw DBusException(QString::fromUtf8("Cannot connect to the D-Bus system bus."));

    QDBusInterface iface(
        service,
        path,
        interface,
        con
        );
    if (!iface.isValid()) {
        throw DBusException(
            QString::fromUtf8("Interface not valid: %1 %2")
                .arg(iface.lastError().name())
                .arg(iface.lastError().message())
            );
    }

    return iface.property(propertyName);
}
