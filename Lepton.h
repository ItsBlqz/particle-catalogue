#ifndef LEPTON_H
#define LEPTON_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<map>
#include<tuple>
#include<memory>

#include "FourMomentum.h"
#include "Particle.h"

class Lepton : public Particle
{
private:
  int lepton_number{1};
public:
  // Default constructor
  Lepton();
  // Parameterized constructor
  Lepton(double);
  Lepton(double mass, double energy, double px, double py, double pz);
  ~Lepton() {};

  // Setters
  void set_anti_particle() override;
  void print_base_data() override;
  int get_lepton_number() const {return lepton_number;}

};


#endif