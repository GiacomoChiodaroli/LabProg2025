#include <SFML/Graphics.hpp>
#include "pg.h"
#include "Mappa.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <iostream>
#include "findpath.cpp"

// riadattare le righ 139-158 in findpath.cpp per usare la mappa creata dalla classe



int main() {
    int mouseX, mouseY;
    int characterX, characterY;
    bool mousepressed=false;
    srand(time(0));
    int randX=rand() % 32, randY=rand() % 18;
    Mappa map;
    MapSearchNode nodeStart;
    MapSearchNode nodeEnd;
    AStarSearch<MapSearchNode> astarsearch;
    unsigned int SearchState;
    unsigned int SearchSteps = 0;
    while (map.getValue(randX,randY)==999) {
        randX=rand() % 32;
        randY=rand() % 18;
    }
    pg player(randX*60.f,randY*60.f);
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(240);


    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                    mouseX=floor(mouseButtonPressed->position.x/60);
                    mouseY=floor(mouseButtonPressed->position.y/60);
                    mousepressed=true;
                    nodeEnd.x = mouseX;
                    nodeEnd.y = mouseY;
                    nodeStart.x = player.getX();
                    nodeStart.y = player.getY();
                    astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);
                   /* do {
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

                    } while (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);*/
                }

            }
        }
        if (mousepressed) {
            player.MoveDirection(mouseX, mouseY);
            /*if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED) {
                cout << "Search found goal state\n";

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

                    node->PrintNodeInfo();
                    steps++;
                };

                cout << "Solution steps " << steps << endl;

                // Once you're done with the solution you can free the nodes up
                astarsearch.FreeSolutionNodes();

            } else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED) {
                cout << "Search terminated. Did not find goal state\n";
            }

            // Display the number of loops the search went through
            cout << "SearchSteps : " << SearchSteps << "\n";
            astarsearch.EnsureMemoryFreed();*/
        }
        }

        window.clear();
        map.drawMap( window);
        window.draw(player.character);
        window.display();
    }



