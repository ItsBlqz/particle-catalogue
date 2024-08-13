#ifndef HIGGS_H
#define HIGGS_H

#include "Boson.h"

class Higgs : public Boson
{
public:
  //Constructors
  Higgs();
  Higgs(double, double, double, double);
  ~Higgs() {};

  //Setters
  void set_decay(std::shared_ptr<Particle>, std::shared_ptr<Particle>) override;

  //Getters
  std::vector<std::shared_ptr<Particle>> get_decay() const override {return decay_products;}
};

#endif