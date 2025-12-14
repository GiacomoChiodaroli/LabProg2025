#include <SFML/Graphics.hpp>
#include "pg.h"
#include "Mappa.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <iostream>
#include "findpath.h"

int main() {
    int mouseX=0, mouseY=0;
    bool canmove=false;
    srand(time(0));
    int randX=rand() % 32, randY=rand() % 18;
    Mappa map;
    AStarSearch<MapSearchNode> astarsearch;
    unsigned int SearchState;
    unsigned int SearchSteps = 0;
    while (map.getValue(randX,randY)==999) {
        randX=rand() % 32;
        randY=rand() % 18;
    }
//
    pg player(randX*60.f,randY*60.f);
    MapSearchNode nodeStart;
    MapSearchNode nodeEnd;
    MapSearchNode* node;
    nodeStart.x = player.getX();
    nodeStart.y = player.getY();
    nodeEnd.x = mouseX;
    nodeEnd.y = mouseY;
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(240);
    MapSearchNode::defineMap(map);
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
                astarsearch.EnsureMemoryFreed();
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                    mouseX=floor(mouseButtonPressed->position.x/60);
                    mouseY=floor(mouseButtonPressed->position.y/60);
                    nodeEnd.x = mouseX;
                    nodeEnd.y = mouseY;
                    nodeStart.x = floor(player.getX()/60);
                    nodeStart.y = floor(player.getY()/60);
                    astarsearch.SetStartAndGoalStates(nodeStart,nodeEnd);
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
                        canmove = true;
                        cout << "Search found goal state\n";

                        node = astarsearch.GetSolutionStart();

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

                            node->PrintNodeInfo();
                            steps++;
                        };

                        cout << "Solution steps " << steps << endl;
                        steps = 0;
                        node = astarsearch.GetSolutionStart();

                        // Once you're done with the solution you can free the nodes up
                        //astarsearch.FreeSolutionNodes();

                    } else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED) {
                        canmove = false;
                        cout << "Search terminated. Did not find goal state\n";
                    }

                    // Display the number of loops the search went through
                    cout << "SearchSteps : " << SearchSteps << "\n";

                }

            }
        }
        if (canmove) {
            player.MoveDirection(node->x, node->y);
            if (node->x*60+8==player.getX() && node->y*60+8==player.getY()) {
                node = astarsearch.GetSolutionNext();
                if (!node) {
                    astarsearch.FreeSolutionNodes();
                    canmove = false;
                }
            }
        }


            window.clear();
            map.drawMap( window);
            window.draw(player.character);
            window.display();
        }
    }


