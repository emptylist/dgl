#include "Bond.hpp"

Bond::Bond(GraphNode& origin, 
	   GraphNode& partner, 
	   float strength, 
	   sf::RenderWindow& w):
  m_strength(strength),
  m_control(new sf::Vector2f(w.getSize().x/2, w.getSize().y/2)),
  m_origin(&origin),
  m_partner(&partner),
  m_graphic(new QuadraticBezier(origin.getPos(), *m_control, partner.getPos(), w)) 
{}

Bond::~Bond() {
  delete m_graphic;
  delete m_control;
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
  float x1 = m_origin->getx();
  float y1 = m_origin->gety();
  float x2 = m_partner->getx();
  float y2 = m_partner->gety();
  m_control->x = ((y1 - y2) / 2) + ((x1 + x2) / 2);
  m_control->y = x1 - ((x1 + x2) / 2) + ((y1 + y2) / 2);
  m_graphic->draw();
}

void Bond::writeAsSVG(std::ostream& stream) {
  stream << "\t<path d=\"M" << m_origin->getx() << " " << m_origin->gety() << " "
	 << "Q" << m_control->x << ","<< m_control->y << " "
	 << m_partner->getx() << "," << m_partner->gety() << "\" "
	 << "fill=\"none\" stroke=\"#888888\" />" << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Bond& bond) {
  stream << "bond"
	 << " origin " << bond.m_origin
	 << " partner " << bond.m_partner
	 << " strength " << bond.m_strength
	 << std::endl;
  return stream;
}
