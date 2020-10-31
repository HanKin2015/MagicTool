#include "passwordmanager.h"
#include "ui_passwordmanager.h"

PasswordManager::PasswordManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordManager)
{
    ui->setupUi(this);
}

PasswordManager::~PasswordManager()
{
    delete ui;
}
