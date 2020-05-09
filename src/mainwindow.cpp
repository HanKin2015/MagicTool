#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    application_dir_path = QCoreApplication::applicationDirPath();

    //初始化主窗口菜单栏
    InitMainWindowMenu();
    //初始化主窗口
    InitMainWindow();
    InitTableWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitMainWindow()
{
    QGridLayout *main_window_gl = new QGridLayout(this);

    QLineEdit *search_le = new QLineEdit(this);
    QPushButton *search_btn = new QPushButton("搜索", this);

    //main_window_gl->addWidget(search_le, 1, 0, 1, 3, Qt::AlignLeft);
    main_window_gl->addWidget(search_le, 1, 0, 1, 3);
    main_window_gl->addWidget(search_btn, 1, 3, 1, 1);
    main_window_gl->addWidget(record_tw, 2, 0, 10, 8);

    ui->centralwidget->setLayout(main_window_gl);

   connect(search_btn, &QPushButton::clicked, this, &MainWindow::MyWindow);
}

void MainWindow::InitTableWidget()
{

    record_tw->setColumnCount(6);
    record_tw->setHorizontalHeaderLabels(QStringList() << tr("站点") << tr("用户名") << tr("密码")<< tr("备注") << tr("hide") << tr("other"));    // 设置列名
//    for(int i = 0; i < 5; i++)
//        record_tw->setColumnWidth(i, 200);
    record_tw->setColumnWidth(2, 180);
    record_tw->setColumnWidth(3, 180);
    record_tw->setColumnHidden(4,true);
    record_tw->setColumnWidth(5, 240);
    //获得水平方向表头的item对象
    QTableWidgetItem *columnHeaderItem = record_tw->horizontalHeaderItem(1);
    //columnHeaderItem->setFont(QFont("Helvetica"));  //设置字体
    columnHeaderItem->setBackgroundColor(QColor(0,60,10));  //设置单元格背景颜色
    columnHeaderItem->setTextColor(QColor(200,111,30));     //设置文字颜色

    //无法编辑表格
    record_tw->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //按条件进行搜索
//       string startString = "NULL";
//       if(start->text() != NULL && startLabel->isChecked()) startString = QStringToStdString(start->text());
//       string endString = "NULL";
//       if(end->text() != NULL && endLabel->isChecked()) endString = QStringToStdString(end->text());
//       string timeString = "NULL";
//       if(dateTime->text() != NULL && timeLabel->isChecked()) timeString = QStringToStdString(dateTime->text());
//       string typeString = "NULL";
//       if(type->currentText() != NULL && typeLabel->isChecked()) typeString = QStringToStdString(type->currentText());
//       vector<EventStruct>  es = client.getEvent(startString,endString,timeString,typeString);
//       vector<EventStruct>::iterator iter2 = es.begin();
//       if(es.size() == 0) {
//           record_tw->clearContents();
//           record_tw->setRowCount(0);
//   //        record_tw->show();
//           QMessageBox::information(this, tr(""),
//                   tr("未搜索到结果！"),
//                   QMessageBox::tr("确定"));
//           return ;
//       }
//       record_tw->setRowCount(es.size());   // 设置结果占的行数
//   //    if(es.size() <= resultNum) {
//           record_tw->clearContents();
//   //    }
//       resultNum = es.size();


    qDebug() << application_dir_path;
    QString file_path = ".\\data\\hankin.txt";
    vector<RecordStruct> ret = ReadFile(file_path.toLatin1().data());
    int record_cnt = static_cast<int>(ret.size());

    qDebug("current record size = %d", record_cnt);
    record_tw->setRowCount(record_cnt);

    for (int i = 0; i < record_cnt; i++)
    {
        record_tw->setRowHeight(i,50);
        QTableWidgetItem *item0 = record_tw->item(i,0); // 发布人
        QTableWidgetItem *item1 = record_tw->item(i,1); // 人数
        QTableWidgetItem *item2 = record_tw->item(i,2); // 始发地
        QTableWidgetItem *item3 = record_tw->item(i,3); // 备注
        //QTableWidgetItem *item4 = record_tw->item(i,4); //

        QWidget *remark = new QWidget();
        QGridLayout *layout = new QGridLayout(record_tw);
        // 创建QPushButton控件
        QPushButton *joinBtn = new QPushButton(record_tw);
        joinBtn->setText("一起嗨");
        layout->addWidget(joinBtn,0,0,1,1);
        QPushButton *detailBtn = new QPushButton(record_tw);
        detailBtn->setText("详情");
        layout->addWidget(detailBtn,0,1,1,1);
        remark->setLayout(layout);

        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(StdString2QString(ret[i].web_name));
            item0->setTextAlignment(Qt::AlignCenter);
            record_tw->setItem(i, 0, item0);

            item1 = new QTableWidgetItem;
            //item1->setText(QString("%1人").arg(5));
            item1->setText(StdString2QString(ret[i].user_name));
            item1->setTextAlignment(Qt::AlignCenter);
            record_tw->setItem(i, 1, item1);

            item2 = new QTableWidgetItem;
            item2->setText(StdString2QString(ret[i].pwd));
            item2->setTextAlignment(Qt::AlignCenter);
            record_tw->setItem(i, 2, item2);

            item3 = new QTableWidgetItem;
            item3->setText(StdString2QString(ret[i].note));
            item3->setTextAlignment(Qt::AlignCenter);
            record_tw->setItem(i, 3, item3);

            //item7 = new QTableWidgetItem;
            record_tw->setCellWidget(i,5,remark);

        }
    }
    record_tw->show();
    //record_tw->clearContents();
}

