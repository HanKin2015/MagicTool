#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <QString>
#include <QFont>

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

extern int const fontSize ;
extern int const boldSize ;
extern QString const fontName;
extern QString startLocate;
extern QString endLocate;
extern QString startDate;
extern QString hiType;
extern QString userNameGlobal;
extern int eventIDGlobal;

extern QString startGlobal;
extern QString endGlobal;

extern QFont GetFont();
extern QString GetStyle();
extern string QString2StdString(QString str);
extern QString StdString2QString(string str);
extern char* trim(char* str, const char* delimiter);
extern void SplitString(const string& s, vector<string>& v, const string& c);
extern void SplitStringByChar();
extern int WriteFile(const char *file_path);
extern vector<RecordStruct> ReadFile(const char *file_path);
#endif // GLOBALVARIABLE_H
