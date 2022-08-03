#include <array>
using namespace std;

// EOS class for ideal gas (P = nkT). k is assumed to be 1.
// for now, assume m=1 so rho=n
class EOS{
 public:
  template<size_t nx>
  array<double,nx> pressure(const array<double,nx> rho, const array<double,nx> Eint) const{
    array<double,nx> result = 2./3. * Eint;
    return result;
  }

  template<size_t nx>
  array<double,nx> csound(const array<double,nx> rho, const array<double,nx> P) const{
    array<double,nx> result = P/rho;
    return result;
  }

  template<size_t nx>
  array<double,nx> Eint(const array<double,nx> rho, const array<double,nx> P) const{
    return 3./2. * P;
  }
};
