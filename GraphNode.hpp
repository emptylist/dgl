#ifndef __DGL_GRAPH_NODE_H__
#define __DGL_GRAPH_NODE_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Bond.hpp"

class Bond;
class GraphNode;
typedef std::vector<GraphNode> GraphNodeSet;

class GraphNodeParameters {
private:
  float m_gravity;
  float m_electrical;
  float m_bondLength;
  float m_mu;
  float gravIncrement = 0.2;
  float electricalIncrement = 0.001;
  float bondLengthIncrement = 0.1;
  float muIncrement = 0.05;

public:
  GraphNodeParameters(float g = 10.f, float e = 0.005, 
                      float bl = 5.f, float f = 0.2);
  float grav();
  void grav(float g);
  void incrementGrav();
  void decrementGrav();

  float elec();
  void elect(float e);
  void incrementElec();
  void decrementElec();

  float bondLength();
  void bondLength(float bl);
  void incrementBondLength();
  void decrementBondLength();

  float mu();
  void mu(float f);
  void incrementMu();
  void decrementMu();
};

class GraphNode {
private:
  sf::CircleShape v;
  sf::RenderWindow * w;
  sf::Vector2f pos;
  GraphNodeParameters * params;
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
  GraphNode(float radus, sf::Vector2f& origin, sf::RenderWindow& w, GraphNodeParameters& params,  
	    GraphNodeSet * nodes = NULL, unsigned int x = 0, unsigned int y = 0);
  ~GraphNode();
  
  float getx();
  float gety();
  void addBond(GraphNode& partner, float strength);
  void setFillColor(sf::Color color);
  void updateVelocity(float timestep);
  void updatePosition(float timestep);
  void draw();
};

#endif