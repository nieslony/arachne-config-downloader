/* 
 * File:   DlgUserPassword.cpp
 * Author: claas
 * 
 * Created on 23. September 2016, 18:55
 */

#include "DlgUserPassword.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

DlgUserPassword::DlgUserPassword() 
{
    QGridLayout *grid = new QGridLayout(this);
    QLabel *label;
    int row = 1;
    
    _username = new QLineEdit(this);
    label = new QLabel(tr("Username:"), this);
    label->setBuddy(_username);
    grid->addWidget(label, row, 0);
    grid->addWidget(_username, row, 1);
    row++;
    
    _password = new QLineEdit(this);
    _password->setEchoMode(QLineEdit::Password);
    label = new QLabel(tr("Password:"), this);
    label->setBuddy(_password);
    grid->addWidget(label, row, 0);
    grid->addWidget(_password, row, 1);
    row++;
    
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(QDialogButtonBox::Ok);
    buttons->addButton(QDialogButtonBox::Cancel);
    grid->addWidget(buttons, row, 0, 1, 2);
    connect(buttons, SIGNAL(accepted()), SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), SLOT(reject()));
    row++;
}

DlgUserPassword::~DlgUserPassword() 
{
}

QString DlgUserPassword::username()
{
    return _username->text();
}

QString DlgUserPassword::password()
{
    return _password->text();
}
