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

private:
    Ui::PerfectNote *ui;
};

#endif // PERFECTNOTE_H
