#include <random> // default_random_engine, uniform_real_distribution
#include <cmath> // log
using namespace std;


class RandomNumberGenerator{
 private:

  default_random_engine state;
  uniform_real_distribution<double> U;
  
 public:
  
  // initialize the random number generator with a seed
  RandomNumberGenerator(int seed){
    state = std::default_random_engine(seed);
    U = uniform_real_distribution<double>(0,1);
  }

  double uniform(){
    return U(state);
  }
};
