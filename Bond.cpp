#include "Bond.hpp"

Bond::Bond(GraphNode * partner, float strength) {
	this->partner = partner;
	this->strength = strength;
}

float Bond::getStrength() {
	return strength;
}

GraphNode* Bond::getPartner() {
	return partner;
}

float Bond::getPartnerX() {
	return partner->getx();
}

float Bond::getPartnerY() {
	return partner->gety();
}