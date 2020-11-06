#include "accountbook.h"
#include "ui_accountbook.h"

AccountBook::AccountBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountBook)
{
    ui->setupUi(this);

    //初始化主窗口菜单栏
    InitMainWindowMenu();
    //初始化主窗口
    InitMainWindow();
    InitTableWidget();
}

AccountBook::~AccountBook()
{
    delete ui;
}

void AccountBook::InitMainWindowMenu()
{
    this->resize(900, 600);
    this->setWindowTitle(tr("account book"));
    this->setWindowIcon(QIcon(AB_LOGO_FILE_PATH));

    //创建操作菜单：增删改查
    QMenu* file_menu = new QMenu(tr("&file"));
    QAction *exit_action = file_menu->addAction(tr("&exit"));
    exit_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));

    QMenu *add_menu = new QMenu(tr("&add"));
    QMenu *del_menu = new QMenu(tr("&delete"));
    QMenu *chg_menu = new QMenu(tr("&change"));
    QMenu *qry_menu = new QMenu(tr("&query"));
    connect(add_menu,SIGNAL(triggered()),this,SLOT(AddActionClicked()));
    connect(del_menu,SIGNAL(triggered()),this,SLOT(DelActionClicked()));
    connect(chg_menu,SIGNAL(triggered()),this,SLOT(ChgActionClicked()));
    connect(qry_menu,SIGNAL(triggered()),this,SLOT(QryActionClicked()));
	
    QMenuBar *mb = new QMenuBar(this);
    mb->addMenu(file_menu);
    mb->addMenu(add_menu);
    mb->addMenu(del_menu);
    mb->addMenu(chg_menu);
    mb->addMenu(qry_menu);
    //mb->setGeometry(QRect(0, 0, this->width(), 32));
    mb->setGeometry(0, 0, this->width(), 32);
    connect(mb, SIGNAL(triggered(QAction*)), this, SLOT(TrigerMenu(QAction*)));
	
    //创建工具栏
    QToolBar *tb = new QToolBar(this);
    //QAction *add_act = new QAction(QIcon(ADD_PNG_PATH), tr("add"), this);      //创建QToolButton
    //tb->addAction(add_act);             			//向工具栏添加QToolButton按钮

    QToolButton *add_btn = new QToolButton(this);
    add_btn->setIcon(QIcon(ADD_PNG_PATH));
    add_btn->setFixedSize(30, 30);
    tb->addWidget(add_btn);

    QToolButton *del_btn = new QToolButton(this);
    del_btn->setIcon(QIcon(DELETE_PNG_PATH));
    del_btn->setFixedSize(30, 30);
    tb->addWidget(del_btn);

    QToolButton *chg_btn = new QToolButton(this);
    chg_btn->setIcon(QIcon(CHANGE_PNG_PATH));
    chg_btn->setFixedSize(30, 30);
    tb->addWidget(chg_btn);

    QToolButton *qry_btn = new QToolButton(this);
    qry_btn->setIcon(QIcon(QUERY_PNG_PATH));
    qry_btn->setFixedSize(30, 30);
    tb->addWidget(qry_btn);
    
    //tb->setStyleSheet("background-color:rgb(200,40,43);color:rgb(204,204,204)");
    tb->setGeometry(0, 32, this->width(), 32);
    connect(tb, SIGNAL(triggered(QToolButton*)), this, SLOT(TrigerToolBar(QToolButton*)));
}

/*
 * 打印日志吧
 *
 */
void AccountBook::TrigerMenu(QAction* act)
{
    qDebug() << act->text() << "键被按下";
}

void AccountBook::TrigerToolBar(QToolButton* tb)
{
    qDebug() << tb->text() << "键被按下";
}

void AccountBook::InitMainWindow()
{
    QWidget *main_window = new QWidget(this);
    main_window->resize(900, 600 - 64);
    main_window->move(0, 64);


    QGridLayout *main_window_gl = new QGridLayout(main_window);

    QLineEdit *search_le = new QLineEdit(main_window);
    QPushButton *search_btn = new QPushButton(tr("search"), main_window);

    //main_window_gl->addWidget(search_le, 1, 0, 1, 3, Qt::AlignLeft);

    main_window_gl->addWidget(search_le, 0, 0, 1, 3);
    main_window_gl->addWidget(search_btn, 0, 3, 1, 1);
    main_window_gl->addWidget(record_tw, 1, 0, 10, 8);

    main_window->setLayout(main_window_gl);
   connect(search_btn, &QPushButton::clicked, this, &AccountBook::AddActionClicked);

   main_window->showFullScreen();
}

