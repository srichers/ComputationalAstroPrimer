#include <array>
// primitive: [density, velocity, pressure]
// conservative: [density, momentum density, energy density]

// given conservative variables, return primitive variables
array<double,3> get_primitive(const array<double,3>& conservative, const EOS& eos){
  array<double,3> prim;

  // density
  prim[0] = conservative[0];

  // velocity
  prim[1] = conservative[1]/conservative[0];

  // pressure
  double internal_energy_density = 1./conservative[0] *
    (conservative[2] - .5*(conservative[1]*conservative[1]/conservative[0]) );
  prim[2] = eos.pressure(conservative[0], internal_energy_density);

  return prim;
}

// given primitive variables, return conservative variables
array<double,3> get_conservative(const array<double,3>& primitive, const EOS& eos){
  array<double,3> con;

  // density
  con[0] = primitive[0];

  // momentum density
  con[1] = primitive[0]*primitive[1];

  // total energy density
  double internal_energy_density = eos.internal_energy_density(primitive[0],primitive[2]);
  con[2] = primitive[0] * (.5*primitive[1]*primitive[1]
			   + internal_energy_density);

  return con;
}