void MainWindow::InitMainWindowMenu()
{
    this->resize(900, 600);
    this->setWindowTitle("Magic Tool");
    this->setWindowIcon(QIcon(application_dir_path + "/image/alienx64.png"));
    //QFont font;
    //font.setPointSize(20);
    //font.setFamily("Consolas");
    //this->setFont(font);

    // 创建文件菜单
    QMenu *file_menu = ui->menubar->addMenu(tr("文件(&F)"));
    QAction *csv_actoion = file_menu->addAction("导出为csv");
    QAction *txt_actoion = file_menu->addAction("导出为txt");
    QAction *xlsx_actoion = file_menu->addAction("导出为xlsx");
    QAction *backup_action = file_menu->addAction("创建备份");
    QAction *exit_action = file_menu->addAction(tr("退出"));
    connect(csv_actoion,SIGNAL(triggered()),this,SLOT(BlackActionClicked()));
    connect(txt_actoion,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));
    connect(xlsx_actoion,SIGNAL(triggered()),this,SLOT(BlackActionClicked()));
    connect(exit_action,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));
    connect(backup_action,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));

    // 创建换肤菜单
    QMenu *skin_menu = ui->menubar->addMenu(tr("换肤(&S)"));
    QAction *black_action = skin_menu->addAction(tr("&黑色炫酷"));
    QAction *white_action = skin_menu->addAction(tr("&白色靓丽"));
    QAction *default_action = skin_menu->addAction(tr("&默认皮肤"));
    connect(black_action,SIGNAL(triggered()),this,SLOT(BlackActionClicked()));
    connect(white_action,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));
    connect(default_action,SIGNAL(triggered()),this,SLOT(DefaultActionClicked()));

    // 创建窗口菜单（由于不需要全局使用，所以可以在cpp文件中声明定义）
    QMenu *window_menu = ui->menubar->addMenu(tr("窗口(&W)"));
    QAction *cteam_action = window_menu->addAction(tr("&cteam"));
    QAction *demo_action = window_menu->addAction(tr("&笔记搜索"));
    connect(cteam_action,SIGNAL(triggered()),this,SLOT(CTeamDemo()));
    connect(demo_action,SIGNAL(triggered()),this,SLOT(DemoActionClicked()));

    //创建操作菜单：增删改查
    QMenu *operation_menu = ui->menubar->addMenu(tr("操作(&O)"));
    QAction *add_action = operation_menu->addAction(tr("&增加"));
    QAction *del_action = operation_menu->addAction(tr("&删除"));
    QAction *chg_action = operation_menu->addAction(tr("&修改"));
    QAction *qry_action = operation_menu->addAction(tr("&查询"));
    connect(add_action,SIGNAL(triggered()),this,SLOT(AddActionClicked()));
    connect(del_action,SIGNAL(triggered()),this,SLOT(DelActionClicked()));
    connect(chg_action,SIGNAL(triggered()),this,SLOT(ChgActionClicked()));
    connect(qry_action,SIGNAL(triggered()),this,SLOT(QryActionClicked()));

    // 创建帮助菜单
    QMenu *help_menu = ui->menubar->addMenu(tr("帮助(&H)"));
    QAction *document_action = help_menu->addAction(tr("&文档"));
    QAction *update_log_action = help_menu->addAction(tr("更新日志"));
    QAction *about_action = help_menu->addAction(tr("&关于"));
    connect(about_action,SIGNAL(triggered()),this,SLOT(AboutActionClicked()));
    connect(document_action,SIGNAL(triggered()),this,SLOT(DocumentActionClicked()));
    connect(update_log_action,SIGNAL(triggered()),this,SLOT(UpdateLogActionClicked()));
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

