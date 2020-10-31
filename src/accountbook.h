#ifndef ACCOUNTBOOK_H
#define ACCOUNTBOOK_H

#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QRect>
#include <QColor>
#include <QTextBrowser>
#include <QDialog>
#include <QObject>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QDateEdit>
#include <QCloseEvent>
#include <QCheckBox>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QSignalMapper>
#include "globalvariable.h"

namespace Ui {
class AccountBook;
}

class AccountBook : public QDialog
{
    Q_OBJECT

public:
    explicit AccountBook(QWidget *parent = nullptr);
    ~AccountBook();

    void InitMainWindow();		//初始化主界面
    void InitMainWindowMenu();	//初始化窗口菜单栏
    void InitTableWidget();		//初始化表格
    void DetailMessage();		//显示记录框的内容
    bool IsValidRecord();
    void Tips();
    bool Save2Local();

private:
    Ui::AccountBook *ui;

    QString application_dir_path;

    QTableWidget *record_tw = new QTableWidget(this);
    QDialog *detail_dialog;	//记录弹窗
    QLineEdit *web_name2;	//站点
    QLineEdit *user_name2;	//用户名
    QLineEdit *pwd_name2;	//密码
    QLineEdit *note_name2;	//备注
    QPushButton *ok_btn;	//确定按钮
    int current_select_row;	//当前表格选择的行号

private slots:
    //操作菜单槽
    void AddActionClicked();
    void DelActionClicked();
    void ChgActionClicked();
    void QryActionClicked();
    void AddBtnClicked();
    void ChgBtnClicked();
};

#endif // ACCOUNTBOOK_H
