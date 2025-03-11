#include "nmconnection.h"
#include "dbus_extra.h"

#include <QDBusConnection>
#include <QDBusArgument>
#include <QIcon>

QString NmConnection::TypeWired = QString::fromUtf8("802-3-ethernet");
QString NmConnection::TypeWireless = QString::fromUtf8("802-11-wireless");
QString NmConnection::TypeLoopback = QString::fromUtf8("loopback");
QString NmConnection::TypeBridge = QString::fromUtf8("bridge");
QString NmConnection::TypeTun = QString::fromUtf8("tun");

NmConnection::NmConnection(QDBusInterface &iface) :
    _name(iface.property("Id").toString()),
    _type(iface.property("Type").toString()),
    _uuid(iface.property("Uuid").toString())
{}

NmConnection::NmConnection(VariantDict &props) :
    _name(props.value(QString::fromUtf8("id")).toString()),
    _type(props.value(QString::fromUtf8("type")).toString()),
    _uuid(props.value(QString::fromUtf8("uuid")).toString())
{}

QListWidgetItem *NmConnection::toListWidgetItem() const
{
    QListWidgetItem *item;
    if (_type == TypeWired)
        item = new QListWidgetItem(
            QIcon::fromTheme(QIcon::ThemeIcon::NetworkWired),
            _name
            );
    else if (_type == TypeWireless)
        item = new QListWidgetItem(
            QIcon::fromTheme(QIcon::ThemeIcon::NetworkWireless),
            _name
            );
    else
        item = new QListWidgetItem(_name);

    QVariant data;
    data.setValue(*this);
    item->setData(Qt::UserRole, data);

    return item;
}

QDebug& operator<<(QDebug& os, const NmConnection& nmc)
{
    os << "NmConnection("
       << "name=" << nmc._name << ", "
       << "type=" << nmc._type << ", "
       << "uuid=" << nmc._uuid
       << ")";

    return os;
}

QList<NmConnection> allNmConnections()
{
    QList<NmConnection> connections;

    try {
        const QDBusArgument activeConnections =
            dbus_call<VariantDict>(
                QString::fromUtf8("org.freedesktop.NetworkManager"),
                QString::fromUtf8("/org/freedesktop/NetworkManager/Settings"),
                QString::fromUtf8("org.freedesktop.DBus.Properties"),
                QString::fromUtf8("GetAll"), QString::fromUtf8("org.freedesktop.NetworkManager.Settings")
                )
                .value()
                .value(QString::fromUtf8("Connections"))
                .value<QDBusArgument>();

        QDBusConnection bus = QDBusConnection::systemBus();
        if (!bus.isConnected())
            throw DBusException(QString::fromUtf8("Cannot connect to the D-Bus system bus."));

        activeConnections.beginArray();
        while (!activeConnections.atEnd()) {
            QDBusObjectPath conPath;
            activeConnections >> conPath;

            QDBusInterface iface(
                QString::fromUtf8("org.freedesktop.NetworkManager"),
                conPath.path(),
                QString::fromUtf8("org.freedesktop.NetworkManager.Settings.Connection"),
                bus
                );
            if (!iface.isValid()) {
                throw DBusException(
                    QString::fromUtf8("Interface not valid: %1 %2")
                        .arg(iface.lastError().name())
                        .arg(iface.lastError().message())
                    );
            }

            QDBusReply<ConSettings> reply = dbus_call<ConSettings>(
                conPath.path(),
                iface,
                QString::fromUtf8("GetSettings")
            );

            VariantDict props = reply.value()
                                    .value(QString::fromUtf8("connection"));
            NmConnection con(props);
            connections.append(con);
        }
        activeConnections.endArray();
    }
    catch (DBusException ex) {
        qWarning() << ex.msg();
    }

    return connections;
}

QList<NmConnection> activeNmConnections()
{
    QList<NmConnection> connections;

    const QDBusArgument activeConnections =
        dbus_call<VariantDict>(
            QString::fromUtf8("org.freedesktop.NetworkManager"),
            QString::fromUtf8("/org/freedesktop/NetworkManager"),
            QString::fromUtf8("org.freedesktop.DBus.Properties"),
            QString::fromUtf8("GetAll"), QString::fromUtf8("org.freedesktop.NetworkManager")
        )
        .value()
        .value(QString::fromUtf8("ActiveConnections"))
        .value<QDBusArgument>();

    QDBusConnection bus = QDBusConnection::systemBus();
    if (!bus.isConnected())
        throw DBusException(QString::fromUtf8("Cannot connect to the D-Bus system bus."));

    activeConnections.beginArray();
    while (!activeConnections.atEnd()) {
        QDBusObjectPath conPath;
        activeConnections >> conPath;

        QDBusInterface iface(
            QString::fromUtf8("org.freedesktop.NetworkManager"),
            conPath.path(),
            QString::fromUtf8("org.freedesktop.NetworkManager.Connection.Active"),
            bus
            );
        if (!iface.isValid()) {
            throw DBusException(
                QString::fromUtf8("Interface not valid: %1 %2")
                    .arg(iface.lastError().name())
                    .arg(iface.lastError().message())
                );
        }

        NmConnection con(iface);
        connections.append(con);
    }
    activeConnections.endArray();

    return connections;
}