FAILED:
    return false;
}

void MainWindow::ChgBtnClicked()
{
    record_tw->item(current_select_row, 0)->setText(web_name2->text());
    record_tw->item(current_select_row, 1)->setText(user_name2->text());
    record_tw->item(current_select_row, 2)->setText(pwd_name2->text());
    record_tw->item(current_select_row, 3)->setText(note_name2->text());
    Save2Local();
    detail_dialog->close();
}

void MainWindow::Tips()
{
    QMessageBox::information(this, tr(""),
            tr("无效的记录！"),
            QMessageBox::tr("确定"));
}

bool MainWindow::IsValidRecord()
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



void MainWindow::AddBtnClicked()
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
                    QMessageBox::tr("确定"));
        } else {
            QMessageBox::information(this, tr(""),
                    tr("添加失败！"),
                    QMessageBox::tr("确定"));
        }
    }
    detail_dialog->close();
}



void MainWindow::CTeamDemo()
{
    QPixmap image;
    //QImage *image = new QImage();//定义一张图片
    QLabel *avatar = new QLabel(this);  //头像
    QLabel *userName = new QLabel(this);//用户名称
    QGridLayout *mainLayout = new QGridLayout(this);
    QCheckBox *startLabel = new QCheckBox(this);
    QLineEdit *start = new QLineEdit(this); //始发地
    QCheckBox *endLabel = new QCheckBox(this);
    QLineEdit *end = new QLineEdit(this);   //目的地
    QCheckBox *timeLabel = new QCheckBox(this);
    QDateEdit *dateTime = new QDateEdit(this);//出发日期
    QCheckBox *typeLabel = new QCheckBox(this);
    QComboBox *type = new QComboBox(this);  //活动项目

    QPushButton *searchBtn = new QPushButton(this); //搜索按钮
    QPushButton *publishBtn = new QPushButton(this);  //发布按钮


    image.load("images/alienx64.png");//加载
    avatar->clear();//清空
    avatar->setPixmap(image);//加载到Label标签
    avatar->show();//显示
    avatar->setMaximumHeight(80);
    avatar->setMaximumWidth(80);
     mainLayout->addWidget(avatar,0,3,1,1);
    //    userName->setText(userNameGlobal);
     userName->setAlignment(Qt::AlignCenter);
     userName->setMinimumHeight(100);
     mainLayout->addWidget(userName,0,2,1,3);

     startLabel->setText("始发地:");
     mainLayout->addWidget(startLabel,1,0,1,1);
     mainLayout->addWidget(start,1,1,1,3);
     timeLabel->setText("出发日期:");
     dateTime->setDisplayFormat("yyyy-MM-dd");
     dateTime->setCalendarPopup(true);
    //    QDateTime current_date_time = QDateTime::currentDateTime().;
    //    QString current_date = current_date_time.toString("yyyy-MM-dd");
     dateTime->setDate(QDate::currentDate());
    //    dateTime->setDisplayFormat(current_date);
     mainLayout->addWidget(timeLabel,1,4,1,1);
     mainLayout->addWidget(dateTime,1,5,1,3);

     endLabel->setText("目的地:");
     mainLayout->addWidget(endLabel,2,0,1,1);
     mainLayout->addWidget(end,2,1,1,3);
     typeLabel->setText("活动项目:");
     mainLayout->addWidget(typeLabel,2,4,1,1);
     type->addItem("电影");
     type->addItem("骑自行车");
     type->addItem("旅游");
     type->addItem("打球");
     type->addItem("下棋");
     type->addItem("打牌");
     type->addItem("露营");
     mainLayout->addWidget(type,2,5,1,3);
     QLabel *hj = new QLabel();
     hj->setText("温馨提示:搜索时可以勾选相应的条件.");
     hj->setStyleSheet("color:rgb(100,100,100);");
     mainLayout->addWidget(hj,3,0,1,2);

     searchBtn->setText("搜索");
     mainLayout->addWidget(searchBtn,3,7,1,1);
     publishBtn->setText("发布");
     mainLayout->addWidget(publishBtn,3,6,1,1);

     // 反馈信息

    mainLayout->addWidget(record_tw, 4, 0, 1, 8);

     ui->centralwidget->setLayout(mainLayout);

    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::MyWindow);
}

