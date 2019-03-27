#include <array>

// this should get the values at the left (0) and right (1) side of each cell
// This is trivial for piecewise constant, but not so trivial for higher-order schemes.
template<typename T, int nx>
array< array<T,nx-1>, 2> piecewise_constant_reconstruct(array<T,nx> input){

  array< array<T,nx-1> ,2> output;

  for(int i=0; i<nx-1; i++){
    output[0][i] = input[i];
    output[1][i] = input[i+1];
  }

  return output;
}
