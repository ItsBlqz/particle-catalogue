#ifndef QUARK_H
#define QUARK_H

#include <vector>
#include <map>
#include <string>
#include "Particle.h"

class Quark : public Particle
{
private:
  double baryon_number{1.0/3.0}; 
  std::string quark_colour;
  static const std::map <std::string, std::tuple<std::string, double, double>> quark_data;
  std::string quark_flavour;

public:

  // Constructors
  Quark();
  Quark(std::string, bool);
  Quark(std::string, bool, double, double, double, double);

  // Setters
  void set_flavour(std::string flavour);
  void set_anti_particle() override;
  void set_colour(std::string);
  // Getters
  std::string get_flavour() const {return quark_flavour;}
  std::string get_colour_charge() const {return quark_colour;}
  void print_info() override;
};
#endif 