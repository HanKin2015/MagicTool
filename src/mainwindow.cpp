#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化主窗口菜单栏
    InitMainWindowMenu();
    // 初始化主窗口
    InitMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * 初始化主窗口菜单栏
 *
*/
void MainWindow::InitMainWindowMenu()
{
    this->resize(900, 600);
    this->setWindowTitle(tr("Magic Tool"));
    this->setWindowIcon(QIcon(APP_LOGO_FILE_PATH));
    //QFont font;
    //font.setPointSize(20);
    //font.setFamily("Consolas");
    //this->setFont(font);

    // 创建文件菜单
    QMenu *file_menu = ui->menubar->addMenu(tr("file(&F)"));
    QAction *csv_actoion = file_menu->addAction(tr("export to csv"));
    QAction *txt_actoion = file_menu->addAction(tr("export to txt"));
    QAction *xlsx_actoion = file_menu->addAction(tr("export to xlsx"));
    QAction *backup_action = file_menu->addAction(tr("create backup"));
    QAction *exit_action = file_menu->addAction(tr("exit"));
    connect(csv_actoion,SIGNAL(triggered()),this,SLOT(BlackActionClicked()));
    connect(txt_actoion,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));
    connect(xlsx_actoion,SIGNAL(triggered()),this,SLOT(BlackActionClicked()));
    connect(exit_action,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));
    connect(backup_action,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));

    // 创建换肤菜单
    QMenu *skin_menu = ui->menubar->addMenu(tr("skin(&S)"));
    QAction *black_action = skin_menu->addAction(tr("&cool black"));
    QAction *white_action = skin_menu->addAction(tr("&beautiful white"));
    QAction *default_action = skin_menu->addAction(tr("&default"));
    connect(black_action,SIGNAL(triggered()),this,SLOT(BlackActionClicked()));
    connect(white_action,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));
    connect(default_action,SIGNAL(triggered()),this,SLOT(DefaultActionClicked()));

    // 创建窗口菜单（由于不需要全局使用，所以可以在cpp文件中声明定义）
    QMenu *window_menu = ui->menubar->addMenu(tr("window(&W)"));
    QAction *AB_action = window_menu->addAction(tr("&account book"));
    QAction *PN_action = window_menu->addAction(tr("&perfect note"));
    QAction *PM_action = window_menu->addAction(tr("&password manager"));
    connect(AB_action,SIGNAL(triggered()),this,SLOT(ABActionClicked()));
    connect(PN_action,SIGNAL(triggered()),this,SLOT(PNActionClicked()));
    connect(PM_action,SIGNAL(triggered()),this,SLOT(PMActionClicked()));

    // 创建操作菜单：增删改查
    QMenu *operation_menu = ui->menubar->addMenu(tr("operation(&O)"));
    QAction *add_action = operation_menu->addAction(tr("&add"));
    QAction *del_action = operation_menu->addAction(tr("&delete"));
    QAction *chg_action = operation_menu->addAction(tr("&change"));
    QAction *qry_action = operation_menu->addAction(tr("&query"));
    connect(add_action,SIGNAL(triggered()),this,SLOT(AddActionClicked()));
    connect(del_action,SIGNAL(triggered()),this,SLOT(DelActionClicked()));
    connect(chg_action,SIGNAL(triggered()),this,SLOT(ChgActionClicked()));
    connect(qry_action,SIGNAL(triggered()),this,SLOT(QryActionClicked()));

    // 创建语言菜单：中文英文
    QMenu *lang_menu = ui->menubar->addMenu(tr("language(&Y)"));
    QAction *chinese_action = lang_menu->addAction(tr("&中文"));
    QAction *english_action = lang_menu->addAction(tr("&english"));
    connect(chinese_action,SIGNAL(triggered()),this,SLOT(ChineseActionClicked()));
    connect(english_action,SIGNAL(triggered()),this,SLOT(EnglishActionClicked()));

    // 创建帮助菜单
    QMenu *help_menu = ui->menubar->addMenu(tr("help(&H)"));
    QAction *document_action = help_menu->addAction(tr("&document"));
    QAction *update_log_action = help_menu->addAction(tr("&update log"));
    QAction *about_action = help_menu->addAction(tr("&about"));
    connect(about_action,SIGNAL(triggered()),this,SLOT(AboutActionClicked()));
    connect(document_action,SIGNAL(triggered()),this,SLOT(DocumentActionClicked()));
    connect(update_log_action,SIGNAL(triggered()),this,SLOT(UpdateLogActionClicked()));
}

void MainWindow::InitMainWindow()
{
    QGridLayout *main_window_gl = new QGridLayout(this);

    QLineEdit *search_le = new QLineEdit(this);
    QPushButton *search_btn = new QPushButton(tr("search"), this);

    //main_window_gl->addWidget(search_le, 1, 0, 1, 3, Qt::AlignLeft);
    main_window_gl->addWidget(search_le, 1, 0, 1, 3);
    main_window_gl->addWidget(search_btn, 1, 3, 1, 1);
    main_window_gl->addWidget(record_tw, 2, 0, 10, 8);

    ui->centralwidget->setLayout(main_window_gl);

   connect(search_btn, &QPushButton::clicked, this, &MainWindow::ABActionClicked);
}



