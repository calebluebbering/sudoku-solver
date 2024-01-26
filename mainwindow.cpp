#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <iostream>
#include <QTextEdit>
#include <vector>
#include <QString>
#include <iostream>
#include <QPushButton>
#include <QKeyEvent>





//MAIN CONSTRUCTOR
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //resize();

    isSlotRunning = false;
    test = 0;

    //Not the most ideal lolllll
    numbers = {ui->n1, ui->n2, ui->n3, ui->n4, ui->n5, ui->n6, ui->n7, ui->n8, ui->n9,
               ui->n10, ui->n11, ui->n12, ui->n13, ui->n14, ui->n15, ui->n16, ui->n17, ui->n18,
               ui->n19, ui->n20, ui->n21, ui->n22, ui->n23, ui->n24, ui->n25, ui->n26, ui->n27,
               ui->n28, ui->n29, ui->n30, ui->n31, ui->n32, ui->n33, ui->n34, ui->n35, ui->n36,
               ui->n37, ui->n38, ui->n39, ui->n40, ui->n41, ui->n42, ui->n43, ui->n44, ui->n45,
               ui->n46, ui->n47, ui->n48, ui->n49, ui->n50, ui->n51, ui->n52, ui->n53, ui->n54,
               ui->n55, ui->n56, ui->n57, ui->n58, ui->n59, ui->n60, ui->n61, ui->n62, ui->n63,
               ui->n64, ui->n65, ui->n66, ui->n67, ui->n68, ui->n69, ui->n70, ui->n71, ui->n72,
               ui->n73, ui->n74, ui->n75, ui->n76, ui->n77, ui->n78, ui->n79, ui->n80, ui->n81};

    for (int i = 0; i < numbers.size(); i++) {
        numbers[i]->setStyleSheet("background-color: white; color: black; font-size: 20pt;");
        connect(numbers[i], &QTextEdit::textChanged, this, [this, i]() { onTextEditTextChanged(numbers[i], i); });
    }

    ui->submitButton->setStyleSheet("color: black;");
    ui->resetButton->setStyleSheet("color: black;");

    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::onSubmitButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);

    grid = std::vector<std::vector<int>>(9, std::vector<int>(9));



}
//DECONSTRUCTOR
MainWindow::~MainWindow()
{
    delete ui;
}







//INPUT ONLY 1-9
void MainWindow::onTextEditTextChanged(QTextEdit *numberTextEdit, int index)
{
    // Check if the slot is already running to avoid infinite loop
    if (isSlotRunning) {
        return;
    }

    isSlotRunning = true;

    QString text = numberTextEdit->toPlainText();
    bool isNumber = false;

    // Use a regular expression to check if the text is a number between 1 and 9
    static QRegularExpression numberRegex("^[1-9]$");

    if (numberRegex.match(text).hasMatch()) {
        isNumber = true;
    } else {
        // Text is not a number between 1 and 9, so reset it to an empty string
        numberTextEdit->setPlainText("");
    }

    numberTextEdit->setAlignment(Qt::AlignCenter);

    isSlotRunning = false;

    if (isNumber) {
        // Handle the case when the text is a valid number
        // You can perform other actions or validation here
    }
}






void MainWindow::onSubmitButtonClicked() {
    int index = 0;
    isSafeCount = 0;

    //DELETE AFTER TESTING
    //testSolvableSudoku();

    //FILL GRID WITH textEdit numbers
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            QString text = numbers[index]->toPlainText();
            int value = text.toInt();
            grid[i][j] = value;
            index++;
        }
    }

    //GRID IS SOLVED
    if (tryToSolve(grid, 0, 0)) {
        qDebug() << isSafeCount;
        FillUI();

        /*
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cout << grid[i][j];
            }
            std::cout << std::endl;
        }
*/
    }
    //GRID CANNOT BE SOLVED
    else {
        qDebug() << "Cannot be solved: " << isSafeCount;
        ui->textDisplay->setStyleSheet("color: black");
    }
}






bool MainWindow::tryToSolve(std::vector<std::vector<int>>& grid, int row, int col) {
    if (isSafeCount > 9999999)
        return false;
    //qDebug() << "tryToSolve";
    // Check if we have reached the last cell of the grid.
    if (row == 9) {
        return true;  // We've successfully filled all cells.
    }

    // Move to the next row and reset the column to 0 when reaching the end of a row.
    if (col == 9) {
        return tryToSolve(grid, row + 1, 0);
    }

    // Check if the current cell is already filled.
    if (grid[row][col] > 0) {
        return tryToSolve(grid, row, col + 1);
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // Assign the number to the current cell.
            grid[row][col] = num;

            // Move to the next column.
            if (tryToSolve(grid, row, col + 1)) {
                return true;
            }

            // If the current assignment doesn't lead to a solution, reset the cell.
            grid[row][col] = 0;
        }
    }

    // No valid number can be placed in this cell. Mark the puzzle as unsolvable.
    return false;
}






bool MainWindow::isSafe(std::vector<std::vector<int>>& grid, int row, int col, int num) {
    isSafeCount++;
    // Check if find the same num
    // in the similar row ,
    // return false
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return false;

    // Check if find the same num in
    // the similar column ,
    // return false
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return false;

    // Check if find the same num in
    // the particular 3*3 matrix,
    // return false
    int startRow = row - row % 3,
        startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j +
                                   startCol] == num)
                return false;

    return true;
}








void MainWindow::FillUI() {
    int index = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            QString val = QString::number(grid[i][j]);
            numbers[index]->setPlainText(val);
            index++;
        }
    }

}








void MainWindow::onResetButtonClicked() {
    for (int i = 0; i < numbers.size(); i++)
        numbers[i]->setPlainText("");
    ui->textDisplay->setStyleSheet("color: white;");
}

//just for testing:)
void MainWindow::testSolvableSudoku() {
    numbers[1]->setPlainText("7");
    numbers[2]->setPlainText("8");
    numbers[8]->setPlainText("1");
    numbers[11]->setPlainText("2");
    numbers[12]->setPlainText("1");
    numbers[15]->setPlainText("6");
    numbers[17]->setPlainText("4");
    numbers[21]->setPlainText("6");
    numbers[25]->setPlainText("8");
    numbers[28]->setPlainText("5");
    numbers[36]->setPlainText("7");
    numbers[38]->setPlainText("4");
    numbers[39]->setPlainText("3");
    numbers[44]->setPlainText("8");
    numbers[52]->setPlainText("9");
    numbers[53]->setPlainText("7");
    numbers[54]->setPlainText("3");
    numbers[57]->setPlainText("5");
    numbers[71]->setPlainText("2");
    numbers[73]->setPlainText("1");
    numbers[76]->setPlainText("3");
    numbers[77]->setPlainText("4");
    numbers[78]->setPlainText("5");
}
