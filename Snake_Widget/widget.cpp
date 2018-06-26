#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->grabKeyboard();
    this->setWindowTitle("Snake (F1=Restart)");
    this->setGeometry(50,50,900,900);

    view = new QGraphicsView();
    scene = new QGraphicsScene();
    layout = new QHBoxLayout();

    scene->setSceneRect(0,0,800,800);
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(view);
    setLayout(layout);

    QGraphicsRectItem *edge = new QGraphicsRectItem(0,0,800,800);
    edge->setPos(0,0);
    scene->addItem(edge);

    snake = new Snake();
    snake->init();

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(gameruning()));
    timer->start(70);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        if(up_lock)
        {
            direction = UP;
            qDebug() << "Up";
            left_lock = true;
            right_lock = true;

            up_lock = false;
            down_lock = false;
        }
        break;
    case Qt::Key_Down:
        if(down_lock)
        {
            direction = DOWN;
            qDebug() << "Down";
            left_lock = true;
            right_lock = true;

            up_lock = false;
            down_lock = false;
        }
        break;
    case Qt::Key_Left:
        if(left_lock)
        {
            direction = LEFT;
            qDebug() << "Left";
            up_lock = true;
            down_lock = true;

            left_lock = false;
            right_lock = false;
        }
        break;
    case Qt::Key_Right:
        if(right_lock)
        {
            direction = RIGHT;
            qDebug() << "Right";
            up_lock = true;
            down_lock = true;

            left_lock = false;
            right_lock = false;
        }
        break;
    case Qt::Key_F1:
        if(snake->isgameover)
        {
            direction = LEFT;
            up_lock = true;
            down_lock = true;
            left_lock = false; //false is lock
            right_lock = false;
            delete snake;
            snake = new Snake();
            snake->init();
            timer->start(70);
        }
        break;
    default:
        break;
    }
    QWidget::keyPressEvent(event);
}

void Widget::gameruning()
{
    QGraphicsRectItem *headitem;
    int index = 0;

    snake->direction = direction;
    snake->move();


    scene->clear();
    SnakeBone *temp;
    temp = snake->head;
    while(temp != NULL)
    {
        QGraphicsRectItem *item = new QGraphicsRectItem(0,0,800.0/33,800.0/33);
        item->setPos(800.0/33.0*temp->x,800.0/33*temp->y);
        scene->addItem(item);
        temp = temp->next;
        if(index == 0) {headitem = item;}
        index++;
    }
    index = 0;

    if(snake->isgameover)
    {
        timer->stop();
        scene->removeItem(headitem);

    }

    QGraphicsRectItem *apple = new QGraphicsRectItem(0,0,800.0/33,800.0/33);
    apple->setPos(800.0/33.0*snake->apple->x,800.0/33*snake->apple->y);
    apple->setPen(QPen(Qt::red));
    scene->addItem(apple);

    QGraphicsRectItem *edge = new QGraphicsRectItem(0,0,800,800);
    edge->setPos(0,0);
    scene->addItem(edge);

    QGraphicsTextItem *score = new QGraphicsTextItem();
    score->setPlainText(QString::number(snake->score));
    score->setPos(400,10);
    scene->addItem(score);


}


