#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <set>

#include "W_Boson.h"
#include "Particle.h"
#include "Quark.h"
#include "Muon.h"
#include "Neutrino.h"

W_Boson::W_Boson() : Boson{80400}
{
  charge = -1; //Default is W-
  particle_name = "W- Boson";
  particle_id = "w_boson";
}

W_Boson::W_Boson(bool anti_particle) : Boson{80400}
{
  charge = -1; //Default is W-
  particle_name = "W- Boson";
  particle_id = "w_boson";
  if(anti_particle)
    set_anti_particle();
}

W_Boson::W_Boson(bool anti_particle, double energy, double px, double py, double pz) : Boson{80400, energy, px, py, pz}
{
  charge = -1;
  particle_name = "W- Boson";
  particle_id = "w_boson";
  if(anti_particle)
    set_anti_particle();
}


void W_Boson::set_decay(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{
  //Checking for various kinds of decays
  //For lepton check later on
  std::set<std::string> lepton_set = {"electron", "muon", "tau"};
  if (p1->get_base_particle_type() == "quark" && p2->get_base_particle_type() == "quark")
  {
    //Both are quarks so true!
    if((p1->get_particle_id() != p2->get_particle_id()) && (p1->get_if_anti_particle() != p2->get_if_anti_particle()))
    {
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
    //Now one has to be a lepton and other same flavour anti-leptonic-neutrino. To check this we check if one of them contains the id
    //eg electron_neutrino will contain electron as a substring
    if (check_substring_contained(p1->get_particle_id(), p2->get_particle_id()) || check_substring_contained(p2->get_particle_id(), p1->get_particle_id()))
    {
      //Now both leptons are of same flavour!
      if ((p1->get_rest_mass() != p2->get_rest_mass()) && (p1->get_if_anti_particle() != p2->get_if_anti_particle())
      && (charge == (p1->get_charge() + p2->get_charge())))
      {
        //Different masses means one HAS to be neutrino and one has to be a lepton
        //Also verifies that one is anti one is not This is now a valid delay!
        //Charge verifies that correct leptonic decay depending on W+ or W-
        decay_products.clear();
        decay_products.push_back(std::move(p1));
        decay_products.push_back(std::move(p2));
      }
      else
      {
        std::cerr<<"Not a valid leptonic decay! Please rectify! Exiting..."<<std::endl;
        exit(0);
      }
    }
    else
    {
      std::cerr<<"Not a valid leptonic decay! Please rectify! Exiting..."<<std::endl;
      exit(0);
    }
  }
  else
  {
    std::cerr<<"Not a valid W+/- Boson decay! Please rectify! Exiting..."<<std::endl;
    exit(0);
  }
}

void W_Boson::set_anti_particle()
{
  if(!is_anti_particle)
  {
    is_anti_particle = 1;
    charge *= -1;
    particle_name = "W+ Boson";
  }
  //Not changing particle_id here too!
}

