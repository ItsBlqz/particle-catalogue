#include <iostream>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include <unordered_set>

#include "Quark.h"

using std::cout;
using std::endl;
using std::cerr;

const std::map <std::string, std::tuple<std::string, double, double>> Quark::quark_data = 
{
  // flavour, name, rest_mass, charge
  {"up", std::make_tuple("Up Quark", 2.3, 2.0/3.0)},
  {"down", std::make_tuple("Down Quark", 4.8, -1.0/3.0)},
  {"charm", std::make_tuple("Charm Quark", 1275, 2.0/3.0)},
  {"strange", std::make_tuple("Strange Quark", 95, -1.0/3.0)},
  {"top", std::make_tuple("Top Quark", 173070, 2.0/3.0)},
  {"bottom", std::make_tuple("Bottom Quark", 4180, -1.0/3.0)},
};

Quark::Quark() : Particle{0}
{
  spin = 1.0/2.0;
  set_flavour("up"); //A default placeholder in case someone forgets to set flavour, prevents code breakage
  set_colour("red"); //A default placeholder here aswell;
  particle_four_momentum->set_E(rest_mass); //Default Initialisation
  particle_four_momentum->set_px(0);
  particle_four_momentum->set_py(0);
  particle_four_momentum->set_pz(0);
  base_particle_type = "quark";
}

Quark::Quark(std::string flavour, bool anti_particle) : Particle{0}
{
  spin = 1.0/2.0;
  set_flavour(flavour);
  set_colour("red"); //A default placeholder here aswell;
  particle_four_momentum->set_E(rest_mass); //Default Initialisation
  particle_four_momentum->set_px(0);
  particle_four_momentum->set_py(0);
  particle_four_momentum->set_pz(0);
  base_particle_type = "quark";
  if(anti_particle)
    set_anti_particle();
}

Quark::Quark(std::string flavour, bool anti_particle, double energy, double px, double py, double pz) : Particle{0, energy, px, py, pz}
{
  spin = 1.0/2.0;
  set_flavour(flavour);
  set_colour("red"); 
  base_particle_type = "quark";
  if(anti_particle)
    set_anti_particle();
}

void Quark::set_flavour(const std::string flavour)
{
  std::string temp_flavour_verifier = flavour;
  std::string temp_flavour = clean_input(flavour);

  // Now finally checking if this exists in the particle set
  try
  {
    auto it = quark_data.find(temp_flavour);
    if(it == quark_data.end())
      throw std::invalid_argument("Invalid quark type [" + temp_flavour + "]. ");
    
    //Since the quark/anti-quark now exists. Setting the necessary things.
    const auto& quark_info = quark_data.at(temp_flavour);
    const auto& [formatted_flavour, quark_mass, quark_charge] = quark_info;

    if(temp_flavour != temp_flavour_verifier)
      cout<<"Corrected the input "<<flavour<<". I think you meant "<<temp_flavour<<"."<<endl;
    
    //Now setting the variables
    quark_flavour = formatted_flavour;
    rest_mass = quark_mass;
    charge = quark_charge;
    //Setting the particle_id here itself
    particle_id = temp_flavour; //Not setting anti-up etc as that can be obtained from get_anti_particle()!
    particle_name = quark_flavour;

    if(is_anti_particle)
      set_anti_particle(); // Running in case someone declares an empty quark and sets it as an anti-particle before setting the flavour
  }
  catch(const std::exception& e)
  {
    cerr<<e.what()<<"Please rectify. Reverting to default flavour: up"<<endl;
    set_flavour("up");
  }
}

void Quark::set_colour(const std::string colour)
{
  // Using a set to check if valid color as this has constant time complexity (ideally) and allows for a cleaner dynamic code
  static const std::unordered_set<std::string> valid_colours = {"red", "green", "blue"};
  static const std::unordered_set<std::string> valid_anti_colours = {"antired", "antigreen", "antiblue"};
  std::string temp_quark_colour_verifier = colour;
  std::string temp_quark_colour = clean_input(colour);
  // Find a nice way to set anti-colours, maybe use 3 bools and set one of the bool to true? Might be easier this way for gluons pairing
  if(!get_if_anti_particle())
  {
    if(valid_colours.find(temp_quark_colour) == valid_colours.end())
    {
      cerr<<"Invalid colour type ["<<temp_quark_colour<<"] found for "<<particle_name<<". Please rectify. Reverting to default value of red."<<endl;
      set_colour("red");
    }
  }
  else
  {
    if(valid_anti_colours.find(temp_quark_colour) == valid_anti_colours.end())
    {
      cerr<<"Invalid colour type ["<<temp_quark_colour<<"] found for "<<particle_name<<". Please rectify. Reverting to default value of anti-red."<<endl;
      set_colour("antired");
    }
  }
  quark_colour = temp_quark_colour;
}

void Quark::set_anti_particle()
{
  if(!is_anti_particle)
  {
    is_anti_particle = 1;
    // Reversing signs of charge and baryon number
    charge *= -1;
    baryon_number *= -1;
    particle_name = "Anti-" + particle_name;
    if(!check_substring_contained("anti", quark_colour))
      quark_colour = "anti" + quark_colour; //Changes colour to anti-colour if someone sets colour before setting anti-particle
  }
}

void Quark::print_info()
{
  print_base_data();
  cout<<endl;
  cout<<"Additional Info [Colour, Baryon Number]: ["<<quark_colour<<", "<<beautify_fractions(baryon_number)<<"]"<<endl;
}