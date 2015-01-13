#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include "GraphNode.hpp"

int main() {
  sf::VideoMode vm;
  sf::RenderWindow window(vm.getDesktopMode(), "Directed Graph Layout Tool");
  sf::Event event;

  auto now = std::chrono::system_clock::now();
  std::default_random_engine generator;
  generator.seed(now.time_since_epoch().count());
  std::uniform_int_distribution<int> xDistribution(0, window.getSize().x);
  std::uniform_int_distribution<int> yDistribution(0, window.getSize().y);
  auto randX = std::bind(xDistribution, generator);
  auto randY = std::bind(yDistribution, generator);

  sf::Vector2f origin(window.getSize().x / 2, window.getSize().y / 2);
  GraphNode g1(20.f, origin, window, 0.8, 0, 0);

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

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
	window.close();
      }
    }

    window.clear(sf::Color::White);
    for (std::vector<sf::CircleShape>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
      it->move(randX()/1600, randY()/1600);
      window.draw(*it);
    }

    window.display();
  
  }

  return 0;

}
