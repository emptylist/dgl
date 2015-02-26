#include "Bezier.hpp"
#include <iostream>

QuadraticBezier::QuadraticBezier(sf::Vector2f& s,
				 sf::Vector2f& c,
				 sf::Vector2f& e,
				 sf::RenderWindow& w):
  window(&w),
  m_start(&s),
  m_control(&c),
  m_end(&e),
  polyline(new sf::VertexArray(sf::LinesStrip, 101))
{}

void QuadraticBezier::computePolyline() {
  float t;
  sf::Vector2f p0;
  sf::Vector2f p1;
  for(int i = 0; i < (int)polyline->getVertexCount(); i++) {
    t = (float)i / ((float)(polyline->getVertexCount() - 1));
    p0 = (1 - t) * *m_start + t * *m_control;
    p1 = (1 - t) * *m_control + t * *m_end;
    (*polyline)[i].position = (1 - t) * p0 + t * p1;
    (*polyline)[i].color = sf::Color(0x88, 0x88, 0x88);
  }
  cached = false;
}

void QuadraticBezier::draw() {
  if (!cached) {
    computePolyline();
  }
  window->draw(*polyline);
}

sf::Vector2f& QuadraticBezier::start() { return *m_start; }
void QuadraticBezier::start(sf::Vector2f& s) {
  m_start = &s;
  cached = false;
}

sf::Vector2f& QuadraticBezier::control() { return *m_control; }
void QuadraticBezier::control(sf::Vector2f& c) {
  m_control = &c;
  cached = false;
}

sf::Vector2f& QuadraticBezier::end() { return *m_end; }
void QuadraticBezier::end(sf::Vector2f& e) {
  m_end = &e;
  cached = false;
}

unsigned int QuadraticBezier::resolution() { return polyline->getVertexCount() - 1; }
void QuadraticBezier::resolution(unsigned int r) {
  if (r >= 1) {
    polyline->resize(r+1);
    cached = false;
  } // else don't be stupid
}
