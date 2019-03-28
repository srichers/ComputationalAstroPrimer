array<double, 2> HLL_wave_speeds(const array<double,3> primitiveL,
				 const array<double,3> primitiveR,
				 const EOS eos){
  array<double,2> wavespeedLR;

  double csL = eos.soundspeed(primitiveL[0],primitiveL[2]);
  double csR = eos.soundspeed(primitiveR[0],primitiveR[2]);

  wavespeedLR[0] = primitiveL[1] - csL;
  wavespeedLR[1] = primitiveR[1] + csR;

  return wavespeedLR;
}

array<double,3> HLL_flux(const array<array<double,3>,2> primitiveLR,
			 const array<array<double,3>,2> conservativeLR,
			 const array<double,2> wavespeedLR){
  array<double,3> flux, fluxL, fluxR;

  fluxL = conservative_flux(primitiveLR[0], conservativeLR[0]);
  fluxR = conservative_flux(primitiveLR[1], conservativeLR[0]);
  
  if     (wavespeedLR[0]>=0) flux = fluxL;
  else if(wavespeedLR[1]<=0) flux = fluxR;
  else
    for(int i=0; i<3; i++){
      flux[i] = (wavespeedLR[1]*fluxL[i] -
		 wavespeedLR[0]*fluxR[i] +
		 wavespeedLR[0]*wavespeedLR[1] * (conservativeLR[1][i]-conservativeLR[0][i])
		 ) / (wavespeedLR[1]-wavespeedLR[0]);
    }
  
  return flux;
}
