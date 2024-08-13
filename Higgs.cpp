#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <set>

#include "Higgs.h"
#include "Quark.h"
#include "Muon.h"


Higgs::Higgs() : Boson{126000}
{
  spin = 0;
  particle_name = "Higgs Boson";
  particle_id = "higgs_boson";
}

Higgs::Higgs(double energy, double px, double py, double pz) : Boson{126000, energy, px, py, pz}
{
  spin = 0;
  particle_name = "Higgs Boson";
  particle_id = "higgs_boson";
}

void Higgs::set_decay(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{
  //Will move ownership to this object
  //Checking for various kinds of decays
  if (p1->get_particle_id() == "bottom" && p2->get_particle_id() == "bottom")
  {
    //A valid bottom bottom decay, now checking if one of them is anti quark, both can't be same
    if(p1->get_if_anti_particle() != p2->get_if_anti_particle())
    {
      //Can only be true if one of them is bottom and one is anti-bottom
      if((p1->get_charge() + p2->get_charge()) == charge)
      {
        decay_products.clear();
        decay_products.push_back(std::move(p1));
        decay_products.push_back(std::move(p2));
      }
      else
      {
        std::cout<<"The charges of quarks don't add up to 0 for "<<particle_name<<"! Please Rectify. Exiting..."<<std::endl;
        exit(0);
      }
    }
    else
    {
      std::cerr<<"Invalid Higgs decay! Please rectify! Exiting..."<<std::endl;
      exit(0);
    }
  }
  else if (p1->get_particle_id() == "z_boson" && p2->get_particle_id() == "z_boson")
  {
    if((p1->get_charge() + p2->get_charge()) == charge)
    {
      decay_products.clear();
      decay_products.push_back(std::move(p1));
      decay_products.push_back(std::move(p2));
    }
    else
    {
      std::cout<<"The charges don't add up to 0 for "<<particle_name<<"! Please Rectify. Exiting..."<<std::endl;
      exit(0);
    }
  }
  else if (p1->get_particle_id() == "w_boson" && p2->get_particle_id() == "w_boson")
  {
    if(p1->get_if_anti_particle() != p2->get_if_anti_particle())
    {
      //Can only be true if both opp signs
      if((p1->get_charge() + p2->get_charge()) == charge)
      {
        decay_products.clear();
        decay_products.push_back(std::move(p1));
        decay_products.push_back(std::move(p2));
      }
      else
      {
        std::cout<<"The charges don't add up to 0 for "<<particle_name<<"! Please Rectify. Exiting..."<<std::endl;
        exit(0);
      }
    }
    else
    {
      std::cerr<<"Invalid Higgs decay! Please rectify! Exiting..."<<std::endl;
      exit(0);
    }
  }
  else if (p1->get_particle_id() == "photon" && p2->get_particle_id() == "photon")
  {
    if((p1->get_charge() + p2->get_charge()) == charge)
    {
      decay_products.clear();
      decay_products.push_back(std::move(p1));
      decay_products.push_back(std::move(p2));
    }
    else
    {
      std::cout<<"The charges don't add up to 0 for "<<particle_name<<"! Please Rectify. Exiting..."<<std::endl;
      exit(0);
    }
  }
  else
  {
    std::cerr<<"Invalid Higgs decay! Please rectify! Exiting..."<<std::endl;
    exit(0);
  }
}

