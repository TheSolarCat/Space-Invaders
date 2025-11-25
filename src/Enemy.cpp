#include "Enemy.h"
#include <cstdlib>
#include <ctime>

const float Enemy::WIDTH = 40.0f;
const float Enemy::HEIGHT = 30.0f;

Enemy::Enemy(float x, float y, int difficulty)
    : health(1), difficulty(difficulty)
{
    shape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);

    // Speed increases with difficulty
    float baseSpeed = 100.0f;
    if (difficulty == 1) // MEDIUM
        baseSpeed = 150.0f;
    else if (difficulty == 2) // HARD
        baseSpeed = 250.0f;

    vx = (rand() % 2 == 0) ? baseSpeed : -baseSpeed;
    vy = 30.0f + (rand() % 50);
    
    if (difficulty == 2) // HARD - more health
        health = 2;
}

void Enemy::update(float deltaTime)
{
    sf::Vector2f pos = shape.getPosition();
    pos.x += vx * deltaTime;
    pos.y += vy * deltaTime;

    // Bounce off walls
    if (pos.x <= 0 || pos.x + WIDTH >= 1200)
        vx = -vx;

    // Remove if out of bounds vertically
    if (pos.y > 800)
        health = 0;

    shape.setPosition(pos);
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition() const
{
    return shape.getPosition();
}

void Enemy::setColor(const sf::Color& color)
{
    shape.setFillColor(color);
}

bool Enemy::isAlive() const
{
    return health > 0;
}

void Enemy::hit()
{
    health--;
}
