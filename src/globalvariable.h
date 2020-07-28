#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <QString>
#include <QFont>
#include <QDebug>

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
using namespace std;

struct RecordStruct{
    string web_name;
    string user_name;
    string pwd;
    string note;
};

struct AccountBookStruct{
    string date;
    string weather;
    string type;
    string money;
    string mode;
    string note;
};

extern int const fontSize ;
extern int const boldSize ;


extern QFont GetFont();
extern QString GetStyle();
extern string QString2StdString(QString str);
extern QString StdString2QString(string str);
extern char* trim(char* str, const char* delimiter);
extern void SplitString(const string& s, vector<string>& v, const string& c);
extern void SplitStringByChar();
extern int WriteFile(const char *file_path, const char *write_type, RecordStruct rs);
//密码器专用读取
extern vector<RecordStruct> ReadFile(const char *file_path);
//读取以逗号隔开的文件，返回不定长的数据
extern vector<vector<string> > ReadFileAll(const char *file_path);
#endif // GLOBALVARIABLE_H
