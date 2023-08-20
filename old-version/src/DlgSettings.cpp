/* 
 * File:   DlgSettings.cpp
 * Author: claas
 * 
 * Created on 15. September 2016, 21:02
 */

#include "Settings.h"
#include "DlgSettings.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

DlgSettings::DlgSettings() 
{
    createGui();
    readValues();    
    onToggleAutoDownload(autoDownload->checkState());
}

DlgSettings::~DlgSettings() 
{
}

void DlgSettings::readValues()
{
    adminServerUrl->setText(Settings::getGlobalSettings().adminServerUrl());
    autoDownload->setChecked(Settings::getGlobalSettings().autoDownload());
    downloadDelay->setValue(Settings::getGlobalSettings().downloadDelay());
    downloadInterval->setValue(Settings::getGlobalSettings().downloadInterval());
    openvpnConfigFolder->setText(Settings::getGlobalSettings().openvpnConfigFolder());
    ignoreSslErrors->setChecked(Settings::getGlobalSettings().ignoreSslErrors());
    downloadFormat->setCurrentIndex(
        downloadFormat->findData(Settings::getGlobalSettings().downloadType())
    );
    downloadIntervalUnit->setCurrentIndex(
        downloadIntervalUnit->findData(Settings::getGlobalSettings().downloadIntervalUnit())
    );
    downloadDelayUnit->setCurrentIndex(
        downloadDelayUnit->findData(Settings::getGlobalSettings().downloadDelayUnit())
    );    
    
    onDownloadTypeChanged(downloadFormat->currentIndex());
}

void DlgSettings::saveValues()
{
    Settings::getGlobalSettings().setAdminServerUrl(adminServerUrl->text());
    Settings::getGlobalSettings().setAutoDownload(autoDownload->isChecked());
    Settings::getGlobalSettings().setDownloadDelay(downloadDelay->value());
    Settings::getGlobalSettings().setDownloadInterval(downloadInterval->value());
    Settings::getGlobalSettings().setIgnoreSslErrors(ignoreSslErrors->isChecked());
    Settings::getGlobalSettings().setOpenvpnConfigFolder(openvpnConfigFolder->text());
    Settings::getGlobalSettings().setDownloadDelayUnit(
        static_cast<Settings::TimeUnit>(downloadDelayUnit->currentData().toInt())
    );
    Settings::getGlobalSettings().setDownloadIntervalUnit(
        static_cast<Settings::TimeUnit>(downloadIntervalUnit->currentData().toInt())
    );
    Settings::getGlobalSettings().setDownloadType(
        static_cast<Settings::DownloadType>(downloadFormat->currentData().toInt())
    );
  
    accept();
}

void DlgSettings::createGui()
{
    QGridLayout *grid = new QGridLayout(this);    
    QLabel *label;
    QHBoxLayout *hbox;
    int row = 0;
    QStringList units;
        
    label = new QLabel(tr("Admin server URL:"), this);
    adminServerUrl = new QLineEdit(this);
    adminServerUrl->setMinimumWidth(fontMetrics().averageCharWidth() * 50);
    label->setBuddy(adminServerUrl);
    grid->addWidget(label, row, 0);
    grid->addWidget(adminServerUrl, row, 1);
    row++;
    
    ignoreSslErrors = new QCheckBox(tr("Ignore SSL errors"), this);
    grid->addWidget(ignoreSslErrors, row, 1);
    row++;

    label = new QLabel(tr("Download format:"), this);
    downloadFormat = new QComboBox(this);
    downloadFormat->addItem(tr("NetworkManager installer (downlaod and ecxecute)"), Settings::NM_EXECUTE);
    downloadFormat->addItem(tr("NetworkManager installer (downlaod only)"), Settings::NM_DOWNLOAD);
    downloadFormat->addItem(tr(".ovpn file"), Settings::OVPN_DOWNLOAD);
    connect(downloadFormat, SIGNAL(currentIndexChanged(int)),
            SLOT(onDownloadTypeChanged(int)));
    label->setBuddy(downloadFormat);
    grid->addWidget(label, row, 0);
    grid->addWidget(downloadFormat, row, 1);
    row++;
    
    label = new QLabel(tr(".ovpn config folder:"), this);
    openvpnConfigFolder = new QLineEdit(this);
    label->setBuddy(openvpnConfigFolder);
    grid->addWidget(label, row, 0);
    grid->addWidget(openvpnConfigFolder, row, 1);
    row++;
    
    autoDownload = new QCheckBox(tr("Downlaod config periodocally"), this);
    connect(autoDownload, SIGNAL(stateChanged(int)), SLOT(onToggleAutoDownload(int)));
    grid->addWidget(autoDownload, row, 1);
    row++;

    label = new QLabel(tr("Download interval:"), this);
    downloadInterval = new QSpinBox(this);
    downloadInterval->setValue(Settings::getGlobalSettings().downloadInterval());
    label->setBuddy(downloadInterval);
    downloadIntervalUnit = new QComboBox(this);
    downloadIntervalUnit->addItem(tr("sec"), Settings::SEC);
    downloadIntervalUnit->addItem(tr("min"), Settings::MIN);
    downloadIntervalUnit->addItem(tr("hour"), Settings::HOUR);
    hbox = new QHBoxLayout();
    hbox->addWidget(downloadInterval);
    hbox->addWidget(downloadIntervalUnit);
    grid->addWidget(label, row, 0);    
    grid->addLayout(hbox, row, 1);
    row++;
    
    label = new QLabel(tr("Download delay:"), this);
    downloadDelay = new QSpinBox(this);
    label->setBuddy(downloadDelay);
    downloadDelayUnit = new QComboBox(this);
    downloadDelayUnit->addItem(tr("sec"), Settings::SEC);
    downloadDelayUnit->addItem(tr("min"), Settings::MIN);
    downloadDelayUnit->addItem(tr("hour"), Settings::HOUR);
    hbox = new QHBoxLayout();
    hbox->addWidget(downloadDelay);
    hbox->addWidget(downloadDelayUnit);
    grid->addWidget(label, row, 0);    
    grid->addLayout(hbox, row, 1);
    row++;
    
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(QDialogButtonBox::Ok);
    buttons->addButton(QDialogButtonBox::Cancel);
    grid->addWidget(buttons, row, 0, 1, 2);
    connect(buttons, SIGNAL(accepted()), SLOT(saveValues()));
    connect(buttons, SIGNAL(rejected()), SLOT(reject()));
    row++;
}

void DlgSettings::onToggleAutoDownload(int state)
{
    bool enable = state == Qt::Checked;
    
    downloadInterval->setEnabled(enable);
    downloadIntervalUnit->setEnabled(enable);
    downloadDelay->setEnabled(enable);
    downloadDelayUnit->setEnabled(enable);
}

void DlgSettings::onDownloadTypeChanged(int index)
{
    Settings::DownloadType tu = static_cast<Settings::DownloadType>(downloadFormat->itemData(index).toInt());
    
    openvpnConfigFolder->setEnabled(tu != Settings::NM_EXECUTE);
}
