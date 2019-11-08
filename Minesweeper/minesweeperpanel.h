#ifndef MINESWEEPERPANEL_H
#define MINESWEEPERPANEL_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

/**
 * @brief The MinesweeperPanel class
 * Panel with Minesweeper buttons and
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
    void bombClicked();

public slots:

private:
    int rows, cols;
    QPushButton ***board;
    bool **bombs;

    QVector<QString> stylesheets = {"", "blue","darkGreen", "red", "darkBlue", "darkRed", "darkCyan", "black", "gray"};

    bool isWithinBounds(int x, int y);
    void floodFill(int x, int y);
    bool isBomb(int x, int y);
    int neighboringBombs(int x, int y);


private slots:
    void buttonClicked(int row, int col);

};

#endif // MINESWEEPERPANEL_H
