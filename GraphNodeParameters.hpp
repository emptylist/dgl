class GraphNodeParameters {
private:
	float m_gravity;
	float m_electrical;
	float m_bondLength;
	float m_mu;
	float gravIncrement = 0.2;

	float electricalIncrement = 0.001;
  float bondLengthIncrement = 0.1;
  float muIncrement = 0.05;

public:
  GraphNodeParameters(float g = 10.f, float e = 0.005, 
                      float bl = 5.f, float f = 0.2);
  float grav();
  void grav(float g);
  void incrementGrav();
  void decrementGrav();

  float elec();
  void elec(float e);
  void incrementElec();
  void decrementElec();

  float bondLength();
  void bondLength(float bl);
  void incrementBondLength();
  void decrementBondLength();

  float mu();
  void mu(float f);
  void incrementMu();
  void decrementMu();
};
