#include "DGLLoader.hpp"

#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include "GraphNode.hpp"
#include "Bond.hpp"

/*
  This is a state machine controlled by 
  a horrifying morass of switchs that badly needs refactoring
*/

enum class TokenType {
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

struct Token {
private:
  Token();
public:
  TokenType type;
  std::string val;
  Token(TokenType t) : type(t) {};
  Token(TokenType t, std::string s) : type(t), val(s) {};
};

Token tokenize(std::string s) {
  if (s == "parameters") { return Token(TokenType::PARAMETERS); }
  else if (s == "g") { return Token(TokenType::G); }
  else if (s == "e") { return Token(TokenType::E); }
  else if (s == "bl") { return Token(TokenType::BL); }
  else if (s == "mu") { return Token(TokenType::MU); }
  else if (s == "node") { return Token(TokenType::NODE); }
  else if (s == "id") { return Token(TokenType::ID); }
  else if (s == "x") { return Token(TokenType::X); }
  else if (s == "y") { return Token(TokenType::Y); }
  else if (s == "r") { return Token(TokenType::R); }
  else if (s == "bond") { return Token(TokenType::BOND); }
  else if (s == "origin") { return Token(TokenType::ORIGIN_ID); }
  else if (s == "partner") { return Token(TokenType::PARTNER_ID); }
  else if (s == "strength") { return Token(TokenType::STRENGTH); }
  else { return Token(TokenType::VALUE, s); }
}

void duplicateErrorMessage(std::string duplicate) {
  std::cerr << "Duplicate " << duplicate << " found; ignoring" << std::endl;
}

void LoaderParameters::g(float g) {
  if (isnan(m_g)) {
    m_g = g;
  } else {
    duplicateErrorMessage("Parameters G");
  }
}

void LoaderParameters::e(float e) {
  if (isnan(m_e)) {
    m_e = e;
  } else {
    duplicateErrorMessage("Parameters E");
  }
}

void LoaderParameters::bl(float bl) {
  if (isnan(m_bl)) {
    m_bl = bl;
  } else {
    duplicateErrorMessage("Parameters BL");
  }
}

void LoaderParameters::mu(float mu) {
  if (isnan(m_mu)) {
    m_mu = mu;
  } else {
    duplicateErrorMessage("Parameters MU");
  }
}

void LoaderParameters::clear() {
  m_g = NAN;
  m_e = NAN;
  m_bl = NAN;
  m_mu = NAN;
}

void LoaderNode::id(std::string s) {
  if (m_id.empty()) {
    m_id = s;
  } else {
    duplicateErrorMessage("Node ID");
  }
}

void LoaderNode::x(float x) {
  if (isnan(m_x)) {
    m_x = x;
  } else {
    duplicateErrorMessage("Node X");
  }
}

void LoaderNode::y(float y) {
  if (isnan(m_y)) {
    m_y = y;
  } else {
    duplicateErrorMessage("Node Y");
  }
}

void LoaderNode::r(float r) {
  if (isnan(m_r)) {
    m_r = r;
  } else {
    duplicateErrorMessage("Node R");
  }
}
void LoaderNode::clear() {
  m_id.clear();
  m_x = NAN;
  m_y = NAN;
  m_r = NAN;
}

void LoaderBond::originId(std::string originID) {
  if (m_origin_id.empty()) {
    m_origin_id = originID;
  } else {
    duplicateErrorMessage("Bond ORIGIN_ID");
  }
}

void LoaderBond::partnerId(std::string partnerID) {
  if (m_partner_id.empty()) {
    m_partner_id = partnerID;
  } else {
    duplicateErrorMessage("Bond PARTNER_ID");
  }
}

void LoaderBond::strength(float strength) {
  if (isnan(m_strength)) {
    m_strength = strength;
  } else {
    duplicateErrorMessage("Bond STRENGTH");
  }
}

void LoaderBond::clear() {
  m_origin_id.clear();
  m_partner_id.clear();
  m_strength = NAN;
}

void DGLLoader::addParameters(LoaderParameters& lp) {
  if (!parametersSet) {
    parameters.g(lp.g());
    parameters.e(lp.e());
    parameters.bl(lp.bl());
    parameters.mu(lp.mu());
    parametersSet = true;
  } else {
    duplicateErrorMessage("PARAMETERS");
  }
}

void DGLLoader::addNode(LoaderNode& lnode) {
  nodeList.push_back(LoaderNode(lnode));
}

void DGLLoader::addBond(LoaderBond& lbond) {
  bondList.push_back(LoaderBond(lbond));
}

bool DGLLoader::validate() {
  return true; // TODO: Actually validate things!
}

GraphNodeSet * DGLLoader::generateGraph(sf::RenderWindow& window, sf::Vector2f& origin) {
  auto now = std::chrono::system_clock::now();
  std::default_random_engine generator;
  generator.seed(now.time_since_epoch().count());
  std::uniform_int_distribution<int> distribution(0,100);
  auto randomInt = std::bind(distribution, generator);

  GraphNodeParameters * params = new GraphNodeParameters();
  if (!isnan(parameters.g())) { params->grav(parameters.g()); }
  if (!isnan(parameters.e())) { params->elec(parameters.e()); }
  if (!isnan(parameters.bl())) { params->bondLength(parameters.bl()); }
  if (!isnan(parameters.mu())) { params->mu(parameters.mu()); }
  GraphNodeSet * graph = new GraphNodeSet(*params, window, origin);
  for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
    graph->createNode(isnan(it->r()) ? 3.f : it->r(),
                      isnan(it->x()) ? ((float)randomInt() / 100) * window.getSize().x : it->x(),
		      isnan(it->y()) ? ((float)randomInt() / 100) * window.getSize().y / 2 : it->y());
  }
  for (auto it = bondList.begin(); it != bondList.end(); it++) {
    size_t nodeLoc1 = 0;
    size_t nodeLoc2 = 0;
    for (int i = 0; i < nodeList.end() - nodeList.begin(); i++) {
      if (it->originId() == nodeList[i].id()) { nodeLoc1 = i; }
      if (it->partnerId() == nodeList[i].id()) { nodeLoc2 = i; }
    }
    (*graph)[nodeLoc1].addBond((*graph)[nodeLoc2], isnan(it->strength()) ? 10 : it->strength());
  }
  return graph;
}

