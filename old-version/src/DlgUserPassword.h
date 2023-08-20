/* 
 * File:   DlgUserPassword.h
 * Author: claas
 *
 * Created on 23. September 2016, 18:55
 */

#ifndef DLGUSERPASSWORD_H
#define	DLGUSERPASSWORD_H

#include <QDialog>

class QLineEdit;

class DlgUserPassword : public QDialog {
public:
    DlgUserPassword();

    virtual ~DlgUserPassword();
    
    QString username();
    QString password();

private:
    QLineEdit *_username;
    QLineEdit *_password;
};

#endif	/* DLGUSERPASSWORD_H */

