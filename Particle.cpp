#include <sstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include "Particle.h"

Particle::Particle()
{
  //Default four momentum, since no particle initialised yet, performs no validation!
  particle_four_momentum = std::make_unique<FourMomentum<double>>(0, 0, 0, 0);  
}

Particle::Particle(double mass)
{
  rest_mass = mass;
  //Default four momentum, different initialisations for massless particles as (0, 0, 0, 0) not a valid momentum!
  if (rest_mass > 0)
  {
    particle_four_momentum = std::make_unique<FourMomentum<double>>(rest_mass, 0, 0, 0);
  }
  else
  {
    //Setting a random momentum for massless particles
    std::default_random_engine engine(std::random_device{}());
    std::uniform_real_distribution<float> distribution(100.0f, 100000.0f); //Not using rand() as can cause problems
    float random_momentum = distribution(engine);
    particle_four_momentum = std::make_unique<FourMomentum<double>>(random_momentum, random_momentum, 0, 0); 
  }
  particle_four_momentum->validate_rest_mass(rest_mass);
  
}

Particle::Particle(double mass, double energy, double px, double py, double pz)
{
  rest_mass = mass;
  particle_four_momentum = std::make_unique<FourMomentum<double>>(energy, px, py, pz);
  particle_four_momentum->validate_rest_mass(rest_mass);
}

//Copy constructor and assignment
Particle::Particle(Particle& p)
{
  charge = p.charge;
  rest_mass = p.rest_mass;
  spin = p.spin;
  is_anti_particle = p.is_anti_particle;
  particle_four_momentum = std::make_unique<FourMomentum<double>>(p.get_four_momentum().get_E(), p.get_four_momentum().get_px(), p.get_four_momentum().get_py(), p.get_four_momentum().get_pz());
  particle_name = p.particle_name;
  base_particle_type = p.base_particle_type;
  particle_id = p.base_particle_type;
}

Particle& Particle::operator=(Particle& p)
{
  if(&p == this) return *this; // Avoiding self assignment
  //Copying all other data types
  charge = p.charge;
  rest_mass = p.rest_mass;
  spin = p.spin;
  is_anti_particle = p.is_anti_particle;
  particle_four_momentum = std::make_unique<FourMomentum<double>>(p.get_four_momentum().get_E(), p.get_four_momentum().get_px(), p.get_four_momentum().get_py(), p.get_four_momentum().get_pz());
  particle_name = p.particle_name;
  base_particle_type = p.base_particle_type;
  particle_id = p.base_particle_type;

  return *this;
}

//Move constructor and assignment
Particle::Particle(Particle&& p)
{
  //Copying all other data types
  charge = p.charge;
  rest_mass = p.rest_mass;
  spin = p.spin;
  is_anti_particle = p.is_anti_particle;
  particle_four_momentum = std::move(p.particle_four_momentum); //The original particle four momentum becomes null automatically
  particle_name = p.particle_name;
  base_particle_type = p.base_particle_type;
  particle_id = p.base_particle_type;

}

Particle& Particle::operator=(Particle&& p)
{
  std::swap(charge, p.charge);
  std::swap(rest_mass, p.rest_mass);
  std::swap(spin, p.spin);
  std::swap(is_anti_particle, p.is_anti_particle);
  std::swap(particle_name, p.particle_name);
  std::swap(particle_four_momentum, p.particle_four_momentum);
  std::swap(particle_id, p.particle_id);
  std::swap(base_particle_type, p.base_particle_type);

  return *this;
}


std::string Particle::clean_input(std::string input_str)
{
  std::transform(input_str.begin(), input_str.end(), input_str.begin(), [](unsigned char c) { return std::tolower(c); }); //First converting this to lowercase for ease of comparison
  input_str.erase(std::remove_if(input_str.begin(), input_str.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }), input_str.end()); //Removing all characters like space, tab, etc from the string
  // Also removing non-alpha characters to clean the input
  input_str.erase(std::remove_if(input_str.begin(), input_str.end(), [](char c) { return !std::isalpha(static_cast<unsigned char>(c)); }), input_str.end());
  return input_str;
}

bool Particle::check_substring_contained(std::string text, std::set<std::string> str_set)
{
  bool found = false;
  for (const std::string& substring : str_set) {
    if (text.find(substring) != std::string::npos) {
      found = true;
      break;
    }
  }
  return found;
}

bool Particle::check_substring_contained(std::string text, std::string substring)
{
  size_t found_position = text.find(substring);
  if (found_position != std::string::npos)
    return true;
  return false;
}

void Particle::print_base_data()
{
  std::cout<<particle_name<<" Info: ";
  cout<<"[Rest Mass (MeV), Charge (e), Spin, (E, px, py, pz) MeV] : ["
      <<(rest_mass > 1e4 ? std::setprecision(6) : std::setprecision(4))<<rest_mass<<", "
      <<beautify_fractions(charge)
      <<", "<<beautify_fractions(spin)
      <<std::setprecision(4)
      <<", ("<<particle_four_momentum->get_E()
      <<", "<<particle_four_momentum->get_px()
      <<", "<<particle_four_momentum->get_py()
      <<", "<<particle_four_momentum->get_pz()
      <<")]";

}

std::string Particle::beautify_fractions(double number)
{
  if(number == (2.0/3.0)) return "2/3";
  if(number == -(2.0/3.0)) return "-2/3";
  if(number == (1.0/3.0)) return "1/3";
  if(number == -(1.0/3.0)) return "-1/3";
  if(number == (1.0/2.0)) return "1/2";
  if(number == -(1.0/2.0)) return "-1/2";
  if(number == -1) return "-1";
  if(number == 1) return "1";
  if(number == 0) return "0";
  return std::to_string(number);
}


