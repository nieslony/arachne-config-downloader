#ifndef NMCONNECTION_H
#define NMCONNECTION_H

#include <QString>
#include <QList>
#include <QDBusInterface>
#include <QDebug>
#include <QMap>
#include <QVariant>
#include <QListWidgetItem>
#include <QMetaType>

typedef QMap<QString, QVariant> VariantDict;
typedef QMap<QString, VariantDict> ConSettings;

class NmConnection {
public:
    NmConnection() = default;
    ~NmConnection() = default;
    NmConnection(const NmConnection&) = default;
    NmConnection(QDBusInterface &iface);
    NmConnection(VariantDict &props);
    NmConnection &operator=(const NmConnection&) = default;

    static QString TypeWired;
    static QString TypeWireless;
    static QString TypeLoopback;
    static QString TypeBridge;
    static QString TypeTun;

    const QString &name() const { return _name; }
    const QString &type() const { return _type; }
    const QString &uuid() const { return _uuid; }

    QListWidgetItem *toListWidgetItem() const;

    static QList<NmConnection> allNmConnections();
    static QList<NmConnection> activeNmConnections();

private:
    QString _name;
    QString _type;
    QString _uuid;

    friend QDebug& operator<<(QDebug& os, const NmConnection& dt);
};

Q_DECLARE_METATYPE(NmConnection)

extern QDebug& operator<<(QDebug& os, const NmConnection& dt);

#endif // NMCONNECTION_H
