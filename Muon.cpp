#include "muon.h"

Muon::Muon() : Lepton{105.66}
{
  particle_name = "Muon";
  particle_id = "muon";
}

Muon::Muon(bool anti_particle) : Lepton{105.66}
{
  particle_name = "Muon";
  particle_id = "muon";
  if(anti_particle) set_anti_particle();
}

Muon::Muon(bool anti_particle, double energy, double px, double py, double pz, bool isolated) : Lepton{105.66, energy, px, py, pz}
{
  particle_name = "Muon";
  particle_id = "muon";
  set_isolated(isolated);
  if(anti_particle) set_anti_particle();
}

void Muon::set_isolated(bool isolated)
{
  is_isolated = isolated;
}

void Muon::print_info()
{
  print_base_data();
  cout<<endl;
  cout<<particle_name<<" Isolated? : "<<(is_isolated ? "Yes" : "No")<<endl;
}