#include "snake.h"

Snake::Snake()
{

}

void Snake::init()
{
    isgameover = false;
    score = 0;
    head = NULL;
    end = NULL;
    apple = NULL;
    direction = LEFT;

    SnakeBone *temp;
    score = 0;
    qDebug() << "[1] createing snake..";
    head = new SnakeBone();
    head->x = WIDTH/2;
    head->y = HEIGHT/2;
    head->next = NULL;
    qDebug() << "head"<<":"<<"(" << head->x << "," << head->y << ")";
    temp = head;
    for(int i = 0;i<INIT_SNAKE_LENGTH-1;i++)
    {
        SnakeBone *bone = new SnakeBone();
        bone->x = WIDTH/2 + i + 1;
        bone->y = HEIGHT/2;
        bone->next = NULL;
        qDebug() << "bone-"<<":"<<"(" << bone->x << "," << bone->y << ")";
        if(i == 0) {head->next = bone;}
        temp->next = bone;
        temp = bone;
        end = temp; //set the end
    }
    apple = newbone();
}

void Snake::move()
{
    switch (direction) {
    case UP:
        qDebug() << "move up";
        head->y -= 1;
        selfharm();
        outplayground();
        eatapple();
        movebones();
        break;
    case DOWN:
        qDebug() << "move down";
        head->y += 1;
        selfharm();
        outplayground();
        eatapple();
        movebones();
        break;
    case LEFT:
        qDebug() << "move left";
        head->x -= 1;
        selfharm();
        outplayground();
        eatapple();
        movebones();
        break;
    case RIGHT:
        qDebug() << "move right";
        head->x += 1;
        selfharm();
        outplayground();
        eatapple();
        movebones();
        break;
    }
}

void Snake::selfharm()
{
    qDebug() << "--selfharmt";
    SnakeBone *temp;
    temp = head->next;
    while (temp != NULL) {
       if((head->x == temp->x) && (head->y == temp->y))
       {
           qDebug() << "--------------selfharm:true";
           isgameover = true;
       }
       temp = temp->next;
    }
    //isgameover = false;
}

void Snake::outplayground()
{
    qDebug() << "--outplayground";
    if((head->x < 0) || (head->x > WIDTH) || (head->y < 0) || (head->y > HEIGHT))
    {
        qDebug() << "--------------outplayground:true";
        isgameover = true;
    }
    //isgameover = false;
}

void Snake::eatapple()
{
    //head->next = new SnakeBone(1,1);
    //apple = newbone();
    if((apple->x == head->x) && (apple->y == head->y))
    {
        qDebug() << "EAT EAT!";
        score++;
        SnakeBone *newbody = new SnakeBone(apple->x,apple->y);
        newbody->next = NULL;
        end->next = newbody;
        end = newbody;
        delete apple;
        apple = newbone();
    }
}

void Snake::movebones()
{

    SnakeBone *temp;
    int list_x[MAX_LENGTH] = {0};
    int list_y[MAX_LENGTH] = {0};
    int index = 1;
    temp = head->next;

    switch (direction) {
    case UP:
        list_x[0] = head->x;
        list_y[0] = head->y + 1;
        break;
    case DOWN:
        list_x[0] = head->x;
        list_y[0] = head->y - 1;
        break;
    case LEFT:
        list_x[0] = head->x + 1;
        list_y[0] = head->y;
        break;
    case RIGHT:
        list_x[0] = head->x - 1;
        list_y[0] = head->y;
        break;

    }

    while (temp != NULL) {
        list_x[index] = temp->x;
        list_y[index] = temp->y;
        index++;
        temp = temp->next;
    }

    temp = head->next;
    for(int i = 0;i<MAX_LENGTH;i++)
    {
        //qDebug() << "list" << list_x[i] << "-" <<list_y[i];
        if(temp != NULL)
        {
            temp->x = list_x[i];
            temp->y = list_y[i];
            temp = temp->next;
        }

    }

    /*
    index = 1;
    temp = head->next;
    while (temp != NULL) {
       temp->x = list_x[index+1];
       temp->y = list_y[index+1];
       index++;
       temp = temp->next;
    }
    */
}

SnakeBone* Snake::newbone()
{
    SnakeBone *temp;

    START:
    temp = head;
    SnakeBone *newapple = new SnakeBone();
    newapple->x = qrand()%WIDTH;
    newapple->y = qrand()%HEIGHT;
    newapple->next = NULL;
    qDebug() << "[2] createing apple..";
    while (temp != NULL) {
        if((temp->x == newapple->x) && (temp->y == newapple->y))
        {
            //qDebug() << "-----------------------------------------";
            //qDebug() <<  "bad apple" << newapple->x << "-" << newapple->y;
            delete newapple;
            goto START;
        }
        temp = temp->next;
    }
    temp = NULL;
    //qDebug() <<  "new apple" << newapple->x << "-" << newapple->y;
    return newapple;
}

void Snake::debug()
{
    qDebug() << "---------------";
    SnakeBone *temp;
    temp = head;
    while (temp != NULL) {
      qDebug() << temp->x << "-" << temp->y;
      temp = temp->next;
    }
}
