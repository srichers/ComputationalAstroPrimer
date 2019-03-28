#include <cassert>
#include <array>
using namespace std;
double poison = 0./0.;

// set the initial conditions
template<int nx,int nghost>
void set_initial_conditions(double rhoL, double rhoR,
			    double vxL, double vxR,
			    double pressL, double pressR,
			    array< array<double,nx>, 3>& primitive){
  // make sure our array is big enough
  assert(nx > 2*nghost);
  
  // set left and right states
  for(int i=0; i<nx; i++){
    if(i<nx/2){
      primitive[0][i] = rhoL;
      primitive[1][i] = vxL;
      primitive[2][i] = pressL;
    }
    else{
      primitive[0][i] = rhoR;
      primitive[1][i] = vxR;
      primitive[2][i] = pressR;
    }
  }
}
