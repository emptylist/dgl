#include "GraphNodeParameters.hpp"

GraphNodeParameters::GraphNodeParameters(float g,
					 float e,
					 float bl,
					 float f) {
  m_gravity = g;
  m_electrical = e;
  m_bondLength = bl;
  m_mu = f;
}

float GraphNodeParameters::grav() { return m_gravity; }
void GraphNodeParameters::grav(float g) {
  if (g > 0) {
    m_gravity = g;
  } else {
    m_gravity = 0.f;
  }
}
void GraphNodeParameters::incrementGrav() {
  grav(grav() + gravIncrement);
}
void GraphNodeParameters::decrementGrav() {
  grav(grav() - gravIncrement);
}

float GraphNodeParameters::elec() { return m_electrical; }
void GraphNodeParameters::elec(float e) {
  if (e > 0) {
    m_electrical = e;
  } else {
    m_electrical = 0.f;
  }
}
void GraphNodeParameters::incrementElec() {
  elec(elec() + electricalIncrement);
}
void GraphNodeParameters::decrementElec() {
  elec(elec() - electricalIncrement);
}

float GraphNodeParameters::bondLength() { return m_bondLength; }
void GraphNodeParameters::bondLength(float bl) {
  if (bl > 0) {
    m_bondLength = bl;
  } else {
    m_bondLength = 0.f;
  }
}
void GraphNodeParameters::incrementBondLength() {
  bondLength(bondLength() + bondLengthIncrement);
}
void GraphNodeParameters::decrementBondLength() {
  bondLength(bondLength() - bondLengthIncrement);
}

float GraphNodeParameters::mu() { return m_mu; }
void GraphNodeParameters::mu(float f) {
  if ((f > 0) && (f < 1)) {
    m_mu = f;
  } else {
    if (f < 0) {
      m_mu = 0;
    } else { // case f > 1
      m_mu = 1;
    }
  }
}
void GraphNodeParameters::incrementMu() {
  mu(mu() + muIncrement);
}
void GraphNodeParameters::decrementMu() {
  mu(mu() - muIncrement);
}

