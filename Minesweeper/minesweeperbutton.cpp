#include "minesweeperbutton.h"
#include <QMouseEvent>

MinesweeperButton::MinesweeperButton(QWidget *parent) :
    QPushButton(parent)
{

}

void MinesweeperButton::mousePressEvent(QMouseEvent *e){
    if (e->button()==Qt::RightButton)
        emit rightClicked();

    QPushButton::mousePressEvent(e);
}
