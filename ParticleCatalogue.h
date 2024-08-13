#ifndef PARTICLECATALOGUE_H
#define PARTICLECATALOGUE_H

#include "Particle.h"

class ParticleCatalogue
{
private:
  std::vector<std::shared_ptr<Particle>> particle_container;
  std::string clean_input(std::string); //A function to clean string inputs, this is used commonly in my code

public:
  
  ParticleCatalogue() {};
  ParticleCatalogue(const std::shared_ptr<Particle> particle) {add_particle(particle);} //Just to initialse the catalogue with a single particle
  ~ParticleCatalogue() {};

  //Setters
  void add_particle(const std::shared_ptr<Particle>);

  //Getters
  std::vector<std::shared_ptr<Particle>> get_particle_container() const {return particle_container;}
  std::vector<std::shared_ptr<Particle>> get_sub_container(std::string);
  void print(std::vector<std::shared_ptr<Particle>>, int);
  FourMomentum<double> sum_container_four_momentum(std::vector<std::shared_ptr<Particle>>);
  int get_particle_count(std::vector<std::shared_ptr<Particle>>, std::string);

};

#endif