#include "GraphNode.hpp"

GraphNode::GraphNode(float radius, sf::Vector2f &orig, sf::RenderWindow &window, 
	  float friction, unsigned int x, unsigned int y) {
  v = sf::CircleShape(radius);
  w = &window;
  v.setPosition(x, y);
  origin = &orig;
  gravity = sf::Vector2f(0.f, 0.f);
  electrostatic = sf::Vector2f(0.f, 0.f);
  bonded = sf::Vector2f(0.f, 0.f);
  forces = sf::Vector2f(0.f, 0.f);
}

GraphNode::~GraphNode() {
  delete &v;
  delete &gravity;
  delete &electrostatic;
  delete &bonded;
}

void GraphNode::calcGravity() {}

void GraphNode::calcElectrostatic() {}

void GraphNode::calcBonded() {}

void GraphNode::updateForces() {
  
}

void GraphNode::updatePosition(float timestep) {
  v.move(timestep * forces.x, timestep * forces.y);
}

void GraphNode::draw() {
  w->draw(this->v);
}
