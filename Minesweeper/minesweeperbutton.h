#ifndef MINESWEEPERBUTTON_H
#define MINESWEEPERBUTTON_H

#include <QPushButton>
#include <QObject>

class MinesweeperButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MinesweeperButton(QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightClicked();

};

#endif // MINESWEEPERBUTTON_H
