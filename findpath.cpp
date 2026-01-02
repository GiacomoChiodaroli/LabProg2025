////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "findpath.h"
#include "Mappa.h"
using namespace std;

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

// Global data



const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 18;
int world_map[MAP_WIDTH * MAP_HEIGHT] = {0};
void MapSearchNode::defineMap(Mappa map) {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 18; j++) {
            world_map[j*MAP_WIDTH+i]= map.getValue(i,j);
        }
    }
}

// map helper functions

int GetMap(int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return 9;
    }

    return world_map[(y * MAP_WIDTH) + x];
}

// Definitions



bool MapSearchNode::IsSameState(MapSearchNode& rhs) {
    // same state in a maze search is simply when (x,y) are the same
    if ((x == rhs.x) && (y == rhs.y)) {
        return true;
    } else {
        return false;
    }
}

size_t MapSearchNode::Hash() {
    size_t h1 = hash<float>{}(x);
    size_t h2 = hash<float>{}(y);
    return h1 ^ (h2 << 1);
}

void MapSearchNode::PrintNodeInfo() {
    const int strSize = 100;
    char str[strSize];
    snprintf(str, strSize, "Node position : (%d,%d)\n", x, y);

    cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate(MapSearchNode& nodeGoal) {
    return abs(x - nodeGoal.x) + abs(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal(MapSearchNode& nodeGoal) {
    if ((x == nodeGoal.x) && (y == nodeGoal.y)) {
        return true;
    }

    return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors(
    AStarSearch<MapSearchNode>* astarsearch, MapSearchNode* parent_node) {
    int parent_x = -1;
    int parent_y = -1;

    if (parent_node) {
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }

    MapSearchNode NewNode;

    // push each possible move except allowing the search to go backwards

    if ((GetMap(x - 1, y) < 9) && !((parent_x == x - 1) && (parent_y == y))) {
        NewNode = MapSearchNode(x - 1, y);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((GetMap(x, y - 1) < 9) && !((parent_x == x) && (parent_y == y - 1))) {
        NewNode = MapSearchNode(x, y - 1);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((GetMap(x + 1, y) < 9) && !((parent_x == x + 1) && (parent_y == y))) {
        NewNode = MapSearchNode(x + 1, y);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((GetMap(x, y + 1) < 9) && !((parent_x == x) && (parent_y == y + 1))) {
        NewNode = MapSearchNode(x, y + 1);
        astarsearch->AddSuccessor(NewNode);
    }

    return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost(MapSearchNode& successor) {
    return (float)GetMap(x, y);
}


bool MapSearchNode::pathsearch(MapSearchNode nodeStart, MapSearchNode nodeEnd, std::vector<sf::Vector2i>& path) {
    // Our sample problem defines the world as a 2d array representing a terrain
    // Each element contains an integer from 0 to 5 which indicates the cost
    // of travel across the terrain. Zero means the least possible difficulty
    // in travelling (think ice rink if you can skate) whilst 5 represents the
    // most difficult. 9 indicates that we cannot pass.

    // Create an instance of the search class...
    path.clear();
    AStarSearch<MapSearchNode> astarsearch;
    bool succed=false;

    unsigned int SearchCount = 0;

    const unsigned int NumSearches = 1;

    while (SearchCount < NumSearches) {

        astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

        unsigned int SearchState;
        unsigned int SearchSteps = 0;

        do {
            SearchState = astarsearch.SearchStep();

            SearchSteps++;

#if DEBUG_LISTS

            cout << "Steps:" << SearchSteps << "\n";

            int len = 0;

            cout << "Open:\n";
            MapSearchNode* p = astarsearch.GetOpenListStart();
            while (p) {
                len++;
#if !DEBUG_LIST_LENGTHS_ONLY
                ((MapSearchNode*)p)->PrintNodeInfo();
#endif
                p = astarsearch.GetOpenListNext();
            }

            cout << "Open list has " << len << " nodes\n";

            len = 0;

            cout << "Closed:\n";
            p = astarsearch.GetClosedListStart();
            while (p) {
                len++;
#if !DEBUG_LIST_LENGTHS_ONLY
                p->PrintNodeInfo();
#endif
                p = astarsearch.GetClosedListNext();
            }

            cout << "Closed list has " << len << " nodes\n";
#endif

        } while (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

        if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED) {
            cout << "Search found goal state\n";
            succed = true;
            MapSearchNode* node = astarsearch.GetSolutionStart();

#if DISPLAY_SOLUTION
            cout << "Displaying solution\n";
#endif
            int steps = 0;

            node->PrintNodeInfo();
            for (;;) {
                node = astarsearch.GetSolutionNext();
                if (!node) {
                    break;
                }
                path.push_back(sf::Vector2i(node->x, node->y));
                node->PrintNodeInfo();
                steps++;
            };

            cout << "Solution steps " << steps << endl;

            // Once you're done with the solution you can free the nodes up
            astarsearch.FreeSolutionNodes();

        } else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED) {
            cout << "Search terminated. Did not find goal state\n";
            succed = false;
        }

        // Display the number of loops the search went through
        cout << "SearchSteps : " << SearchSteps << "\n";

        SearchCount++;

        astarsearch.EnsureMemoryFreed();
    }

    return succed;
}