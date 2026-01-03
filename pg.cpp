
#include "pg.h"


pg::pg(float x, float y) {
    character.setRadius(20.f);
    character.setPointCount(2*20.f*3);
    character.setFillColor({0, 0, 100});
    character.setPosition({x, y});
}
float pg::getX() {
    return character.getPosition().x;
};
float pg::getY() {
    return character.getPosition().y;
};


void pg::MoveDirection(int x, int y,Mappa map) {
    int charx = character.getPosition().x-8;
    int chary = character.getPosition().y-8;
    x=x*60;
    y=y*60;
    float offsetX = 0;
    float offsetY = 0;
    offsetX = (charx < x) ? 5/map.getValue(x/60,y/60) : (charx > x) ? -5/map.getValue(x/60,y/60) : 0;
    if (offsetX==0) {
       offsetY = (chary < y) ? 5/map.getValue(x/60,y/60) : (chary > y) ? -5/map.getValue(x/60,y/60) : 0;
    }
    character.move({offsetX, offsetY});
}