QString read_csv(const char *file_path)
{
    qDebug("start read csv");

    const int buffer_size = 100;
    char buffer[buffer_size + 1];
    QString tmp = "";
    char *current_path;
    current_path = getcwd(nullptr, 0);
    if (current_path == nullptr) {
        qDebug("get current_path faild! err=%u, %s", errno, strerror(errno));
        return tmp;
    }
    qDebug("current_path = %s", current_path);

    FILE *fp = fopen(file_path, "r");
    if (fp == nullptr) {
        qDebug("fopen error! err=%u, %s", errno, strerror(errno));
        return tmp;
    }
    while (fgets(buffer, buffer_size, fp) != nullptr) {
        //qDebug() << buffer;
        tmp += QString::fromLocal8Bit(buffer);
    }
    fclose(fp);
    return tmp;
}

void MainWindow::StlFopenButtonClicked()
{
    char *current_path;
    current_path = getcwd(nullptr, 0);
    if (current_path == nullptr) {
        qDebug("get current_path faild! err=%u, %s", errno, strerror(errno));
        return;
    }

    QString tmp = search_content->text();
    QString file_path = QString(".\\data\\stl_%1.txt").arg(tmp);


    QString demo = read_csv(file_path.toLatin1().data());
    demo_example->setText(demo);
}

void MainWindow::MyWindow()
{

}

void MainWindow::DemoActionClicked()
{
    QDialog *demo = new QDialog(this);
    demo->setWindowTitle("知识库");


    QWidget *win=new QWidget(demo);

    win->resize(800, 600);

    QHBoxLayout *hbox_layout=new QHBoxLayout(win);//水平布局管理器（父管理器）；
    QVBoxLayout *vbox_left =new QVBoxLayout;//垂直布局管理器（子管理器）；
    QVBoxLayout *vbox_right=new QVBoxLayout;

    //设定每个布局管理器中的部件间间隔
    hbox_layout->setSpacing(50);
    vbox_left->setSpacing(25);
    vbox_right->setSpacing(25);

    //搜索框
    search_content = new QLineEdit(win);
    QPushButton *search_button = new QPushButton("搜索", win);
    connect(search_button, &QPushButton::clicked, this, &MainWindow::StlFopenButtonClicked);

    QPushButton *stl_fopen = new QPushButton(win);
    stl_fopen->setText(tr("读文件"));
    QObject::connect(stl_fopen, &QPushButton::clicked, this, &MainWindow::StlFopenButtonClicked);

    QPushButton *quit=new QPushButton(win);
    quit->setText(tr("退出"));
    QObject::connect(quit,SIGNAL(clicked()),win,SLOT(close()));

    QTableWidget *catalog_tw = new QTableWidget(win);
    catalog_tw->setColumnCount(1);
    catalog_tw->setColumnWidth(0, 150);
    catalog_tw->setHorizontalHeaderLabels((QStringList() << tr("name")));
    QString file_path = ".\\data\\catalog.txt";
    vector<vector<string> > ret = ReadFileAll(file_path.toLatin1().data());
    int catalog_cnt = static_cast<int>(ret.size());
    catalog_tw->setRowCount(catalog_cnt);
    for (int i = 0; i < catalog_cnt; i++) {
        //catalog_tw->setRowHeight(i,50);
        QTableWidgetItem *item = catalog_tw->item(i, 0);
        item = new QTableWidgetItem;
        item->setText(StdString2QString(ret[i][0]));
        item->setTextAlignment(Qt::AlignCenter);
        catalog_tw->setItem(i, 0, item);
    }
    catalog_tw->show();


    QWidget *show_widget = new QWidget(win);
    show_widget->resize(600, 600);

    demo_example=new QTextEdit(show_widget);
    demo_example->resize(600, 600);
    demo_example->setText("hello world!");

    vbox_left->addWidget(search_content);
    vbox_left->addWidget(search_button);
    vbox_left->addWidget(stl_fopen);
    vbox_left->addWidget(quit);
    vbox_left->addWidget(catalog_tw);

    vbox_right->addWidget(show_widget);

    hbox_layout->addLayout(vbox_left, 2);
    hbox_layout->addLayout(vbox_right, 6);

    win->show();
    demo->show();
}


