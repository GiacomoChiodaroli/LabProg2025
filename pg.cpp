
#include "pg.h"


pg::pg(float x, float y) {
    character.setRadius(15.f);
    character.setPointCount(2*15.f*3);
    character.setFillColor({89, 255, 205});
    character.setPosition({x, y});
}



void pg::MoveDirection(float x, float y) {
    int charx = character.getPosition().x;
    int chary = character.getPosition().y;
    float offsetX = 0;
    float offsetY = 0;
    offsetX = (x > charx) ? 1 : (x < charx) ? -1 : 0;
    offsetY = (y > chary) ? 1 : (y < chary) ? -1 : 0;
    character.move({offsetX, offsetY});
}


