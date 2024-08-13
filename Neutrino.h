#ifndef NEUTRINO_H
#define NEUTRINO_H

#include <iostream>
#include <map>
#include "Lepton.h"

class Neutrino : public Lepton
{
private:
  static const std::map <std::string, std::tuple<std::string, bool, double>> neutrino_data;
  std::string neutrino_flavour{""};
  bool has_interacted{0};

public:

  Neutrino();
  Neutrino(std::string);
  Neutrino(std::string, double, double, double, double);
  ~Neutrino() {};

  //Setters
  void set_flavour(const std::string flavour);
  void set_interacted(bool interacted) {has_interacted = interacted;}

  //Getters
  std::string get_flavour() const {return neutrino_flavour;}
  bool get_if_interacted() const {return has_interacted;}
  void print_info() override;
};

#endif