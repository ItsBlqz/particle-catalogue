// PHYS 30762 Programming in C++
// Project : Particle Catalogue
// Compile line g++ -std=c++17 -g .\Boson.cpp .\Electron.cpp .\Gluon.cpp .\Higgs.cpp .\Lepton.cpp .\Muon.cpp .\Neutrino.cpp .\Particle.cpp .\ParticleCatalogue.cpp .\Photon.cpp .\Quark.cpp .\Tau.cpp .\W_Boson.cpp .\Z_Boson.cpp .\project_main.cpp -o project_main
// Author : Hardik Kohli
// Student ID: 10636495
// Date: 08/05/2024

#include <iostream>
#include <typeinfo>
#include <set>
#include <iomanip>


#include "ParticleCatalogue.h"
#include "Electron.h"
#include "Neutrino.h"
#include "Lepton.h"
#include "Particle.h"
#include "Quark.h"
#include "W_Boson.h"
#include "Muon.h"
#include "Neutrino.h"
#include "Gluon.h"
#include "Photon.h"
#include "Z_Boson.h"
#include "Higgs.h"
#include "Tau.h"

void initialise_catalogue_quarks(ParticleCatalogue &catalogue)
{
  std::shared_ptr<Quark> up = std::make_shared<Quark>("up", 0);
  up->set_colour("red");
  catalogue.add_particle(std::move(up));
  
  std::shared_ptr<Quark> anti_up = std::make_shared<Quark>("up", 1);
  anti_up->set_colour("green"); //Showing input correction by putting wrong input
  catalogue.add_particle(std::move(anti_up));

  std::shared_ptr<Quark> charm = std::make_shared<Quark>("charm", 0);
  charm->set_colour("blue");
  catalogue.add_particle(std::move(charm));
  
  std::shared_ptr<Quark> anti_charm = std::make_shared<Quark>("charm", 1);
  anti_charm->set_colour("antiblue");
  catalogue.add_particle(std::move(anti_charm));

  std::shared_ptr<Quark> top = std::make_shared<Quark>("top", 0);
  top->set_colour("blue");
  catalogue.add_particle(std::move(top));

  std::shared_ptr<Quark> anti_top = std::make_shared<Quark>("top", 1);
  anti_top->set_colour("antiblue");
  catalogue.add_particle(std::move(anti_top));

  std::shared_ptr<Quark> down = std::make_shared<Quark>("down", 0);
  down->set_colour("blue");
  catalogue.add_particle(std::move(down));
  
  std::shared_ptr<Quark> anti_down = std::make_shared<Quark>("down", 1);
  anti_down->set_colour("antired");
  catalogue.add_particle(std::move(anti_down));
  
  std::shared_ptr<Quark> strange = std::make_shared<Quark>("strange", 0);
  strange->set_colour("blue");
  catalogue.add_particle(std::move(strange));
  
  std::shared_ptr<Quark> anti_strange = std::make_shared<Quark>("strange", 1);
  anti_strange->set_colour("antired");
  catalogue.add_particle(std::move(anti_strange));
  
  std::shared_ptr<Quark> bottom = std::make_shared<Quark>("bottom", 0);
  bottom->set_colour("blue");
  catalogue.add_particle(std::move(bottom));
  
  std::shared_ptr<Quark> anti_bottom = std::make_shared<Quark>("bottom", 1, 2000, 10, 10, 10);
  anti_bottom->set_colour("antired");
  catalogue.add_particle(std::move(anti_bottom));
}

void initialise_catalogue_bosons(ParticleCatalogue &catalogue)
{
  std::shared_ptr<Gluon> gluon = std::make_shared<Gluon>("red", "antigreen", 0, 1000, 10, 10, 10);
  catalogue.add_particle(std::move(gluon));

  std::shared_ptr<Gluon> anti_gluon = std::make_shared<Gluon>("blue", "antired", 1);
  catalogue.add_particle(std::move(anti_gluon));

  std::shared_ptr<Photon> photon = std::make_shared<Photon>();
  catalogue.add_particle(std::move(photon));

  std::shared_ptr<Z_Boson> z_boson = std::make_shared<Z_Boson>();
  std::shared_ptr<Neutrino> z_decay_neutrino = std::make_shared<Neutrino>("muon");
  std::shared_ptr<Neutrino> z_decay_anti_neutrino = std::make_shared<Neutrino>("antimuon");
  z_boson->set_decay(std::move(z_decay_neutrino), std::move(z_decay_anti_neutrino));
  catalogue.add_particle(std::move(z_boson));

  std::shared_ptr<W_Boson> w_boson = std::make_shared<W_Boson>(0);
  std::shared_ptr<Quark> decay_b1 = std::make_shared<Quark>("bottom", 0);
  std::shared_ptr<Quark> decay_t1 = std::make_shared<Quark>("top", 1);
  decay_t1->set_colour("antiblue");
  w_boson->set_decay(std::move(decay_b1), std::move(decay_t1));
  catalogue.add_particle(std::move(w_boson));

  std::shared_ptr<W_Boson> w_anti_boson = std::make_shared<W_Boson>(1);
  std::shared_ptr<Muon> decay_muon = std::make_shared<Muon>(1);
  std::shared_ptr<Neutrino> decay_neutrino = std::make_shared<Neutrino>("muo2n"); //Showing input correction
  decay_muon->set_isolated(1);
  decay_neutrino->set_interacted(0);
  w_anti_boson->set_decay(std::move(decay_muon), std::move(decay_neutrino));
  catalogue.add_particle(std::move(w_anti_boson));
  
  std::shared_ptr<Higgs> higgs_boson = std::make_shared<Higgs>();
  std::shared_ptr<Photon> decay_photon_1 = std::make_shared<Photon>();
  std::shared_ptr<Photon> decay_photon_2 = std::make_shared<Photon>();
  higgs_boson->set_decay(std::move(decay_photon_1), std::move(decay_photon_2));
  catalogue.add_particle(std::move(higgs_boson));
}

