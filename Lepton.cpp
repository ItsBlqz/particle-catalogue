#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include "Lepton.h"
using std::cout;
using std::endl;
using std::cerr;

Lepton::Lepton() : Particle(0)
{
  charge = -1; //Default charge for leptons, neutrinos handle it differently so this works
  spin = (1.0/2.0);
  base_particle_type = "lepton";
}

Lepton::Lepton(double mass) : Particle(mass)
{
  charge = -1; //Default charge for leptons, neutrinos handle it differently so this works
  spin = (1.0/2.0);
  base_particle_type = "lepton";
}

Lepton::Lepton(double mass, double energy, double px, double py, double pz) : Particle{mass, energy, px, py, pz}
{
  charge = -1;
  spin = (1.0/2.0);
  base_particle_type = "lepton";
}

void Lepton::print_base_data()
{
  std::cout<<particle_name<<" Info: ";
  //Using a simple check for mass printing, as if particle is a neutrino then only a limit exists on the mass!
  cout<<"[Rest Mass (MeV), Charge (e), Spin, Lepton Number, (E, px, py, pz) MeV] : ["
      <<((base_particle_type == "neutrino") ? "<" : "")
      <<rest_mass
      <<std::setprecision(4)
      <<", "<<beautify_fractions(charge)
      <<", "<<beautify_fractions(spin)
      <<", "<<lepton_number
      <<", ("<<particle_four_momentum->get_E()
      <<", "<<particle_four_momentum->get_px()
      <<", "<<particle_four_momentum->get_py()
      <<", "<<particle_four_momentum->get_pz()
      <<")]";
}

void Lepton::set_anti_particle()
{
  if(!is_anti_particle)
  {
    is_anti_particle = 1;
    lepton_number *= -1;
    if (charge == -1.0)
    {
      charge = 1.0; // Only reversing charge if not neutral 
      particle_name = "Anti-" + particle_name; // Only adding Anti- in case of leptons and not lepton neutrinos as neutrinos have different name handling!
      //Once again not adding anti to particle id as get_if_anti_particle() returns if particle or not and makes comparison easier
    }
  }
}

