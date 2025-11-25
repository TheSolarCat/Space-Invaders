#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game()
    : window(sf::VideoMode(1200, 800), "Space Invaders"),
      player(600, 700),
      score(0),
      wave(1),
      spawnTimer(0),
      gameRunning(true),
      menuActive(true)
{
    srand(static_cast<unsigned>(time(0)));
    
    config.loadConfig("config.ini");
    
    window.setFramerateLimit(60);
    
    // Set spawn rate based on difficulty
    switch (config.getDifficulty())
    {
    case Difficulty::EASY:
        spawnRate = 1.5f;
        break;
    case Difficulty::MEDIUM:
        spawnRate = 1.0f;
        break;
    case Difficulty::HARD:
        spawnRate = 0.5f;
        break;
    }
    
    setThemeColors();
    
    // Initialize UI text - try multiple font paths
    bool fontLoaded = font.loadFromFile("arial.ttf");
    if (!fontLoaded)
        fontLoaded = font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    if (!fontLoaded)
        fontLoaded = font.loadFromFile("arial");
    
    if (fontLoaded)
    {
        scoreText.setFont(font);
        scoreText.setCharacterSize(20);
        scoreText.setPosition(10, 10);
        
        waveText.setFont(font);
        waveText.setCharacterSize(20);
        waveText.setPosition(1000, 10);
        
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(60);
        gameOverText.setString("GAME OVER");
        gameOverText.setPosition(350, 300);
    }
    
    player.setColor(playerColor);
}

Game::~Game()
{
}

void Game::run()
{
    sf::Clock clock;
    
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        
        handleInput();
        
        if (menuActive)
        {
            showMenu();
        }
        else
        {
            update(deltaTime);
            render();
        }
    }
}

void Game::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed)
        {
            if (menuActive)
            {
                if (event.key.code == sf::Keyboard::M)
                {
                    menuActive = false;
                    enemies.clear();
                    bullets.clear();
                    score = 0;
                    wave = 1;
                }
                else if (event.key.code == sf::Keyboard::E)
                    config.setDifficulty(Difficulty::EASY);
                else if (event.key.code == sf::Keyboard::D)
                    config.setDifficulty(Difficulty::MEDIUM);
                else if (event.key.code == sf::Keyboard::H)
                    config.setDifficulty(Difficulty::HARD);
                else if (event.key.code == sf::Keyboard::Num1)
                    config.setTheme(Theme::CLASSIC);
                else if (event.key.code == sf::Keyboard::Num2)
                    config.setTheme(Theme::NEON);
                else if (event.key.code == sf::Keyboard::Num3)
                    config.setTheme(Theme::DARK);
            }
            else if (!gameRunning && event.key.code == sf::Keyboard::R)
            {
                menuActive = true;
                gameRunning = true;
            }
        }
    }
    
    if (!menuActive && gameRunning)
    {
        player.handleInput(0.016f); // Approximate deltaTime
    }
}

void Game::update(float deltaTime)
{
    player.update(deltaTime);
    
    // Spawn enemies
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnRate)
    {
        spawnEnemies();
        spawnTimer = 0;
    }
    
    // Update enemies
    for (auto& enemy : enemies)
        enemy.update(deltaTime);
    
    // Update bullets
    for (auto& bullet : bullets)
        bullet.update(deltaTime);
    
    // Handle shooting
    if (player.isShooting())
    {
        sf::Vector2f playerPos = player.getPosition();
        bullets.emplace_back(playerPos.x + 12.5f, playerPos.y);
        player.resetShoot();
    }
    
    // Check collisions
    checkCollisions();
    
    // Remove dead enemies and inactive bullets
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                  [](const Enemy& e) { return !e.isAlive(); }),
                  enemies.end());
    
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                  [](const Bullet& b) { return !b.isActive(); }),
                  bullets.end());
    
    // Check if all enemies defeated
    if (enemies.empty() && spawnTimer > 2.0f)
    {
        wave++;
        spawnRate *= 0.9f;
    }
    
    updateUI();
}

