
#include <math.h>
#include <stdio.h>
#include <vector>

#include <iostream>
#include "Mappa.h"

#include "stlastar.h"  // See header for copyright and usage information
#include "SFML/System/Vector2.hpp"

#ifndef FINDPATH_H
#define FINDPATH_H
class MapSearchNode {
public:
    int x;  // the (x,y) positions of the node
    int y;

    MapSearchNode() {
        x = y = 0;
    }
    MapSearchNode(int px, int py) {
        x = px;
        y = py;
    }
    static void defineMap(Mappa map);
    static void drawPath(std::vector<sf::Vector2i>& path,sf::RenderWindow &window);
    float GoalDistanceEstimate(MapSearchNode& nodeGoal);
    bool IsGoal(MapSearchNode& nodeGoal);
    bool GetSuccessors(AStarSearch<MapSearchNode>* astarsearch, MapSearchNode* parent_node);
    float GetCost(MapSearchNode& successor);
    bool IsSameState(MapSearchNode& rhs);
    size_t Hash();
    void PrintNodeInfo();
    static bool pathsearch( MapSearchNode nodeStart, MapSearchNode nodeEnd, std::vector<sf::Vector2i>& path);

};

#endif //FINDPATH_H
