#pragma once

#include <string>
#include <unordered_map>

enum class Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

enum class Theme
{
    CLASSIC,
    NEON,
    DARK
};

class GameConfig
{
public:
    GameConfig();
    
    void loadConfig(const std::string& filename);
    
    Difficulty getDifficulty() const { return difficulty; }
    Theme getTheme() const { return theme; }
    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }
    
    void setDifficulty(Difficulty d) { difficulty = d; }
    void setTheme(Theme t) { theme = t; }
    
private:
    Difficulty difficulty;
    Theme theme;
    int windowWidth;
    int windowHeight;
    
    std::string trimString(const std::string& str);
    Difficulty stringToDifficulty(const std::string& str);
    Theme stringToTheme(const std::string& str);
};
