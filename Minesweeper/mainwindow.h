#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <minesweeperpanel.h>
#include <QLabel>
#include <QGridLayout>

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MinesweeperPanel *panel;
    QLabel *clicksCountLbl;
    int uncoveredSquares;
    int numBombs;
    QGridLayout *layout;

    void startGame(int rows, int cols, int bombs);

private slots:
    void endGame(bool status);
    void click(int x, int y);
    void uncovered(int x, int y);
    void openGame();

};
#endif // MAINWINDOW_H
