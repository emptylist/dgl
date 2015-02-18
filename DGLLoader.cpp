#include "DGLLoader.hpp"

#include <vector>
#include <string>
#include "GraphNode.hpp"
#include "Bond.hpp"

enum LoaderType {
  PARAMETERS,
  NODE,
  BOND
};

struct LoaderParameters {
  float g;
  float e;
  float bl;
  float mu;
};

struct LoaderNode {
  std::string id;
  float x;
  float y;
  float r;
};

struct LoaderBond {
  std::string origin_id;
  std::string partner_id;
  float strength;
};

struct LoaderTarget {
  LoaderType type;
  union data {
    LoaderParameters parameters;
    LoaderNode node;
    LoaderBond bond;
  };
};

GraphNodeSet& loadDGL(std::ifstream& inputFile, sf::RenderWindow& window, sf::Vector2f&) {
  // Tokenize the input
  std::vector<std::string> tokens;
  std::string bufferString;
  char c;
  if (!inputFile.is_open()) { inputFile.open(); }
  while (!inputFile.eof()) {
    s.clear();
    do {
      inputFile.get(c);
      if (c != ' ' && c != '\n' && c != '\t') { s += c; }
    } while (c != ' ' && c != '\n' && c != '\t');
    if (t.compare("")) { tokens.push_back(t); }
  }
  
}
