#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include "GraphNode.hpp"

static const float ts = 0.05;

int main() {
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

  std::vector<GraphNode> nodeList;

  for(int i = 0; i < 1000; i++) {
    nodeList.push_back(GraphNode(3.f, origin, window, 0.1, 
      &nodeList, randomInt() * window.getSize().x / 100, randomInt() * window.getSize().y /100));
    nodeList[i].setFillColor(sf::Color::Blue);
    if (i > 0) {
      nodeList[i].addBond(&nodeList[i-1], randomInt() / 100.f);
    }
  }
  /*
  GraphNode g1(20.f, origin, window, 0.5, randX(), randY());
  g1.setFillColor(sf::Color::Blue);

  GraphNode g2(20.f, origin, window, 0.5, randX(), randY());
  g2.setFillColor(sf::Color::Green);

  GraphNode g3(20.f, origin, window, 0.5, randX(), randY());
  g3.setFillColor(sf::Color::Red);

  g1.addBond(&g3, 0.5);

/*
  sf::CircleShape v1(30.f);
  v1.setFillColor(sf::Color::Green);
  v1.setPosition(randX(), randY());

  sf::CircleShape v2(30.f);
  v2.setFillColor(sf::Color::Blue);
  v2.setPosition(randX(), randY());

  sf::CircleShape v3(30.f);
  v3.setFillColor(sf::Color::Red);
  v3.setPosition(randX(), randY());

  std::vector<sf::CircleShape> nodeList;
  nodeList.push_back(v1);
  nodeList.push_back(v2);
  nodeList.push_back(v3);
*/

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        goto exit;
      }
    }
    window.clear(sf::Color::White);
    /*
    for (std::vector<sf::CircleShape>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
      it->move(randX()/1600, randY()/1600);
      window.draw(*it);
    }
    */
/*
    g1.updateVelocity(ts);
    g2.updateVelocity(ts);
    g3.updateVelocity(ts);
    g1.updatePosition(ts);
    g2.updatePosition(ts);
    g3.updatePosition(ts);
    g1.draw();
    g2.draw();
    g3.draw();
    */
    window.draw(o);

    for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
      it->updateVelocity(ts);
    }

    for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
      it->updatePosition(ts);
      it->draw();
    }
    window.display();
    //std::cout << "New Frame" << std::endl;
  }

  exit:
  window.close();
  return 0;

}
