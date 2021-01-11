#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

#define LOG 1

// transfor utf8
void ChangeTextCodec()
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);
}

int main(int argc, char *argv[])
{
#if LOG
    // 日志收集回调函数
    qInstallMessageHandler(MessageOutPut);
#endif

    LOGI << QString("===== begin =====");

    int exit_code = 0;
    do {
        QApplication app(argc, argv);

        // 当前代码路径，QT相对路径是相对于QtCreator的build路径，可以在项目中设置。推荐在代码中修改当前的相对路径。
        QDir::setCurrent(CURRENT_DEMO_PATH);
        LOGI << QString("current demo path = %1").arg(QDir::currentPath());

        // 字体设置
        QFont font = app.font();
        font.setPixelSize(14);
        //app.setFont(font);

        // 中英文设置
        QTranslator translator;
        vector<char*> data;
        ReadFile(LANG_FILE_PATH.toStdString().data(), data);
        if (data.size() == 1) {
            if (strncmp(data[0], "1", 1) == 0) {
                translator.load(ZH_CN_QM_FILE_NAME, CONFIG_DIR_PATH);
                qDebug("load zh_cn.qm file success!\n");
            } else {
                //translator.load();
                qDebug("change english layout!\n");
            }
            app.installTranslator(&translator);
        }

        MainWindow w;
        w.show();

        exit_code = app.exec();
    } while(exit_code == EXIT_CODE_REBOOT);

    LOGI << QString("===== end =====");
    return exit_code;
}
