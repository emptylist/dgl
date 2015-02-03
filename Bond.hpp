#ifndef __DGL_BOND_H__
#define __DGL_BOND_H__

#include "GraphNode.hpp"
#include "Bezier.hpp"

class GraphNode;

class Bond {
private:
	float m_strength;
	GraphNode * m_origin;
	GraphNode * m_partner;
	QuadraticBezier * m_graphic;

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
};

#endif