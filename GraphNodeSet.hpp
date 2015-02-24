#ifndef __DGL_GRAPH_NODE_SET_H__
#define __DGL_GRAPH_NODE_SET_H__

#include <cstddef>
#include <vector>
#include <iostream>
#include "GraphNode.hpp"
#include "GraphNodeParameters.hpp"
#include "Bond.hpp"

class GraphNode;
class Bond;

class GraphNodeSet {
private:
	std::vector<GraphNode *> nodeList;
	std::vector<Bond *> bondList;
	GraphNodeParameters * parameters;
	sf::RenderWindow * window;
	sf::Vector2f origin;

	GraphNodeSet();
	friend std::ostream& operator<<(std::ostream&, const GraphNodeSet&);

public:
	GraphNodeSet(GraphNodeParameters&, sf::RenderWindow&, sf::Vector2f&);
	void createNode(float r, float x = 0.f, float y = 0.f);
	void addBond(Bond&);
	void update(float);
	void draw();
	std::vector<GraphNode *>::iterator begin();
	std::vector<GraphNode *>::iterator end();
	GraphNode& operator[](std::size_t);
	void writeAsSVG(std::ostream&);
	GraphNodeParameters& params() { return *parameters; };
};

#endif