void Game::render()
{
    window.clear(backgroundColor);
    
    player.draw(window);
    
    for (auto& enemy : enemies)
        enemy.draw(window);
    
    for (auto& bullet : bullets)
        bullet.draw(window);
    
    window.draw(scoreText);
    window.draw(waveText);
    
    if (!gameRunning)
    {
        window.draw(gameOverText);
    }
    
    window.display();
}

void Game::showMenu()
{
    window.clear(backgroundColor);
    
    // Display menu text
    sf::Text titleText;
    if (font.loadFromFile("arial.ttf"))
    {
        titleText.setFont(font);
        titleText.setCharacterSize(50);
        titleText.setString("SPACE INVADERS");
        titleText.setPosition(350, 50);
        titleText.setFillColor(playerColor);
        
        sf::Text difficultyText;
        difficultyText.setFont(font);
        difficultyText.setCharacterSize(30);
        difficultyText.setString("SELECT DIFFICULTY\nE - Easy\nD - Medium\nH - Hard");
        difficultyText.setPosition(300, 200);
        difficultyText.setFillColor(sf::Color::White);
        
        sf::Text themeText;
        themeText.setFont(font);
        themeText.setCharacterSize(30);
        themeText.setString("SELECT THEME\n1 - Classic\n2 - Neon\n3 - Dark");
        themeText.setPosition(300, 400);
        themeText.setFillColor(sf::Color::White);
        
        sf::Text startText;
        startText.setFont(font);
        startText.setCharacterSize(25);
        startText.setString("Press M to Start");
        startText.setPosition(450, 650);
        startText.setFillColor(bulletColor);
        
        window.draw(titleText);
        window.draw(difficultyText);
        window.draw(themeText);
        window.draw(startText);
    }
    
    window.display();
}

void Game::updateScore(int points)
{
    score += points;
}

void Game::checkCollisions()
{
    sf::FloatRect playerBounds = player.getBounds();
    
    for (auto& enemy : enemies)
    {
        sf::FloatRect enemyBounds = enemy.getBounds();
        
        if (playerBounds.intersects(enemyBounds))
        {
            gameRunning = false;
            return;
        }
        
        for (auto& bullet : bullets)
        {
            if (bullet.isActive() && enemyBounds.intersects(bullet.getBounds()))
            {
                enemy.hit();
                updateScore(10);
            }
        }
    }
}

void Game::spawnEnemies()
{
    int enemyCount = 3 + wave;
    if (config.getDifficulty() == Difficulty::HARD)
        enemyCount = 5 + wave;
    
    for (int i = 0; i < enemyCount; i++)
    {
        float x = (rand() % 1160);
        enemies.emplace_back(x, -30, static_cast<int>(config.getDifficulty()));
        enemies.back().setColor(enemyColor);
    }
}

void Game::gameOver()
{
    gameRunning = false;
}

void Game::setThemeColors()
{
    switch (config.getTheme())
    {
    case Theme::CLASSIC:
        backgroundColor = sf::Color::Black;
        playerColor = sf::Color::Green;
        enemyColor = sf::Color::Red;
        bulletColor = sf::Color::Yellow;
        break;
    case Theme::NEON:
        backgroundColor = sf::Color(10, 10, 30);
        playerColor = sf::Color::Cyan;
        enemyColor = sf::Color::Magenta;
        bulletColor = sf::Color(0, 255, 0);
        break;
    case Theme::DARK:
        backgroundColor = sf::Color(20, 20, 20);
        playerColor = sf::Color(200, 200, 255);
        enemyColor = sf::Color(255, 100, 100);
        bulletColor = sf::Color(255, 200, 0);
        break;
    }
    
    scoreText.setFillColor(playerColor);
    waveText.setFillColor(playerColor);
    gameOverText.setFillColor(enemyColor);
}

void Game::updateUI()
{
    scoreText.setString("Score: " + std::to_string(score));
    waveText.setString("Wave: " + std::to_string(wave));
}
