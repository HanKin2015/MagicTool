#ifndef PERFECTNOTE_H
#define PERFECTNOTE_H

#include <QDialog>
#include "globalvariable.h"

namespace Ui {
class PerfectNote;
}

class PerfectNote : public QDialog
{
    Q_OBJECT

public:
    explicit PerfectNote(QWidget *parent = nullptr);
    ~PerfectNote();

    QTextEdit *demo_example;      //show demo window
    QLineEdit *search_line_edit;  //search content

    void InitMainWindow();			//初始化主界面


private:
    Ui::PerfectNote *ui;

private slots:
    void StlFopenButtonClicked();
};

#endif // PERFECTNOTE_H
