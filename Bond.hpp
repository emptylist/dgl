#ifndef __DGL_BOND_H__
#define __DGL_BOND_H__

#include <SFML/System.hpp>
#include "GraphNode.hpp"
#include "Bezier.hpp"
#include <iostream>

class GraphNode;

class Bond {
private:
  float m_strength;
  sf::Vector2f * m_control;
  GraphNode * m_origin;
  GraphNode * m_partner;
  QuadraticBezier * m_graphic;
  friend std::ostream& operator<<(std::ostream&, const Bond&);
  
public:
  Bond(GraphNode& origin, 
       GraphNode& partner, 
       float strength, 
       sf::RenderWindow& w);
  ~Bond();
  float strength();
  GraphNode& getPartner();
  float getPartnerX();
  float getPartnerY();
  void draw();
  void writeAsSVG(std::ostream&);
};

#endif
