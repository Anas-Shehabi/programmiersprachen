#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <queue>


Graph::~Graph() 
{
    for (auto &_node : _nodes)
        delete _node;
}

bool Graph::init( std::string path)
{
    std::ifstream file;
    file.open(path, std::ios_base::in);
    if (!file)
	{
        std::cout << "Cannot open file." << std::endl;
        return false;
    }
	else 
	{
        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);

        iss >> _anzKnoten; //Erste Zeile Auslesen
		//Alle Knoten anlegen
        for (int i = 0; i < _anzKnoten; i++) 
		{
            GraphNode *newNode = new GraphNode{i};
            _nodes.push_back(newNode);
        }
		//Alle Kanten anlegen
        while (std::getline(file, line)) 
		{
            std::istringstream edgeLine(line);
            int startKnotenKey;
            int zielKnotenKey;
            int gewicht;
            edgeLine >> startKnotenKey >> zielKnotenKey >> gewicht;
            GraphNode *startKnoten = GetNodeByKey(startKnotenKey);
            GraphNode *zielKnoten = GetNodeByKey(zielKnotenKey);
            //Hin- und Rückkanten
            GraphNode::edge edge{startKnoten, zielKnoten, gewicht};
            startKnoten->addEdge(edge);
            edge = {zielKnoten, startKnoten, gewicht};
            zielKnoten->addEdge(edge);
        }
        return true;
    }
}

bool Graph::printAll() 
{
    for (auto &_node : _nodes) 
	{
        std::cout << std::setw(3) << _node->getKey() << std::setw(5);
        for (int j = 0; j < _node->getNumberOfEdges(); ++j)
		{
            std::cout << " -> " << std::setw(2) << _node->getEdge(j)->zielKnoten->getKey() << '['
                      << std::setw(2) << _node->getEdge(j)->gewicht << ']';
        }
        std::cout << std::endl;
    }
    return true;
}

bool Graph::depthSearchRek(int startKey) 
{
    setAllUnvisited();
    std::cout << "[ ";
    startDepthSearchRek(GetNodeByKey(startKey));
    std::cout << "]" << std::endl;
    return checkVisited();
}

void Graph::startDepthSearchRek(GraphNode *node) 
{
    node->setVisited(true);
    std::cout << node->getKey() << ' ';
    for (int i = 0; i < node->getNumberOfEdges(); ++i)
	{
        if (!node->getEdge(i)->zielKnoten->getVisited())
            startDepthSearchRek(node->getEdge(i)->zielKnoten);
    }
}


bool Graph::breadthSearchIter(int startKey) 
{
    setAllUnvisited();
    std::queue<GraphNode *> nodesQueue;
    nodesQueue.push(GetNodeByKey(startKey));
    std::cout << "[ ";
    while (!nodesQueue.empty()) 
	{
        GraphNode *frontNode = nodesQueue.front();
        if (!frontNode->getVisited())
			std::cout << frontNode->getKey() << ' ';
        frontNode->setVisited(true);

        nodesQueue.pop();
        for (int i = 0; i < frontNode->getNumberOfEdges(); ++i)
		{
            if (!frontNode->getEdge(i)->zielKnoten->getVisited())
                nodesQueue.push(frontNode->getEdge(i)->zielKnoten);
        }

    }
    std::cout << "]" << std::endl;
    return checkVisited();
}

double Graph::prim(int startKey) 
{
    setAllUnvisited();
    double mstKosten = 0;

    std::priority_queue<GraphNode::edge *, std::vector<GraphNode::edge *>, GraphNode::edge> edgesQueue;// aufsteigend sortierung für die elemente in der queue
	
    GraphNode *startKnoten = GetNodeByKey(startKey);

    for (int i = 0; i < startKnoten->getNumberOfEdges(); ++i)
        edgesQueue.push(startKnoten->getEdge(i));

    startKnoten->setVisited(true);

    while (!edgesQueue.empty())
	{
        GraphNode::edge *topEdge = edgesQueue.top();
        edgesQueue.pop();

        if (!topEdge->zielKnoten->getVisited())
		{
            for (int i = 0; i < topEdge->zielKnoten->getNumberOfEdges(); ++i) 
			{
                if (!topEdge->zielKnoten->getEdge(i)->zielKnoten->getVisited())
                    edgesQueue.push(topEdge->zielKnoten->getEdge(i));
            }
            topEdge->zielKnoten->setVisited(true);
            printEdge(topEdge);
            mstKosten += topEdge->gewicht;
        }
    }
    std::cout << "MST Kosten : " << mstKosten << std::endl;
    return mstKosten;
}

double Graph::kruskal() 
{
    double mstKosten = 0;
    std::queue<GraphNode::edge *> mstEdges;
    std::priority_queue<GraphNode::edge *, std::vector<GraphNode::edge *>, GraphNode::edge> edgesQueue;

    for (int i = 0; i < _anzKnoten; i++) 
	{
        _nodes[i]->setComponent(i);
        for (int j = 0; j < _nodes[i]->getNumberOfEdges(); ++j)
            edgesQueue.push(_nodes[i]->getEdge(j));
    }

    while (!edgesQueue.empty() && mstEdges.size() < _anzKnoten - 1) 
	{
        GraphNode::edge *topEdge = edgesQueue.top();
        edgesQueue.pop();
        GraphNode *v = topEdge->startKnoten;
        GraphNode *w = topEdge->zielKnoten;

        if (v->getComponent() != w->getComponent()) 
		{
            mstKosten += topEdge->gewicht;
            printEdge(topEdge);
            mstEdges.push(topEdge);

            int w_Component = w->getComponent();

            for (auto &_node : _nodes)
                if (_node->getComponent() == w_Component) 
                    _node->setComponent(v->getComponent());
        }

    }
    std::cout << "MST Kosten : " << mstKosten << std::endl;
    return mstKosten;
}


int Graph::getAnzKnoten() const {
    return _anzKnoten;
}

GraphNode *Graph::GetNodeByKey(int key) {
    for (auto &_node : _nodes)
        if (_node->getKey() == key) return _node;
    return nullptr;
}

void Graph::setAllUnvisited() {
    for (auto &_node : _nodes)
        _node->setVisited(false);
}

bool Graph::checkVisited() {
    for (auto &_node : _nodes)
        if (!_node->getVisited()) return false;
    return true;
}

bool Graph::testChildComponent(GraphNode *node) {
    return true;
}
