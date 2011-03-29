#include    <QMainWindow>
#include    <QCloseEvent>
#include    <QCheckBox>
#include    <QSpinBox>
#include    <QPushButton>
#include    <QLabel>
#include    <map>

#ifndef     OPTIONWINDOW_H
#define     OPTIONWINDOW_H

#define     OPTION_WIN_X        180
#define     OPTION_WIN_Y        170
#define     TEXT_OPTION_WIN     "QTNibbler's Options"
#define     TEXT_LEVEL          "Initial Level :"
#define     TEXT_MULTI          "Tron Like"
#define     TEXT_WALL           "Wall Visibility"
#define     TEXT_OK             "Ok"

class               OptionWindow :          public QMainWindow
{
    Q_OBJECT
public :
    OptionWindow(QWidget *parent);
    virtual ~OptionWindow();

public:
    bool            getMulti()              const;
    bool            getWallVisibility()     const;
    int             getLevel()              const;

protected:
    void            keyPressEvent(QKeyEvent *event);

private:
    QCheckBox       *_multiButton;
    QCheckBox       *_wallButton;
    QSpinBox        *_levelButton;
    QPushButton     *_okButton;
    QLabel          *_levelTitle;

    bool            _multi;
    int             _level;
    bool            _wallVisibility;

private slots:
    void            updateLevel(int level);
    void            changeMulti();
    void            changeWall();
};


#endif  // OPTIONWINDOW_H
