#include "GraphNode.h"
#include <iostream>
#include <iomanip>

GraphNode::GraphNode(int key) : _key{key} {}

int GraphNode::getKey() const {
    return _key;
}

void GraphNode::setKey(int value) {
    _key = value;
}

bool GraphNode::getVisited() const {
    return _visited;
}

void GraphNode::setVisited(bool value) {
    _visited = value;
}

void GraphNode::addEdge(GraphNode::edge value) {
    _edges.push_back(value);
}

GraphNode::edge *GraphNode::getEdge(int value) {
    return &_edges[value];
}

int GraphNode::getNumberOfEdges() const {
    return _edges.size();
}

int GraphNode::getComponent() const {
    return _component;
}

void GraphNode::setComponent(int value) {
    _component = value;
}

void printEdge(GraphNode::edge *edge) {
    std::cout << "( " << std::setw(2) << edge->startKnoten->getKey() << " , " << std::setw(2)
              << edge->zielKnoten->getKey() << " | " << std::setw(2) << edge->gewicht
              << " )" << std::endl;

}



