#pragma execution_character_set("utf-8")
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QMainWindow>
#include <QLineEdit>
#include "peer.h"
#include "dialognickname.h"
#include "messenger.h"
#include "pmwindow.h"
#include "roomwindow.h"
#include "dialogroom.h"
#include "dialogabout.h"
#include<QTcpServer>

namespace Ui {
class MainWindow;
class TcpSerever;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


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
protected:
    void hasPendingFile(QString name);
signals:
    //void target(QString);
    void sendtarget(QString userid);

private:
    Ui::MainWindow *ui;
    Messenger* msgr;
    QMap<QString, PMWindow*> pms;
    QMap<PMWindow*, QString> pmr;
    QMap<QString, RoomWindow*> rms;
    PMWindow* makePMWindow(QString title);
    QString fileName;

};

#endif // MAINWINDOW_H
