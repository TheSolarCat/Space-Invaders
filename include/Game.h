#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameConfig.h"

class Game
{
public:
    Game();
    ~Game();
    
    void run();
    void handleInput();
    void update(float deltaTime);
    void render();
    void showMenu();
    void updateScore(int points);
    void checkCollisions();
    void spawnEnemies();
    void gameOver();
    
private:
    sf::RenderWindow window;
    GameConfig config;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    
    int score;
    int wave;
    float spawnTimer;
    float spawnRate;
    bool gameRunning;
    bool menuActive;
    
    // Theme colors
    sf::Color backgroundColor;
    sf::Color playerColor;
    sf::Color enemyColor;
    sf::Color bulletColor;
    
    sf::Font font;
    sf::Text scoreText;
    sf::Text waveText;
    sf::Text gameOverText;
    
    void setThemeColors();
    void updateUI();
};
