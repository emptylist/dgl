#ifndef __DGL_DGLLOADER_H__
#define __DGL_DGLLOADER_H__

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "GraphNodeSet.hpp"
#include <cmath>

class LoaderParameters {
private:
  float m_g;
  float m_e;
  float m_bl;
  float m_mu;
public:
  LoaderParameters() : m_g(NAN), m_e(NAN), m_bl(NAN), m_mu(NAN) {};
  float g() { return m_g; };
  float e() { return m_e; };
  float bl() { return m_bl; };
  float mu() { return m_mu; };
  void g(float);
  void e(float);
  void bl(float);
  void mu(float);
  void clear();
};

class LoaderNode {
private:
  std::string m_id;
  float m_x;
  float m_y;
  float m_r;
public:
	std::string id() { return m_id; };
	float x() { return m_x; };
	float y() { return m_y; };
	float r() { return m_r; };
  void id(std::string);
  void x(float);
  void y(float);
  void r(float);
  void clear();
};

class LoaderBond {
private:
  std::string m_origin_id;
  std::string m_partner_id;
  float m_strength;
public:
  std::string originId() { return m_origin_id; };
  std::string partnerId() { return m_partner_id; };
  float strength() { return m_strength; };
  void originId(std::string);
  void partnerId(std::string);
  void strength(float);
  void clear();
};

class DGLLoader {
private:
  LoaderParameters parameters;
  bool parametersSet;
  std::vector<LoaderNode> nodeList;
  std::vector<LoaderBond> bondList;

public:
  DGLLoader() : parametersSet(false) {};
  void addParameters(LoaderParameters&);
  void addNode(LoaderNode&);
  void addBond(LoaderBond&);
  bool validate();
  GraphNodeSet * generateGraph(sf::RenderWindow&, sf::Vector2f&);
};

DGLLoader loadDGL(std::ifstream&, sf::RenderWindow&, sf::Vector2f&);

#endif
