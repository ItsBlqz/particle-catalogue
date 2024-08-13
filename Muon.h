#ifndef MUON_H
#define MUON_H

#include "Lepton.h"

class Muon : public Lepton
{
private:
  bool is_isolated{0};

public:
  Muon();
  Muon(bool);
  Muon(bool, double, double, double, double, bool);
  ~Muon() {};
  
  //Setters
  void set_isolated(bool);

  //Getters
  bool get_if_isolated() const {return is_isolated;}

  void print_info() override;
};

#endif