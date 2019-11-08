#include "minesweeperpanel.h"
#include <QGridLayout>
#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

MinesweeperPanel::MinesweeperPanel(int rows, int cols, int numBombs, QWidget *parent) :
    QWidget(parent),
    rows(rows),
    cols(cols)
{

    setStyleSheet("QPushButton{min-width: 30px; max-width: 30px; min-height: 30px; max-height: 30px;}");
    QGridLayout *layout = new QGridLayout;

    board = new QPushButton**[cols]; // dynamic array (size rows) of pointers to buttons
    bombs = new bool*[cols]; //dynamic array (size rows) of pointers to bools for bombs

    //set up board and initailize bombs
    for (int i = 0; i < rows; i++) {
        //allocate row
        board[i] = new QPushButton*[cols];
        bombs[i] = new bool[cols];
        for (int j = 0; j < cols; j++){
            //
            board[i][j] = new QPushButton;
            board[i][j]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            connect(board[i][j], &QPushButton::clicked, this, [=](void){buttonClicked(i,j);});
            layout->addWidget(board[i][j], i, j);
            //initialize all bomb spots to false
            bombs[i][j] = false;
        }
        // each i-th pointer is now pointing to dynamic array (size rows) of actual int values
    }

    for (int i=0; i<numBombs; i++){
        int x = static_cast<int>(QRandomGenerator::global()->generateDouble() * (rows-1));
        int y = static_cast<int>(QRandomGenerator::global()->generateDouble() * (cols-1));
        bombs[x][y] = true;
        board[x][y]->setText("B");
    }

    this->setLayout(layout);
}

MinesweeperPanel::~MinesweeperPanel()
{
    for (int i = 0; i < rows; i++){

    }
}

void MinesweeperPanel::buttonClicked(int row, int col){
    emit click(row, col);

    if (bombs[row][col])
        emit bombClicked();

    floodFill(row, col);
}

bool MinesweeperPanel::isWithinBounds(int x, int y){
    return x>=0 && x<rows && y>=0 && y<cols;
}

void MinesweeperPanel::floodFill(int x, int y){

    if (!isWithinBounds(x,y) //if out of bounds
            || bombs[x][y] //or found bomb
            || !board[x][y]->isEnabled()) //or already visited this square
        return;

    board[x][y]->setEnabled(false);
    emit uncovered(x,y);

    int neighbors = neighboringBombs(x, y);
    if (neighbors != 0){
        board[x][y]->setText(QString::number(neighbors));
        board[x][y]->setStyleSheet("color: " + stylesheets[neighbors]);
    }else{
        //search neighbors
        floodFill(x-1, y); //left
        floodFill(x+1, y); //right
        floodFill(x-1, y-1); //left up
        floodFill(x-1, y+1); //left down
        floodFill(x+1, y-1); //right up
        floodFill(x+1, y+1); //right down
        floodFill(x, y+1); //up
        floodFill(x, y-1); //down
    }
}

bool MinesweeperPanel::isBomb(int x, int y){
    return !isWithinBounds(x,y) //within bounds
            && bombs[x][y]; //is bomb
}

int MinesweeperPanel::neighboringBombs(int x, int y){
    int bombNeighbors=0;
    for (int i=-1; i<=1; i++){
        for (int j=-1; j<=1; j++){
            if (isWithinBounds(x+i, y+j) && //is within bounds
                    !(i==0 && j==0) && //don't check current square
                    bombs[x+i][y+j]) //is bomb
              bombNeighbors++;
        }
    }

    return bombNeighbors;
}
