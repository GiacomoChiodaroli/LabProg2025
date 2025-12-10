
#include "Mappa.h"
#include "node.h"
Mappa::Mappa(): myMap{} {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 18; j++) {
            myMap[i][j] = true;
        }
    }
} ;

void Mappa::drawMap(sf::RenderWindow &window) {
    sf::CircleShape square(30.f*1.41, 4);
    square.setRotation(sf::degrees(45));
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 18; j++) {
            if (myMap[i][j]) {
                square.setFillColor({120,120,120});
            } else {
                square.setFillColor(sf::Color::Black);
            }
            square.setPosition({i * 60.f+30, j * 60.f-30});
            window.draw(square);
        }
    }
}