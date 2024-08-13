#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

#include <iostream>
#include <vector>
#include <type_traits>
#include <cmath>
#include <random>

using std::cout;
using std::endl;


template<class c_type> class FourMomentum
{
static_assert(std::is_arithmetic<c_type>::value, "Template parameter c_type must be a numeric type.");

private:
  std::vector<c_type>* four_momentum = new std::vector<c_type>(4);

public:
  FourMomentum() {this->set_E(0), this->set_px(0), this->set_py(0), this->set_pz(0);}
  FourMomentum(c_type temp_energy, c_type temp_px, c_type temp_py, c_type temp_pz);
  ~FourMomentum() {delete four_momentum;}

  //Copy and move operators and constructors
  FourMomentum(FourMomentum<c_type>&);
  FourMomentum(FourMomentum<c_type>&&);
  FourMomentum<c_type>& operator=(FourMomentum<c_type>&); //copy assignment
  FourMomentum<c_type>& operator=(FourMomentum<c_type>&&);

  // Setters
  void set_E(const c_type energy);
  void set_px(const c_type px) {four_momentum->at(1) = px;}
  void set_py(const c_type py) {four_momentum->at(2) = py;}
  void set_pz(const c_type pz) {four_momentum->at(3) = pz;}

  // Getters
  c_type get_E() const {return four_momentum->at(0);}
  c_type get_px() const {return four_momentum->at(1);}
  c_type get_py() const {return four_momentum->at(2);}
  c_type get_pz() const {return four_momentum->at(3);}

  c_type get_invariant_mass() const;
  bool validate_rest_mass(double);
  void print_four_momentum() const;

  FourMomentum<c_type> operator+(const FourMomentum<c_type> &); // Will add momentum
  FourMomentum<c_type> operator-(const FourMomentum<c_type> &); // Will subtract momentum
  c_type operator*(const FourMomentum<c_type> &) const; // Will dot momentum
  c_type dot_product(const FourMomentum<c_type> &, const FourMomentum<c_type> &) const; // Dot product with another particle

};

//Copy constructor and assignment
template<class c_type> FourMomentum<c_type>::FourMomentum(FourMomentum<c_type>& other)
{
  //Assigning values
  four_momentum->at(0) = other.get_E();
  four_momentum->at(1) = other.get_px();
  four_momentum->at(2) = other.get_py();
  four_momentum->at(3) = other.get_pz();
}

template<class c_type> FourMomentum<c_type>& FourMomentum<c_type>::operator=(FourMomentum<c_type>& other)
{
  if(&other == this) return *this;
  //Deleting the 4 momentum.
  delete four_momentum;
  four_momentum = new std::vector<double>(4);
  four_momentum->at(0) = other.get_E();
  four_momentum->at(1) = other.get_px();
  four_momentum->at(2) = other.get_py();
  four_momentum->at(3) = other.get_pz();
  return *this;
}

//Move constructor and assignment
template<class c_type> FourMomentum<c_type>::FourMomentum(FourMomentum<c_type>&& other)
{  
  four_momentum->at(0) = other.get_E();
  four_momentum->at(1) = other.get_px();
  four_momentum->at(2) = other.get_py();
  four_momentum->at(3) = other.get_pz();

  other.four_momentum = nullptr;
}

template<class c_type> FourMomentum<c_type>& FourMomentum<c_type>::operator=(FourMomentum<c_type>&& other)
{
  std::swap(four_momentum, other.four_momentum);
  return *this;
}

template<class c_type> FourMomentum<c_type>::FourMomentum(c_type temp_energy, c_type temp_px, c_type temp_py, c_type temp_pz)
{
  set_E(temp_energy);
  set_px(temp_px);
  set_py(temp_py);
  set_pz(temp_pz);
}

template<class c_type> void FourMomentum<c_type>::set_E(const c_type temp_energy)
{
  if(!(temp_energy >= 0))
  {
    std::cerr<<"Energy is less than 0! Please edit this to be greater than this! Exiting...";
    exit(0); 
  }
  four_momentum->at(0) = temp_energy;
}

