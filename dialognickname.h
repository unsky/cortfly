#pragma execution_character_set("utf-8")
#ifndef DIALOGNICKNAME_H
#define DIALOGNICKNAME_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogNickName;
}

class DialogNickName : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNickName(QWidget *parent = 0);
    ~DialogNickName();
    
private slots:
    void on_btnOk_clicked();


    void on_touxiangButton_clicked();

signals:
    void setName(QString name);
    void setImage(QString image);

private:
    Ui::DialogNickName *ui;
};

#endif // DIALOGNICKNAME_H
