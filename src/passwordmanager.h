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

    void InitMainWindow();

private:
    Ui::PasswordManager *ui;
};

#endif // PASSWORDMANAGER_H
