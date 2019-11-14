#include "minesweeperpanel.h"
#include <QGridLayout>
#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

int MinesweeperPanel::boxDimensions = 30;

MinesweeperPanel::MinesweeperPanel(int rows, int cols, int numBombs, QWidget *parent) :
    QWidget(parent),
    rows(rows),
    cols(cols),
    numBombs(numBombs)
{

    setStyleSheet("QPushButton{min-width:" + QString::number(boxDimensions) + "px; \
                                max-width:" + QString::number(boxDimensions) + "px; \
                                min-height:" + QString::number(boxDimensions) + "px; \
                                max-height:" + QString::number(boxDimensions) + "px; \
                                background-color:rgb(185,185,185);}");
    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(0);

    //allocate dynamic arrays of size rows
    board = new MinesweeperButton**[cols];
    bombs = new bool*[cols];
    flags = new bool*[cols];
    revealed = new bool*[cols];

    //set up board and initailize bombs
    for (int i = 0; i < rows; i++) {
        //allocate row
        board[i] = new MinesweeperButton*[cols];
        bombs[i] = new bool[cols];
        flags[i] = new bool[cols];
        revealed[i] = new bool[cols];
        for (int j = 0; j < cols; j++){
            //create button
            board[i][j] = new MinesweeperButton;
            board[i][j]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            board[i][j]->setIcon(QIcon("://images/facingDown.png"));
            board[i][j]->setIconSize(QSize(boxDimensions, boxDimensions));
            connect(board[i][j], &QPushButton::clicked, this, [=](void){buttonClicked(i,j);});
            connect(board[i][j], &MinesweeperButton::rightClicked, this, [=](void){buttonRightClicked(i,j);});
            layout->addWidget(board[i][j], i, j);
            //initialize all bomb spots to false
            bombs[i][j] = false;
            flags[i][j] = false;
            revealed[i][j] = false;
        }
        // each i-th pointer is now pointing to dynamic array (size rows) of actual int values
    }

    for (int i=0; i<numBombs; i++){
        int x = static_cast<int>(QRandomGenerator::global()->generateDouble() * (rows-1));
        int y = static_cast<int>(QRandomGenerator::global()->generateDouble() * (cols-1));
        bombs[x][y] = true;
    }

    this->setLayout(layout);
}

MinesweeperPanel::~MinesweeperPanel()
{
    for (int i=0; i<rows; i++){
        for (int j=0;j<cols; j++){
            delete board[i][j];
        }
    }
    delete this->layout();
}

/**
 * @brief MinesweeperPanel::buttonClicked
 * Checks for bomb, then starts flood fill from given coordinate
 * @param row
 * @param col
 */
void MinesweeperPanel::buttonClicked(int row, int col){

    if(revealed[row][col])
        return;

    emit click(row, col);

    if (bombs[row][col]){ //bomb clicked
        board[row][col]->setStyleSheet("background-color:red;");
        board[row][col]->setIcon(QIcon("://images/bomb.png"));
        emit bombClicked();
    }

    floodFill(row, col);
}

/**
 * @brief MinesweeperPanel::buttonRightClicked
 * Toggles flag on given coordinates
 * @param row
 * @param col
 */
void MinesweeperPanel::buttonRightClicked(int row, int col){

    if(revealed[row][col])
        return;

    flags[row][col] = !flags[row][col]; //flip flag

    emit flagged(row, col, flags[row][col]);

    if (flags[row][col]){
        board[row][col]->setIcon(QIcon("://images/flagged.png"));
    } else{
        board[row][col]->setIcon(QIcon("://images/facingDown.png"));
    }

}

/**
 * @brief MinesweeperPanel::isWithinBounds
 * @param x
 * @param y
 * @return square is within bounds of grid
 */
bool MinesweeperPanel::isWithinBounds(int x, int y){
    return x>=0 && x<rows && y>=0 && y<cols;
}

/**
 * @brief MinesweeperPanel::floodFill
 * Recursive method that reveals board starting from given coordinates,
 * then checks all neighbors if square has no neighboring bombs.
 * @param x
 * @param y
 */
void MinesweeperPanel::floodFill(int x, int y){

     if (!isWithinBounds(x,y) //if out of bounds
            || bombs[x][y] //or found bomb
            || revealed[x][y]) //or already visited this square
        return;

    revealed[x][y] = true;

    int neighbors = neighboringBombs(x, y);
    board[x][y]->setIcon(QIcon("://images/" + QString::number(neighbors) + ".png"));

    emit uncovered(x,y);

    if (neighbors == 0){
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

/**
 * @brief MinesweeperPanel::isBomb
 * @param x
 * @param y
 * @return square contains bomb
 */
bool MinesweeperPanel::isBomb(int x, int y){
    return !isWithinBounds(x,y) //within bounds
            && bombs[x][y]; //is bomb
}

/**
 * @brief MinesweeperPanel::neighboringBombs
 * @param x
 * @param y
 * @return number of neighboring squares that are bombs
 */
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

/**
 * @brief MinesweeperPanel::revealBoard
 * Uncover all squares in the board
 */
void MinesweeperPanel::revealBoard(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            if (!revealed[i][j]){
                if (bombs[i][j])
                    board[i][j]->setIcon(QIcon("://images/bomb.png")); //reveal bomb
                else
                    board[i][j]->setIcon(QIcon("://images/" + QString::number(neighboringBombs(i, j)) + ".png")); //reveal # neighbors
            }
        }
    }
}
