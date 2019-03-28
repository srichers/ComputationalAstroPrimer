#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <cassert>
#include "EOS.h"
#include "initial_conditions.h"
#include "misc.h"
using namespace std;

const int nx = 52;
const int nghost = 1;
const double dx = 1./nx;
const double tend = 10.;
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

  // Eint is internal energy density
  // px is x momentum density
  array<double,nx> x, rho, Eint, px;

  // set up the EOS with an adiabatic index
  EOS eos;
  eos.gamma = adiabatic_index;
  
  // set up the initial conditions
  // rho left/right, vx left/right, pressure left/right
  set_initial_conditions<nx>(rhoL, rhoR, vL, vR, PL, PR, primitive);

  // set up file
  int it=0;
  double t=0;
  ofstream output;
  output.open("output.dat");
  output << "# it t i x rho vx P px Etot" << endl;
  print<nx>(output, it, t, primitive, conservative);
  
  // // start time integration
  // bool end = false;
  // while(!end){
  //   // get dt
  //   double cs_max = max(eos.csound(rho,P));
  //   double dt= courant * dx / cs_max;
  //   if(t+dt > tend){
  //     dt = tend-t;
  //     end = true; // prevent infinite loop due to floating point precision in t
  //   }

  //   // Physics!
  //   vx = px / rho;
  //   P = eos.pressure(rho,Eint);
  //   dpx_dt = -grad(P,dx);
  //   drho_dt = -rho * div(vx,dx);
  //   dEint_dt = -P * div(vx,dx);
    
  //   // increment the timestep
  //   t += dt;
  //   it++;
  //   px   = px   +   dpx_dt*dt;
  //   rho  = rho  +  drho_dt*dt;
  //   Eint = Eint + dEint_dt*dt;

  //   // output the fluid data
  //   print(output, it, t, dt, x, rho, Eint, px);
  // }

  output.close();
  return 0;
}
