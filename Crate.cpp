/*Copyright 2023 Brandon Nguyen*/
#include <iostream>
#include "Crate.hpp"

Sokoban::Sokoban() {
    if (!Wall.loadFromFile("block_06.png")) {
        std::cerr << "Could not load wall texture" << std::endl;
    }

    if (!Box.loadFromFile("crate_03.png")) {
        std::cerr << "Could not load box texture" << std::endl;
    }

    if (!Empty.loadFromFile("ground_01.png")) {
        std::cerr << "Could not load empty texture" << std::endl;
    }

    if (!Storage.loadFromFile("ground_04.png")) {
        std::cerr << "Could not load storage texture" << std::endl;
    }

    if (!Environment.loadFromFile("environment_03.png")) {
        std::cerr << "Could not load environment texture" << std::endl;
    }

    if (!playerFront.loadFromFile("player_05.png")) {
        std::cerr << "Could not load playerFront texture" << std::endl;
    }
}

int Sokoban::getWindowHeight() const {
    return window_height;
}

int Sokoban::getWindowWidth() const {
    return window_width;
}

void Sokoban::movePlayer(Direction direction) {
    int playerX = -1;
    int playerY = -1;

    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            if (main_game[i][j] == '@') {
                playerY = i;
                playerX = j;
                break;
            }
        }
        if (playerX != -1) {
            break;
        }
    }

    int newX = playerX;
    int newY = playerY;
    switch (direction) {
        case Direction::Up:
            newY--;
            break;
        case Direction::Down:
            newY++;
            break;
        case Direction::Left:
            newX--;
            break;
        case Direction::Right:
            newX++;
            break;
    }

    if (newX >= 0 && newX < width() && newY >= 0 && newY < height()) {
        char targetCell = main_game[newY][newX];

        if (targetCell == '.' || targetCell == 'a') {
            main_game[playerY][playerX] = main_game[playerY][playerX] == '@' ? '.' : 'a';
            main_game[newY][newX] = '@';

            if (og_game[playerY][playerX] == 'a') {
                main_game[playerY][playerX] = 'a';
            }
        } else if (targetCell == 'A') {
            int boxX = newX;
            int boxY = newY;
            switch (direction) {
                case Direction::Up:
                    boxY--;
                    break;
                case Direction::Down:
                    boxY++;
                    break;
                case Direction::Left:
                    boxX--;
                    break;
                case Direction::Right:
                    boxX++;
                    break;
            }

            if (boxX >= 0 && boxX < width() && boxY >= 0 && boxY < height()) {
                char boxTarget = main_game[boxY][boxX];
                if (boxTarget == '.' || boxTarget == 'a') {
                    main_game[playerY][playerX] = main_game[playerY][playerX] == '@' ? '.' : 'a';
                    main_game[newY][newX] = '@';
                    main_game[boxY][boxX] = 'A';

                    if (og_game[playerY][playerX] == 'a') {
                        main_game[playerY][playerX] = 'a';
                    }
                }
            }
        }
    }
}

bool Sokoban::isWon() {
    int crateCount = 0;
    int storageCount = 0;
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            if (og_game[i][j] == 'a') {
                storageCount++;
                if (main_game[i][j] != 'A') {
                    return false;
                }
            }
            if (main_game[i][j] == 'A') {
                crateCount++;
            }
        }
    }
    if (crateCount == storageCount) {
        return true;
    } else if (crateCount == 0 && storageCount > 0) {
        return true;
    } else {
        return false;
    }
}

int Sokoban::width() const {
    return w;
}

void Sokoban::resetLevel() {
    main_game = og_game;
}

int Sokoban::height() const {
    return h;
}

std::istream& operator>>(std::ifstream& input, Sokoban& obj) {
    int width, height;
    input >> height;
    input >> width;
    obj.w = width;
    obj.h = height;

    obj.main_game.resize(height, std::vector<char>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            input >> obj.main_game[i][j];
        }
    }

    obj.og_game = obj.main_game;
    return input;
}

std::ostream& operator<<(std::ostream& out, const Sokoban& obj) {
    for (int i = 0; i < obj.height(); i++) {
        for (int j = 0; j < obj.width(); j++) {
            out << obj.main_game[i][j];
        }
        out << std::endl;
    }
    return out;
}
