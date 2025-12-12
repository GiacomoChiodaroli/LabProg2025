
#include "pg.h"


pg::pg(float x, float y) {
    character.setRadius(20.f);
    character.setPointCount(2*20.f*3);
    character.setFillColor({0, 0, 100});
    character.setPosition({x, y});
}



void pg::MoveDirection(int x, int y) {
    int charx = character.getPosition().x-8;
    int chary = character.getPosition().y-8;
    x=x*60;
    y=y*60;
    float offsetX = 0;
    float offsetY = 0;
    offsetX = (charx < x) ? 1 : (charx > x) ? -1 : 0;
    if (offsetX==0) {
       offsetY = (chary < y) ? 1 : (chary > y) ? -1 : 0;
    }
    character.move({offsetX, offsetY});
}


