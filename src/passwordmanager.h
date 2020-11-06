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

    void InitMenuBar();
    void InitToolBar();
    void InitMainBody();
    void InitTableWidget();

private:
    Ui::PasswordManager *ui;

public slots:
    void TrigerMenuBar(QAction* act);
    void TrigerToolBar(QToolButton* tb);
    void AddActionClicked();
};

#endif // PASSWORDMANAGER_H
