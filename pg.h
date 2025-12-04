#include "Mappa.h"
#ifndef PG_H
#define PG_H



class pg {
private:
    int x;
    int y;
public:
    void move(int x, int y);
    int getX();
    int getY();
    void draw();
};



#endif
