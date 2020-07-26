#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <QDir>
#include <QMessageBox>
#include <algorithm>
#include <iterator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tree23 = new Tree23();

    updateDotFile();
    updateImage();
    renderImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDotFile()
{
    std::ofstream myFile;
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    myFile.open
    (
        "file.dot"
    );

    std::string textToFile = tree23->getDotFileContent();

    myFile << textToFile;
    myFile.close();
}

void MainWindow::updateImage()
{
    std::string message =
                "dot -Tpng file.dot > file.png";
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    system(message.c_str());
}

void MainWindow::renderImage()
{
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    QPixmap image("file.png");
    ui->labelOfImage->setPixmap(image);
    ui->labelOfImage->show();
}

template <class Container>
void MainWindow::split3(const std::string& str, Container& cont,
              char delim)
{
    std::size_t current, previous = 0;
    current = str.find(delim);
    while (current != std::string::npos)
    {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find(delim, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
}

void MainWindow::on_pushButtonOfInsertion_clicked()
{
    std::vector<std::string> numbersAsString;
    std::string numbers = ui->lineEditOfInsert->text().toStdString();
    split3(numbers, numbersAsString);

    bool ret;
    for (auto numberAsStr: numbersAsString)
    {
        int number = std::atoi(numberAsStr.c_str());
        ret = tree23->insert(number);

        QMessageBox msgBox;
        if (ret)
            msgBox.setText("The number "+QString::number(number)+" was inserted");
        else
            msgBox.setText("Already exists a node with this data");
        msgBox.exec();
    }

    updateDotFile();
    updateImage();
    renderImage();
}

void MainWindow::on_pushButtonOfSearch_clicked()
{
    int number = ui->lineEditOfSearch->text().toInt();
    int ret = tree23->search(number) != nullptr;

    QMessageBox msgBox;
    if (ret)
        msgBox.setText("This number exists in the tree");
    else
        msgBox.setText("This number does not exists in the tree");
    msgBox.exec();
}

void MainWindow::on_pushButtonOfRemove_clicked()
{
    int number = ui->lineEditOfRemove->text().toInt();
    tree23->remove(number);

    updateDotFile();
    updateImage();
    renderImage();
}
