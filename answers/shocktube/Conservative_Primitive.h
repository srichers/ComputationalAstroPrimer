#include <array>

// given conservative variables, return primitive variables
template<int nx>
array<array<double,nx>,3> get_primitive(const array<array<double,nx>,3>& conservative,
					const EOS& eos){
  array<array<double,nx>,3> primitive;

  // density
  for(int i=0; i<nx; i++)
    primitive[0][i] = conservative[0][i];

  // velocity
  for(int i=0; i<nx; i++)
    primitive[1][i] = conservative[1][i]/conservative[0][i];

  // pressure
  for(int i=0; i<nx; i++){
    double internal_energy_density = 1./conservative[0][i] *
      (conservative[2][i] - .5*(conservative[1][i]*conservative[1][i]/conservative[0][i]) );
    primitive[2][i] = eos.pressure(conservative[0][i], internal_energy_density);
  }
    
  return primitive;
}

// given primitive variables, return conservative variables
template<int nx>
array<array<double,nx>,3> get_conservative(const array<array<double,nx>,3>& primitive,
					   const EOS& eos){
  array<array<double,nx>,3> conservative;

  // density
  for(int i=0; i<nx; i++)
    conservative[0][i] = primitive[0][i];

  // momentum density
  for(int i=0; i<nx; i++)
    conservative[1][i] = primitive[0][i]*primitive[1][i];

  // total energy density
  for(int i=0; i<nx; i++){
    double internal_energy_density = eos.internal_energy_density(primitive[0][i],primitive[2][i]);
    conservative[2][i] = primitive[0][i] * (.5*primitive[1][i]*primitive[1][i]
					    + internal_energy_density);
  }

  return conservative;
}
