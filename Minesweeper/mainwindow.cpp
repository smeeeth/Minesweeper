#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QDebug>
#include <gamedialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      clicksCountLbl(new QLabel),
      layout(new QGridLayout)
{
    QAction *gamesAction = menuBar()->addAction("Game");
    connect(gamesAction, &QAction::triggered, this, &MainWindow::openGame);

    QWidget *centralWidget = new QWidget;

    int rows = 10;
    int cols = 10;
    numBombs = 8;
    uncoveredSquares = rows*cols - numBombs;

    panel = new MinesweeperPanel(10, 10, 8, this);
    connect(panel, &MinesweeperPanel::bombClicked, this, [=](void){endGame(false);});
    connect(panel, &MinesweeperPanel::click, this, &MainWindow::click);
    connect(panel, &MinesweeperPanel::uncovered, this, &MainWindow::uncovered);

    layout->addWidget(clicksCountLbl, 0, 1);
    layout->addWidget(panel, 1, 0, 1, 2);

    centralWidget->setLayout(layout);

    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

/**
 * @brief MainWindow::endGame
 * Reveal board and display win message
 * @param win
 */
void MainWindow::endGame(bool win){
    panel->revealBoard();
    QMessageBox msg;
    if (win)
        msg.setText("Win");
    else
        msg.setText("Loss");
    msg.exec();
    close();
}

/**
 * @brief MainWindow::click
 * Update click counter on screen
 * @param x
 * @param y
 */
void MainWindow::click(int x, int y){
    clicksCountLbl->setText(QString::number(clicksCountLbl->text().toInt() + 1));
}

/**
 * @brief MainWindow::uncovered
 *
 * @param x
 * @param y
 */
void MainWindow::uncovered(int x, int y){
    qDebug() << "Uncovered (" + QString::number(x) + ","  + QString::number(y) + ")";
    uncoveredSquares--;
    if (uncoveredSquares <= 0)
        endGame(true);
}

void MainWindow::openGame(){
    GameDialog dialog;

    dialog.exec();

    layout->removeWidget(panel);

    delete panel;

    panel = new MinesweeperPanel(dialog.height(), dialog.width(), dialog.mines());

    layout->addWidget(panel, 1, 0, 1, 2);

    this->update();
}
