#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMenu *file_menu;           //文件菜单
    QAction *exit_action;       //退出
    QMenu *help_menu;           //帮助菜单
    QAction *document_action;   //软件操作帮助文档
    QAction *update_log_action; //更新日志
    QAction *about_action;      //关于软件
    QMenu *skin_menu;           //换肤菜单
    QAction *black_action;      //黑色炫酷
    QAction *white_action;      //白色靓丽
    QAction *default_action;    //原生态

    //不能在这里进行初始化new，否则在cpp文件中就无法知道其类型
    QTextEdit *demo_example;
    QLineEdit *search_content;


    QTableWidget *messageWidget = new QTableWidget(this);

    QString application_dir_path;


    QLineEdit *web_name2;
    QLineEdit *user_name2;
    QLineEdit *pwd_name2;
    QLineEdit *note_name2;
    QPushButton *ok_btn;

    //初始化主界面
    void InitMainWindow();
    //
    void InitMainWindowMenu();
    void InitTableWidget();
    void DetailMessage();
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

    void DemoActionClicked();
    void MyWindow();
    void StlFopenButtonClicked();
    void CTeamDemo();

    //void UserNameClicked();
    void BlackActionClicked();
    void WhiteActionClicked();
    void DefaultActionClicked();

    //
    void AddActionClicked();
    void DelActionClicked();
    void ChgActionClicked();
    void QryActionClicked();
    void AddBtnClicked();

    void AboutActionClicked();
    void DocumentActionClicked();
    void UpdateLogActionClicked();
};
#endif // MAINWINDOW_H
