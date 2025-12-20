
#include <math.h>
#include <stdio.h>
#include <vector>

#include <iostream>
#include "Mappa.h"

#include "stlastar.h"  // See header for copyright and usage information

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
    float GoalDistanceEstimate(MapSearchNode& nodeGoal);
    bool IsGoal(MapSearchNode& nodeGoal);
    bool GetSuccessors(AStarSearch<MapSearchNode>* astarsearch, MapSearchNode* parent_node);
    float GetCost(MapSearchNode& successor);
    bool IsSameState(MapSearchNode& rhs);
    size_t Hash();
    void PrintNodeInfo();
    //int pathsearch( MapSearchNode nodeStart, MapSearchNode nodeEnd, std::vector<sf::Vector2i>& path);
};

#endif //FINDPATH_H
