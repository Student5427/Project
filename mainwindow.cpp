#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{  //"Обнулить" строку с путём файла
   filepath = "";
   //Очистить текст
   ui->textEdit->setText("");
   //Оповестить пользователя
   ui->statusbar->showMessage("New file");
}

void MainWindow::on_actionOpen_triggered()
{
 //Получаем имя открываемого файла
 QString filename = QFileDialog::getOpenFileName(this, "Open the file");
 //Объявляем файл
 QFile file(filename);
 //Фиксируем путь файла
 filepath = filename;
 //Удалось открыть файл?
 if(!file.open(QFile::ReadOnly | QFile::Text)) {
     //Вывести сообщение об ошибке
     QMessageBox::warning(this,"..","file not open");
     //Вернуть управление пользователю
     return;
 }
 //Выводим текст файла
 QTextStream in(&file);
 QString text = in.readAll();
 ui->textEdit->setText(text);
 //Не забываем закрыть файл
 file.close();
 //Выводим имя открытого файла
 ui->statusbar->showMessage(filepath);

}

void MainWindow::on_actionSave_triggered()
{
    QFile file(filepath);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    //Записываем текст в файл
    file.flush();
    //Не забываем закрыть файл
    file.close();
    ui->statusbar->showMessage("File is saved");
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save the file:");
    QFile file(filename);
    filepath = filename;
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
    ui->statusbar->showMessage("File is saved");
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionAbout_Notepad_triggered()
{

    QString about_text;
    about_text = "Author : Andry Koposov 22106\n";
    about_text += "Date : 25/06/2021\n";
    about_text += "(C) Notepad (R)";
 QMessageBox::about(this,"About Notepad", about_text);
}
