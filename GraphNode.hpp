#ifndef __DGL_GRAPH_NODE_H__
#define __DGL_GRAPH_NODE_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Bond.hpp"

class Bond;
class GraphNode;
typedef std::vector<GraphNode> GraphNodeSet;

class GraphNode {
private:
  sf::CircleShape v;
  sf::RenderWindow * w;
  sf::Vector2f pos;
  float mu;
  sf::Vector2f * origin;
  sf::Vector2f gravity;
  sf::Vector2f electrostatic;
  sf::Vector2f bonded;
  sf::Vector2f friction;
  sf::Vector2f velocity;
  std::vector<Bond> bonds;
  GraphNodeSet * nodes;

  void calcGravity();
  void calcElectrostatic();
  void calcBonded();
  void calcFriction();

public:
  GraphNode(float radus, sf::Vector2f &origin, sf::RenderWindow &w,  
	    float friction = 0.8, GraphNodeSet * nodes = NULL, unsigned int x = 0, unsigned int y = 0);
  ~GraphNode();
  
  float getx();
  float gety();
  void addBond(GraphNode * partner, float strength);
  void setFillColor(sf::Color color);
  void updateVelocity(float timestep);
  void updatePosition(float timestep);
  void draw();
};

#endif