void MainWindow::DetailMessage()
{
    detail_dialog = new QDialog(this);

    QGridLayout *grid_layout = new QGridLayout;

    QLabel *web_name1 = new QLabel("站 点");
    web_name2 = new QLineEdit();
    grid_layout->addWidget(web_name1, 0, 0, 1, 2);
    grid_layout->addWidget(web_name2, 0, 2, 1, 3);
    QLabel *user_name1 = new QLabel("用户名");
    user_name2 = new QLineEdit();
    grid_layout->addWidget(user_name1, 1, 0, 1, 2);
    grid_layout->addWidget(user_name2, 1, 2, 1, 3);
    QLabel *pwd_name1 = new QLabel("密 码");
    pwd_name2 = new QLineEdit();
    grid_layout->addWidget(pwd_name1, 2, 0, 1, 2);
    grid_layout->addWidget(pwd_name2, 2, 2, 1, 3);
    QLabel *note_name1 = new QLabel("备 注");
    note_name2 = new QLineEdit();
    grid_layout->addWidget(note_name1, 3, 0, 1, 2);
    grid_layout->addWidget(note_name2, 3, 2, 1, 3);
    ok_btn = new QPushButton("确定");
    grid_layout->addWidget(ok_btn, 4, 3, 1, 2);

    detail_dialog->setLayout(grid_layout);
    detail_dialog->show();
}

void MainWindow::AddActionClicked()
{
    DetailMessage();
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
}

void MainWindow::DelActionClicked()
{

}

void MainWindow::ChgActionClicked()
{
    DetailMessage();

    QList<QTableWidgetItem*> items = record_tw->selectedItems();
    current_select_row = record_tw->currentRow();
//    for(int i = 0; i < 4; i++)
//    {
//        QTableWidgetItem *item = record_tw->item(row, i);
//        QString text = item->text(); //获取内容
//        qDebug() << text;
//    }

    web_name2->setText(record_tw->item(current_select_row, 0)->text());
    user_name2->setText(record_tw->item(current_select_row, 1)->text());
    pwd_name2->setText(record_tw->item(current_select_row, 2)->text());
    note_name2->setText(record_tw->item(current_select_row, 3)->text());
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(ChgBtnClicked()));
}

void MainWindow::QryActionClicked()
{

}

bool MainWindow::Save2Local()
{
    int rows = record_tw->rowCount();
    int columns = record_tw->columnCount();

    QString file_path = ".\\data\\hankin.txt";
    FILE *fp = fopen(file_path.toLatin1().data(), "w");
    if (fp == nullptr) {
        qDebug("fopen error! err=%u, %s", errno, strerror(errno));
        goto FAILED;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (record_tw->item(i, j)) {
                string str = GetTableItemData(record_tw, i, j);
                fprintf(fp, "%s", str.data());
            }
            fprintf(fp, "%s", (j == (columns - 1)) ? "\n" : ",");
        }
    }

    fclose(fp);

FAILED:
    return false;
}

void MainWindow::ABActionClicked()
{
    AccountBook *ab = new AccountBook();
    ab->show();
}

void MainWindow::PNActionClicked()
{
    PerfectNote *pn = new PerfectNote();
    pn->show();
}

void MainWindow::PMActionClicked()
{
    PasswordManager *pm = new PasswordManager();
    pm->show();
}

//重写退出事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox close_mb(QMessageBox::Warning, "",tr("Are you sure exit?"));
    //close_mb.setWindowTitle("你舍得离开吗");
    close_mb.setWindowFlag(Qt::FramelessWindowHint);
    close_mb.setAttribute(Qt::WA_ShowModal, true);

    close_mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    close_mb.setButtonText (QMessageBox::Ok,QString(tr("yes")));
    close_mb.setButtonText (QMessageBox::Cancel,QString(tr("no")));
    if(close_mb.exec() == QMessageBox::Ok)
    {
        //关闭服务器
        //TerminateProcess(hProcess, 0);
        event->accept();
    }
    else
    {
        event->ignore();
    }
    return ;
}

void MainWindow::BlackActionClicked()
{
    QFile qss(BLACK_SKIN_FILE_PATH);
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::WhiteActionClicked()
{
    QFile qss(WHITE_SKIN_FILE_PATH);
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::DefaultActionClicked()
{
    QFont font;
    font.setPointSize(20);
    font.setFamily(("Consolas"));
    this->setFont(font);
    this->update();
    this->repaint();



    QFile qss(DEFAULT_SKIN_FILE_PATH);
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::DocumentActionClicked()
{
    QMessageBox::information(this, tr("document"),
                tr("集密码和学习笔记于一身！"),
                QMessageBox::tr("ok"));
}

void MainWindow::AboutActionClicked()
{
    QMessageBox::information(this, tr("about software"),
                tr("Build time : 23 Octouber 2020\nBuild 1001"),
                QMessageBox::tr("ok"));
}

void MainWindow::UpdateLogActionClicked()
{
    QMessageBox::information(this, tr("update log"),
                tr("从文件里读取。"),
                QMessageBox::tr("ok"));
}


/*
 * 切换为中文语言
 * 保存一个标记到本地配置数据文件lang.ini
 * 1则表示为中文模式，0则表示为英文模式
 */
void MainWindow::ChineseActionClicked()
{
    qDebug() << "Chinese";
    vector<char*> data;
    data.push_back(const_cast<char*>("1"));
    WriteFile(LANG_FILE_PATH.toStdString().data(), data);
    Reboot();
}

/*
 * 切换为英文语言
 */
void MainWindow::EnglishActionClicked()
{
    qDebug() << "English";
    vector<char*> data;
    data.push_back(const_cast<char*>("0"));
    WriteFile(LANG_FILE_PATH.toStdString().data(), data);
    Reboot();
}

/*
 *
 *
 */
void MainWindow::Reboot()
{
    qApp->exit(EXIT_CODE_REBOOT);
}
