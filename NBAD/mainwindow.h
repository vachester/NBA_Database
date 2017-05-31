#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QtSql>
#include <QTextEdit>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton * btn;
    QPushButton * del_btn;
    QPushButton * conn_btn;
    QPushButton * nest_btn;
    QPushButton * group_btn;

    QLineEdit * edit[7];
    QLineEdit * del_edit;
    QLineEdit * conn_edit[3];
    QLineEdit * nest_edit[2];
    QLineEdit * group_edit;

    QLabel * show_label;
    QTextEdit * label;

    QSqlDatabase dbconn;
    QSqlQuery query;

public slots:
    void insert_player();
    void delete_player();
    void conn_query();
    void nest_query();
    void group_query();

signals:
    void getInsertResult(QString);
    void getDeleteResult(QString);
    void getConnResult(QString);
    void getNestResult(QString);
    void getGroupResult(QString);
};

#endif // MAINWINDOW_H
