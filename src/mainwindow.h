#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globalvariable.h"
#include "accountbook.h"
#include "libary/common.h"
#include "perfectnote.h"
#include "passwordmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //不能在这里进行初始化new，否则在cpp文件中就无法知道其类型

    //record
    QTableWidget *record_tw = new QTableWidget(this);
    QDialog *detail_dialog;	//记录弹窗
    QLineEdit *web_name2;	//站点
    QLineEdit *user_name2;	//用户名
    QLineEdit *pwd_name2;	//密码
    QLineEdit *note_name2;	//备注
    QPushButton *ok_btn;	//确定按钮
    int current_select_row;	//当前表格选择的行号

    void InitMainWindow();			//初始化主界面
    void InitMainWindowMenu();	//初始化窗口菜单栏
    void DetailMessage();				//显示记录框的内容
    bool IsValidRecord();				//判断是不是合法的记录
    void Tips();								//警告提示弹窗
    bool Save2Local();					//保存表格中的内容到本地数据库
    void Reboot();

protected:
    void MouseDownEvent(QMouseEvent* );
    void MouseUpEvent(QMouseEvent* );
    void MouseMoveEvent(QMouseEvent* );
    void MouseReleaseEvent(QMouseEvent* );
    void iSlot();
    void closeEvent(QCloseEvent* );

private:
    Ui::MainWindow *ui;

private slots:
	
	//窗口菜单槽
    void ABActionClicked();
    void PNActionClicked();
    void PMActionClicked();
    void UTActionClicked();

    //皮肤菜单槽
    void BlackActionClicked();
    void WhiteActionClicked();
    void DefaultActionClicked();

    //操作菜单槽
    void AddActionClicked();
    void DelActionClicked();
    void ChgActionClicked();
    void QryActionClicked();

    //语言菜单槽
    void ChineseActionClicked();
    void EnglishActionClicked();

	//帮助菜单槽
    void AboutActionClicked();
    void DocumentActionClicked();
    void UpdateLogActionClicked();
	
	//文件菜单槽
	//bool Save2Txt();
    //bool Save2Csv();
    //bool Save2Xlsx();
};
#endif // MAINWINDOW_H
