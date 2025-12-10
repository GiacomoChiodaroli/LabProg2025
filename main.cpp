#include <SFML/Graphics.hpp>
#include "pg.h"
#include "Mappa.h"
#include <iostream>
//mappa 32x18, 60px per cell
int main()
{
    pg player(100.f,200.f);
    Mappa map;
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(240);
    float mouseX, mouseY;
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
                    mouseX=mouseButtonPressed->position.x;
                    mouseY=mouseButtonPressed->position.y;
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
