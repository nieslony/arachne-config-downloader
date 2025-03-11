#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

class QLineEdit;
class QSpinBox;
class QCheckBox;
class QComboBox;

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

    void createGui();
    QWidget* createDownloadTab();
    QWidget* createAllowedNmConsTab();
    void loadSettings();
    void saveSettings();

private Q_SLOTS:
    void onToggleAutoDownload(bool);
    void onChangeDownloadType(int);
};

#endif // SETTINGSDIALOG_H
