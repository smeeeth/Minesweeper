#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <minesweeperpanel.h>
#include <QLabel>

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

private slots:
    void endGame(bool status);
    void click(int x, int y);
    void uncovered(int x, int y);

};
#endif // MAINWINDOW_H
