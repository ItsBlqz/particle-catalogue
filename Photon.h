#ifndef PHOTON_H
#define PHOTON_H

#include "Boson.h"

class Photon : public Boson
{
public:
  Photon();
  Photon(double, double, double, double);
  ~Photon() {};
};

#endif