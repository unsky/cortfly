#include "dialognickname.h"
#include "ui_dialognickname.h"
#include<QFileDialog>


DialogNickName::DialogNickName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNickName)
{
    ui->setupUi(this);
}

DialogNickName::~DialogNickName()
{
    delete ui;
}

void DialogNickName::on_btnOk_clicked()
{  if(!ui->txtName->text().isEmpty())
    {
    emit setName(ui->txtName->text());
    this->deleteLater();
}}


void DialogNickName::on_touxiangButton_clicked()
{QString fileName = QFileDialog::getOpenFileName(this,
                                                 "open iamge",
                                                  ".", "image files(*.jpg *.png *.bmp)");
    if (!fileName.isEmpty())
    {
            ui->touxiangButton->setIcon(QIcon(fileName));
             emit setImage(fileName);
}

}
