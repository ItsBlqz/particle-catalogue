#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <tuple>
#include <memory>
#include <set>

#include "FourMomentum.h"
class Particle
{
protected:
  std::unique_ptr<FourMomentum<double>> particle_four_momentum;
  double charge{0}; // in e
  double spin{0};
  double rest_mass{0};
  std::string base_particle_type{""};
  std::string particle_id{""};
  std::string particle_name{""};
  bool is_anti_particle{0}; 

  std::string clean_input(std::string); //A function to clean string inputs, this is used commonly in my code
  bool check_substring_contained(std::string, std::set<std::string>); //Another useful function to check if given map contains a substring of given string
  bool check_substring_contained(std::string, std::string); //Overloading the function to perform more necessary checks later on
  std::string beautify_fractions(double);
  virtual void print_base_data();

public:
  Particle();
  Particle(double);
  Particle(double mass, double energy, double px, double py, double pz);

  
  Particle(Particle&); // copy
  Particle(Particle&&); //move
  
  Particle& operator=(Particle&); //copy assignment
  Particle& operator=(Particle&&); //move assignment
  
  virtual void set_anti_particle() = 0;
  
  //Getters
  virtual void print_info() = 0;
  double get_spin() const {return spin;}
  double get_rest_mass() const {return rest_mass;}
  double get_charge() const {return charge;}
  std::string get_particle_name() const {return particle_name;}
  std::string get_particle_id() const {return particle_id;}
  bool get_if_anti_particle() const {return is_anti_particle;}
  const FourMomentum<double> get_four_momentum() const {return *particle_four_momentum;}
  std::string get_base_particle_type() const {return base_particle_type;}

  virtual ~Particle() {};

};

#endif 