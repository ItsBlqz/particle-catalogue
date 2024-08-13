#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <set>

#include "Z_Boson.h"
#include "Particle.h"
#include "Quark.h"
#include "Muon.h"
#include "Neutrino.h"


Z_Boson::Z_Boson() : Boson{91200}
{
  particle_name = "Z Boson";
}

Z_Boson::Z_Boson(double energy, double px, double py, double pz) : Boson{91200, energy, px, py, pz}
{
  particle_name = "Z Boson";
}


void Z_Boson::set_decay(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{

  //Checking for various kinds of decays
  std::set<std::string> lepton_set = {"electron", "muon", "tau"}; //To verify lepton decay later on.
  if (p1->get_base_particle_type() == "quark" && p2->get_base_particle_type() == "quark")
  {
    //Both are quarks so true!
    if((p1->get_particle_id() == p2->get_particle_id()) && (p1->get_if_anti_particle() != p2->get_if_anti_particle()))
    {
      //Both quarks same flavour but one is anti!
      if((p1->get_charge() + p2->get_charge()) == charge)
      {
        decay_products.clear();
        decay_products.push_back(std::move(p1));
        decay_products.push_back(std::move(p2));
      }
      else
      {
        std::cout<<"The charges of quarks don't add up to the "<<particle_name<<"! Please Rectify. Exiting..."<<std::endl;
        exit(0);
      }
    }
    else
    {
      std::cerr<<"Not a valid quark decay! Please rectify! Exiting..."<<std::endl;
      exit(0);
    }
  }
  else if (check_substring_contained(p1->get_particle_id(), lepton_set) && check_substring_contained(p2->get_particle_id(), lepton_set))
  {
    //If this is true means both are of leptonic types!
    //Now one has to be a lepton and other same flavour anti-lepton or neutrino and anti-neutrino, this
    //can only be true if both have the same mass! So fastest check if this is satisfied is to check if both have same masses
    //but one of them is the anti-variant!
    if ((p1->get_rest_mass() == p2->get_rest_mass()) && (p1->get_if_anti_particle() != p2->get_if_anti_particle()))
    {
      //Verifying charge
      if((p1->get_charge() + p2->get_charge()) == charge)
      {
        decay_products.clear();
        decay_products.push_back(std::move(p1));
        decay_products.push_back(std::move(p2));
      }
      else
      {
        std::cout<<"The charges of leptons don't add up to the "<<particle_name<<"! Please Rectify. Exiting..."<<std::endl;
        exit(0);
      }
    }
    else
    {
      std::cerr<<"Not a valid leptonic decay of Z-Boson! Please rectify! Exiting..."<<std::endl;
      exit(0);
    }
  }
  else
  {
    std::cerr<<"Not a valid Z-Boson decay! Please rectify! Exiting..."<<std::endl;
    exit(0);
  }
}
