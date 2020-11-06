#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QDialog>
#include "globalvariable.h"

namespace Ui {
class PasswordManager;
}

class PasswordManager : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordManager(QWidget *parent = nullptr);
    ~PasswordManager();

    QTableWidget *passwd_table = new QTableWidget(this);
    QDialog *dialog;
    QString platform;
    QString account;
    QString password;
    QString remarks;

    void InitMenuBar();
    void InitToolBar();
    void InitMainBody();
    void InitTableWidget();
    void PasswordMessageWindow();
    void PassMsgWindowBtnClicked();
    bool IsValidRecord();
    void Tips();
    bool Save2Local();

private:
    Ui::PasswordManager *ui;

public slots:
    void TrigerMenuBar(QAction* act);
    void AddActionClicked();
    void DelActionClicked();
    void ChgActionClicked();
    void QryActionClicked();
};

#endif // PASSWORDMANAGER_H
