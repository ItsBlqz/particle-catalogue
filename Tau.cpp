#include "Tau.h"
#include "Neutrino.h"
#include <algorithm>
#include <iomanip>
#include <unordered_set>
#include <random>
#include <array>

Tau::Tau() : Lepton{1776.80}
{
  particle_name = "Tau";
  particle_id = "tau";
}

Tau::Tau(bool anti_particle) : Lepton{1776.80}
{
  particle_name = "Tau";
  particle_id = "tau";
  if(anti_particle) set_anti_particle();
}

Tau::Tau(bool anti_particle, double energy, double px, double py, double pz) : Lepton{1776.80, energy, px, py, pz}
{
  particle_name = "Tau";
  particle_id = "tau";
  if(anti_particle) set_anti_particle();
}

void Tau::set_decay(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{
  //Tau neutrino/anti_neutrino will be set automatically
  //For lepton check later on
  
  std::set<std::string> lepton_set = {"electron", "muon"}; //Tau can only decay into a tau!
  if (p1->get_base_particle_type() == "quark" && p2->get_base_particle_type() == "quark")
  {
    //Both are quarks so true!
    if((p1->get_particle_id() != p2->get_particle_id()) && (p1->get_if_anti_particle() != p2->get_if_anti_particle()))
    {
      //As tau decays via W Boson, the quarks need to be different flavours!
      if((p1->get_charge() + p2->get_charge()) == charge)
      {
        //Neutrino has charge 0!
        decay_products.clear();
        decay_products.push_back(std::move(p1));
        decay_products.push_back(std::move(p2));
        if (is_anti_particle)
        {
          std::shared_ptr<Neutrino> tau_anti_neutrino = std::make_unique<Neutrino>("antitau"); //Producing them at rest
          decay_products.push_back(std::move(tau_anti_neutrino));
        }
        else
        {
          std::shared_ptr<Neutrino> tau_neutrino = std::make_unique<Neutrino>("tau");
          decay_products.push_back(std::move(tau_neutrino));
        }
      }
      else
      {
        std::cout<<"The charges of products don't add up to the "<<particle_name<<"! Please Rectify. Exiting..."<<std::endl;
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
        //Charge verifies that correct leptonic decay 
        decay_products.clear();
        decay_products.push_back(std::move(p1));
        decay_products.push_back(std::move(p2));
        if (is_anti_particle)
        {
          std::shared_ptr<Neutrino> tau_anti_neutrino = std::make_unique<Neutrino>("antitau");
          decay_products.push_back(std::move(tau_anti_neutrino));
        }
        else
        {
          std::shared_ptr<Neutrino> tau_neutrino = std::make_unique<Neutrino>("tau");
          decay_products.push_back(std::move(tau_neutrino));
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
      std::cerr<<"Not a valid leptonic decay! Please rectify! Exiting..."<<std::endl;
      exit(0);
    }
  }
  else
  {
    std::cerr<<"Not a valid Tau / Anti-Tau decay! Please rectify! Exiting..."<<std::endl;
    exit(0);
  }
}

void Tau::print_info()
{
  print_base_data();
  cout<<endl;
  if(decay_products.empty())
  {
    cout<<particle_name<<" has not decayed."<<endl;
  }
  else
  {
    cout<<particle_name<<" Decay Channel : "<<particle_name<<" -> "<<decay_products[0]->get_particle_name()<<" + "<<decay_products[1]->get_particle_name()<<" + "<<decay_products[2]->get_particle_name()<<endl;
  }
}