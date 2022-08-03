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
  array<double,nx> csL = eos.soundspeed<nx>(primitiveLR[0][0],primitiveLR[0][2]);
  array<double,nx> csR = eos.soundspeed<nx>(primitiveLR[1][0],primitiveLR[1][2]);

  // set the left and right wavespeeds according to HLL prescription
  for(int i=0; i<nx; i++){
    wavespeedLR[0][i] = primitiveLR[0][1][i] - csL[i];
    wavespeedLR[1][i] = primitiveLR[1][1][i] + csR[i];
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
  fluxL = conservative_flux<nx>(primitiveLR[0], conservativeLR[0]);
  fluxR = conservative_flux<nx>(primitiveLR[1], conservativeLR[1]);

  // get the left and right wave speeds
  // while we're at it, compute the maximum to pass back to determine timestep
  array<array<double,nx>,2> wavespeedLR = HLL_wave_speeds<nx>(primitiveLR, eos);
  *max_wavespeed = 0;
  for(int LR=0; LR<=1; LR++)
    for(int i=0; i<nx; i++)
    *max_wavespeed = max(*max_wavespeed, abs(wavespeedLR[LR][i]));
  
  // calculate center flux using the HLL prescription
  for(int v=0; v<3; v++){
    for(int i=0; i<nx; i++){
      flux[v][i] = (wavespeedLR[1][i]*fluxL[v][i] -
		    wavespeedLR[0][i]*fluxR[v][i] +
		    wavespeedLR[0][i]*wavespeedLR[1][i] *
		    (conservativeLR[1][v][i]-conservativeLR[0][v][i])
		    ) / (wavespeedLR[1][i]-wavespeedLR[0][i]);
    }
  }

  // apply limiting logic
  // if left speed is positive, the interface flux is the left flux
  // if the right speed is negative, the interface flux is the right flux
  for(int i=0; i<nx; i++){
    if (wavespeedLR[0][i]>=0)
      for(int v=0; v<3; v++)
	flux[v][i] = fluxL[v][i];
    else if(wavespeedLR[1][i]<=0)
      for(int v=0; v<3; v++)
	flux[v][i] = fluxR[v][i];
  }
  
  return flux;
}

#endif
