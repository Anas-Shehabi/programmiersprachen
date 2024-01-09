#ifndef PRAKTIKUM_5_GRAPHNODE_H
#define PRAKTIKUM_5_GRAPHNODE_H

#include <vector>
//Die Graphen sind ungerichtet und gewichtet.
class GraphNode 
{
public:
    struct edge 
	{
        GraphNode *startKnoten = nullptr;
        GraphNode *zielKnoten = nullptr;
        int gewicht = 0;
        bool operator()(edge *&lhs, edge *&rhs)
		{
           
			if (lhs->gewicht == rhs->gewicht)
				return lhs->startKnoten->getKey() > rhs->startKnoten->getKey();
			else
				return lhs->gewicht > rhs->gewicht;
        }
    };

    GraphNode(int key);

    int getKey() const;

    void setKey(int value);

    bool getVisited() const;

    void setVisited(bool value);

    void addEdge(edge value);

    edge *getEdge(int value);

    int getNumberOfEdges() const;

    int getComponent() const;

    void setComponent(int value);

    friend void printEdge(edge *edge);

private:
    int _key;
    std::vector<edge> _edges = {};
    bool _visited = false;
    int _component = 0;

};


#endif //PRAKTIKUM_5_GRAPHNODE_H
