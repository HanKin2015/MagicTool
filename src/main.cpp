#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

//transfor utf8
void ChangeTextCodec()
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);
}

int main(int argc, char *argv[])
{
    int exit_code = 0;

    do {
        QApplication app(argc, argv);

        QFont font = app.font();
        font.setPixelSize(14);
        //app.setFont(font);

        QTranslator translator;
        vector<char*> data;
        ReadFile(MainWindow::LANG_FILE_PATH.toStdString().data(), data);
        if (data.size() == 1) {
            if (strncmp(data[0], "1", 1) == 0) {
                translator.load("zh_CN.qm", "D:\\Users\\Administrator\\My Document\\MagicTool\\config\\");
            } else {
                //translator.load();
            }
            app.installTranslator(&translator);
        }

        MainWindow w;
        w.show();

        exit_code = app.exec();
    } while(exit_code == MainWindow::EXIT_CODE_REBOOT);

    return exit_code;
}
