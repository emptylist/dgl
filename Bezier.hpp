#ifndef __DGL_BEZIER_H__
#define __DGL_BEZIER_H__

#include <vector>
#include <SFML/Graphics.hpp>

class QuadraticBezier {
private:
	sf::RenderWindow * window;
	sf::Vector2f * m_start;
	sf::Vector2f * m_control;
	sf::Vector2f * m_end;
	sf::VertexArray * polyline;
	bool cached = false;

	QuadraticBezier() {};
	void computePolyline();
public:
	QuadraticBezier(sf::Vector2f&,
					sf::Vector2f&,
					sf::Vector2f&,
					sf::RenderWindow&);
	sf::Vector2f& start();
	void start(sf::Vector2f& s);
	
	sf::Vector2f& control();
	void control(sf::Vector2f& c);
	
	sf::Vector2f& end();
	void end(sf::Vector2f& e);

	unsigned int resolution();
	void resolution(unsigned int r);

	void draw();
};

#endif