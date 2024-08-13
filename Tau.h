#ifndef TAU_H
#define TAU_H

#include "Lepton.h"
#include "Electron.h"
#include "Muon.h"
#include <vector>
#include <memory>

class Tau : public Lepton
{
private:
  std::vector<std::shared_ptr<Particle>> decay_products; 
public:
  Tau();
  Tau(bool);
  Tau(bool, double, double, double, double);
  ~Tau() {};

  void set_decay(std::shared_ptr<Particle>, std::shared_ptr<Particle>); //A tau neutrino/anti-neutrino is always a product so not having that as an argument
  
  //Getters
  std::vector<std::shared_ptr<Particle>> get_decay() {return decay_products;}
  void print_info() override;
};

#endif