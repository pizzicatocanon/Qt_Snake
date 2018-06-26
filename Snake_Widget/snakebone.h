#ifndef SNAKEBONE_H
#define SNAKEBONE_H

class SnakeBone
{
public:
    SnakeBone();
    SnakeBone(int x, int y);

    int x;
    int y;
    SnakeBone *next = nullptr;
};

#endif // SNAKEBONE_H
