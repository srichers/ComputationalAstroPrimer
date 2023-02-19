#include <random> // default_random_engine, uniform_real_distribution
#include <cmath> // log
#include <omp.h> // thread stuff
#include <ctime> // time
using namespace std;


class RandomNumberGenerator{
 private:

  vector<default_random_engine> state;
  uniform_real_distribution<double> U;
  
 public:
  
  RandomNumberGenerator(){
    // define uniform numbers to be between 0 and 1
    U = uniform_real_distribution<double>(0,1);

    // resize the state vector to be the maximum number of threads
    int numthreads=1;
#ifdef _OPENMP
    numthreads = omp_get_max_threads();
#endif
    state.resize(numthreads);

    // properly initialize the states to random values
    state[0] = default_random_engine(time(NULL));
    for(int i=1; i<numthreads; i++)
      state[i] = default_random_engine(U(state[i-1]));
  }

  double uniform(){
    // use the appropriate state to generate a random number
    int threadID = 0;
#ifdef _OPENMP
    threadID = omp_get_thread_num();
#endif
    return U(state[threadID]);
  }
};
