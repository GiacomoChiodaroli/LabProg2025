
#include "node.h"
#include <map>
#include <SFML/Graphics.hpp>

using namespace std;
#ifndef MAPPA_H
#define MAPPA_H



class Mappa {
private:

    int width;
    int height;
    bool myMap [32][18];
public:
    explicit Mappa();
    void drawMap(sf::RenderWindow &window);
    ~Mappa() = default;
};



#endif //MAPPA_H
