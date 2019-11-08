#include "mainwindow.h"
#include <QVBoxLayout>
#include <minesweeperpanel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget;

    MinesweeperPanel *panel = new MinesweeperPanel(10, 10, 8, this);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(panel, 0, 0);

    centralWidget->setLayout(layout);

    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

