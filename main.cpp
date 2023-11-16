/*Copyright 2023 Brandon Nguyen*/
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Crate.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>" << std::endl;
        return 1;
    }
    const std::string levelFileName = argv[1];
    Sokoban sokoban;
    std::ifstream levelFile(levelFileName);
    if (!levelFile) {
        std::cerr << "Failed to open the specified level file." << std::endl;
        return 1;
    }
    levelFile >> sokoban;
    sf::RenderWindow window(sf::VideoMode(sokoban.width() * 64,
    sokoban.height() * 64), "Sokoban Game");

    bool gameWon = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!gameWon && event.type == sf::Event::KeyPressed) {
                Direction direction = Direction::Up;
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        direction = Direction::Up;
                        break;
                    case sf::Keyboard::A:
                        direction = Direction::Left;
                        break;
                    case sf::Keyboard::S:
                        direction = Direction::Down;
                        break;
                    case sf::Keyboard::D:
                        direction = Direction::Right;
                        break;
                    default:
                        break;
                }
                if (!gameWon) {
                    sokoban.movePlayer(direction);
                }
                std::cout << sokoban;
            }

            if (!gameWon && sokoban.isWon()) {
                gameWon = true;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    sokoban.resetLevel();
                    gameWon = false;
                }
            }

            window.clear();
            window.draw(sokoban);
            if (gameWon) {
                sf::Font font;
                font.loadFromFile("arial.ttf");

                sf::Text winText("You Win!", font, 50);
                winText.setFillColor(sf::Color::Green);
                winText.setPosition(100, 100);

                window.draw(winText);
            }
            window.display();
        }
    }
    return 0;
}
