#ifndef GLUON_H
#define GLUON_H

#include "Boson.h"

class Gluon : public Boson
{
private:
  std::string colour{""};
  std::string anti_colour{""};
public:

  Gluon();
  Gluon(std::string, std::string, bool);
  Gluon(std::string, std::string, bool, double, double, double, double);
  ~Gluon() {};

  //Setters
  void set_colours(const std::string, const std::string);
  void set_anti_particle() override;
  void set_decay(std::shared_ptr<Particle>, std::shared_ptr<Particle>) override {std::cout<<particle_name<<" does not decay!"<<std::endl;}
  
  //Getters
  std::string get_colour() const {return colour;}
  std::string get_anti_colour() const {return anti_colour;} 
  void print_info() override;

};

#endif