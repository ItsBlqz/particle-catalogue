#include <algorithm>
#include <sstream>
#include <map>

#include "ParticleCatalogue.h"
#include "Boson.h"
#include "Quark.h"

void ParticleCatalogue::add_particle(std::shared_ptr<Particle> particle)
{
  //Will move this to the main container instead of keeping it shared
  particle_container.push_back(std::move(particle));
}
void ParticleCatalogue::print(std::vector<std::shared_ptr<Particle>> container, int verbosity)
{
  //Verbosity = 0, Only prints particle counts inside the container
  //Verbosity = 1, Prints names of each particle grouped by type and counts
  //Verbosity = 2, Prints all particle information again grouped by type

  //Using a vector in combination with a pair to have clean printing and preserve order
  std::vector<std::tuple<std::string, std::string, bool>> filters = 
  {
    //Tuple contains valid filter, polished name, boolean if particle or anti-particle
    std::make_tuple("boson", "Bosons", 0),
    std::make_tuple("antiboson", "Anti-Bosons", 1),
    std::make_tuple("quark", "Quarks", 0),
    std::make_tuple("antiquark", "Anti-Quarks", 1),
    std::make_tuple("lepton", "Leptons", 0),
    std::make_tuple("antilepton", "Anti-Leptons", 1),
    std::make_tuple("neutrino", "Neutrinos", 0),
    std::make_tuple("antineutrino", "Anti-Neutrinos", 1)
  };
  if(verbosity == 0)
  {
    cout<<"================================================================"<<endl;
    cout<<"Particle Catalogue"<<endl;
    cout<<"================================================================"<<endl;
    cout<<"Total Particles: "<<get_particle_count(container, "all")<<endl;
    for (const auto& tuple : filters) 
    {
      if(get_particle_count(container, std::get<0>(tuple)) > 0)
        cout<<std::get<1>(tuple)<<": "<<get_particle_count(container, std::get<0>(tuple))<<endl;
    }
    cout<<"----------------------------------------------------------------"<<endl;
  }
  else if(verbosity == 1 || verbosity == 2)
  {
    for (const auto& tuple : filters) 
    {
      if(get_particle_count(container, std::get<0>(tuple)) > 0)
      {
        cout<<"================================================================"<<endl;
        cout<<"Particle Catalogue : ";
        std::for_each(std::get<1>(tuple).begin(), std::get<1>(tuple).end(), [](unsigned char c)
        {
          std::cout << static_cast<char>(std::toupper(c)); //Printing in all caps
        });
        cout<<" : "<<get_particle_count(container, std::get<0>(tuple))<<endl;
        cout<<"================================================================"<<endl<<endl;
        for(auto particle : container)
        {
          if(((particle->get_base_particle_type() == std::get<0>(tuple)) || ("anti" + particle->get_base_particle_type() == std::get<0>(tuple))) && particle->get_if_anti_particle() == std::get<2>(tuple))
          {
            //The anti is needed as an or check because base type doesn't have anti in it.
            if(verbosity == 1) cout<<"\""<<particle->get_particle_name()<<"\" ";
            if(verbosity == 2)
            {
              particle->print_info();
              cout<<endl;
            }
          }
        }
        cout<<endl;
        cout<<"----------------------------------------------------------------"<<endl<<endl;
        }
    }
  }
  else
  {
    std::cerr<<"Incorrect value of verbosity! It should be 0-2. Please rectify! Displaying with verbosity 0!"<<endl;
    print(container, 0);
  }
}

int ParticleCatalogue::get_particle_count(std::vector<std::shared_ptr<Particle>> container, std::string query)
{
  int count = 0;
  query = clean_input(query);

  std::map<std::string, bool> query_verifier = 
  {
    //The map represents a Valid query as key and if anti-particle or not boolean as element
    {"boson", 0},
    {"antiboson", 1},
    {"quark", 0},
    {"antiquark", 1},
    {"lepton", 0},
    {"antilepton", 1},
    {"neutrino", 0},
    {"antineutrino", 1},
  };

  if(query == "all" || query == "a")
  {
    count = container.size();
  }
  else if (query_verifier.find(query) != query_verifier.end())
  {
    for(auto particle : container)
    {
      if(((particle->get_base_particle_type() == query) || ("anti" + particle->get_base_particle_type() == query)) && particle->get_if_anti_particle() == query_verifier.at(query))
        count++;
    }
  }
  else
  { 
    //Now checking if that particle_id is found
    bool found = false;
    for(auto particle : container)
    {
      if(particle->get_particle_id() == query)
        count++;
    }
    if (count > 0) found=true;

    if (!found)
    {
      std::cerr<<"Invalid query ["<<query<<"] please use a valid filter! Exiting..."<<endl;
      exit(0);
    }
  }
  
  return count;
}

std::string ParticleCatalogue::clean_input(std::string input_str)
{
  std::transform(input_str.begin(), input_str.end(), input_str.begin(), [](unsigned char c) { return std::tolower(c); }); //First converting this to lowercase for ease of comparison
  input_str.erase(std::remove_if(input_str.begin(), input_str.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }), input_str.end()); //Removing all characters like space, tab, etc from the string
  // Also removing non-alpha characters to clean the input
  input_str.erase(std::remove_if(input_str.begin(), input_str.end(), [](char c) { return !std::isalpha(static_cast<unsigned char>(c)); }), input_str.end());
  return input_str;
}

std::vector<std::shared_ptr<Particle>> ParticleCatalogue::get_sub_container(std::string filter)
{
  std::vector<std::shared_ptr<Particle>> sub_container;
  filter = clean_input(filter);
  bool found = false;
  for(int i = 0; i < particle_container.size(); i++)
  {
    if(particle_container[i]->get_base_particle_type() == filter)
    {
      sub_container.push_back(particle_container[i]); //This does not transfer ownership to the subcontainer!
      found = true;
    }
    else if(particle_container[i]->get_particle_id() == filter)
    {
      sub_container.push_back(particle_container[i]); //Also sorting by particle_id
      found = true;
    }
  }
  if(!found)
  {
    std::cerr<<"Invalid query ["<<filter<<"] or none found. Please rectify! Exiting..."<<endl;
    exit(0);
  }

  return sub_container;
}


FourMomentum<double> ParticleCatalogue::sum_container_four_momentum(std::vector<std::shared_ptr<Particle>> container)
{
  FourMomentum<double> momentum{0, 0, 0, 0};
  for(auto particle : container)
  {
    momentum = momentum + particle->get_four_momentum();
  }
  return momentum;
}
