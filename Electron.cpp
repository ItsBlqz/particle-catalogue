#include "Electron.h"
using std::cout;
using std::endl;

Electron::Electron() : Lepton{0.511}
{
  particle_name = "Electron";
  particle_id = "electron";
  initialise_energy_deposited();
}

Electron::Electron(bool anti_particle) : Lepton{0.511}
{
  particle_name = "Electron";
  particle_id = "electron";
  initialise_energy_deposited();
  if(anti_particle) set_anti_particle();
}

Electron::Electron(bool anti_particle, double energy, double px, double py, double pz) : Lepton{0.511, energy, px, py, pz}
{
  particle_name = "Electron";
  particle_id = "electron";
  initialise_energy_deposited();
  if(anti_particle) set_anti_particle();
}

void Electron::initialise_energy_deposited() 
{
  energy_deposited_layers = 
  {
    {"EM_1", 0.0},
    {"EM_2", 0.0},
    {"HAD_1", 0.0},
    {"HAD_2", 0.0}
  };
}

void Electron::deposit_energy(double energy_layer_1, double energy_layer_2, double energy_layer_3, double energy_layer_4)
{
  initialise_energy_deposited();
  double total_energy_deposited =  energy_layer_1 + energy_layer_2 + energy_layer_3 + energy_layer_4;
  double electron_energy = particle_four_momentum->get_E();
  // Checks if deposited energy lies between +- 0.01% of electron energy or if it lies between [0, electron energy], both cases allowed. So a margin of 0.1% exists
  if(energy_layer_1 < 0 || energy_layer_2 < 0 || energy_layer_3 < 0 || energy_layer_4 < 0)
  {
    std::cerr<<"The deposited energy can't be less than 0! Please rectify. Setting to default values of 0."<<endl;
    deposit_energy(0, 0, 0, 0);
  }
  else
  {
    if((((total_energy_deposited + 0.001*total_energy_deposited) <= electron_energy) && ((total_energy_deposited - 0.001*total_energy_deposited) == electron_energy)) || ((total_energy_deposited <= electron_energy) && total_energy_deposited >= 0)) // Check if matches 4 momentum initial energy with a tolerance of 0.01
    {
      energy_deposited_layers["EM_1"] = energy_layer_1;
      energy_deposited_layers["EM_2"] = energy_layer_2;
      energy_deposited_layers["HAD_1"] = energy_layer_3;
      energy_deposited_layers["HAD_2"] = energy_layer_4;
    }
    else
    {
      std::cerr<<"The deposited energies don't match the true energy! Please change this. Setting to default values of 0."<<endl;
      deposit_energy(0, 0, 0, 0);
    }
  }
}

void Electron::print_info()
{
  print_base_data();
  cout<<endl;
  std::cout<<"Deposited Energies in calorimeter [EM_1, EM_2, HAD_1, HAD_2] (MeV) : ["<<energy_deposited_layers["EM_1"]<<", "<<energy_deposited_layers["EM_2"]<<", "<<energy_deposited_layers["HAD_1"]<<", "<<energy_deposited_layers["HAD_2"]<<"]"<<std::endl;
}