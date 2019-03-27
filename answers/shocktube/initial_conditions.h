#include <cassert>
#include <array>
using namespace std;
double poison = 0./0.;

// set the initial conditions
template<int nx,int nghost>
void set_initial_conditions(double rhoL, double rhoR, array<double,nx>& rho,
			      double EintL, double EintR, array<double,nx>& Eint,
			      double pxL, double pxR, array<double,nx>& px){
  // make sure our array is big enough
  assert(nx > 2*nghost);
  
  // set left and right states
  for(int i=0; i<nx; i++){
    if(i<nx/2){
      rho[i] = rhoL;
      Eint[i] = EintL;
      px[i] = pxL;
    }
    else{
      rho[i] = rhoR;
      Eint[i] = EintR;
      px[i] = pxR;
    }
  }
}
