#ifndef MINESWEEPERPANEL_H
#define MINESWEEPERPANEL_H

#include <QObject>
#include <QWidget>
#include <minesweeperbutton.h>

/**
 * @brief The MinesweeperPanel class
 * Panel with Minesweeper buttons
 */
class MinesweeperPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MinesweeperPanel(int rows, int cols, int numBombs, QWidget *parent = nullptr);
    ~MinesweeperPanel();

signals:
    void click(int x, int y);
    void uncovered(int x, int y);
    void flagged(int x, int y, bool flagged);
    void bombClicked();

public slots:
    void revealBoard();

private:
    int rows, cols, numBombs;
    MinesweeperButton ***board;
    bool **bombs;
    bool **flags;
    bool **revealed;

    QVector<QString> stylesheets = {"", "blue","darkGreen", "red", "darkBlue", "darkRed", "darkCyan", "black", "gray"};

    bool isWithinBounds(int x, int y);
    void floodFill(int x, int y);
    bool isBomb(int x, int y);
    int neighboringBombs(int x, int y);

    static int boxDimensions;

private slots:
    void buttonClicked(int row, int col);
    void buttonRightClicked(int row, int col);

};

#endif // MINESWEEPERPANEL_H
