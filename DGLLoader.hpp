#ifndef __DGL_DGLLOADER_H__
#define __DGL_DGLLOADER_H__

#include <iostream>
#include <SFML/Graphics>
#include "GraphNodeSet.hpp"

GraphNodeSet& loadDGL(std::istream&, sf::RenderWindow&, sf::Vector2f&);

#endif
