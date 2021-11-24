#ifndef FOOD_H
#define FOOD_H
#include <SFML\Graphics.hpp>

class Food : public sf::Drawable
{
    private:
        sf::RectangleShape shape;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(shape);
        }
    public:
        Food();
        //void setPosition(const Vector2f& position);

};

#endif // FOOD_H
