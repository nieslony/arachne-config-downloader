#include "settingsdialog.h"
#include "arachneconfigdownloaderapplication.h"
#include "settings.h"
#include "nmconnection.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QTimer>
#include <QGroupBox>
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>

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
    tabs->addTab(createAllowedNmConsTab(), QString::fromUtf8("Allowed NetworkManager Connections"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tabs);
    layout->addWidget(buttonBox);
    setLayout(layout);
}

QWidget* SettingsDialog::createAllowedNmConsTab()
{
    QVBoxLayout *layout = new QVBoxLayout();

    allowDownloadFromVpn = new QCheckBox(QString::fromUtf8("Allow Download from configured VPN"));
    layout->addWidget(allowDownloadFromVpn);

    allowAllWifi = new QCheckBox(QString::fromUtf8("Allow all Wifi Connections"));
    layout->addWidget(allowAllWifi);

    allowAllWired = new QCheckBox(QString::fromUtf8("Allow all wired Connections"));
    layout->addWidget(allowAllWired);

    QGridLayout *conLayout = new QGridLayout();
    QVBoxLayout *vbox;

    QListWidget *allConnections = new QListWidget();
    for (auto &con: allNmConnections()) {
        if (
            con.type() != NmConnection::TypeBridge &&
            con.type() != NmConnection::TypeLoopback &&
            con.type() != NmConnection::TypeTun
            )
            allConnections->addItem(con.toListWidgetItem());
    }
    allConnections->setSortingEnabled(true);
    conLayout->addWidget(new QLabel(QString::fromUtf8("Available Connections:")), 0, 0);
    conLayout->addWidget(allConnections, 1, 0);

    QPushButton *add = new QPushButton(QString::fromUtf8("Add"));
    add->setEnabled(false);
    QPushButton *addAll = new QPushButton(QString::fromUtf8("Add All"));
    QPushButton *removeAll = new QPushButton(QString::fromUtf8("Remove All"));
    QPushButton *remove = new QPushButton(QString::fromUtf8("Remove"));
    remove->setEnabled(false);
    vbox = new QVBoxLayout();
    vbox->addWidget(add);
    vbox->addWidget(addAll);
    vbox->addWidget(removeAll);
    vbox->addWidget(remove);
    conLayout->addLayout(vbox, 1, 1);

    QListWidget *allowedConnections = new QListWidget();
    allowedConnections->setSortingEnabled(true);
    conLayout->addWidget(new QLabel(QString::fromUtf8("Allowed Connections:")), 0, 2);
    conLayout->addWidget(allowedConnections, 1, 2);

    connect(
        allConnections, &QListWidget::itemSelectionChanged, this,
        [allConnections, add]() {
            add->setEnabled(!allConnections->selectedItems().empty());
    });
    connect(
        allowedConnections, &QListWidget::itemSelectionChanged, this,
        [allConnections, remove]() {
            remove->setEnabled(!allConnections->selectedItems().empty());
    });
    connect(
        add, &QPushButton::clicked, this,
        [allConnections, allowedConnections](bool) {
            auto selection = allConnections->currentItem();
            auto data = selection->data(Qt::UserRole);
            NmConnection con = qvariant_cast<NmConnection>(data);
            allowedConnections->addItem(con.toListWidgetItem());
            delete allConnections->takeItem(allConnections->currentRow());
    });
    connect(
        remove, &QPushButton::clicked, this,
        [allConnections, allowedConnections](bool) {
            auto selection = allowedConnections->currentItem();
            auto data = selection->data(Qt::UserRole);
            NmConnection con = qvariant_cast<NmConnection>(data);
            allConnections->addItem(con.toListWidgetItem());
            delete allowedConnections->takeItem(allowedConnections->currentRow());
    });
    connect(
        addAll, &QPushButton::clicked, this,
        [allConnections, allowedConnections](bool) {
            for (int i = allConnections->count()-1; i >= 0; i--) {
                auto data = allConnections->item(i)->data(Qt::UserRole);
                NmConnection con = qvariant_cast<NmConnection>(data);
                allowedConnections->addItem(con.toListWidgetItem());
            }
            allConnections->clear();
    });
    connect(
        removeAll, &QPushButton::clicked, this,
        [allConnections, allowedConnections](bool) {
            for (int i = allowedConnections->count()-1; i >= 0; i--) {
                auto data = allowedConnections->item(i)->data(Qt::UserRole);
                NmConnection con = qvariant_cast<NmConnection>(data);
                allConnections->addItem(con.toListWidgetItem());
            }
            allowedConnections->clear();
        });

    layout->addLayout(conLayout);

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

    allowDownloadFromVpn->setChecked(settings.allowDownloadFromVpn());
    allowAllWifi->setChecked(settings.allowDownloadAllWifi());
    allowAllWired->setChecked(settings.allowDownloadAllWired());

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

    settings.setAllowDownloadFromVpn(allowDownloadFromVpn->checkState());
    settings.setAllowDownloadAllWifi(allowAllWifi->checkState());
    settings.setAllowDownloadAllWired(allowAllWired->checkState());

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
