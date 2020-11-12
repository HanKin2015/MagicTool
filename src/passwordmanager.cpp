#include "passwordmanager.h"
#include "ui_passwordmanager.h"

PasswordManager::PasswordManager(QWidget *parent) :
    QDialog(parent),
    passwd_table(nullptr),
    dialog(nullptr),
    platform_edit(nullptr),
    account_edit(nullptr),
    password_edit(nullptr),
    remarks_edit(nullptr),
    current_row(0),
    ui(new Ui::PasswordManager)
{
    ui->setupUi(this);

    this->resize(900, 600);
    this->setWindowIcon(QIcon(PM_LOGO_FILE_PATH));
    this->setWindowTitle(tr("password manager"));

    // 初始化菜单栏
    InitMenuBar();

    // 初始化工具栏
    InitToolBar();

    // 初始化主体
    InitMainBody();

    // 初始化表格
    InitTableWidget();
}

PasswordManager::~PasswordManager()
{
    delete ui;
}

/*
 * 初始化菜单栏：文件、操作、帮助
 */
void PasswordManager::InitMenuBar()
{
    //创建文件菜单
    QMenu* file_menu = new QMenu(tr("file(&F)"));
    QAction *exit_action = file_menu->addAction(tr("&exit"));
    exit_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));

    // 创建操作菜单：增删改查
    QMenu *operation_menu = new QMenu(tr("operation(&O)"));
    QAction *add_action = operation_menu->addAction(tr("&add"));
    QAction *del_action = operation_menu->addAction(tr("&delete"));
    QAction *chg_action = operation_menu->addAction(tr("&change"));
    QAction *qry_action = operation_menu->addAction(tr("&query"));
    connect(add_action,SIGNAL(triggered()),this,SLOT(AddActionClicked()));
    connect(del_action,SIGNAL(triggered()),this,SLOT(DelActionClicked()));
    connect(chg_action,SIGNAL(triggered()),this,SLOT(ChgActionClicked()));
    connect(qry_action,SIGNAL(triggered()),this,SLOT(QryActionClicked()));

    // 创建帮助菜单
    QMenu *help_menu = new QMenu(tr("help(&H)"));
    QAction *document_action = help_menu->addAction(tr("&document"));
    QAction *update_log_action = help_menu->addAction(tr("&update log"));
    QAction *about_action = help_menu->addAction(tr("&about"));
    //connect(about_action,SIGNAL(triggered()),this,SLOT(AboutActionClicked()));
    //connect(document_action,SIGNAL(triggered()),this,SLOT(DocumentActionClicked()));
    //connect(update_log_action,SIGNAL(triggered()),this,SLOT(UpdateLogActionClicked()));

    QMenuBar *mb = new QMenuBar(this);
    mb->addMenu(file_menu);
    mb->addMenu(operation_menu);
    mb->addMenu(help_menu);
    //mb->setGeometry(QRect(0, 0, this->width(), 32));
    mb->setGeometry(0, 0, this->width(), 32);
    connect(mb, SIGNAL(triggered(QAction*)), this, SLOT(TrigerMenuBar(QAction*)));
}

/*
 * 初始化工具栏：增加、删除、修改、查询
 */
void PasswordManager::InitToolBar()
{
    //创建工具栏
    QToolBar *tb = new QToolBar(this);
    //QAction *add_act = new QAction(QIcon(ADD_PNG_PATH), tr("add"), this);      //创建QToolButton
    //tb->addAction(add_act);             			//向工具栏添加QToolButton按钮

    QToolButton *add_btn = new QToolButton(this);
    add_btn->setIcon(QIcon(ADD_PNG_PATH));
    add_btn->setFixedSize(30, 30);
    tb->addWidget(add_btn);
    connect(add_btn, SIGNAL(clicked()), this, SLOT(AddActionClicked()));

    QToolButton *del_btn = new QToolButton(this);
    del_btn->setIcon(QIcon(DELETE_PNG_PATH));
    del_btn->setFixedSize(30, 30);
    tb->addWidget(del_btn);
    connect(del_btn, SIGNAL(clicked()), this, SLOT(DelActionClicked()));

    QToolButton *chg_btn = new QToolButton(this);
    chg_btn->setIcon(QIcon(CHANGE_PNG_PATH));
    chg_btn->setFixedSize(30, 30);
    tb->addWidget(chg_btn);
    connect(chg_btn, SIGNAL(clicked()), this, SLOT(ChgActionClicked()));

    QToolButton *qry_btn = new QToolButton(this);
    qry_btn->setIcon(QIcon(QUERY_PNG_PATH));
    qry_btn->setFixedSize(30, 30);
    tb->addWidget(qry_btn);
    connect(qry_btn, SIGNAL(clicked()), this, SLOT(QryActionClicked()));

    //tb->setStyleSheet("background-color:rgb(200,40,43);color:rgb(204,204,204)");
    tb->setGeometry(0, 32, this->width(), 32);
}

