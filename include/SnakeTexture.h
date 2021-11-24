#ifndef SNAKETEXTURE_H
#define SNAKETEXTURE_H

#include <SFML/Graphics.hpp>

class SnakeTexture : public sf::Drawable
{
    private:

    sf::RectangleShape shape;

    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(shape);
        }

        SnakeTexture();

};

#endif // SNAKETEXTURE_H
