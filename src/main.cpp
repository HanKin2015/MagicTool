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
    QApplication app(argc, argv);

    QFont font = app.font();
    font.setPixelSize(14);
    //app.setFont(font);



    MainWindow w;
    w.show();
    return app.exec();
}
