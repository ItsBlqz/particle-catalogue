#include "Photon.h"

Photon::Photon() : Boson{0}
{
  particle_name = "Photon";
  particle_id = "photon";
}

Photon::Photon(double energy, double px, double py, double pz) : Boson{0, energy, px, py, pz}
{
  particle_name = "Photon";
  particle_id = "photon";
}