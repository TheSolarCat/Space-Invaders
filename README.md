# Space Invaders - C++ Arcade Game

A classic Space Invaders arcade game built with C++ and SFML (Simple and Fast Multimedia Library).

## Features

- **Customizable Difficulty**: Choose between Easy, Medium, and Hard modes
- **Theme Colors**: Select from Classic, Neon, and Dark color schemes
- **Keyboard Controls**: 
  - Arrow Keys: Move your spaceship (Up, Down, Left, Right)
  - Spacebar: Shoot
- **Wave System**: Difficulty increases with each wave
- **Score Tracking**: Keep track of your score and current wave

## Requirements

- C++17 or later
- SFML 2.5 or later
- CMake 3.10 or later
- Windows, Linux, or macOS

## Installation

### Windows

1. Install SFML:
   - Download from: https://www.sfml-dev.org/
   - Extract to a known location

2. Clone or download this project

3. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

4. Configure CMake (update SFML_DIR path):
   ```bash
   cmake .. -DSFML_DIR="C:/path/to/SFML/lib/cmake/SFML"
   ```

5. Build:
   ```bash
   cmake --build . --config Release
   ```

6. Run:
   ```bash
   ./SpaceInvaders.exe
   ```

### Linux

1. Install SFML and development tools:
   ```bash
   sudo apt-get install libsfml-dev cmake g++
   ```

2. Build and run:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ./SpaceInvaders
   ```

### macOS

1. Install SFML using Homebrew:
   ```bash
   brew install sfml cmake
   ```

2. Build and run:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ./SpaceInvaders
   ```

## How to Play

### Main Menu
- **E**: Select Easy difficulty
- **D**: Select Medium difficulty
- **H**: Select Hard difficulty
- **1**: Select Classic theme (Black background, Green player)
- **2**: Select Neon theme (Cyan player, Magenta enemies)
- **3**: Select Dark theme (Dark background, Light colors)
- **M**: Start the game

### In-Game
- **Arrow Keys**: Move your spaceship
- **Spacebar**: Shoot at enemies
- **R**: Restart (when game is over)

## Game Mechanics

- **Enemies**: Spawn from the top and move side to side, increasing in speed with difficulty
- **Scoring**: Each destroyed enemy gives 10 points
- **Waves**: After clearing all enemies, the next wave begins with more enemies
- **Difficulty Scaling**:
  - **Easy**: Slower enemies, fewer spawn
  - **Medium**: Standard speed and spawn rate
  - **Hard**: Faster enemies with more health, higher spawn rate
- **Game Over**: Touch an enemy to end the game

## Configuration

Edit `config.ini` to customize game settings:

```ini
[Game]
Difficulty=MEDIUM  # EASY, MEDIUM, or HARD

[Theme]
Theme=CLASSIC      # CLASSIC, NEON, or DARK

[Window]
Width=1200
Height=800
```

## Project Structure

```
Space Invaders/
├── CMakeLists.txt          # Build configuration
├── config.ini              # Game configuration
├── README.md               # This file
├── include/                # Header files
│   ├── Game.h
│   ├── Player.h
│   ├── Enemy.h
│   ├── Bullet.h
│   └── GameConfig.h
└── src/                    # Source files
    ├── main.cpp
    ├── Game.cpp
    ├── Player.cpp
    ├── Enemy.cpp
    ├── Bullet.cpp
    └── GameConfig.cpp
```

## Controls Summary

| Key | Action |
|-----|--------|
| Arrow Left | Move left |
| Arrow Right | Move right |
| Arrow Up | Move up |
| Arrow Down | Move down |
| Spacebar | Shoot |
| E | Easy mode (menu) |
| D | Medium mode (menu) |
| H | Hard mode (menu) |
| 1 | Classic theme (menu) |
| 2 | Neon theme (menu) |
| 3 | Dark theme (menu) |
| M | Start game (menu) |
| R | Restart (game over) |

## Future Enhancements

- Sound effects and background music
- Power-ups and special weapons
- High score persistence
- Multiple lives system
- Pause functionality
- Enemy formation patterns
- Bonus stages

## License

This is a personal project for educational purposes.

## Troubleshooting

### Build Errors
- Ensure SFML is properly installed and CMake can find it
- Verify C++17 support in your compiler
- Update CMake path if SFML location changes

### Runtime Issues
- Ensure config.ini is in the same directory as the executable
- Check font file availability (arial.ttf is attempted to load)
- Verify keyboard input is working

## Author

Created as a classic arcade game implementation.
