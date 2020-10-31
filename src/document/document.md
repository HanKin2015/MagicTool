# 设计与规划

# 20201023
- 重构项目结构后，规范代码，运行无bug
- 检查缺少什么并给出下一步设计
- 英文切换先放一边
- 文件加密先放一边

## 1、编译运行提示No rule to make target 'xxx' needed by 'xxx'
修改pro文件，查看SOURCES和HEADERS地方是否加载文件地址正确。

## 2、程序关闭框未在主界面居中

## 3、中英文切换迫在眉睫
使用重启软件机制，重新加载qm文件。
下面这种方式不可取，仅仅是重启了一下软件。
```
#include <QApplication>
#include <QDir>
#include <QProcess>
void MainWindow::reboot()
{
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QApplication::exit();
}
```

使用自定义的退出码方法，结果一直报undefined reference to `MainWindow::EXIT_CODE_REBOOT'错误。
原因：只在h文件中声明，却在cpp函数中定义，从而未找到变量的定义，需要在全局中定义。

已解决中英文切换问题（20201028）

# 20201028
## 1、解决全局变量问题
类中的变量给外部调用使用static？
static变量不能直接初始化？
static变量初始化需要指定类型和域空间？

## 2、相对路径问题
```
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

    currentPath = QDir::homePath();
    qDebug() << "home_path = " << currentPath;
    currentPath = QDir::tempPath();
    qDebug() << "temp_path = " << currentPath;
```

已解决。

## 3、翻译问题，部分词语未翻译
对已有词语进行翻译。

## 消除警告

## 增加日志

## 增加在线更新

## 解决lupdate: File ... won't be updated: it contains translation but the target language is not recognized
```
OK looks like the new lupdate version needs additional info about the file's language so I had to add something like this:
<TS version="2.1" language="cs_CZ">
Works now!
```

已解决。

## 分离出完美笔记为单独的文件

## 首页设计成图片幻灯片