enum class EntryState {
  NONE,
  PARAMETERS,
  NODE,
  BOND
};

enum class VarState {
  NONE,
  G,
  E,
  BL,
  MU,
  ID,
  X,
  Y,
  R,
  ORIGIN,
  PARTNER,
  STRENGTH
};

class DGLTokenParser {
private:
  EntryState entryState;
  VarState varState;
  DGLLoader output;
  LoaderParameters parametersBuffer;
  LoaderNode nodeBuffer;
  LoaderBond bondBuffer;

  void flushParameters();
  void flushNode();
  void flushBond();

  void noneParseToken(Token);
  void parametersParseToken(Token);
  void nodeParseToken(Token);
  void bondParseToken(Token);

public:
  DGLTokenParser() : entryState(EntryState::NONE), varState(VarState::NONE) {};
  void flush();
  void parseToken(Token);
  DGLLoader finish();
};

void DGLTokenParser::flushParameters() {
  output.addParameters(parametersBuffer);
  parametersBuffer.clear();
}

void DGLTokenParser::flushNode() {
  output.addNode(nodeBuffer);
  nodeBuffer.clear();
}

void DGLTokenParser::flushBond() {
  output.addBond(bondBuffer);
  bondBuffer.clear();
}

void DGLTokenParser::flush() {
  if (varState != VarState::NONE) {
    std::cerr << "Incomplete token encountered; Ignoring." << std::endl;
  }
  switch(entryState) {
    case EntryState::NONE:
      break;
    case EntryState::PARAMETERS:
      flushParameters();
      break;
    case EntryState::NODE:
      flushNode();
      break;
    case EntryState::BOND:
      flushBond();
      break;
  }
  parametersBuffer.clear();
  nodeBuffer.clear();
  bondBuffer.clear();
  entryState = EntryState::NONE;
  varState = VarState::NONE;
}

void DGLTokenParser::noneParseToken(Token t) {
  switch (t.type) {
    case TokenType::PARAMETERS:
      entryState = EntryState::PARAMETERS;
      break;
    case TokenType::NODE:
      entryState = EntryState::NODE;
      break;
    case TokenType::BOND:
      entryState = EntryState::BOND;
      break;
    default:
      std::cerr << "Unexpected token of type encountered. Ignoring." << std::endl;
      break;
  }
}

void DGLTokenParser::parametersParseToken(Token t) {
  switch (t.type) {
    case TokenType::PARAMETERS:
      flush();
      entryState = EntryState::PARAMETERS;
      break;
    case TokenType::NODE:
      flush();
      entryState = EntryState::NODE;
      break;
    case TokenType::BOND:
      flush();
      entryState = EntryState::BOND;
      break;
    case TokenType::VALUE:
      if (varState == VarState::NONE) {
        std::cerr << "Unexpected VALUE token; ignoring." << std::endl;
      } else {
        switch (varState) {
          case VarState::G:
            parametersBuffer.g(std::stof(t.val));
            varState = VarState::NONE;
            break;
          case VarState::E:
            parametersBuffer.e(std::stof(t.val));
            varState = VarState::NONE;
            break;
          case VarState::BL:
            parametersBuffer.bl(std::stof(t.val));
            varState = VarState::NONE;
            break;
          case VarState::MU:
            parametersBuffer.mu(std::stof(t.val));
            varState = VarState::NONE;
            break;
          default:
            std::cerr << "Parsed VALUE while in invalid state" << std::endl;
        }
      }
      break;
    case TokenType::G:
      varState = VarState::G;
      break;
    case TokenType::E:
      varState = VarState::E;
      break;
    case TokenType::BL:
      varState = VarState::BL;
      break;
    case TokenType::MU:
      varState = VarState::MU;
      break;
    default:
      std::cerr << "Invalid token of type encountered; ignoring." << std::endl;
  }
}

