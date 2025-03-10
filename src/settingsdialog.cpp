#include "settingsdialog.h"
#include "arachneconfigdownloaderapplication.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QTimer>
#include <QDebug>

SettingsDialog::SettingsDialog()
{
    setWindowTitle(QString::fromUtf8("Arachne Settings"));
    setWindowIcon(QIcon(QString::fromUtf8(":/images/ovpncdl-green-16x16.png")));
    createGui();
    loadSettings();

    connect(autoDownload, &QCheckBox::toggled, this, &SettingsDialog::onToggleAutoDownload);
    connect(downloadType, &QComboBox::currentIndexChanged, this, &SettingsDialog::onChangeDownloadType);
    connect(this, &QDialog::accepted, this, &SettingsDialog::saveSettings);    
}

void SettingsDialog::createGui()
{
    QTabWidget *tabs = new QTabWidget();
    tabs->addTab(createDownloadTab(), QString::fromUtf8("Download"));
    tabs->addTab(createEnabledNmConsTab(), QString::fromUtf8("Enabled NetworkManager Connections"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tabs);
    layout->addWidget(buttonBox);
    setLayout(layout);
}

QWidget* SettingsDialog::createEnabledNmConsTab()
{
    QVBoxLayout *layout = new QVBoxLayout();

    allowDownloadFromVpn = new QCheckBox(QString::fromUtf8("Allow Download from VPN"));
    layout->addWidget(allowDownloadFromVpn);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    return widget;
}

QWidget* SettingsDialog::createDownloadTab()
{
    QGridLayout *grid = new QGridLayout();
    QLabel *label;
    int row = 0;
    QHBoxLayout *hbox;

    adminServerUrl = new QLineEdit(this);
    adminServerUrl->setMinimumWidth(fontMetrics().averageCharWidth() * 50);
    label = new QLabel(tr("Admin Server Url:"), this);
    label->setBuddy(adminServerUrl);
    hbox = new QHBoxLayout();
    hbox->addWidget(adminServerUrl, 1);
    hbox->addWidget(new QLabel(ArachneConfigDownloaderApplication::USER_CONFIG_API_PATH));
    grid->addWidget(label, row, 0);
    grid->addLayout(hbox, row, 1);
    row++;

    ignoreSslErrors = new QCheckBox(tr("Ignore SSL Errors"), this);
    grid->addWidget(ignoreSslErrors, row, 1);
    row++;

    autoDownload = new QCheckBox(tr("Download periodically"), this);
    grid->addWidget(autoDownload, row, 1);
    row++;

    downloadInterval = new QSpinBox(this);
    downloadIntervalUnit = new QComboBox(this);
    downloadIntervalUnit->addItem(tr("Seconds"), Settings::TimeUnit::SEC);
    downloadIntervalUnit->addItem(tr("Minutes"), Settings::TimeUnit::MIN);
    downloadIntervalUnit->addItem(tr("Hours"), Settings::TimeUnit::HOUR);
    label = new QLabel(tr("Download Interval:"), this);
    label->setBuddy(downloadInterval);
    grid->addWidget(label, row, 0);
    hbox = new QHBoxLayout();
    hbox->addWidget(downloadInterval);
    hbox->addWidget(downloadIntervalUnit);
    grid->addLayout(hbox, row, 1);
    row++;

    downloadDelay = new QSpinBox(this);
    downloadDelayUnit = new QComboBox(this);
    downloadDelayUnit->addItem(tr("Seconds"), Settings::TimeUnit::SEC);
    downloadDelayUnit->addItem(tr("Minutes"), Settings::TimeUnit::MIN);
    downloadDelayUnit->addItem(tr("Hours"), Settings::TimeUnit::HOUR);
    label = new QLabel(tr("Download Delay:"), this);
    label->setBuddy(downloadDelay);
    grid->addWidget(label, row, 0);
    hbox = new QHBoxLayout();
    hbox->addWidget(downloadDelay);
    hbox->addWidget(downloadDelayUnit);
    grid->addLayout(hbox, row, 1);
    row++;

    downloadType = new QComboBox(this);
    downloadType->addItem(tr("NetworkManager Connection"), Settings::DownloadType::NETWORK_MANAGER);
    downloadType->addItem(tr("OpenVPN Configuration"), Settings::DownloadType::OVPN);
    label = new QLabel(tr("Download Type:"), this);
    label->setBuddy(downloadType);
    grid->addWidget(label, row, 0);
    grid->addWidget(downloadType, row, 1);
    row++;

    downloadDestination = new QLineEdit(this);
    downloadDestination->setMinimumWidth(fontMetrics().averageCharWidth() * 50);
    label = new QLabel(tr("Download Destination:"), this);
    grid->addWidget(label, row, 0);
    grid->addWidget(downloadDestination, row, 1);

    QWidget *widget = new QWidget();
    widget->setLayout(grid);
    return widget;
}

void SettingsDialog::loadSettings()
{
    Settings &settings = Settings::getInstance();
    settings.sync();

    adminServerUrl->setText(settings.adminServerUrl());
    ignoreSslErrors->setChecked(settings.ignoreSslErrors());
    autoDownload->setChecked(settings.autoDownload());
    downloadInterval->setValue(settings.downloadInterval());
    downloadIntervalUnit->setCurrentIndex(
                downloadIntervalUnit->findData(settings.downloadIntervalUnit())
                );
    downloadDelay->setValue(settings.downloadDelay());
    downloadDelayUnit->setCurrentIndex(
                downloadDelayUnit->findData(settings.downloadDelayUnit())
                );
    downloadType->setCurrentIndex(
                downloadType->findData(settings.downloadType())
                );
   downloadDestination->setText(settings.downloadDestination());

   onToggleAutoDownload(settings.autoDownload());
   onChangeDownloadType(settings.downloadType());
}

void SettingsDialog::saveSettings()
{
    qDebug() << "Saving settings";
    Settings &settings = Settings::getInstance();

    QTimer &timer = static_cast<ArachneConfigDownloaderApplication*>(qApp)->downloadTimer();
    bool setNewInterval = false;
    if (autoDownload->checkState()) {
        Settings::TimeUnit unit = static_cast<Settings::TimeUnit>(downloadIntervalUnit->currentIndex());
        if (downloadInterval->value() != settings.downloadInterval()
                || unit != settings.downloadIntervalUnit()
                )
            setNewInterval = true;
    }
    else {
        timer.stop();
    }

    settings.setAdminServerUrl(adminServerUrl->text());
    settings.setIgnoreSslErrors(ignoreSslErrors->checkState());
    settings.setAutoDownload(autoDownload->checkState());
    settings.setDownloadInterval(downloadInterval->value());
    settings.setDownloadIntervalUnit(
                static_cast<Settings::TimeUnit>(downloadIntervalUnit->currentIndex())
    );
    settings.setDownloadDelay(downloadDelay->value());
    settings.setDownloadDelayUnit(
                static_cast<Settings::TimeUnit>(downloadDelayUnit->currentIndex())
    );
    settings.setDownloadType(
                static_cast<Settings::DownloadType>(downloadType->currentIndex())
    );
    settings.setDownloadDestination(downloadDestination->text());

    if (setNewInterval) {
        timer.setInterval(settings.downloadIntervalMsec());
        if (!timer.isActive())
            timer.start();
    }

    settings.sync();
}

void SettingsDialog::onToggleAutoDownload(bool enabled)
{
    downloadInterval->setEnabled(enabled);
    downloadIntervalUnit->setEnabled(enabled);
    downloadDelay->setEnabled(enabled);
    downloadDelayUnit->setEnabled(enabled);
}

void SettingsDialog::onChangeDownloadType(int index)
{
    Settings::DownloadType type = static_cast<Settings::DownloadType>(downloadType->itemData(index).toInt());
    downloadDestination->setEnabled(type == Settings::OVPN);
}
