
#include "node.h"
#include <map>
#include <SFML/Graphics.hpp>

using namespace std;
#ifndef MAPPA_H
#define MAPPA_H



class Mappa {
private:
    int dimension;
    map<int, node> myMap;
public:
    Mappa(int width, int height) ;
    void draw(sf::RenderWindow window, map<int, node> myMap);
    ~Mappa() = default;
};



#endif //MAPPA_H
