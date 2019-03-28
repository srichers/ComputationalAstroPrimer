#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <cassert>
#include "EOS.h"
#include "initial_conditions.h"
#include "Conservative_Primitive.h"
#include "reconstruct.h"
#include "HLL.h"
#include "evolve.h"
#include "misc.h"
using namespace std;

const int nx = 52;
const int nghost = 1;
const double dx = 1./nx;
const double tend = 0.1;
const double courant_factor = 0.1;
const double adiabatic_index = 1.4;
const double PL=1.0, PR=0.1, vL=0, vR=0, rhoL=1.0, rhoR=0.125;

int main(){
  // evolved variables. Assume tube cross-section of 1
  // [variable index][radial index]
  array<array<double,nx>, 3> primitive, conservative;
    
  // temporary variables - left and right side of interfaces
  // [0=left 1=right][variable index][radial index]
  array< array< array<double,nx-1>, 3>, 2> conservativeLR, primitiveLR;
  array<array<double,nx-1>, 3> flux, dc_dt;
  array<array<double,nx>, 3> dcons_dt;
  double max_wavespeed;
  
  // set up the EOS with an adiabatic index
  EOS eos;
  eos.gamma = adiabatic_index;
  
  // set up the initial conditions
  // rho left/right, vx left/right, pressure left/right
  set_initial_conditions<nx>(rhoL, rhoR, vL, vR, PL, PR, primitive);
  conservative = get_conservative<nx>(primitive, eos);
  
  // set up file
  int it=0;
  double t=0;
  ofstream output;
  output.open("output.dat");
  output << "# it t i rho vx P px Etot" << endl;
  print<nx>(output, it, t, primitive, conservative);
  
  // start time integration
  bool end = false;
  while(!end){
    // reconstruct to face values
    conservativeLR = piecewise_constant_reconstruct<nx>(conservative);

    // get primitive values at faces
    primitiveLR[0] = get_primitive<nx-1>(conservativeLR[0], eos);
    primitiveLR[1] = get_primitive<nx-1>(conservativeLR[1], eos);
    
    // get HLL fluxes at interfaces
    flux = HLL_flux<nx-1>(primitiveLR, conservativeLR, eos, &max_wavespeed);

    // use the flux to get the rate of change of conservative variables
    dcons_dt = dConservative_dt<nx>(flux, dx);

    // determine the timestep and evolve forward
    double dt = courant_factor * dx / max_wavespeed;
    if(t+dt > tend){
      dt = tend-t;
      end = true;
    }
    it++;
    t += dt;
    for(int v=0; v<3; v++)
      for(int i=0; i<nx; i++)
	conservative[v][i] += dt * dcons_dt[v][i];
    primitive = get_primitive<nx>(conservative, eos);
    
    // output the fluid data
    print<nx>(output, it, t, primitive, conservative);
  }

  output.close();
  return 0;
}
