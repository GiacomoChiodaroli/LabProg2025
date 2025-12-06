
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
    Mappa(int width, int height);
    ~Mappa() = default;
};



#endif //MAPPA_H
