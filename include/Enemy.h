#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    Enemy(float x, float y, int difficulty);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setColor(const sf::Color& color);
    
    bool isAlive() const;
    void hit();
    
    static const float WIDTH;
    static const float HEIGHT;
    
private:
    sf::RectangleShape shape;
    float vx, vy;
    int health;
    int difficulty;
};
