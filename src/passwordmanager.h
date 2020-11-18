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

    QTableWidget *passwd_table;
    QDialog *dialog;
    QLineEdit *platform_edit;
    QLineEdit *account_edit;
    QLineEdit *password_edit;
    QLineEdit *remarks_edit;
    int current_row;            // 如果是增加则为总数加1，如果是修改则是当前选中的行号

    void InitMenuBar();
    void InitToolBar();
    void InitMainBody();
    void InitTableWidget();
    void PasswordMessageWindow(QString platform, QString account, QString password, QString remarks);
    bool IsValidRecord();
    void Tips();
    bool Save2Local();
    void AddTableWidgetItemData(int column, QLineEdit *data);

private:
    Ui::PasswordManager *ui;

private slots:
    void TrigerMenuBar(QAction* act);
    void PwdMsgWindowBtnClicked();
    void AddActionClicked();
    void DelActionClicked();
    void ChgActionClicked();
    void QryActionClicked();
    void BackupActionClicked();

protected:
    void MouseDownEvent(QMouseEvent* );
    void MouseUpEvent(QMouseEvent* );
    void MouseMoveEvent(QMouseEvent* );
    void MouseReleaseEvent(QMouseEvent* );
    void iSlot();
    void closeEvent(QCloseEvent* );
};

#endif // PASSWORDMANAGER_H
