#ifndef DBUS_EXTRA_H
#define DBUS_EXTRA_H

#include <QString>
#include <QDBusArgument>
#include <QMetaType>
#include <QDBusReply>
#include <QDBusMessage>
#include <QDBusInterface>

class QDBusConnection;

typedef QMap<QString,QString> StringMap;

QDBusArgument &operator<<(QDBusArgument &argument, const StringMap &map);
const QDBusArgument &operator>>(const QDBusArgument &argument, StringMap &map);

Q_DECLARE_METATYPE(StringMap)

class NMException {
public:
    NMException(const QString &_msg) {
        this->_msg = _msg;
    }

    const QString &msg() {
        return _msg;
    }

private:
    QString _msg;
};

class DBusException {
public:
    DBusException(const QString &_msg) {
        this->_msg = _msg;
    }

    const QString &msg() {
        return _msg;
    }

private:
    QString _msg;
};

template<typename T>
QDBusReply<T> dbus_call(
        const QString &service,
        const QString &path,
        const QString &interface,
        const QString &method,
        QVariant arg=QVariant())
{
    QDBusConnection con = QDBusConnection::systemBus();
    if (!con.isConnected())
        throw DBusException("Cannot connect to the D-Bus system bus.");

    QDBusInterface iface(
            service,
            path,
            interface,
            con
            );
    if (!iface.isValid()) {
        throw DBusException(
                    QString("Interface not valid: %1 %2")
                    .arg(iface.lastError().name())
                    .arg(iface.lastError().message())
                    );
    }

    QDBusReply<T> reply;
    if (arg.isValid())
        reply = iface.call(method, arg);
    else
        reply = iface.call(method);
    if (!reply.isValid())
        throw DBusException(
                QString("Cannot call %1 on %2: %3: %4")
                .arg(method)
                .arg(path)
                .arg(reply.error().name())
                .arg(reply.error().message())
                );

    return reply;
}

typedef QMap<QString, QMap<QString,QVariant>> ConnectionSettings;

#endif // DBUS_EXTRA_H
