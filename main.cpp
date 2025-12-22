#include <SFML/Graphics.hpp>
#include "pg.h"
#include "Mappa.h"
#include "findpath.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <iostream>
#include <vector>
//file note per controllare i metodi necessari

int main() {
    int mouseX=0, mouseY=0;
    bool canmove=false;
    srand(time(0));
    int randX=rand() % 32, randY=rand() % 18;
    Mappa map;
    std::vector<sf::Vector2i> path;
    while (map.getValue(randX,randY)==999) {
        randX=rand() % 32;
        randY=rand() % 18;
    }
    pg player(randX*60.f,randY*60.f);
    MapSearchNode nodeStart;
    MapSearchNode nodeEnd;
    //MapSearchNode* node;
    nodeStart.x = player.getX();
    nodeStart.y = player.getY();
    nodeEnd.x = mouseX;
    nodeEnd.y = mouseY;
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(240);
    MapSearchNode::defineMap(map);
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseButtonPressed->button == sf::Mouse::Button::Right && map.getValue(floor(mouseButtonPressed->position.x/60),floor(mouseButtonPressed->position.y/60))!=999) {
                    mouseX=floor(mouseButtonPressed->position.x/60);
                    mouseY=floor(mouseButtonPressed->position.y/60);
                    nodeEnd.x = mouseX;
                    nodeEnd.y = mouseY;
                    nodeStart.x = floor(player.getX()/60);
                    nodeStart.y = floor(player.getY()/60);
                    cout << "ciao";
                    canmove = MapSearchNode::pathsearch(nodeStart, nodeEnd, path);
                }

            }
        }
        if (canmove) {
            sf::Vector2i target = path.front();
            player.MoveDirection(target.x, target.y);
            if (target.x*60+8==player.getX() && target.y*60+8==player.getY()) {
                path.erase(path.begin());
                if (path.empty()) {
                    canmove = false;
                }

            }
        }


            window.clear();
            map.drawMap( window);
            window.draw(player.character);
            window.display();
        }
    }

