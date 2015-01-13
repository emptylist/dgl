#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class GraphNode {
private:
  sf::CircleShape v;
  sf::RenderWindow * w;
  sf::Vector2f * origin;
  sf::Vector2f gravity;
  sf::Vector2f electrostatic;
  sf::Vector2f bonded;
  sf::Vector2f forces;

  void calcGravity();
  void calcElectrostatic();
  void calcBonded();

public:
  GraphNode(float radus, sf::Vector2f &origin, sf::RenderWindow &w,  
	    float friction = 0.8, unsigned int x = 0, unsigned int y = 0);
  ~GraphNode();

  void updateForces();
  void updatePosition(float timestep);
  void draw();
};