void DGLTokenParser::nodeParseToken(Token t) {
  switch (t.type) {
    case TokenType::PARAMETERS:
      flush();
      entryState = EntryState::PARAMETERS;
      break;
    case TokenType::NODE:
      flush();
      entryState = EntryState::NODE;
      break;
    case TokenType::BOND:
      flush();
      entryState = EntryState::BOND;
      break;
    case TokenType::VALUE:
      if (varState == VarState::NONE) {
        std::cerr << "Unexpected VALUE token; ignoring." << std::endl;
      } else {
        switch (varState) {
          case VarState::ID:
            nodeBuffer.id(t.val);
            varState = VarState::NONE;
            break;
          case VarState::X:
            nodeBuffer.x(std::stof(t.val));
            varState = VarState::NONE;
            break;
          case VarState::Y:
            nodeBuffer.y(std::stof(t.val));
            varState = VarState::NONE;
            break;
          case VarState::R:
            nodeBuffer.r(std::stof(t.val));
            varState = VarState::NONE;
            break;
          default:
            std::cerr << "Parsed VALUE while in invalid state" << std::endl;
        }
      }
      break;
      // VarState tokens
    case TokenType::ID:
      varState = VarState::ID;
      break;
    case TokenType::X:
      varState = VarState::X;
      break;
    case TokenType::Y:
      varState = VarState::Y;
      break;
    case TokenType::R:
      varState = VarState::R;
      break;
    default:
      std::cerr << "Invalid token to type encountered; ignoring." << std::endl;
  }
}

void DGLTokenParser::bondParseToken(Token t) {
  switch (t.type) {
    case TokenType::PARAMETERS:
      flush();
      entryState = EntryState::PARAMETERS;
      break;
    case TokenType::NODE:
      flush();
      entryState = EntryState::NODE;
      break;
    case TokenType::BOND:
      flush();
      entryState = EntryState::BOND;
      break;
    case TokenType::VALUE:
      if (varState == VarState::NONE) {
        std::cerr << "Unexpected VALUE token; ignoring." << std::endl;
      } else {
        switch (varState) {
          case VarState::ORIGIN:
            bondBuffer.originId(t.val);
            varState = VarState::NONE;
            break;
          case VarState::PARTNER:
            bondBuffer.partnerId(t.val);
            varState = VarState::NONE;
            break;
          case VarState::STRENGTH:
            bondBuffer.strength(std::stof(t.val));
            varState = VarState::NONE;
            break;
          default:
            std::cerr << "Parsed VALUE while in invalid state" << std::endl;
        }
      }
      break;
    case TokenType::ORIGIN_ID:
      varState = VarState::ORIGIN;
      break;
    case TokenType::PARTNER_ID:
      varState = VarState::PARTNER;
      break;
    case TokenType::STRENGTH:
      varState = VarState::STRENGTH;
      break;
    default:
      std::cerr << "Invalid token to type encountered; ignoring." << std::endl;
  }
}

void DGLTokenParser::parseToken(Token t) {
  switch(entryState) {
    case EntryState::NONE:
      noneParseToken(t);
      break;
    case EntryState::PARAMETERS:
      parametersParseToken(t);
      break;
    case EntryState::NODE:
      nodeParseToken(t);
      break;
    case EntryState::BOND:
      bondParseToken(t);
      break;
  }
}

DGLLoader DGLTokenParser::finish() {
  flush();
  return output;
}

DGLLoader loadDGL(std::ifstream& inputFile, 
  sf::RenderWindow& window, 
  sf::Vector2f& origin) {

  // Tokenize the input
  std::vector<Token> tokens;
  std::string s;
  char c;
  while (!inputFile.eof()) {
    s.clear();
    do {
      inputFile.get(c);
      if (c != ' ' && c != '\n' && c != '\t') { s += c; }
    } while (c != ' ' && c != '\n' && c != '\t');
    if (!s.empty()) { tokens.push_back(tokenize(s)); }
  }
  // Parse Tokens
  DGLTokenParser parser;
  for (auto it = tokens.begin(); it != tokens.end(); it++) {
    parser.parseToken(*it);
  }
  return parser.finish();
}
