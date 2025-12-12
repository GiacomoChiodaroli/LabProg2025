#include "Mappa.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#ifndef PG_H
#define PG_H



class pg {
public:
    sf::CircleShape character;
    explicit pg(float x, float y);
    void MoveDirection(int x, int y);

};



#endif
