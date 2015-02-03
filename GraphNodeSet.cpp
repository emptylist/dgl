#include "GraphNodeSet.hpp"
#include <iostream>

GraphNodeSet::GraphNodeSet(GraphNodeParameters& p, sf::RenderWindow& w, sf::Vector2f& o)
	: parameters(&p), window(&w), origin(o) {}

void GraphNodeSet::createNode(float r, float x, float y) {
	nodeList.push_back(new GraphNode(r, 
															origin, 
															*window, 
															*parameters, 
															this,
															x,
															y));

}

void GraphNodeSet::addBond(Bond& b) {
	bondList.push_back(&b);
}

void GraphNodeSet::update(float ts) {
	for (auto node = nodeList.begin(); node < nodeList.end(); node++) {
		(*node)->updateVelocity(ts);
	}

	for (auto node = nodeList.begin(); node < nodeList.end(); node++) {
		(*node)->updatePosition(ts);
	}
}

void GraphNodeSet::draw() {
	for(auto bondptr = bondList.begin(); bondptr < bondList.end(); bondptr++) {
		(*bondptr)->draw();
	}
	
	for(auto node = nodeList.begin(); node < nodeList.end(); node++) {
		(*node)->draw();
	}
}

std::vector<GraphNode *>::iterator GraphNodeSet::begin() {
	return nodeList.begin();
}

std::vector<GraphNode *>::iterator GraphNodeSet::end() {
	return nodeList.end();
}

GraphNode& GraphNodeSet::operator[](std::size_t idx) {
	return *(nodeList[idx]);
}