/*
 * 检测菜单栏什么键被按下
 */
void PasswordManager::TrigerMenuBar(QAction* act)
{
    qDebug() << act->text() << "键被按下";
}

/*
 * 初始化主体布局：上部分搜索栏，下部分是表格
 *
 * 搜索栏可以去掉，设计为在查询的时候弹框
 */
void PasswordManager::InitMainBody()
{
    QWidget *main_window = new QWidget(this);
    main_window->resize(900, 600 - 64);
    main_window->move(0, 64);

    QGridLayout *main_window_gl = new QGridLayout(main_window);

    QLineEdit *search_content = new QLineEdit(main_window);
    QPushButton *search_btn = new QPushButton(tr("search"), main_window);

    passwd_table = new QTableWidget(main_window);

    main_window_gl->addWidget(search_content, 0, 1, 1, 2);
    main_window_gl->addWidget(search_btn, 0, 3, 1, 1);
    main_window_gl->addWidget(passwd_table, 1, 0, 10, 4);

    main_window->setLayout(main_window_gl);
    connect(search_btn, &QPushButton::clicked, this, &PasswordManager::AddActionClicked);

    main_window->showFullScreen();
}

/*
 * 初始化表格
 *
 * 从PM_DATA_FILE_PATH本地文件中导入数据
 */
void PasswordManager::InitTableWidget()
{
    passwd_table->setColumnCount(4);
    passwd_table->setHorizontalHeaderLabels(QStringList() << tr("platform") << tr("account") << tr("password")<< tr("remarks"));    // 设置列名
    for(int i = 0; i < 4; i++)
        passwd_table->setColumnWidth(i, 150);
    //获得水平方向表头的item对象
    QTableWidgetItem *columnHeaderItem = passwd_table->horizontalHeaderItem(1);
    //columnHeaderItem->setFont(QFont("Helvetica"));  //设置字体
    columnHeaderItem->setBackgroundColor(QColor(0,60,10));  //设置单元格背景颜色
    columnHeaderItem->setTextColor(QColor(200,111,30));     //设置文字颜色

    //无法编辑表格
    passwd_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    vector<vector<string> > ret = ReadFileAll(PM_DATA_FILE_PATH.toLatin1().data());
    int record_cnt = static_cast<int>(ret.size());

    qDebug("current record size = %d", record_cnt);
    passwd_table->setRowCount(record_cnt);

    for (int i = 0; i < record_cnt; i++)
    {
        passwd_table->setRowHeight(i,50);
        size_t j =  static_cast<size_t>(i);
        int item_cnt = static_cast<int>(ret[j].size());
        for (int k = 0; k < item_cnt; k++) {
            QTableWidgetItem *item = passwd_table->item(i, k);
            item = new QTableWidgetItem;
            item->setText(StdString2QString(ret[j][static_cast<size_t>(k)]));
            item->setTextAlignment(Qt::AlignCenter);
            passwd_table->setItem(i, k, item);
        }
    }
    passwd_table->show();
    //passwd_table->clearContents();
}


/*
 * 密码信息详细弹框
 *
 * 增加和修改都会调用这个弹框
 */
void PasswordManager::PasswordMessageWindow(QString platform, QString account, QString password, QString remarks)
{
    qDebug("%s:%d", __FUNCTION__, __LINE__);

    dialog = new QDialog(this);
    dialog->setWindowTitle(tr("password message"));

    QGridLayout *grid_layout = new QGridLayout();

    QLabel *platform_label = new QLabel(tr("platform"));
    platform_edit = new QLineEdit(platform, dialog);
    grid_layout->addWidget(platform_label, 0, 0, 1, 2);
    grid_layout->addWidget(platform_edit, 0, 2, 1, 3);

    QLabel *account_label = new QLabel(tr("account"));
    account_edit = new QLineEdit(account, dialog);
    grid_layout->addWidget(account_label, 1, 0, 1, 2);
    grid_layout->addWidget(account_edit, 1, 2, 1, 3);

    QLabel *password_label = new QLabel(tr("password"));
    password_edit = new QLineEdit(password, dialog);
    grid_layout->addWidget(password_label, 2, 0, 1, 2);
    grid_layout->addWidget(password_edit, 2, 2, 1, 3);

    QLabel *remarks_label = new QLabel(tr("remarks"));
    remarks_edit = new QLineEdit(remarks, dialog);
    grid_layout->addWidget(remarks_label, 3, 0, 1, 2);
    grid_layout->addWidget(remarks_edit, 3, 2, 1, 3);


    QPushButton *ok_btn = new QPushButton(tr("ok"));
    grid_layout->addWidget(ok_btn, 4, 3, 1, 2);
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(PwdMsgWindowBtnClicked()));

    dialog->setLayout(grid_layout);
    dialog->show();
}

/*
 * 增加 功能点击事件
 */
