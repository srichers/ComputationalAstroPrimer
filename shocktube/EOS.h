#ifndef EOS_H
#define EOS_H

#include <array>
#include <cmath>
using namespace std;

// EOS class for ideal gas [P = eps*rho(gamma-1)]
class EOS{
 public:
  double gamma; // adiabatic index

  //=================//
  // EOS constructor //
  //=================//
  // When you make and EOS, you have to give it an adiabatic index
  // call with:
  //      EOS eos(adiabatic_index);
 EOS(double in_gamma):gamma(in_gamma) {}

  //=========================//
  // internal_energy_density //
  //=========================//
  // set internal energy density array given array of density and pressure
  // call with:
  //      epsilon = internal_energy_density<nx>(density, press);
  template<int nx>
  array<double,nx> internal_energy_density(const array<double,nx>& density,
					   const array<double,nx>& pressure) const{
    array<double,nx> epsilon;
    for(int i=0; i<nx; i++)
      epsilon[i] = 0;// IMPLEMENT ME

    return epsilon;
  }

  //==========//
  // pressure //
  //==========//
  // set pressure array given array of density and internal energy density
  // call with:
  //      press = pressure<nx>(density, epsilon);
  template<int nx>
  array<double,nx> pressure(const array<double,nx>& density,
			    const array<double,nx>& internal_energy_density) const{
    array<double,nx> press;
    for(int i=0; i<nx; i++)
      press[i] = 0;//IMPLEMENT ME
    
    return press;
  }

  //============//
  // soundspeed //
  //============//
  // set sound speed array given array of density and pressure
  // call with:
  //      cs = soundspeed<nx>(density, press);
  template<int nx>
  array<double,nx> soundspeed(const array<double,nx>& density,
				const array<double,nx>& pressure) const{
    array<double,nx> cs;
    for(int i=0; i<nx; i++)
      cs[i] = 0;//IMPLEMENT ME

    return cs;
  }  
};

#endif
