#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(float x, float y);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;
    bool isActive() const;
    
    static const float SPEED;
    static const float WIDTH;
    static const float HEIGHT;
    
private:
    sf::RectangleShape shape;
    bool active;
};
