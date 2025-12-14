
#include "Mappa.h"
#include "node.h"
Mappa::Mappa(): myMap{} {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 18; j++) {

            myMap[i][j] = 1;
        }
    }
    for (int i = 0; i < 32; i=i+4) {
        for (int j = 0; j < 18; j=j+2) {

            myMap[i][j] = 999;
        }
    }
    for (int j = 1; j < 9; j=j+2) {
        myMap[4][j] = 999;
    }

};

int Mappa::getValue(int x, int y) {
    if (x < 0 || x >= 32 || y < 0 || y >= 18) {
        return 999;
    }
    return myMap[x][y];
}

void Mappa::drawMap(sf::RenderWindow &window) {
    sf::CircleShape square(30.f*1.41, 4);
    square.setRotation(sf::degrees(45));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(4.f);
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 18; j++) {
            if (myMap[i][j]==1) {
                square.setFillColor({120,120,120});
            } else {
                square.setFillColor(sf::Color::Black);
            }
            square.setPosition({i * 60.f+30, j * 60.f-30});
            window.draw(square);
        }
    }
}