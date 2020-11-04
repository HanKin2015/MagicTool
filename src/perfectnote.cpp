#include "perfectnote.h"
#include "ui_perfectnote.h"

PerfectNote::PerfectNote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PerfectNote)
{
    ui->setupUi(this);

    // 初始化主窗口
    InitMainWindow();
}

void PerfectNote::InitMainWindow()
{
    this->resize(1200, 800);
    this->setWindowIcon(QIcon(PN_LOGO_FILE_PATH));
    this->setWindowTitle(tr("perfect note"));

    QWidget *win=new QWidget(this);

    win->resize(1200, 800);

    QHBoxLayout *hbox_layout=new QHBoxLayout(win);//水平布局管理器（父管理器）；
    QVBoxLayout *vbox_left =new QVBoxLayout;//垂直布局管理器（子管理器）；
    QVBoxLayout *vbox_right=new QVBoxLayout;

    //设定每个布局管理器中的部件间间隔
    hbox_layout->setSpacing(50);
    vbox_left->setSpacing(25);
    vbox_right->setSpacing(25);

    //搜索框
    search_line_edit = new QLineEdit(win);
    QPushButton *search_button = new QPushButton(tr("search"), win);
    connect(search_button, &QPushButton::clicked, this, &PerfectNote::StlFopenButtonClicked);

    QPushButton *stl_fopen = new QPushButton(win);
    stl_fopen->setText(tr("read file"));
    QObject::connect(stl_fopen, &QPushButton::clicked, this, &PerfectNote::StlFopenButtonClicked);

    QPushButton *quit=new QPushButton(win);
    quit->setText(tr("exit"));
    QObject::connect(quit,SIGNAL(clicked()),win,SLOT(close()));

    QTableWidget *catalog_tw = new QTableWidget(win);
    catalog_tw->setColumnCount(1);
    catalog_tw->setColumnWidth(0, 150);
    catalog_tw->setHorizontalHeaderLabels((QStringList() << tr("catalog")));
    vector<vector<string> > ret = ReadFileAll(PN_CATALOG_FILE_PATH.toLatin1().data());
    int catalog_cnt = static_cast<int>(ret.size());
    catalog_tw->setRowCount(catalog_cnt);
    for (int i = 0; i < catalog_cnt; i++) {
        //catalog_tw->setRowHeight(i,50);
        QTableWidgetItem *item = catalog_tw->item(i, 0);
        item = new QTableWidgetItem;
        item->setText(StdString2QString(ret[static_cast<size_t>(i)][0]));
        item->setTextAlignment(Qt::AlignCenter);
        catalog_tw->setItem(i, 0, item);
    }
    catalog_tw->show();


    QWidget *show_widget = new QWidget(win);
    show_widget->resize(1000, 800);

    demo_example=new QTextEdit(show_widget);
    demo_example->resize(1000, 800);
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    font.setFamily("Consolas");
    demo_example->setFont(font);
    demo_example->setText("hello world!");

    vbox_left->addWidget(search_line_edit);
    vbox_left->addWidget(search_button);
    vbox_left->addWidget(stl_fopen);
    vbox_left->addWidget(quit);
    vbox_left->addWidget(catalog_tw);

    vbox_right->addWidget(show_widget);

    hbox_layout->addLayout(vbox_left, 2);
    hbox_layout->addLayout(vbox_right, 10);

    win->show();
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

void PerfectNote::StlFopenButtonClicked()
{
    char *current_path;
    current_path = getcwd(nullptr, 0);
    if (current_path == nullptr) {
        qDebug("get current_path faild! err=%u, %s", errno, strerror(errno));
        return;
    }

    QString tmp = search_line_edit->text();
    QString file_path = QString(PN_DATA_DIR_PATH + "%1.txt").arg(tmp);

    QString demo = read_csv(file_path.toLatin1().data());
    demo_example->setText(demo);
}

PerfectNote::~PerfectNote()
{
    delete ui;
}
