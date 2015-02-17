#include "GraphNode.hpp"
#include <iostream>
#include <vector>
#include <cmath>

GraphNode::GraphNode(float radius, 
                    sf::Vector2f& origin, 
                    sf::RenderWindow& window, 
                    GraphNodeParameters& parameters, 
                    GraphNodeSet * nodes, 
                    float x, 
                    float y) {
  v = sf::CircleShape(radius);
  w = &window;
  pos = sf::Vector2f(x, y);
  params = &parameters;
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

float GraphNode::getx() const {
  return pos.x;
}

float GraphNode::gety() const {
  return pos.y;
}

sf::Vector2f& GraphNode::getPos() {
  return pos;
}

void GraphNode::calcGravity() {
  gravity.x = -params->grav() * 
              (getx() - origin->x) / w->getSize().x;
  gravity.y = -params->grav() * 
              (gety() - origin->y) / w->getSize().y;
}

void GraphNode::calcElectrostatic() {
  electrostatic.x = 0.f;
  electrostatic.y = 0.f;
  float r;
  float x_dist;
  float y_dist;
  
  for (auto it = nodes->begin(); it != nodes->end(); it++) {
    if (this != *it) {
      x_dist = (getx() - (*it)->getx()) / w->getSize().x;
      y_dist = (gety() - (*it)->gety()) / w->getSize().y;
      r = sqrt((x_dist * x_dist) + (y_dist * y_dist));
      if (r != 0) {
        electrostatic.x += params->elec() * (x_dist) / r;
        electrostatic.y += params->elec() * (y_dist) / r;
      }
    }
  }
}

void GraphNode::calcBonded() {
  std::vector<Bond *>::iterator it;
  float bondLength;
  bonded.x = 0.f;
  bonded.y = 0.f;
  for(it = bonds.begin(); it != bonds.end(); it++) {
    bondLength = 
      pow(getx() - (*it)->getPartnerX(), 2) + 
      pow(gety() - (*it)->getPartnerY(), 2);
    if (bondLength > params->bondLength()) {
      bonded.x += 
        1 * (*it)->strength() * 
        (getx() - (*it)->getPartnerX()) / (bondLength - params->bondLength());
      bonded.y +=
        1 * (*it)->strength() *
        (gety() - (*it)->getPartnerY()) / (bondLength - params->bondLength());
    } else if (bondLength < params->bondLength()) {
      bonded.x +=
        -1 * (*it)->strength() *
        (getx() - (*it)->getPartnerX()) / (bondLength - params->bondLength());
      bonded.y +=
        -1 * (*it)->strength() *
        (gety() - (*it)->getPartnerY()) / (bondLength - params->bondLength());
    }
  }
}

void GraphNode::calcFriction() {
  friction.x = -params->mu() * velocity.x;
  friction.y = -params->mu() * velocity.y;
}

void GraphNode::addBond(GraphNode& partner, float strength) {

  auto b = new Bond(*this, partner, strength, *w);
  bonds.push_back(b);
  nodes->addBond(*b);
}

void GraphNode::updateVelocity(float timestep) {
  calcGravity();
  calcElectrostatic();
  calcBonded();

  velocity.x += timestep * w->getSize().x * 
                (gravity.x + electrostatic.x + bonded.x);
  velocity.y += timestep * w->getSize().y * 
                (gravity.y + electrostatic.y + bonded.y);

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

void GraphNode::writeAsSVG(std::ostream& stream) {
  stream << "\t<circle cx=\""
         << getx()
         << "\" cy=\""
         << gety()
         << "\" r=\""
         << v.getRadius()
         << "\" fill=\""
         << "green"
         << "\"/>"
         << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const GraphNode& node) {
  stream << "\t<node id="
        << &node
        << " x=" 
        << node.getx() 
        << " y=" 
        << node.gety() 
        << ">"
        << std::endl;
  for (auto it = node.bonds.begin(); it != node.bonds.end(); it++) {
    stream << **it;
  }
  stream << "\t</node>" << std::endl;
  return stream;
}