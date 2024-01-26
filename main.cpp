#include "mainwindow.h"
#include <iostream>

#include <QApplication>

//FRICK SUDOKU

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    QSize windowSize(800, 600); // Adjust the width and height as needed
    window.setGeometry(QRect(300, 100, windowSize.width(), windowSize.height()));
    window.show();

    return a.exec();
}
