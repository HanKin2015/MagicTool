#include "passwordmanager.h"
#include "ui_passwordmanager.h"

PasswordManager::PasswordManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordManager)
{
    ui->setupUi(this);

    // 初始化主窗口
    InitMainWindow();
}

void PasswordManager::InitMainWindow()
{
    this->resize(900, 600);
    this->setWindowIcon(QIcon(PM_LOGO_FILE_PATH));
    this->setWindowTitle(tr("password manager"));
}

PasswordManager::~PasswordManager()
{
    delete ui;
}
