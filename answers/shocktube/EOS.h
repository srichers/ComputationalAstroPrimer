#ifndef EOS_H
#define EOS_H

#include <array>
#include <cmath>
using namespace std;

// EOS class for ideal gas (P = eps*rho(gamma-1)
class EOS{
 public:
  double gamma;
  
  template<int nx>
  array<double,nx> internal_energy_density(const array<double,nx>& density,
					   const array<double,nx>& pressure) const{
    assert(gamma>1.); // make sure EOS is initialized

    array<double,nx> epsilon;
    for(int i=0; i<nx; i++)
      epsilon[i] = pressure[i] / (density[i] * (gamma-1.));

    return epsilon;
  }

  template<int nx>
  array<double,nx> pressure(const array<double,nx>& density,
			    const array<double,nx>& internal_energy_density) const{
    assert(gamma>1.); // make sure EOS is initialized

    array<double,nx> press;
    for(int i=0; i<nx; i++)
      press[i] = density[i] * internal_energy_density[i] * (gamma-1.);
    
    return press;
  }

  template<int nx>
  array<double,nx> soundspeed(const array<double,nx>& density,
				const array<double,nx>& pressure) const{
    assert(gamma>1.);

    array<double,nx> cs;
    for(int i=0; i<nx; i++)
      cs[i] = sqrt(gamma * pressure[i] / density[i]);

    return cs;
  }  
};

#endif
