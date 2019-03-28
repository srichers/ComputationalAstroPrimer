#ifndef HLL_H
#define HLL_H

#include <cmath>
#include "flux.h"

//=================//
// HLL_wave_speeds //
//=================//
// return the left and right HLL wave speeds given left and right primitive values
// call with:
//     wavespeedLR = HLL_wave_speeds<nx>(primitiveLR, eos);
template<int nx>
array< array<double,nx>, 2> HLL_wave_speeds
  (const array< array< array<double,nx>, 3>, 2>& primitiveLR,
   const EOS& eos){
  
  array< array<double,nx>, 2> wavespeedLR;

  // use the EOS to get the sound speeds at the left and right of the interface
  //array<double,nx> csL = // IMPLEMENT ME
  //array<double,nx> csR = // IMPLEMENT ME

  // set the left and right wavespeeds according to HLL prescription
  for(int i=0; i<nx; i++){
    wavespeedLR[0][i] = 0;// IMPLEMENT ME
    wavespeedLR[1][i] = 0;// IMPLEMENT ME
  }

  return wavespeedLR;
}


//==========//
// HLL_flux //
//==========//
// return the flux at the interface given primitive and conservative variables
// on both sides of the interface. Also, return the maximum of the wave speeds
// for use in computing the timestep.
// call with:
//     flux = HLL_flux<nx>(primitiveLR, conservativeLR, eos, &max_wavespeed);
template<int nx>
array<array<double,nx>,3> HLL_flux(const array<array<array<double,nx>,3>,2>& primitiveLR,
				   const array<array<array<double,nx>,3>,2>& conservativeLR,
				   const EOS& eos, double* max_wavespeed){
  array<array<double,nx>,3> flux, fluxL, fluxR;

  // calculate the analytic left and right fluxes using fluid variables
  // on the corresponding side of the interface
  //fluxL = // IMPLEMENT ME
  //fluxR = // IMPLEMENT ME

  // get the left and right wave speeds
  // while we're at it, compute the maximum to pass back to determine timestep
  //array<array<double,nx>,2> wavespeedLR = // IMPLEMENT ME
  *max_wavespeed = 0; // IMPLEMENT ME
  
  // calculate flux using the HLL prescription
  for(int v=0; v<3; v++){
    for(int i=0; i<nx; i++){
      flux[v][i] = 0;// IMPLEMENT ME
    }
  }

  
  return flux;
}

#endif
