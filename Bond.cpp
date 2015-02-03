#include "Bond.hpp"
#include <iostream>

Bond::Bond(GraphNode& origin, 
		GraphNode& partner, 
		float strength, 
		sf::RenderWindow& w):
		m_strength(strength),
		m_origin(&origin),
		m_partner(&partner),
		m_graphic(new QuadraticBezier(origin.getPos(), partner.getPos(), partner.getPos(), w)) 
		{}

Bond::~Bond() {
	delete m_graphic;
}

float Bond::strength() {
	return m_strength;
}

GraphNode& Bond::getPartner() {
	return *m_partner;
}

float Bond::getPartnerX() {
	return m_partner->getx();
}

float Bond::getPartnerY() {
	return m_partner->gety();
}

void Bond::draw() {
	m_graphic->draw();
}