#ifndef SNAKE_H
#define SNAKE_H

#include "snakebone.h"
#include <QDebug>
#include <stdio.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define WIDTH 32
#define HEIGHT 32

#define MAX_APPLES 4
#define MAX_LENGTH 500 //48
#define INIT_SNAKE_LENGTH 4


class Snake
{
public:
    Snake();
    bool isgameover = false;
    int seed;
    int score = 0;
    SnakeBone *head;
    SnakeBone *end;
    SnakeBone *apple;
    int direction = LEFT;
    void init();
    void move();
    SnakeBone* newbone();

    void selfharm();
    void outplayground();
    void eatapple();
    void movebones();
    void debug();
};

#endif // SNAKE_H