void initialise_catalogue_leptons(ParticleCatalogue &catalogue)
{
  std::shared_ptr<Electron> electron = std::make_shared<Electron>(0);
  electron->deposit_energy(60.0, 20.5, 20.5, 19.0);
  catalogue.add_particle(std::move(electron));

  std::shared_ptr<Electron> anti_electron = std::make_shared<Electron>(1, 120.0, 40.0, 90.0, 10.0);
  anti_electron->deposit_energy(60.0, 20.5, 20.5, 19.0);
  catalogue.add_particle(std::move(anti_electron));

  std::shared_ptr<Muon> muon = std::make_shared<Muon>(0);
  catalogue.add_particle(std::move(muon));
  
  std::shared_ptr<Muon> anti_muon = std::make_shared<Muon>(1);
  catalogue.add_particle(std::move(anti_muon));

  //Tau Decaying into a anti up and down
  std::shared_ptr<Tau> tau = std::make_shared<Tau>(0);
  std::shared_ptr<Quark> decay_down = std::make_shared<Quark>("down", 0);
  decay_down->set_colour("blue");
  std::shared_ptr<Quark> decay_anti_up = std::make_shared<Quark>("up", 1);
  decay_anti_up->set_colour("red");
  tau->set_decay(std::move(decay_anti_up), std::move(decay_down));
  catalogue.add_particle(std::move(tau));

  
  //Anti-Tau Decaying into a positron
  std::shared_ptr<Tau> anti_tau = std::make_shared<Tau>(1);
  std::shared_ptr<Neutrino> decay_electron_neutrino = std::make_shared<Neutrino>("electron");
  decay_electron_neutrino->set_interacted(0);
  std::shared_ptr<Electron> decay_anti_electron = std::make_shared<Electron>(1, 120.0, 40.0, 90.0, 10.0);
  decay_anti_electron->deposit_energy(160.0, 20.5, 20.5, 19.0);
  anti_tau->set_decay(std::move(decay_anti_electron), std::move(decay_electron_neutrino));
  catalogue.add_particle(std::move(anti_tau));
}

void initialise_catalogue_neutrinos(ParticleCatalogue &catalogue)
{
  std::shared_ptr<Neutrino> electron_neutrino = std::make_shared<Neutrino>("electron");
  electron_neutrino->set_interacted(1);
  catalogue.add_particle(std::move(electron_neutrino));

  std::shared_ptr<Neutrino> anti_electron_neutrino = std::make_shared<Neutrino>("antielectron");
  anti_electron_neutrino->set_interacted(0);
  catalogue.add_particle(std::move(anti_electron_neutrino));

  std::shared_ptr<Neutrino> muon_neutrino = std::make_shared<Neutrino>("muon");
  muon_neutrino->set_interacted(1);
  catalogue.add_particle(std::move(muon_neutrino));

  std::shared_ptr<Neutrino> anti_muon_neutrino = std::make_shared<Neutrino>("antimuon");
  anti_muon_neutrino->set_interacted(0);
  catalogue.add_particle(std::move(anti_muon_neutrino));

  std::shared_ptr<Neutrino> tau_neutrino = std::make_shared<Neutrino>("tau");
  tau_neutrino->set_interacted(1);
  catalogue.add_particle(std::move(tau_neutrino));

  std::shared_ptr<Neutrino> anti_tau_neutrino = std::make_shared<Neutrino>("antitau");
  anti_tau_neutrino->set_interacted(0);
  catalogue.add_particle(std::move(anti_tau_neutrino));
}

int main()
{

  ParticleCatalogue catalogue;
  cout<<endl<<"Initializing container..."<<endl;
  initialise_catalogue_quarks(catalogue);
  initialise_catalogue_bosons(catalogue);
  initialise_catalogue_leptons(catalogue);
  initialise_catalogue_neutrinos(catalogue);
  cout<<endl<<"Now printing container with verbosity 0."<<endl;
  catalogue.print(catalogue.get_particle_container(), 0);
  cout<<endl<<"Printing details of a subcontainer of bosons with verbosity 1."<<endl;
  catalogue.print(catalogue.get_sub_container("boson"), 1);
  cout<<endl<<"Printing details of a subcontainer of neutrinos with verbosity 2."<<endl;
  catalogue.print(catalogue.get_sub_container("neutrino"), 2);

  cout<<"Momentum sum of lepton subcontainer : ";
  catalogue.sum_container_four_momentum(catalogue.get_sub_container("lepton")).print_four_momentum();
  cout<<endl<<endl<<endl;

  cout<<"Momentum sum of all particles in the catalogue : ";
  catalogue.sum_container_four_momentum(catalogue.get_particle_container()).print_four_momentum();
  cout<<endl;
  
  return 0;
}
