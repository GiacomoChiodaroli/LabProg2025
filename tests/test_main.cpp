#include <gtest/gtest.h>
#include "../findpath.h"
#include "../pg.h"


TEST(pgTest, PosizioneIniziale) {
    pg g(8,8);
    EXPECT_FLOAT_EQ(g.getX(), 8.f);
    EXPECT_FLOAT_EQ(g.getY(), 8.f);
}

TEST(pgTest, Movimento) {
    pg g(8,8);
    for (int i=0;i<130;i++) {
        g.MoveDirection(1,1);
    }
    EXPECT_FLOAT_EQ(g.getX(), 68.f);
    EXPECT_FLOAT_EQ(g.getY(), 68.f);

}

TEST(findpathTest, RicercaPercorso) {
    Mappa map;
    MapSearchNode::defineMap(map);
    std::vector<sf::Vector2i> path;
    MapSearchNode nodeStart;
    nodeStart.x=1;
    nodeStart.y=1;
    MapSearchNode nodeEnd;
    nodeEnd.x=5;
    nodeEnd.y=5;
    EXPECT_TRUE(MapSearchNode::pathsearch(nodeStart, nodeEnd, path));
    nodeEnd.x=4;
    nodeEnd.y=4;
    EXPECT_FALSE(MapSearchNode::pathsearch(nodeStart, nodeEnd, path));
    EXPECT_TRUE(path.empty())<<"path non è vuoto";
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}