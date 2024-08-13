#include<iomanip>
#include<sstream>
#include<algorithm>
#include "Neutrino.h"

using std::cout;
using std::endl;
using std::cerr;

const std::map <std::string, std::tuple<std::string, bool, double>> Neutrino::neutrino_data = 
{
  //Name, Anti-Particle, Rest_Mass
  {"electron", std::make_tuple("Electron Neutrino", 0, 0.0022)},
  {"muon", std::make_tuple("Muon Neutrino", 0, 0.17)},
  {"tau", std::make_tuple("Tau Neutrino", 0, 15.5)}, // Maps don't allow aliases so just duplicating the entry

  {"antielectron", std::make_tuple("Electron Anti-Neutrino", 1, 0.0022)},
  {"antimuon", std::make_tuple("Muon Anti-Neutrino", 1, 0.17)},
  {"antitau", std::make_tuple("Tau Anti-Neutrino", 1, 15.5)},
};

Neutrino::Neutrino() : Lepton{0}
{
  charge = 0;
  set_flavour("electron"); //Defaulting to prevent breakage
  particle_four_momentum->set_E(rest_mass); //Default Initialisation
  particle_four_momentum->set_px(0);
  particle_four_momentum->set_py(0);
  particle_four_momentum->set_pz(0);
  base_particle_type = "neutrino";
}

Neutrino::Neutrino(std::string flavour) : Lepton{0}
{
  charge = 0;
  set_flavour(flavour);
  particle_four_momentum->set_E(rest_mass); 
  particle_four_momentum->set_px(0);
  particle_four_momentum->set_py(0);
  particle_four_momentum->set_pz(0);
  base_particle_type = "neutrino";
}

Neutrino::Neutrino(std::string flavour, double energy, double px, double py, double pz) : Lepton{0, energy, px, py, pz}
{
  charge = 0;
  set_flavour(flavour);
  base_particle_type = "neutrino";
}


void Neutrino::set_flavour(const std::string flavour)
{
  std::string temp_flavour_verifier = flavour;
  std::string temp_flavour = clean_input(flavour);

  // Now finally checking if this exists in the particle set
  try
  {
    auto it = neutrino_data.find(temp_flavour);
    if(it == neutrino_data.end())
      throw std::invalid_argument("Invalid neutrino/anti-neutrino type ["+temp_flavour+"] found.");
    //Since the neutrino/anti-neutrino now exists. Setting the necessary things.
    const auto& neutrino_info = neutrino_data.at(temp_flavour);
    const auto& [formatted_flavour, neutrino_base_type, neutrino_mass] = neutrino_info;

    if(temp_flavour != temp_flavour_verifier)
      cout<<"Corrected the input "<<flavour<<". I think you meant "<<temp_flavour<<"."<<endl;
    
    //Now setting the variables
    neutrino_flavour = formatted_flavour;
    if(neutrino_base_type)
      set_anti_particle();
    charge = 0;
    particle_name = neutrino_flavour;
    particle_id = temp_flavour + "neutrino";
    rest_mass = neutrino_mass; 
  }
  catch(const std::exception& e)
  {
    cerr<<e.what()<<"Please rectify. Reverting to default type: electron/anti-electron"<<endl;
    get_if_anti_particle() ? set_flavour("antielectron") : set_flavour("electron");    
  }
  
}

void Neutrino::print_info()
{
  print_base_data();
  cout<<endl;
  cout<<"Has "<<neutrino_flavour<<" Interacted? : "<<(has_interacted ? "Yes" : "No")<<endl;
}