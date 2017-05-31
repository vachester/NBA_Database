#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("Main Window"));

    this->resize(1200,600);
    QFont font("Source Code Pro",15);

    dbconn = QSqlDatabase::addDatabase("QMYSQL");
    dbconn.setHostName("localhost");
    dbconn.setDatabaseName("NBA_DATABASE");
    dbconn.open("root","951118");
    query = (QSqlQuery)dbconn;

    /*****************添加操作*******************/
    for(qint32 i = 0; i < 7; i++) {
        edit[i] = new QLineEdit(this);
        edit[i]->setGeometry(QRect(QPoint(50+130*i,50), QSize(120,50)));
    }

    edit[0]->setPlaceholderText("PSSN");
    edit[1]->setPlaceholderText("PName");
    edit[2]->setPlaceholderText("Birth");
    edit[3]->setPlaceholderText("Possition");
    edit[4]->setPlaceholderText("PNumber");
    edit[5]->setPlaceholderText("EnterTime");
    edit[6]->setPlaceholderText("TName");

    btn = new QPushButton("添加",this);

    btn->setGeometry(QRect(QPoint(980,50), QSize(120,50)));


    btn->setFont(font);
    for(qint32 i = 0; i < 7; i++) {
        edit[i]->setFont(font);
    }

    /*****************删除操作*******************/
    del_edit = new QLineEdit(this);
    del_edit->setGeometry(QRect(QPoint(50,120), QSize(150,50)));
    del_edit->setPlaceholderText("勒布朗-詹姆斯");
    del_edit->setFont(font);

    del_btn = new QPushButton("删除", this);
    del_btn->setGeometry(QRect(QPoint(250,120), QSize(120,50)));
    del_btn->setFont(font);

    /*****************查询操作*******************/
    for(qint32 i = 0; i < 3; i++) {
        conn_edit[i] = new QLineEdit(this);
        conn_edit[i]->setGeometry(QRect(QPoint(50+130*i,190), QSize(120,50)));
        conn_edit[i]->setFont(font);
    }

    conn_edit[0]->setPlaceholderText("PName");
    conn_edit[1]->setPlaceholderText("Player");
    conn_edit[2]->setPlaceholderText("Award");
    conn_btn = new QPushButton("连接查询", this);
    conn_btn->setGeometry(QRect(QPoint(500,190), QSize(120,50)));
    conn_btn->setFont(font);


    nest_edit[0] = new QLineEdit(this);
    nest_edit[0]->setGeometry(QRect(QPoint(50,260), QSize(120,50)));
    nest_edit[0]->setFont(font);
    nest_edit[0]->setPlaceholderText("MVP");
    nest_edit[1] = new QLineEdit(this);
    nest_edit[1]->setGeometry(QRect(QPoint(180,260), QSize(120,50)));
    nest_edit[1]->setFont(font);
    nest_edit[1]->setPlaceholderText("雷霆队");
    nest_btn = new QPushButton("嵌套查询", this);
    nest_btn->setGeometry(QRect(QPoint(330,260), QSize(120,50)));
    nest_btn->setFont(font);


    group_edit = new QLineEdit(this);
    group_edit->setGeometry(QRect(QPoint(50,330), QSize(120,50)));
    group_edit->setFont(font);
    group_edit->setPlaceholderText("30");
    group_btn = new QPushButton("分组查询", this);
    group_btn->setGeometry(QRect(QPoint(200,330), QSize(120,50)));
    group_btn->setFont(font);


    show_label = new QLabel("结果如下：",this);
    show_label->setGeometry(QRect(QPoint(700,250), QSize(100,50)));
    show_label->setFont(font);
    label = new QTextEdit(this);
    label->setGeometry(QRect(QPoint(700,300), QSize(400,200)));
    label->setFont(font);


    /*添加*/
    connect(btn,SIGNAL(clicked()),this,SLOT(insert_player()));
    connect(this,SIGNAL(getInsertResult(QString)),label,SLOT(setText(QString)));

    /*删除*/
    connect(del_btn,SIGNAL(clicked()),this,SLOT(delete_player()));
    connect(this,SIGNAL(getDeleteResult(QString)),label,SLOT(setText(QString)));

    /*连接查询*/
    connect(conn_btn,SIGNAL(clicked()),this,SLOT(conn_query()));
    connect(this,SIGNAL(getConnResult(QString)),label,SLOT(setText(QString)));

    /*嵌套查询*/
    connect(nest_btn,SIGNAL(clicked()),this,SLOT(nest_query()));
    connect(this,SIGNAL(getNestResult(QString)),label,SLOT(setText(QString)));

    /*分组查询*/
    connect(group_btn,SIGNAL(clicked()),this,SLOT(group_query()));
    connect(this,SIGNAL(getGroupResult(QString)),label,SLOT(setText(QString)));

}

MainWindow::~MainWindow()
{
}

void MainWindow::insert_player() {
    query.exec("insert into Player (PSSN, PName, Birth, Possition, PNumber, EnterTime, TName) values (?,?,?,?,?,?,?)");

    QString getEdit;
    bool flag = false;
    for(int i = 0;i < 7; i++) {
        getEdit = edit[i]->text();
        if(i != 2 && i != 5) {
            if(getEdit == "")
                flag = true;
        }
        query.addBindValue(getEdit);
    }

    if(!(query.exec())) {
        if(flag)
            emit getInsertResult("存在空值!");
        else
            emit getInsertResult("重复的数据!");
        return;
    }

    query.finish();

    emit getInsertResult("添加成功");
}

void MainWindow::delete_player() {
    query.exec("select * from Player where PName = ?");

    QString getEdit;
    getEdit = del_edit->text();
    query.addBindValue(getEdit);
    query.exec();
    if(!query.next()) {
        emit getDeleteResult("不存在这样的数据");
        return;
    }

    query.finish();
    query.exec("delete from Player where PName = ?");
    query.addBindValue(getEdit);
    query.exec();

    query.finish();

    emit getDeleteResult("成功删除!");
}

void MainWindow::conn_query() {
    QString query_str = "select ";
    query_str += conn_edit[0]->text() + " from ";
    query_str += conn_edit[1]->text() + " natural join " + conn_edit[2]->text();

    query.exec(query_str);

    QString result = "";
    while (query.next()) {
        result += query.value(0).toString() + "\n";
    }

    query.finish();

    if(result == "") {
        emit getConnResult("结果为空！");
        return;
    }

    emit getConnResult(result);
}

void MainWindow::nest_query() {
    query.exec("select PName from Player join ( select PSSN from Award where AName = ? ) as TEMP using(PSSN) where TName = ?");

    QString getEdit;
    for(int i = 0;i < 2; i++) {
        getEdit = nest_edit[i]->text();
        query.addBindValue(getEdit);
    }

    query.exec();

    QString result = "";
    while (query.next()) {
        result += query.value(0).toString() + "\n";
    }

    query.finish();

    if(result == "") {
        emit getNestResult("结果为空！");
        return;
    }

    emit getNestResult(result);
}

void MainWindow::group_query() {
    QString query_str = "select PName from showAvg where avg_point > ";
    query_str += group_edit->text();

    query.exec(query_str);

    QString result = "";
    while (query.next()) {
        result += query.value(0).toString() + "\n";
    }

    query.finish();

    if(result == "") {
        emit getGroupResult("结果为空！");
        return;
    }

    emit getGroupResult(result);
}
