#ifndef __DGL_BOND_H__
#define __DGL_BOND_H__

#include "GraphNode.hpp"

class GraphNode;

class Bond {
private:
	float strength;
	GraphNode * partner;

public:
	Bond(GraphNode * partner, float strength);
	float getStrength();
	GraphNode * getPartner();
	float getPartnerX();
	float getPartnerY();
};

#endif