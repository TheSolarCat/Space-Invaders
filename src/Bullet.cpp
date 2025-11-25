#include "Bullet.h"

const float Bullet::SPEED = 500.0f;
const float Bullet::WIDTH = 5.0f;
const float Bullet::HEIGHT = 15.0f;

Bullet::Bullet(float x, float y)
    : active(true)
{
    shape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Yellow);
}

void Bullet::update(float deltaTime)
{
    sf::Vector2f pos = shape.getPosition();
    pos.y -= SPEED * deltaTime;

    if (pos.y + HEIGHT < 0)
        active = false;

    shape.setPosition(pos);
}

void Bullet::draw(sf::RenderWindow& window)
{
    if (active)
        window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Bullet::isActive() const
{
    return active;
}
