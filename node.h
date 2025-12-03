
#ifndef NODE_H
#define NODE_H



class node {
private:
    bool walkable;
public:
    explicit node(bool walkable)
        : walkable(walkable) {
    }

    ~node() = default;
};



#endif //NODE_H
