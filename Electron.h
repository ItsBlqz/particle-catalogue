#ifndef ELECTRON_H
#define ELECTRON_H

#include "Lepton.h"

class Electron : public Lepton
{
private:
  std::map <std::string, double> energy_deposited_layers;

public:
  Electron();
  Electron(bool);
  Electron(bool, double, double, double, double); //To set FourMomentum
  ~Electron() {};
  
  //Setters
  void initialise_energy_deposited();
  void deposit_energy(double, double, double, double);

  //Getters
  std::map <std::string, double> get_deposited_energy() const {return energy_deposited_layers;}
  void print_info() override;
};

#endif