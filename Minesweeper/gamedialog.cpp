#include "gamedialog.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>

GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    beginnerChk(new QRadioButton("Beginner")),
    intermediateChk(new QRadioButton("Intermediate")),
    expertChk(new QRadioButton("Expert")),
    customChk(new QRadioButton("Custom")),
    heightTxt(new QLineEdit(QString::number(values[3][0]))),
    widthTxt(new QLineEdit(QString::number(values[3][1]))),
    minesTxt(new QLineEdit(QString::number(values[3][2])))
{
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(new QLabel("Height"), 0, 1);
    layout->addWidget(new QLabel("Width"), 0, 2);
    layout->addWidget(new QLabel("Mines"), 0, 3);

    QGroupBox *groupBox = new QGroupBox;

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    \
    buttonLayout->addWidget(beginnerChk);
    buttonLayout->addWidget(intermediateChk);
    buttonLayout->addWidget(expertChk);
    buttonLayout->addWidget(customChk);

    groupBox->setLayout(buttonLayout);

    layout->addWidget(groupBox, 1, 0, 4, 1);

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            layout->addWidget(new QLabel(QString::number(values[i][j])), i+1, j+1);
        }
    }

    layout->addWidget(heightTxt, 4, 1);
    layout->addWidget(widthTxt, 4, 2);
    layout->addWidget(minesTxt, 4, 3);

    QPushButton *newGameBtn = new QPushButton("New Game");
    connect(newGameBtn, &QPushButton::clicked, this, &GameDialog::newGame);
    layout->addWidget(newGameBtn, 5, 0);

    this->setLayout(layout);

}

void GameDialog::newGame(){
    close();
}

int GameDialog::height(){
    if (intermediateChk->isChecked())
        return values[1][0];
    else if (expertChk->isChecked())
        return values[2][0];
    else if (customChk->isChecked()){
        return heightTxt->text().toInt();
    }
    return values[0][0]; //by default, return beginner
}

int GameDialog::width(){
    if (intermediateChk->isChecked())
        return values[1][1];
    else if (expertChk->isChecked())
        return values[2][1];
    else if (customChk->isChecked()){
        return widthTxt->text().toInt();
    }
    return values[0][1]; //by default, return beginner
}

int GameDialog::mines(){
    if (intermediateChk->isChecked())
        return values[1][2];
    else if (expertChk->isChecked())
        return values[2][2];
    else if (customChk->isChecked()){
        return minesTxt->text().toInt();
    }
    return values[0][2]; //by default, return beginner
}


