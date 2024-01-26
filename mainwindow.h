#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <vector>
#include <iostream>
#include <QtWidgets>
#include <QtGui>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool tryToSolve(std::vector<std::vector<int>>& grid, int row, int col);
    bool isSafe(std::vector<std::vector<int>>& grid, int row, int col, int num);
    void FillUI();

public slots:
    void onTextEditTextChanged(QTextEdit *textEdit, int index); // Declare your slot here
    void onSubmitButtonClicked();
    void onResetButtonClicked();
    void testSolvableSudoku();


private:
    Ui::MainWindow *ui;
    bool isSlotRunning;
    std::vector<QTextEdit*> numbers; // Declare a vector of pointers
    int test;
    int tryToSolveCount = 0;
    int isSafeCount = 0;

    // Create a 3x3 grid, where each cell contains a 3x3 grid
    //std::vector<std::vector<std::vector<int>>> grid;          //PREVIOUSLY USED
    std::vector<std::vector<int>> grid;
};
#endif // MAINWINDOW_H
