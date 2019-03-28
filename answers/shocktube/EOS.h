#ifndef EOS_H
#define EOS_H

#include <array>
#include <cmath>
using namespace std;

// EOS class for ideal gas [P = eps*rho(gamma-1)]
class EOS{
 public:
  double gamma; // adiabatic index
  
  // constructor
  // When you make and EOS, you have to give it an adiabatic index
  // call with:
  //      EOS eos(adiabatic_index);
 EOS(double in_gamma):gamma(in_gamma) {}
  
  // set internal energy density array given array of density and pressure
  template<int nx>
  array<double,nx> internal_energy_density(const array<double,nx>& density,
					   const array<double,nx>& pressure) const{
    array<double,nx> epsilon;
    for(int i=0; i<nx; i++)
      epsilon[i] = pressure[i] / (density[i] * (gamma-1.));

    return epsilon;
  }

  template<int nx>
  array<double,nx> pressure(const array<double,nx>& density,
			    const array<double,nx>& internal_energy_density) const{
    array<double,nx> press;
    for(int i=0; i<nx; i++)
      press[i] = density[i] * internal_energy_density[i] * (gamma-1.);
    
    return press;
  }

  template<int nx>
  array<double,nx> soundspeed(const array<double,nx>& density,
				const array<double,nx>& pressure) const{
    array<double,nx> cs;
    for(int i=0; i<nx; i++)
      cs[i] = sqrt(gamma * pressure[i] / density[i]);

    return cs;
  }  
};

#endif
