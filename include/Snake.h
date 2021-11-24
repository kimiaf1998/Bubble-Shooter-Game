#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SnakeHead.h>
#include <SnakeBody.h>

class Snake
{
    private:
        std::vector <SnakeBody> body;
        SnakeHead head;

    public:
        Snake();
        SnakeBody* getPtrToBodyElement(int index);

};

#endif // SNAKE_H
