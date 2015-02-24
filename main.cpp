#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include "GraphNode.hpp"
#include "GraphNodeSet.hpp"
#include "DGLLoader.hpp"

static const float ts = 0.05;

int main() {
  std::ofstream f;
  f.open("test.xdgl");
  sf::VideoMode vm;
  sf::RenderWindow window(vm.getDesktopMode(), "Directed Graph Layout Tool");
  window.setVerticalSyncEnabled(true);
  sf::Event event;

  auto now = std::chrono::system_clock::now();
  std::default_random_engine generator;
  generator.seed(now.time_since_epoch().count());
  std::uniform_int_distribution<int> distribution(0, 100);
  std::uniform_int_distribution<int> yDistribution(0, window.getSize().y);
  auto randomInt = std::bind(distribution, generator);
  
  sf::Vector2f origin(window.getSize().x / 2, window.getSize().y / 2);
  sf::CircleShape o(5.f);
  o.setPosition(origin.x, origin.y);
  o.setFillColor(sf::Color::Red);
  std::ifstream infile("inTest.dgl");
  DGLLoader loader = loadDGL(infile, window, origin);
  GraphNodeSet * graph = loader.generateGraph(window, origin);
  /*
  GraphNodeParameters params;
  GraphNodeSet nodes(params, window, origin);
  int i;
  for(i = 0; i < 1000; i++) {
    nodes.createNode(3.f, (float)(randomInt() * window.getSize().x / 100), (float)(randomInt() * window.getSize().y /100));
    nodes[i].setFillColor(sf::Color::Green);
    if (i > 0) {
      nodes[i].addBond(nodes[i-1], 50);
      nodes[i-1].addBond(nodes[i], 50);
    }
  }

  nodes[i-1].addBond(nodes[0], 100);
  nodes[0].addBond(nodes[i-1], 100);
  */
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        goto exit;
      }
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::E:
            graph->params().incrementElec();
            break;
          case sf::Keyboard::D:
            graph->params().decrementElec();
            break;
          case sf::Keyboard::Q:
            graph->params().incrementGrav();
            break;
          case sf::Keyboard::A:
            graph->params().decrementGrav();
            break;
          case sf::Keyboard::W:
            graph->params().incrementBondLength();
            break;
          case sf::Keyboard::S:
            graph->params().decrementBondLength();
            break;
          case sf::Keyboard::R:
            graph->params().incrementMu();
            break;
          case sf::Keyboard::F:
            graph->params().decrementMu();
            break;
          case sf::Keyboard::T:
            f.seekp(0);
            graph->writeAsSVG(f);
            break;
          default:
            break;
        }
      }
    }

    window.clear(sf::Color::Black);
    window.draw(o);

    graph->update(ts);
    graph->draw();
    window.display();
  }

  exit:
  window.close();
  f.close();
  return 0;

}
