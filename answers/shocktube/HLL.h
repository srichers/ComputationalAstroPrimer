template<int nx>
array< array<double,nx>, 2> HLL_wave_speeds
  (const array< array< array<double,nx>, 3>, 2> primitiveLR,
   const EOS& eos){
  
  array< array<double,nx>, 2> wavespeedLR;

  array<double,nx> csL = eos.soundspeed<nx>(primitiveLR[0][0],primitiveLR[0][2]);
  array<double,nx> csR = eos.soundspeed<nx>(primitiveLR[1][0],primitiveLR[1][2]);

  for(int i=0; i<nx; i++){
    wavespeedLR[0][i] = primitiveLR[0][1][i] - csL[i];
    wavespeedLR[1][i] = primitiveLR[1][1][i] + csR[i];
  }

  return wavespeedLR;
}

/* array<double,3> HLL_flux(const array<array<double,3>,2> primitiveLR, */
/* 			 const array<array<double,3>,2> conservativeLR, */
/* 			 const array<double,2> wavespeedLR){ */
/*   array<double,3> flux, fluxL, fluxR; */

/*   fluxL = conservative_flux(primitiveLR[0], conservativeLR[0]); */
/*   fluxR = conservative_flux(primitiveLR[1], conservativeLR[0]); */
  
/*   if     (wavespeedLR[0]>=0) flux = fluxL; */
/*   else if(wavespeedLR[1]<=0) flux = fluxR; */
/*   else */
/*     for(int i=0; i<3; i++){ */
/*       flux[i] = (wavespeedLR[1]*fluxL[i] - */
/* 		 wavespeedLR[0]*fluxR[i] + */
/* 		 wavespeedLR[0]*wavespeedLR[1] * (conservativeLR[1][i]-conservativeLR[0][i]) */
/* 		 ) / (wavespeedLR[1]-wavespeedLR[0]); */
/*     } */
  
/*   return flux; */
/* } */
