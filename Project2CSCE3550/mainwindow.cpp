#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QFile file("test.txt");

    QVector <QVector <QString> > myVector;
    QVector <QString> vect;

    //int line = 0;

    QString username = ui -> lineEdit_username -> text();
    QString password = ui -> lineEdit_password -> text();

    QString text;

    int i = 0;
    int size = 0;

    bool valid = false;

    if (!file.exists())
    {
        qDebug() << file.fileName() << " does not exist";
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream txtStream(&file);

        qDebug() << "Reading from file";

        txtStream.seek(0);

        while (!txtStream.atEnd())
        {

            text = txtStream.readLine();

            qDebug() << text;

            QStringList split = text.split(",");

            //qDebug() << split;

            vect.push_back(split.at(0));
            vect.push_back(split.at(1));
            vect.push_back(split.at(2));
            //qDebug() << vect;

            myVector.push_back(vect);
            qDebug() << myVector;
            vect.clear();
            size++;
        }

        file.close();
    }

    for (i = 0; i < size; i++)
    {
        if (username == myVector[i][0] && password == myVector[i][1])
        {
            valid = true;
            break;
        }
        else
        {
            valid = false;
        }
    }

    if (valid == true)
    {
        QMessageBox::information(this, "Login", "Username and Password is correct");
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username and Password is not correct");
    }

}


void MainWindow::on_pushButton_register_clicked()
{
    QFile file("test.txt");

    QString newUsername = ui -> lineEdit_newUsername -> text();
    QString newPhone = ui -> lineEdit_newPhone -> text();
    QString newPassword = ui -> lineEdit_newPassword -> text();

    if (!file.exists())
    {
        qDebug() << file.fileName() << " does not exist";
    }

    if (file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream txtStream(&file);

        qDebug() << "Writing to file";

        txtStream << newUsername << "," << newPassword << "," << newPhone << "\n";

        QMessageBox::information(this, "Register", "Registration Successful");

        file.close();
    }
    else
    {
        qDebug() << "Could not open file";
        return;
    }

}

