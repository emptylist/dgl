#include "DGLLoader.hpp"

#include <vector>
#include <string>
#include <cmath>
#include "GraphNode.hpp"
#include "Bond.hpp"

enum TokenType {
  PARAMETERS,
  G,
  E,
  BL,
  MU,
  NODE,
  ID,
  X,
  Y,
  R,
  BOND,
  ORIGIN_ID,
  PARTNER_ID,
  STRENGTH,
  VALUE
};

struct CompoundToken {
  TokenType type;
  struct data { // note this is semantically a union, but we need a std::string
    std::string str;
    float f;
  };
};

class TokenFusor {
  enum FusorState {
    NONE,
    G,
    E,
    BL,
    MU,
    ID,
    X,
    Y,
    R,
    ORIGIN_ID,
    PARTNER_ID,
    STRENGTH
  };

private:
  FusorState state;
  std::vector<CompoundToken> * output;
  TokenFusor();
  TokenType determineType(std::string);

public:
  TokenFusor(std::vector<CompoundToken> * output) : state(NONE), output(output) {};
  void parseToken(std::string);
};

TokenType TokenFusor::determineType(std::string token) {
  if (token == "parameters") { return PARAMETERS; }
  else if (token == "g") { return G; }
  else if (token == "e") { return E; }
  else if (token == "bl") { return BL; }
  else if (token == "mu") { return MU; }
  else if (token == "node") { return NODE; }
  else if (token == "id") { return ID; }
  else if (token == "x") { return X; }
  else if (token == "y") { return Y; }
  else if (token == "r") { return R; }
  else if (token == "bond") { return BOND; }
  else if (token == "origin") { return ORIGIN; }
  else if (token == "partner") { return PARTNER; }
  else if (token == "strength") { return STRENGTH; }
  else { return VALUE; }
}   
TokenFusor::parseToken(std::string token) {
  
}

class DGLLoaderStateMachine;

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

struct LoaderMachine {
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
    std::string t = std::string(s);
    if (t.compare("")) { tokens.push_back(t); }
  }
  
  // Parse tokens into data tables
  std::vector<LoaderNode> nodeTable;
  std::vector<LoaderBond> bondTable;
  LoaderParameters parameters;
  LoaderMachine sm;

  for (auto it = tokens.begin(); it != tokens.end(); it++) {
    
  }
}
