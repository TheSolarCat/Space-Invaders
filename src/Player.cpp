#include "Player.h"
#include <SFML/Window.hpp>

const float Player::SPEED = 400.0f;
const float Player::WIDTH = 30.0f;
const float Player::HEIGHT = 40.0f;

Player::Player(float x, float y)
    : vx(0), vy(0), shooting(false), windowWidth(1200), windowHeight(800)
{
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(WIDTH / 2, 0));
    shape.setPoint(1, sf::Vector2f(0, HEIGHT));
    shape.setPoint(2, sf::Vector2f(WIDTH, HEIGHT));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

void Player::handleInput(float deltaTime)
{
    vx = 0;
    vy = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        vx = -SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        vx = SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        vy = -SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        vy = SPEED;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        shooting = true;
}

void Player::update(float deltaTime)
{
    sf::Vector2f newPos = shape.getPosition();
    newPos.x += vx * deltaTime;
    newPos.y += vy * deltaTime;

    // Boundary checking
    if (newPos.x < 0)
        newPos.x = 0;
    if (newPos.x + WIDTH > windowWidth)
        newPos.x = windowWidth - WIDTH;
    if (newPos.y < 0)
        newPos.y = 0;
    if (newPos.y + HEIGHT > windowHeight)
        newPos.y = windowHeight - HEIGHT;

    shape.setPosition(newPos);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Player::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const
{
    return shape.getPosition();
}

void Player::setColor(const sf::Color& color)
{
    shape.setFillColor(color);
}

bool Player::isShooting() const
{
    return shooting;
}

void Player::resetShoot()
{
    shooting = false;
}
