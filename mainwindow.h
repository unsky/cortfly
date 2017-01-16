#pragma execution_character_set("utf-8")
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QMainWindow>
#include <QLineEdit>
#include "peer.h"
//#include"tcpserver.h"
#include "dialognickname.h"
#include "messenger.h"
#include "pmwindow.h"
#include "roomwindow.h"
#include "dialogroom.h"
#include "dialogabout.h"
#include "tcpserver.h"
#include<QMenu>
#include <QSystemTrayIcon>
//#include<QTcpServer>

class TcpServer;
namespace Ui {
class MainWindow;
//;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    QSystemTrayIcon *tray;//托盘图标
    QMenu *menu;
    QAction *reset;
    QAction *quit;
    QAction *lab;
    QAction *servercon;


private slots:
    void onSetName(QString name);
    void onUpdateList();
    void onPMSend(QString text);
    void onPMClosed();
    void on_listUsers_doubleClicked(const QModelIndex &index);
    void onReceivedPM(QString from, QString text);
    void on_nichnameButton_clicked();
    void onsetimage(QString filename);
    void getFileName(QString name);
    void on_pushButton_clicked();
    void ref();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

protected:
    void hasPendingFile(QString name);
signals:
    void reject();
    void sendtarget(QString userid);

private:
    Ui::MainWindow *ui;
    Messenger* msgr;
    QMap<QString, PMWindow*> pms;
    QMap<PMWindow*, QString> pmr;
    //QMap<QString, RoomWindow*> rms;
    PMWindow* makePMWindow(QString title);
    QString fileName;
    TcpServer *ser;
public slots:
    void TrayIconAction(QSystemTrayIcon::ActivationReason reason);


};

#endif // MAINWINDOW_H
