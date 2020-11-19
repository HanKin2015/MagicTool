#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <QString>
#include <QFont>
#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QString>
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
#include <QSignalMapper>
#include <QTranslator>
#include <QDir>
#include <QProcess>
#include <QToolBar>
#include <QToolButton>
#include <QMutex>

#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
#include <cstring>
#include <stdarg.h>
#include <direct.h>

#define LOGD qDebug()<<__FUNCTION__<<"["<<__LINE__<<"]"
#define LOGC qCritical()<<__FUNCTION__<<"["<<__LINE__<<"]"
#define LOGI qInfo()<<__FUNCTION__<<"["<<__LINE__<<"]"
#define LOGF qFatal()<<__FUNCTION__<<"["<<__LINE__<<"]"
#define LOGW qWarning()<<__FUNCTION__<<"["<<__LINE__<<"]"

using namespace std;

// 密码管理器 数据结构体
struct PasswordManagerStruct{
    string platform;
    string account;
    string password;
    string remarks;
};

// 账本 数据结构体
struct AccountBookStruct{
    string date;
    string weather;
    string type;
    string money;
    string mode;
    string note;
};

extern int const fontSize;
extern int const boldSize;


// specil
const QString CURRENT_DEMO_PATH = "D:/Github/MagicTool/src/";

// other
const QString ZH_CN_QM_FILE_NAME = "zh_CN.qm";
const int EXIT_CODE_REBOOT = -123456789;

// config
const QString CONFIG_DIR_PATH = "./config/";
const QString LANG_FILE_PATH = "./config/lang.ini";
const QString WHITE_SKIN_FILE_PATH = "./config/white.qss";
const QString BLACK_SKIN_FILE_PATH = "./config/black.qss";
const QString DEFAULT_SKIN_FILE_PATH = "./config/default.qss";

// image
const QString APP_LOGO_FILE_PATH = "./image/alienx64.png";
const QString AB_LOGO_FILE_PATH = "./image/accountbook64.png";
const QString PN_LOGO_FILE_PATH = "./image/perfectnote64.png";
const QString PM_LOGO_FILE_PATH = "./image/passwordmanager64.png";
const QString ADD_PNG_PATH = "./image/add.png";
const QString DELETE_PNG_PATH = "./image/delete.png";
const QString CHANGE_PNG_PATH = "./image/change.png";
const QString QUERY_PNG_PATH = "./image/query.png";
const QString FILE_PNG_PATH = "./image/file.png";
const QString FOLER_PNG_PATH = "./image/folder.png";
const QString ABOUT_PNG_PATH = "./image/about.png";
const QString DOCUMENT_PNG_PATH = "./image/document.png";

// log
const QString LOG_FILE_PATH = "./log/magictool.log";

// data
const QString AB_DATA_DIR_PATH = "./data/accountbook/";
const QString PN_DATA_DIR_PATH = "./data/perfectnote/";
const QString PM_DATA_DIR_PATH = "./data/passwordmanager/";
const QString PN_CATALOG_FILE_PATH = "./data/perfectnote/catalog.txt";
const QString AB_DATA_FILE_PATH = "./data/accountbook/data.txt";
const QString PM_DATA_FILE_PATH = "./data/passwordmanager/data.txt";


//日志收集回调函数
void MessageOutPut(QtMsgType type, const QMessageLogContext &context, const QString &msg);

string GetTableItemData(QTableWidget* table, int row, int column);
extern QFont GetFont();
extern QString GetStyle();
extern string QString2StdString(QString str);
extern QString StdString2QString(string str);
extern char* trim(char* str, const char* delimiter);
extern void SplitString(const string& s, vector<string>& v, const string& c);
extern void SplitStringByChar();
extern int WriteFile(const char *file_path, const char *write_type, PasswordManagerStruct PMS);
//密码器专用读取
extern vector<PasswordManagerStruct> ReadFile(const char *file_path);
//读取以逗号隔开的文件，返回不定长的数据
extern vector<vector<string> > ReadFileAll(const char *file_path);
#endif // GLOBALVARIABLE_H