void AccountBook::InitTableWidget()
{
    record_tw->setColumnCount(6);
    record_tw->setHorizontalHeaderLabels(QStringList() << tr("日期") << tr("天气") << tr("类型")<< tr("方式")<< tr("消费金额/元") << tr("备注"));    // 设置列名
    for(int i = 0; i < 5; i++)
        record_tw->setColumnWidth(i, 150);
    //获得水平方向表头的item对象
    QTableWidgetItem *columnHeaderItem = record_tw->horizontalHeaderItem(1);
    //columnHeaderItem->setFont(QFont("Helvetica"));  //设置字体
    columnHeaderItem->setBackgroundColor(QColor(0,60,10));  //设置单元格背景颜色
    columnHeaderItem->setTextColor(QColor(200,111,30));     //设置文字颜色

    //无法编辑表格
    record_tw->setEditTriggers(QAbstractItemView::NoEditTriggers);

    vector<vector<string> > ret = ReadFileAll(AB_DATA_FILE_PATH.toLatin1().data());
    int record_cnt = static_cast<int>(ret.size());

    qDebug("current record size = %d", record_cnt);
    record_tw->setRowCount(record_cnt);

    for (int i = 0; i < record_cnt; i++)
    {
        record_tw->setRowHeight(i,50);
        size_t j =  static_cast<size_t>(i);
        int item_cnt = static_cast<int>(ret[j].size());
        for (int k = 0; k < item_cnt; k++) {
            QTableWidgetItem *item = record_tw->item(i, k);
            item = new QTableWidgetItem;
            item->setText(StdString2QString(ret[j][static_cast<size_t>(k)]));
            item->setTextAlignment(Qt::AlignCenter);
            record_tw->setItem(i, k, item);
        }
    }
    record_tw->show();
    //record_tw->clearContents();
}



void AccountBook::DetailMessage()
{
    detail_dialog = new QDialog(this);
    detail_dialog->setWindowTitle("detail");

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


    ok_btn = new QPushButton(tr("ok"));
    grid_layout->addWidget(ok_btn, 4, 3, 1, 2);

    detail_dialog->setLayout(grid_layout);
    detail_dialog->show();
}

void AccountBook::AddActionClicked()
{
    DetailMessage();
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
}

void AccountBook::DelActionClicked()
{

}

void AccountBook::ChgActionClicked()
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

void AccountBook::QryActionClicked()
{

}
bool AccountBook::Save2Local()
{
    QString file_path = ".\\data\\hankin.txt";
    FILE *fp = fopen(file_path.toLatin1().data(), "w");
    if (fp == nullptr) {
        qDebug("fopen error! err=%u, %s", errno, strerror(errno));
        return false;
    }

    int rows = record_tw->rowCount();
    for (int i = 0; i < rows; i++) {
        RecordStruct rs;
        rs.web_name = QString2StdString(record_tw->item(i, 0)->text());
        rs.user_name = QString2StdString(record_tw->item(i, 1)->text());
        rs.pwd = QString2StdString(record_tw->item(i, 2)->text());
        if (record_tw->item(i, 3)->text() == "\n") {
            fprintf(fp, "%s,%s,%s,\n", rs.web_name.data(), rs.user_name.data(), rs.pwd.data());
        } else {
            rs.note = QString2StdString(record_tw->item(i, 3)->text());
            fprintf(fp, "%s,%s,%s,%s\n", rs.web_name.data(), rs.user_name.data(), rs.pwd.data(), rs.note.data());
        }
    }

    fclose(fp);
    return true;
}

void AccountBook::ChgBtnClicked()
{
    record_tw->item(current_select_row, 0)->setText(web_name2->text());
    record_tw->item(current_select_row, 1)->setText(user_name2->text());
    record_tw->item(current_select_row, 2)->setText(pwd_name2->text());
    record_tw->item(current_select_row, 3)->setText(note_name2->text());
    Save2Local();
    detail_dialog->close();
}

void AccountBook::Tips()
{
    QMessageBox::information(this, tr(""),
            tr("无效的记录！"),
            QMessageBox::tr("ok"));
}

bool AccountBook::IsValidRecord()
{
    if (web_name2->text() == nullptr) {
        goto FAILED;
    }
    if (user_name2->text() == nullptr) {
        goto FAILED;
    }
    if (pwd_name2->text() == nullptr) {
        goto FAILED;
    }

    return true;
FAILED:
    Tips();
    return false;
}



void AccountBook::AddBtnClicked()
{
    if(IsValidRecord() == false) return ;
    QMessageBox mb(QMessageBox::Warning, "","确定要添加当前记录？");
    mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    mb.setButtonText (QMessageBox::Ok,QString("确 定"));
    mb.setButtonText (QMessageBox::Cancel,QString("取 消"));
    if(mb.exec() == QMessageBox::Ok)
    {
        /*添加event*/
        RecordStruct rs;
        rs.web_name = QString2StdString(web_name2->text());
        rs.user_name = QString2StdString(user_name2->text());
        rs.pwd = QString2StdString(pwd_name2->text());
        rs.note = QString2StdString(note_name2->text());


        QString file_path = ".\\data\\hankin.txt";
        if (!WriteFile(file_path.toLatin1().data(), "a", rs))
        {
            InitTableWidget();
            QMessageBox::information(this, tr(""),
                    tr("添加成功！"),
                    QMessageBox::tr("ok"));
        } else {
            QMessageBox::information(this, tr(""),
                    tr("添加失败！"),
                    QMessageBox::tr("ok"));
        }
    }
    detail_dialog->close();
}





















