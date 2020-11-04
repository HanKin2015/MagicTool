#include "globalvariable.h"

#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QTextCodec>
#include <QFile>
#include "libary/base64.h"
extern int const fontSize = 22;
extern int const boldSize = 60;

extern QFont GetFont()
{
    //中文支持
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    static QString font;
    int loadedFontID = QFontDatabase::addApplicationFont("./fonts/方正宋刻本秀楷简体.TTF");
    if (loadedFontID != -1)
    {
        QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
        if(!loadedFontFamilies.empty()) {
            font = loadedFontFamilies.at(0);
            //printf("%s\n",font.toStdString());
            QFont fontStyle(font, fontSize, boldSize);
            return fontStyle;
        }
    }
    return QFont();
}

extern QString GetStyle()
{
    QFile qssFile("styles/base.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss;
    qss = qssFile.readAll();
    qssFile.close();
    return qss;
}

extern string QString2StdString(QString str)
{
    std::string s = str.toStdString();
    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
    //std::string decoded = base64_decode(encoded);
    //return encoded;
    return s;
}

extern QString StdString2QString(string str)
{
    std::string decoded = base64_decode(str);
    //return QString::fromStdString(decoded);
    //return QString::fromLocal8Bit(str.c_str());
    return QString::fromStdString(str);
}


//巧妙：删除字符串的首尾多余的字符，如空格
//str为字符串，delimiter也可为字符串
//strchr函数：前参数为字符串，后参数为单个字符
extern char* trim(char* str, const char* delimiter)
{
    if (str == nullptr || str[0] == 0) {
        return str;
    }

    char* p1 = str;
    char* p2 = nullptr;
    int len;


    len = static_cast<int>(strlen(p1));
    p2 = p1 + len - 1;
    while (strchr(delimiter, *p1))
        p1++;
    if(p1>p2)
    {
        return nullptr;
    }
    if (*p1 == 0)
        return p1;


    while (strchr(delimiter, *p2))
        p2--;
    if(p2<str)
    {
        return nullptr;
    }
    *(p2+1) = 0;
    return p1;
}

/* can use string split
 * s string
 * v vector
 */
extern void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length()) v.push_back(s.substr(pos1));
}

// only one char split
extern void SplitStringByChar()
{
    char s[] = "a,b*c,d";
    const char *sep = ",*"; //可按多个字符来分割
    char *p;
    p = strtok(s, sep);
    while(p){
      printf("%s ", p);
      p = strtok(nullptr, sep);
    }
}

/*
ReadFile

records are separated by commas,such as:
baidu,hankin,112233,ok
mook,hj,12341234,study this everthing

*/
extern vector<RecordStruct> ReadFile(const char *file_path)
{
    qDebug("start read file = %s", file_path);

    // define varibale
    vector<RecordStruct> ret;
    RecordStruct tmp;
    vector<string> vec;
    const int buffer_size = 10000;
    char buffer[buffer_size + 1];
    char *current_path;
    FILE *fp = nullptr;

    // get current path
    current_path = getcwd(nullptr, 0);
    if (current_path == nullptr) {
        qDebug("get current_path faild! err=%u, %s", errno, strerror(errno));
        goto FAILED;
    }
    qDebug("current_path = %s", current_path);

    // open file
    fp = fopen(file_path, "r");
    if (fp == nullptr) {
        qDebug("fopen error! err=%u, %s", errno, strerror(errno));
         goto FAILED;
    }

    // read file
    while (fgets(buffer, buffer_size, fp) != nullptr) {
        //trim(buffer, "\n");
        SplitString(buffer, vec, ",");
        //qDebug() << QString::fromLocal8Bit(buffer);
        //qDebug("buffer = %s; size = %d", QString::fromLocal8Bit(buffer), vec.size());
        if (vec.size() != 4) {
            qDebug("vec size unequl 4");
            goto FAILED;
        }
        tmp.web_name = vec[0];
        tmp.user_name = vec[1];
        tmp.pwd = vec[2];
        char *ch = const_cast<char*>(vec[3].data());
        trim(ch, "\n");
        tmp.note = ch;

        ret.push_back(tmp);
        vec.clear();
    }

FAILED:
    if (fp != nullptr) {
        fclose(fp);
    }
    return ret;
}

extern vector<vector<string> > ReadFileAll(const char *file_path)
{
    qDebug("start read file = %s", file_path);

    // define varibale
    vector<vector<string> > ret;
    vector<string> vec;
    const int buffer_size = 10000;
    char buffer[buffer_size + 1];
    FILE *fp = nullptr;

    // open file
    fp = fopen(file_path, "r");
    if (fp == nullptr) {
        qDebug("fopen error! err=%u, %s", errno, strerror(errno));
         goto FAILED;
    }

    // read file
    while (fgets(buffer, buffer_size, fp) != nullptr) {
        trim(buffer, "\n");
        SplitString(buffer, vec, ",");
        ret.push_back(vec);
        vec.clear();
    }

FAILED:
    if (fp != nullptr) {
        fclose(fp);
    }
    return ret;
}

extern int WriteFile(const char *file_path, const char *write_type, RecordStruct rs)
{
    qDebug("start read file = %s", file_path);

    string tmp = "";
    FILE *fp = nullptr;

    fp = fopen(file_path, write_type);
    if (fp == nullptr) {
        qDebug("fopen error! err=%u, %s", errno, strerror(errno));
        return -1;
    }

    fprintf(fp, "%s,%s,%s,%s\n", rs.web_name.data(), rs.user_name.data(), rs.pwd.data(), rs.note.data());

    fclose(fp);
    return 0;
}
