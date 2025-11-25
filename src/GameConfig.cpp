#include "GameConfig.h"
#include <fstream>
#include <algorithm>
#include <iostream>

GameConfig::GameConfig()
    : difficulty(Difficulty::MEDIUM), theme(Theme::CLASSIC),
      windowWidth(1200), windowHeight(800)
{
}

void GameConfig::loadConfig(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open config file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '[' || line[0] == '#' || line[0] == ';')
            continue;

        // Find the '=' sign
        size_t pos = line.find('=');
        if (pos == std::string::npos)
            continue;

        std::string key = trimString(line.substr(0, pos));
        std::string value = trimString(line.substr(pos + 1));

        if (key == "Difficulty")
            difficulty = stringToDifficulty(value);
        else if (key == "Theme")
            theme = stringToTheme(value);
        else if (key == "Width")
            windowWidth = std::stoi(value);
        else if (key == "Height")
            windowHeight = std::stoi(value);
    }

    file.close();
}

std::string GameConfig::trimString(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

Difficulty GameConfig::stringToDifficulty(const std::string& str)
{
    if (str == "EASY")
        return Difficulty::EASY;
    else if (str == "HARD")
        return Difficulty::HARD;
    else
        return Difficulty::MEDIUM;
}

Theme GameConfig::stringToTheme(const std::string& str)
{
    if (str == "NEON")
        return Theme::NEON;
    else if (str == "DARK")
        return Theme::DARK;
    else
        return Theme::CLASSIC;
}
