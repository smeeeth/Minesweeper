#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QRadioButton>
#include <QLineEdit>

class GameDialog : public QDialog
{
    Q_OBJECT
public:
    GameDialog(QWidget *parent = nullptr);
    int height();
    int width();
    int mines();

private:
    QRadioButton *beginnerChk, *intermediateChk, *expertChk, *customChk;
    int values[4][3] = {{9, 9, 10}, {16, 16, 40}, {16, 30, 99},{20, 30, 145}};
    QLineEdit *heightTxt, *widthTxt, *minesTxt;

private slots:
    void newGame();
};

#endif // GAMEDIALOG_H
