#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QGraphicsTextItem>
#include <QFont>
#include "snake.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QTimer *timer;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QHBoxLayout *layout;

    Snake *snake;
    int direction = LEFT;
    bool up_lock = true;
    bool down_lock = true;
    bool left_lock = false; //false is lock
    bool right_lock = false;

protected:
    void keyPressEvent(QKeyEvent *event);
public slots:
    void gameruning();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
