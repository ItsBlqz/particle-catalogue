#include "Gluon.h"
#include <unordered_set>

Gluon::Gluon() : Boson{0}
{
  particle_name = "Gluon";
  particle_id = "gluon";
  set_colours("red", "antired");
}

Gluon::Gluon(std::string colour_1, std::string colour_2, bool anti_particle) : Boson{0}
{
  particle_name = "Gluon";
  particle_id = "gluon";
  set_colours(colour_1, colour_2);
  if(anti_particle)
    set_anti_particle();
}

Gluon::Gluon(std::string colour_1, std::string colour_2, bool anti_particle, double energy, double px, double py, double pz) : Boson{0, energy, px, py, pz}
{
  particle_name = "Gluon";
  particle_id = "gluon";
  set_colours(colour_1, colour_2);
  if(anti_particle)
    set_anti_particle();
}

void Gluon::set_colours(const std::string c1, const std::string c2)
{
  static const std::unordered_set<std::string> valid_colours = {"red", "green", "blue"};
  static const std::unordered_set<std::string> valid_anti_colours = {"antired", "antigreen", "antiblue"};
  std::string temp_c1_verifier = c1;
  std::string temp_c1 = clean_input(c1);

  std::string temp_c2_verifier = c2;
  std::string temp_c2 = clean_input(c2);

  if((valid_colours.find(temp_c1) != valid_colours.end()) && (valid_anti_colours.find(temp_c2) != valid_anti_colours.end()))
  {
    //In this case c1 is a valid colour and c2 is a valid anti-colour, if both are colours or anti-colours this won't be triggered
    colour = temp_c1;
    anti_colour = temp_c2;
  }
  else if ((valid_anti_colours.find(temp_c1) != valid_anti_colours.end()) && (valid_colours.find(temp_c2) != valid_colours.end()))
  {
    //Triggered when c1 is an anti-colour and c2 is a colour
    colour = temp_c2;
    anti_colour = temp_c1;
  }
  else
  {
    std::cerr<<"Invalid colour pair ["<<temp_c1<<", "<<temp_c2<<"] found for "<<particle_name<<". Please rectify. Reverting to default value of [red, anti-red]."<<endl;
    set_colours("red", "antired");
  }
  
}

void Gluon::print_info()
{
  print_base_data();
  cout<<endl;
  cout<<"Additional Info [Colour, Anti-Colour]: ["<<colour<<", "<<anti_colour<<"]"<<endl;
}

void Gluon::set_anti_particle()
{
  if(!is_anti_particle)
  {
    is_anti_particle = 1;
    //Gluon doesn't have charge so no reversal needed
    particle_name = "Anti-" + particle_name; //Not changing ID
    //Not changing colour as colours already in a pair of anticolour and colour
  }
}