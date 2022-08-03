#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <cassert>
#include "EOS.h"
#include "operator.h"
#include "misc.h"
using namespace std;

const int nx = 100;
const int nghost = 1;
const double dx = 1./nx;
const double tend = 0.25;
const double courant = 0.1;
const int arrlen = nx + 2*nghost;

void reflecting_boundary_conditions(array<double,arrlen>& px, array<double,arrlen>& rho, array<double,arrlen>& Eint){
    for(int i=0; i<nghost; i++){
      int iL_ghost = i;
      int iL_real = 2*nghost-1-i;
      int iR_ghost = arrlen-1-i;
      int iR_real = arrlen-2*nghost+i;
      px[iL_ghost] = px[iL_real];
      px[iR_ghost] = px[iR_real];
      rho[iL_ghost] = rho[iL_real];
      rho[iR_ghost] = rho[iR_real];
      Eint[iL_ghost] = Eint[iL_real];
      Eint[iR_ghost] = Eint[iR_real];
    }
}

int main(){
  // evolved variables. Assume tube cross-section of 1
  // Eint is internal energy density
  // px is x momentum density
  array<double,arrlen> x, rho, Eint, px;

  // temporary variables
  array<double,arrlen> P, kT, dEint_dt, dpx_dt, drho_dt, vx;
  
  EOS eos;
  
  // set up the initial conditions
  for(int i=0; i<arrlen; i++){
    x[i] = dx * (.5+i-nghost);
    rho[i] = (i<arrlen/2 ? 1.0 : 0.125);
    P[i]   = (i<arrlen/2 ? 1.0 : 0.1);
    px[i] = 0;
  }
  Eint = eos.Eint(rho,P);
  reflecting_boundary_conditions(px, rho, Eint);

  // set up file
  int it=0;
  double t=0;
  ofstream output;
  output.open("output.dat");
  output << "# it t ix x rho px Etot" << endl;
  print(output, it, t, 0, x, rho, px, Eint);
  
  // start time integration
  bool end = false;
  while(!end){
    // get dt
    double cs_max = max(eos.csound(rho,P));
    double dt= courant * dx / cs_max;
    if(t+dt > tend){
      dt = tend-t;
      end = true; // prevent infinite loop due to floating point precision in t
    }

    // Physics!
    vx = px / rho;
    P = eos.pressure(rho,Eint);
    dpx_dt = -grad(P,dx);
    drho_dt = -rho * div(vx,dx);
    dEint_dt = -P * div(vx,dx);
    
    // increment the timestep
    t += dt;
    it++;
    px   = px   +   dpx_dt*dt;
    rho  = rho  +  drho_dt*dt;
    Eint = Eint + dEint_dt*dt;

    // reflecting boundary conditions
    reflecting_boundary_conditions(px, rho, Eint);
    
    // output the fluid data
    print(output, it, t, dt, x, rho, px, Eint);
  }

  output.close();
  return 0;
}
