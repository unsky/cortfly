
#ifndef PMWINDOW_H
#define PMWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QCloseEvent>
class TcpServer;

namespace Ui {
class PMWindow;
}

class PMWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PMWindow(QWidget *parent = 0);
    ~PMWindow();
    
private:
    Ui::PMWindow *ui;
    void closeEvent (QCloseEvent * event) ;
 TcpServer * ser;
public slots:
    void receivedPM(QString text);


signals:
    void enteredText(QString text);
    void closedWindow();

private slots:
    void on_btnSend_clicked();
    void on_txtInput_returnPressed();
    void on_toolButton_3_clicked();


    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_toolButton_4_clicked(bool checked);
    void on_toolButton_clicked(bool checked);

    void on_toolButton_2_clicked();
};

#endif // PMWINDOW_H
