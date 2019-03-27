#include <array>
#include <cmath>
using namespace std;

// EOS class for ideal gas (P = eps*rho(gamma-1)
class EOS{
 public:
  double gamma;
  
  double internal_energy_density(double density, double pressure){
    assert(gamma>1.); // make sure EOS is initialized

    return pressure / (density * (gamma-1.));
  }

  double pressure(double density, double internal_energy_density){
    assert(gamma>1.); // make sure EOS is initialized

    return density * internal_energy_density * (gamma-1.);
  }

  double soundspeed(double density, double pressure){
    assert(gamma>1.);

    return sqrt(gamma * pressure / density);
  }  
};
