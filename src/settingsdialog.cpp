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
    //connect(downloadType, &QComboBox::currentIndexChanged, this, &SettingsDialog::onChangeDownloadType);
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

    allConnectionsList = new QListWidget();
    for (auto &con: NmConnection::allNmConnections()) {
        if (
            con.type() != NmConnection::TypeBridge &&
            con.type() != NmConnection::TypeLoopback &&
            con.type() != NmConnection::TypeTun
            )
            allConnectionsList->addItem(con.toListWidgetItem());
    }
    allConnectionsList->setSortingEnabled(true);
    conLayout->addWidget(new QLabel(QString::fromUtf8("Available Connections:")), 0, 0);
    conLayout->addWidget(allConnectionsList, 1, 0);

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

    allowedConnectionsList = new QListWidget();
    allowedConnectionsList->setSortingEnabled(true);
    conLayout->addWidget(new QLabel(QString::fromUtf8("Allowed Connections:")), 0, 2);
    conLayout->addWidget(allowedConnectionsList, 1, 2);

    connect(
        allConnectionsList, &QListWidget::itemSelectionChanged, this,
        [this, add]() {
            add->setEnabled(!allConnectionsList->selectedItems().empty());
    });
    connect(
        allowedConnectionsList, &QListWidget::itemSelectionChanged, this,
        [this, remove]() {
            remove->setEnabled(!allowedConnectionsList->selectedItems().empty());
    });
    connect(
        add, &QPushButton::clicked, this,
        [this](bool) {
            auto selection = allConnectionsList->currentItem();
            NmConnection con  = nmConnectionFromItem(selection);
            allowedConnectionsList->addItem(con.toListWidgetItem());
            delete allConnectionsList->takeItem(allConnectionsList->currentRow());
    });
    connect(
        remove, &QPushButton::clicked, this,
        [this](bool) {
            auto selection = allowedConnectionsList->currentItem();
            NmConnection con  = nmConnectionFromItem(selection);
            allConnectionsList->addItem(con.toListWidgetItem());
            delete allowedConnectionsList->takeItem(allowedConnectionsList->currentRow());
    });
    connect(
        addAll, &QPushButton::clicked, this,
        [this](bool) {
            for (int i = allConnectionsList->count()-1; i >= 0; i--) {
                NmConnection con = nmConnectionFromItem(allConnectionsList->item(i));
                allowedConnectionsList->addItem(con.toListWidgetItem());
            }
            allConnectionsList->clear();
    });
    connect(
        removeAll, &QPushButton::clicked, this,
        [this](bool) {
            for (int i = allowedConnectionsList->count()-1; i >= 0; i--) {
                NmConnection con = nmConnectionFromItem(allowedConnectionsList->item(i));
                allConnectionsList->addItem(con.toListWidgetItem());
            }
            allowedConnectionsList->clear();
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

    QList<NmConnection> allowedConnections = settings.allowedNmConnections();
    for (auto &alcon: allowedConnections) {
        allowedConnectionsList->addItem(alcon.toListWidgetItem());
        for (int i = allConnectionsList->count()-1; i >= 0; i--) {
            NmConnection con = nmConnectionFromItem(allConnectionsList->item(i));
            if (con.uuid() == alcon.uuid())
                delete allConnectionsList->takeItem(i);
        }
    }

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

    QList<NmConnection> allowdConnections;
    for (int i = allowedConnectionsList->count()-1; i >= 0; i--) {
        QListWidgetItem *item = allowedConnectionsList->item(i);
        NmConnection con = nmConnectionFromItem(item);
        allowdConnections.append(con);
    }
    settings.setAllowedNmConnections(allowdConnections);

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

NmConnection SettingsDialog::nmConnectionFromItem(const QListWidgetItem* item)
{
    if (item == nullptr) {
        qWarning() << "Null item";
        return NmConnection();
    }
    auto data = item->data(Qt::UserRole);
    return qvariant_cast<NmConnection>(data);
}
