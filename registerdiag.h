#ifndef REGISTERDIAG_H
#define REGISTERDIAG_H

#include <QDialog>

namespace Ui {
class registerdiag;
}

class registerdiag : public QDialog
{
    Q_OBJECT
public:
    explicit registerdiag(QWidget *parent = 0);
    ~registerdiag();
    bool judgeId();
    bool Judge=false;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_LineEdit_pass_cursorPositionChanged(int arg1, int arg2);

    void on_LineEdit_Pass2_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::registerdiag *ui;
};

#endif // REGISTERDIAG_H
