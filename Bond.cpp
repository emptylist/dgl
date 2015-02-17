#include "Bond.hpp"

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

void Bond::writeAsSVG(std::ostream& stream) {
  stream << "\t<path d=\"M" << (int)m_origin->getx() << " " << (int)m_origin->gety() << " "
	 << "Q" << (int)m_partner->getx() << ","<< (int)m_origin->gety() << " "
	 << (int)m_partner->getx() << "," << (int)m_partner->gety() << "\" "
	 << "fill=\"none\" stroke=\"#888888\" />" << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Bond& bond) {
	stream << "\t\t <bond partner=" << bond.m_partner << " />" << std::endl;
	return stream;
}
