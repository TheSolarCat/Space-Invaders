#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(float x, float y);
    
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setColor(const sf::Color& color);
    
    bool isShooting() const;
    void resetShoot();
    
    static const float SPEED;
    static const float WIDTH;
    static const float HEIGHT;
    
private:
    sf::ConvexShape shape;
    float vx, vy;
    bool shooting;
    float windowWidth;
    float windowHeight;
};
