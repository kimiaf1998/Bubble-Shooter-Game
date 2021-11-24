#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <MoveDirection.h>
#include <SnakeHead.h>


class SnakeBody
{
    private:
        MoveDirection md;

    public:
        SnakeBody();
        SnakeBody(SnakeHead sh);



};

#endif // SNAKEBODY_H
