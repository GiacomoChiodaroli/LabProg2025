
#include "node.h"
#include <map>
#include <SFML/Graphics.hpp>

using namespace std;
#ifndef MAPPA_H
#define MAPPA_H



class Mappa {
private:
    int myMap [32][18];
public:
    explicit Mappa();
    void drawMap(sf::RenderWindow &window);
    int getValue(int x, int y);
    ~Mappa() = default;
};



#endif //MAPPA_H
