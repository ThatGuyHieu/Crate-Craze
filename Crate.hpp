/*Copyright 2023 Brandon Nguyen*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum Direction {
    Up,
    Down,
    Left,
    Right
};

class Sokoban: public sf::Drawable {
 public:
    Sokoban();
    int width() const;
    int height() const;
    int getWindowHeight() const;
    int getWindowWidth() const;
    bool isWon();
    void resetLevel();
    friend std::istream & operator >> (std::ifstream &input, Sokoban &obj);
    friend std::ostream & operator << (std::ostream &out, const Sokoban &obj);
    void movePlayer(Direction direction);

 protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            sf::Sprite sprite;
            if (main_game[i][j] == '@') {
                sf::Sprite floor;
                floor.setTexture(Empty);
                floor.setPosition(j * 64, i * 64);
                target.draw(floor, states);

                sprite.setTexture(playerFront);
            } else if (main_game[i][j] == '.') {
                sprite.setTexture(Empty);
            } else if (main_game[i][j] == '#') {
                sprite.setTexture(Wall);
            } else if (main_game[i][j] == 'A') {
                sprite.setTexture(Box);
            } else if (main_game[i][j] == 'a') {
                sprite.setTexture(Storage);
            } else {
            }

            sprite.setPosition(j * 64, i * 64);
            target.draw(sprite, states);
        }
    }
}

 private:
    int w, window_width;
    int h, window_height;
    sf::Texture Wall;
    sf::Texture Box;
    sf::Texture Empty;
    sf::Texture Storage;
    sf::Texture Environment;
    sf::Texture playerFront;
    std::vector<std::vector<char>> main_game;
    std::vector<std::vector<char>> og_game;
};
