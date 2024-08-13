#ifndef W_BOSON_H
#define W_BOSON_H

#include "Boson.h"

class W_Boson : public Boson
{
public:
  W_Boson();
  W_Boson(bool);
  W_Boson(bool, double, double, double, double);
  ~W_Boson() {};

  //Setters
  void set_decay(std::shared_ptr<Particle>, std::shared_ptr<Particle>) override;
  void set_anti_particle() override;
  
  //Getters
  std::vector<std::shared_ptr<Particle>> get_decay() const override {return decay_products;}
};

#endif