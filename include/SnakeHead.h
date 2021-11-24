#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include <MoveDirection.h>
#include <cstdlib>

class SnakeHead
{
    private:
        MoveDirection md;

    public:
        SnakeHead();
        MoveDirection getMoveDirection(){return md;}

};

#endif // SNAKEHEAD_H
