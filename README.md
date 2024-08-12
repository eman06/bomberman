# The Legend of Bomberman: A Hero's Journey

## Overview
**The Legend of Bomberman: A Hero's Journey** is a Bomberman game developed using C++ and SFML (Simple and Fast Multimedia Library). Experience a vibrant and explosive maze where you control Bomberman to strategically place bombs, defeat enemies, and uncover hidden exits. The game features both terminal-based and graphical modes with dynamic visuals and animations provided by SFML.

## Features
- **Graphical Display**: Enhanced with SFML for rich graphics and smooth animations.
- **Player Initialization**: Bomberman starts at the top-left corner of the grid.
- **Enemy Initialization**: Enemies are randomly placed on the grid at the start of the game.
- **Bomb Mechanics**: Bombs disappear after 3 seconds with timing managed using `<ctime>`.
- **Movement Controls**: Move Bomberman using up, left, down, right.
- **Bomb Placement**: Place bombs on the current position which explode after a short delay.
- **Grid Display**: Continuously updated to reflect the positions of Bomberman, enemies, and bombs.
- **Object-Oriented Design**: Utilizes inheritance, polymorphism, composition, and aggregation.
  - **Entity**: Abstract base class for common properties and methods.
  - **Player**: Derived from Entity, representing the player.
  - **Enemy**: Derived from Entity, representing enemies.
- **Menu and Save/Load Functionality**: Includes options to start a new game, and exit the game.

## Getting Started

### Prerequisites
- **SFML Library**: Ensure SFML is installed on your system. Follow the [SFML installation guide](https://www.sfml-dev.org/download.php) for setup instructions.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/LegendOfBomberman.git
