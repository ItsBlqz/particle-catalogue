#ifndef Z_BOSON_H
#define Z_BOSON_H

#include "Boson.h"
class Z_Boson : public Boson
{
public:
  //Constructors and Destructors
  Z_Boson();
  Z_Boson(double, double, double, double);
  ~Z_Boson() {};

  //Setters
  void set_decay(std::shared_ptr<Particle>, std::shared_ptr<Particle>) override;

  //Getters
  std::vector<std::shared_ptr<Particle>> get_decay() const override {return decay_products;}
};

#endif