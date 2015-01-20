#include "GraphNode.hpp"
#include <iostream>
#include <vector>
#include <cmath>

static const float coeffG = 10; // Note Gravity is actually a spring on the origin
static const float coeffE = 0.005;
static const float idealBondLength = 5;

GraphNode::GraphNode(float radius, sf::Vector2f &origin, sf::RenderWindow &window, 
	                   float mu, GraphNodeSet * nodes, unsigned int x, unsigned int y) {
  v = sf::CircleShape(radius);
  w = &window;
  pos = sf::Vector2f(x, y);
  this->mu = mu;
  this->origin = &origin;
  gravity = sf::Vector2f(0.f, 0.f);
  electrostatic = sf::Vector2f(0.f, 0.f);
  bonded = sf::Vector2f(0.f, 0.f);
  friction = sf::Vector2f(0.f, 0.f);
  velocity = sf::Vector2f(0.f, 0.f);
  this->nodes = nodes;
}

GraphNode::~GraphNode() {
  /*
  GraphNodeSet::iterator it;
  for(it = nodes.begin(); 
      (it != nodes.end()) || (this != *it); 
      it++);
  if (this == *it) { nodes.erase(it); delete this; }
  */
}

float GraphNode::getx() {
  return pos.x;
}

float GraphNode::gety() {
  return pos.y;
}

void GraphNode::calcGravity() {
  gravity.x =  -coeffG * (getx() - origin->x) / w->getSize().x;
  gravity.y =  -coeffG * (gety() - origin->y) / w->getSize().y;

}

void GraphNode::calcElectrostatic() {
  electrostatic.x = 0.f;
  electrostatic.y = 0.f;
  float r;
  float x_dist;
  float y_dist;
  GraphNodeSet::iterator it;
  for (it = nodes->begin(); it != nodes->end(); it++) {
    if (this != &(*it)) {
      x_dist = (getx() - it->getx()) / w->getSize().x;
      y_dist = (gety() - it->gety()) / w->getSize().y;
      r = sqrt((x_dist * x_dist) + (y_dist * y_dist));
      if (r != 0) {
        electrostatic.x += coeffE * (x_dist) / r;
        electrostatic.y += coeffE * (y_dist) / r;
      }
    }
  }
}

void GraphNode::calcBonded() {
  std::vector<Bond>::iterator it;
  float bondLength;
  bonded.x = 0.f;
  bonded.y = 0.f;

  for(it = bonds.begin(); it != bonds.end(); it++) {
    bondLength = 
      pow(getx() - it->getPartnerX(), 2) + 
      pow(gety() - it->getPartnerY(), 2);
    if (bondLength > idealBondLength) {
      bonded.x += 
        -1 * it->getStrength() * 
        (getx() - it->getPartnerX()) / (bondLength - idealBondLength);
      bonded.y +=
        -1 * it->getStrength() *
        (gety() - it->getPartnerY()) / (bondLength - idealBondLength);
    } else if (bondLength < idealBondLength) {
      bonded.x +=
        it->getStrength() *
        (getx() - it->getPartnerX()) / (bondLength - idealBondLength);
      bonded.y +=
        it->getStrength() *
        (gety() - it->getPartnerY()) / (bondLength - idealBondLength);
    }
  }
}

void GraphNode::calcFriction() {
  friction.x = -mu * velocity.x;
  friction.y = -mu * velocity.y;
}

void GraphNode::addBond(GraphNode * partner, float strength) {
  bonds.push_back(Bond(partner, strength));
}

void GraphNode::updateVelocity(float timestep) {
  calcGravity();
  calcElectrostatic();
  calcBonded();

  velocity.x += timestep * w->getSize().x * (gravity.x + electrostatic.x + bonded.x);
  velocity.y += timestep * w->getSize().y * (gravity.y + electrostatic.y + bonded.y);

  calcFriction();
  velocity.x += friction.x;
  velocity.y += friction.y;
}

void GraphNode::updatePosition(float timestep) {
  pos.x += timestep * velocity.x;
  pos.y += timestep * velocity.y;
}

void GraphNode::setFillColor(sf::Color color) {
  v.setFillColor(color);
}

void GraphNode::draw() {
  v.setPosition((int)pos.x, (int)pos.y);
  w->draw(v);
}
