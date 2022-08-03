#ifndef INITIAL_H
#define INITIAL_H

#include <cassert>
#include <array>
using namespace std;
double poison = 0./0.;

//========================//
// set_initial_conditions //
//========================//
// set the initial conditions given left and right shocktube values
// call with:
//     primitive = initial_conditions<nx>(rhoL, rhoR, vxL, vxR, pressL, pressR);
template<int nx>
array<array<double,nx>,3> set_initial_conditions(double rhoL, double rhoR,
						 double vxL, double vxR,
						 double pressL, double pressR){
  
  array<array<double,nx>,3> primitive;

  // set left and right states
  // if left of middle use left values
  // if right of middle use right values
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

  return primitive;
}

#endif