void PasswordManager::AddActionClicked()
{
    current_row = passwd_table->rowCount();
    PasswordMessageWindow("", "", "", "");
}

/*
 * 删除 功能点击事件
 */
void PasswordManager::DelActionClicked()
{
    current_row = passwd_table->currentRow();
    if (current_row != -1) {
        QMessageBox mb(QMessageBox::Warning, "", tr("Are you sure to delete this password message?"));
        mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        mb.setButtonText (QMessageBox::Ok,QString(tr("yes")));
        mb.setButtonText (QMessageBox::Cancel,QString(tr("no")));
        if(mb.exec() == QMessageBox::Ok) {
            passwd_table->removeRow(current_row);
        }
    }
}

/*
 * 修改 功能点击事件
 */
void PasswordManager::ChgActionClicked()
{
    qDebug("%s:%d", __FUNCTION__, __LINE__);

    QList<QTableWidgetItem*> items = passwd_table->selectedItems();
    current_row = passwd_table->currentRow();
//    for(int i = 0; i < 4; i++)
//    {
//        QTableWidgetItem *item = record_tw->item(row, i);
//        QString text = item->text(); //获取内容
//        qDebug() << text;
//    }
    qDebug("%s:%d", __FUNCTION__, __LINE__);
    PasswordMessageWindow(passwd_table->item(current_row, 0) ? passwd_table->item(current_row, 0)->text() : "",
                          passwd_table->item(current_row, 1) ? passwd_table->item(current_row, 1)->text() : "",
                          passwd_table->item(current_row, 2) ? passwd_table->item(current_row, 2)->text() : "",
                          passwd_table->item(current_row, 3) ? passwd_table->item(current_row, 3)->text() : "");
}

/*
 * 查询 功能点击事件
 */
void PasswordManager::QryActionClicked()
{

}

/*
 * 保存表格数据到本地文件PM_DATA_FILE_PATH
 */
bool PasswordManager::Save2Local()
{
    FILE *fp = fopen(PM_DATA_FILE_PATH.toLatin1().data(), "w");
    if (fp == nullptr) {
        qDebug("fopen error! err=%u, %s", errno, strerror(errno));
        return false;
    }

    int rows = passwd_table->rowCount();
    int columns = passwd_table->columnCount();
    qDebug("There are %d password records.", rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (passwd_table->item(i, j)->text() != "\n") {
                fprintf(fp, "%s", GetTableItemData(passwd_table, i, j));
            }
            fprintf(fp, "%s", j == (columns - 1) ? "\n" : ",");
        }
    }

    fclose(fp);
    return true;
}

/*
 * 提示框
 */
void PasswordManager::Tips()
{
    QMessageBox::information(this, tr("warning"),
            tr("password data message have format errors!"),
            QMessageBox::tr("ok"));
}

/*
 * 判断密码信息录入的合法性
 */
bool PasswordManager::IsValidRecord()
{
    if (platform_edit->text() == "") {
        goto FAILED;
    }
    if (account_edit->text() == "") {
        goto FAILED;
    }
    if (password_edit->text() == "") {
        goto FAILED;
    }

    return true;
FAILED:
    Tips();
    return false;
}

/*
 * 向表格中写入数据
 */
void PasswordManager::AddTableWidgetItemData(int column, QLineEdit *data)
{
    if (passwd_table->item(current_row, column)) {
        passwd_table->item(current_row, column)->setText(data->text());
    } else {
        passwd_table->setRowCount(current_row + 1);
        QTableWidgetItem *item = passwd_table->item(current_row, column);
        item = new QTableWidgetItem;
        item->setText(data->text());
        item->setTextAlignment(Qt::AlignCenter);
        passwd_table->setItem(current_row, column, item);
    }
}

/*
 * 密码详细信息框确定按钮点击事件
 */
void PasswordManager::PwdMsgWindowBtnClicked()
{
    if(IsValidRecord() == false) return;

    AddTableWidgetItemData(0, platform_edit);
    AddTableWidgetItemData(1, account_edit);
    AddTableWidgetItemData(2, password_edit);
    AddTableWidgetItemData(3, remarks_edit);

    dialog->close();
    delete dialog;
    dialog = nullptr;
}

/*
 * 重写退出事件
 */
void PasswordManager::closeEvent(QCloseEvent *event)
{
    QMessageBox close_mb(QMessageBox::Warning, "",tr("Are you sure exit?"));
    close_mb.setWindowFlag(Qt::FramelessWindowHint);
    close_mb.setAttribute(Qt::WA_ShowModal, true);

    close_mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    close_mb.setButtonText (QMessageBox::Ok,QString(tr("yes")));
    close_mb.setButtonText (QMessageBox::Cancel,QString(tr("no")));
    if(close_mb.exec() == QMessageBox::Ok) {
        Save2Local();
        event->accept();
    } else {
        event->ignore();
    }
    return ;
}



















