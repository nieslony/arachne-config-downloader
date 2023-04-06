#include "arachneconfigdownloaderapplication.h"
#include "dbus_extra.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDBusArgument>
#include <QDBusMetaType>

int main(int argc, char *argv[])
{
    ArachneConfigDownloaderApplication a(argc, argv);

    qDBusRegisterMetaType<StringMap>();
    qDBusRegisterMetaType<ConnectionSettings>();

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