//重写退出事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox close_mb(QMessageBox::Warning, "","确定要退出？");
    //close_mb.setWindowTitle("你舍得离开吗");
    close_mb.setWindowFlag(Qt::FramelessWindowHint);
    close_mb.setAttribute(Qt::WA_ShowModal, true);

    close_mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    close_mb.setButtonText (QMessageBox::Ok,QString("确 定"));
    close_mb.setButtonText (QMessageBox::Cancel,QString("取 消"));
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
    QFile qss(application_dir_path + "/style/black.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::WhiteActionClicked()
{
    QFile qss(application_dir_path + "/style/white.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::DefaultActionClicked()
{
    QString applicationDirPath = QCoreApplication::applicationDirPath();
    qDebug()<< "applicationDirPath = " <<applicationDirPath;

    QString applicationFilePath = QCoreApplication::applicationFilePath();
    qDebug()<< "applicationFilePath = " <<applicationFilePath;

    QString currentPath = QDir::currentPath();  //方法一
    qDebug() << "currentPath = " << currentPath;

    char *current_path;     //方法二
    current_path = getcwd(nullptr, 0);
    if (current_path == nullptr) {
        qDebug("get current_path faild! err=%u, %s", errno, strerror(errno));
    }
    qDebug("current_path = %s", current_path);

    QFont font;
    font.setPointSize(20);
    font.setFamily(("Consolas"));
    this->setFont(font);
    this->update();
    this->repaint();



    QFile qss(application_dir_path + "/style/base.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::DocumentActionClicked()
{
    QMessageBox::information(this, tr("文档"),
                tr("用户可以输入始发地、目的地、选择出发类型与活动性质，点击搜索即可查看当前"
                   "行程的群组信息。选择有意愿的群组，点击“一起high”，即可加入。也可点击详情按钮，查看当前群组的人员信息。"
                   "如果当前没有该活动的群组，系统会提示您，是否发布行程。在没有具体地点或者其他打算时，用户也可以选择输入几"
                   "个条件中的一种或者几种，来查找相同行程的群组。\n关于此页面其他按钮说明：\n注销：点击后返回登录界面，用户"
                   "登录状态转换为非登录状态；\n资料：点击后显示用户当前个人资料，并且可以对资料进行修改；\n消息：点击后查看"
                   "站内消息；\n活动：可以查看已发布的活动和参加的活动，还可以看活动记录；\n换肤：根据自己风格，选择界面颜色；"
                   "\n帮助：包含软件使用文档及相关说明。"),
                QMessageBox::tr("确定"));
}

void MainWindow::AboutActionClicked()
{
    QMessageBox::information(this, tr("关于软件"),
                tr("该PC端APP，是一个同行者的信息搜索平台，旨在为喜欢游玩，但是身边同学朋友时间冲突，想找人结伴的年轻人提供"
                   "一个检索平台，让他们尽量能够快速便捷的寻找合适同行者。该APP有登录、注册、主页面（发布行程、搜索）、群组详"
                   "情、个人资料修改等功能。\n             版本·Bate版"),
                QMessageBox::tr("确定"));
}

void MainWindow::UpdateLogActionClicked()
{
    QMessageBox::information(this, tr("更新日志"),
                tr("1. 增加记住密码功能\n2. 皮肤优化\n3.修复参团人数BUG\n4. 增加发送信息检测用户\n5.修复搜索不到结果出现表格边框问题\n"
                   "6.增加密码找回\n7.能显示正在进行的活动\n8.发布日期增加了判断"),
                QMessageBox::tr("确定"));
}

