/* 
 * File:   DlgSettings.h
 * Author: claas
 *
 * Created on 15. September 2016, 21:02
 */

#ifndef DLGSETTINGS_H
#define	DLGSETTINGS_H

#include <QDialog>

class QCheckBox;
class QComboBox;
class QLineEdit;
class QSpinBox;

class DlgSettings : public QDialog {
    Q_OBJECT
    
public:
    DlgSettings();
    virtual ~DlgSettings();

private:
    QLineEdit *adminServerUrl;
    QSpinBox *downloadInterval;
    QComboBox *downloadIntervalUnit;
    QSpinBox *downloadDelay;
    QComboBox *downloadDelayUnit;
    QCheckBox *autoDownload;
    QLineEdit *openvpnConfigFolder;
    QComboBox *downloadFormat;
    QCheckBox *ignoreSslErrors;
    
    void createGui();
    void readValues();
    
private slots:
    void onToggleAutoDownload(int);
    void saveValues();
    void onDownloadTypeChanged(int);
};

#endif	/* DLGSETTINGS_H */
