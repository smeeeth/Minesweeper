#include "minesweeperbutton.h"
#include <QMouseEvent>

MinesweeperButton::MinesweeperButton(QWidget *parent) :
    QPushButton(parent)
{

}

/**
 * @brief MinesweeperButton::mousePressEvent
 * Filter click events for right button clicked
 * @param e
 */
void MinesweeperButton::mousePressEvent(QMouseEvent *e){
    if (e->button()==Qt::RightButton)
        emit rightClicked();

    QPushButton::mousePressEvent(e);
}