template<class c_type> FourMomentum<c_type> FourMomentum<c_type>::operator+(const FourMomentum<c_type>& other) 
{
  return FourMomentum<c_type>(
    four_momentum->at(0) += other.get_E(),
    four_momentum->at(1) += other.get_px(),
    four_momentum->at(2) += other.get_py(),
    four_momentum->at(3) += other.get_pz()
  );
}

template<class c_type> FourMomentum<c_type> FourMomentum<c_type>::operator-(const FourMomentum<c_type>& other) 
{
  return FourMomentum<c_type>(
    four_momentum->at(0) -= other.get_E(),
    four_momentum->at(1) -= other.get_px(),
    four_momentum->at(2) -= other.get_py(),
    four_momentum->at(3) -= other.get_pz()
  );
}

template<class c_type> c_type FourMomentum<c_type>::operator*(const FourMomentum<c_type>& other) const
{
  return (
    four_momentum->at(0) * other.get_E()
    - four_momentum->at(1) * other.get_px()
    - four_momentum->at(2) * other.get_py()
    - four_momentum->at(3) * other.get_pz()
  );
}

template<class c_type> c_type FourMomentum<c_type>::dot_product(const FourMomentum<c_type>& f1, const FourMomentum<c_type>& f2) const
{
  return (f1.get_E()*f2.get_E() - 
  f1.get_px() * f2.get_px() - 
  f1.get_py() * f2.get_py() - 
  f1.get_pz() * f2.get_pz());
}

template<class c_type> void FourMomentum<c_type>::print_four_momentum() const
{
  cout<<"Four Momentum [E, px, py, pz] (MeV) : ["<<this->get_E()<<", "<<this->get_px()<<", "<<this->get_py()<<", "<<this->get_pz()<<"]";
}

template<class c_type> c_type FourMomentum<c_type>::get_invariant_mass() const 
{
  c_type temp_invariant_mass = (*this) * (*this);
  try
  {
    if(temp_invariant_mass < 0)
      throw std::domain_error("Negative mass squared encountered.");
    
  }
  catch(const std::exception& e)
  {
    std::cerr<<e.what()<<" ["<<this->get_E()<<", "<<this->get_px()<<", "<<this->get_py()<<", "<<this->get_pz()<<"] Please rectify. Exiting..."<<endl;
    exit(0);
  }
  return std::sqrt(temp_invariant_mass);
}

template<class c_type> bool FourMomentum<c_type>::validate_rest_mass(double rest_mass)
{
  //Rounding off the four momentum invariant mass to two decimal places first
  bool verified = false;
  c_type momentum_inv_mass = this->get_invariant_mass();
  momentum_inv_mass = std::round(momentum_inv_mass * 100) / 100; //This will round it two decimal places
  try
  {
    //Also makes sure that massless particle momentum is not (0, 0, 0, 0) as that is not possible for a particle to exist!
    if((momentum_inv_mass != rest_mass) || (rest_mass == 0 && this->get_E() == 0 && this->get_px() == 0 && this->get_py() == 0 && this->get_pz() == 0))
      throw std::domain_error("The invariant mass of the momentum is not the same as rest mass or all components are 0. Please rectify. Setting default values.");
    verified = true;
  }
  catch(const std::exception& e)
  {
    std::cerr<<e.what()<<endl;
    if(rest_mass > 0)
    {
      //Producing particle at rest.
      this->set_E(rest_mass);
      this->set_px(0);
      this->set_py(0);
      this->set_pz(0);
    }
    else
    {
      //For massless particles, sending particles in x direction with a random momentum
      std::default_random_engine engine(std::random_device{}());
      std::uniform_real_distribution<float> distribution(100.0f, 100000.0f); //Not using rand() as can cause problems
      float random_momentum = distribution(engine);

      this->set_E(random_momentum);
      this->set_px(random_momentum);
      this->set_py(0);
      this->set_pz(0);
    }
  }
  return verified;
}

#endif