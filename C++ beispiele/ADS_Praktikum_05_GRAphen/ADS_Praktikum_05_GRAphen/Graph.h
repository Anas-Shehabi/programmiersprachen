#ifndef PRAKTIKUM_5_GRAPH_H
#define PRAKTIKUM_5_GRAPH_H

#include "GraphNode.h"
#include <string>

class Graph {
private:
    int _anzKnoten = 0;
    bool _ger = false;
    bool _gew = true;
    std::vector<GraphNode *> _nodes;

public:
	Graph() {};

    ~Graph();

    bool init(std::string file);

    bool printAll();

    bool depthSearchRek(int startKey);

    bool breadthSearchIter(int startKey);

    double prim(int startKey);

    double kruskal();

    int getAnzKnoten() const;

private:
    GraphNode *GetNodeByKey(int key);

    void setAllUnvisited();

    bool checkVisited();

    void startDepthSearchRek(GraphNode *node);

    bool testChildComponent(GraphNode *node);


};


#endif //PRAKTIKUM_5_GRAPH_H
