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








