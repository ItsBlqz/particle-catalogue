#ifndef BOSON_H
#define BOSON_H

#include "Particle.h"
class Boson : public Particle
{
private:

protected:
  std::vector<std::shared_ptr<Particle>> decay_products; 

public:
  Boson();
  Boson(double);
  Boson(double mass, double energy, double px, double py, double pz);
  virtual ~Boson() {};
  
  //Setters
  virtual void set_decay(std::shared_ptr<Particle>, std::shared_ptr<Particle>) {std::cout<<particle_name<<" does not decay!"<<std::endl;}
  void set_anti_particle() override {cout<<particle_name<<" has no anti-particle!"<<endl;}
  //Getters
  virtual std::vector<std::shared_ptr<Particle>> get_decay() const;
  void print_info() override;
};


#endif