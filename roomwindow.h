#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QDialog>

namespace Ui {
class roomwindow;
}

class roomwindow : public QDialog
{
    Q_OBJECT

public:
    explicit roomwindow(QWidget *parent = 0);
    ~roomwindow();

private:
    Ui::roomwindow *ui;
};

#endif // ROOMWINDOW_H
