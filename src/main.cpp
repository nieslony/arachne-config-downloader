#include "arachneconfigdownloaderapplication.h"
#include "dbus_extra.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#ifdef Q_OS_LINUX
#include <QDBusArgument>
#include <QDBusMetaType>
#endif

int main(int argc, char *argv[])
{
    ArachneConfigDownloaderApplication a(argc, argv);

#ifdef Q_OS_LINUX
    qDBusRegisterMetaType<StringMap>();
    qDBusRegisterMetaType<ConnectionSettings>();
    qDBusRegisterMetaType<Uint32List>();
#endif

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ArachneConfigDownloader_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    return a.exec();
}
