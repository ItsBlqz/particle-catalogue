#include "Boson.h"

Boson::Boson() : Particle(0)
{
  spin = 1;
  charge = 0; //Default Values for most bosons
  base_particle_type = "boson";
}

Boson::Boson(double mass) : Particle(mass)
{
  spin = 1;
  charge = 0; 
  base_particle_type = "boson";
}

Boson::Boson(double mass, double energy, double px, double py, double pz) : Particle{mass, energy, px, py, pz}
{
  spin = 1;
  charge = 0; 
  base_particle_type = "boson";
}

std::vector<std::shared_ptr<Particle>> Boson::get_decay() const
{
  std::cerr<<particle_name<<" has no decay products! Giving an empty container!"<<endl;
  return std::vector<std::shared_ptr<Particle>>();
}

void Boson::print_info()
{
  print_base_data();
  cout<<endl;
  if(get_particle_id() != "gluon" && get_particle_id() != "photon")
  {
    if(decay_products.empty())
    {
      cout<<particle_name<<" has not decayed."<<endl;
    }
    else
    {
      cout<<particle_name<<" Decay Channel : "<<particle_name<<" -> "<<decay_products[0]->get_particle_name()<<" + "<<decay_products[1]->get_particle_name()<<endl;
    }
  }
}