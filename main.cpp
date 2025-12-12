#include <SFML/Graphics.hpp>
#include "pg.h"
#include "Mappa.h"
#include <math.h>
#include <iostream>
int main()
{
    pg player(8.f,8.f);
    Mappa map;
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(240);
    int mouseX, mouseY;
    int characterX, characterY;
    bool mousepressed=false;

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                    mouseX=floor(mouseButtonPressed->position.x/60);
                    mouseY=floor(mouseButtonPressed->position.y/60);
                    mousepressed=true;
                }

            }
        }
        if (mousepressed) {
            player.MoveDirection(mouseX, mouseY);
        }

        window.clear();
        map.drawMap( window);
        window.draw(player.character);
        window.display();
    }
}
