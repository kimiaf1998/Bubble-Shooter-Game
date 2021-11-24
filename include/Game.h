#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Food.h>

class Game
{
private:
        sf::RenderWindow window;
        //sf::Ren
        Food food;
public:
        Game();
        void run();
        void processEvents();
        void update();
        void render();

};

#endif // GAME_H
