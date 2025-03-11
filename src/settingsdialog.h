#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

class QLineEdit;
class QSpinBox;
class QCheckBox;
class QComboBox;
class QListWidget;

#include "nmconnection.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog();

private:
    QLineEdit *adminServerUrl;
    QCheckBox *ignoreSslErrors;
    QCheckBox *autoDownload;
    QSpinBox *downloadInterval;
    QSpinBox *downloadDelay;
    QComboBox *downloadIntervalUnit;
    QComboBox *downloadDelayUnit;
    QComboBox *downloadType;
    QLineEdit *downloadDestination;

    QCheckBox *allowDownloadFromVpn;
    QCheckBox *allowAllWifi;
    QCheckBox *allowAllWired;

    QListWidget *allConnectionsList;
    QListWidget *allowedConnectionsList;

    void createGui();
    QWidget* createDownloadTab();
    QWidget* createAllowedNmConsTab();
    void loadSettings();
    void saveSettings();

#ifdef Q_OS_LINUX
    static NmConnection nmConnectionFromItem(const QListWidgetItem*);
#endif

private Q_SLOTS:
    void onToggleAutoDownload(bool);
    void onChangeDownloadType(int);
};

#endif // SETTINGSDIALOG_H
