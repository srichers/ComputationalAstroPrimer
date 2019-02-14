#include <iostream> // cout, endl
#include <vector> // vector
#include <cmath> // sqrt, M_PI
#include <ctime> // time
#include "Particle.h"
#include "SphericalGrid.h"
#include "RandomNumberGenerator.h"
using namespace std;

//================//
// randomDistance //
//================//
// Sample a random distance for the particle to move
double randomDistance(RandomNumberGenerator& rng, double opacity){
  // choose an exponential random number with a mean value of 1/opacity.
  // use the function RandomNumberGenerator::uniform() to sample a uniform random number
  double d = -log(rng.uniform()) / opacity;
  assert(d >= 0);
  return d;
}

//=================//
// randomDirection //
//=================//
// get a uniformily random direction
// theta is the angle from the polar axis
// phi is the azimuthal angle
// v is modified in place
void randomDirection(RandomNumberGenerator& rng, double v[3]){
  // sample a uniform random value for phi from 0 to 2*M_PI
  double phi = 2.*M_PI * rng.uniform();

  // sample a uniform random value for costheta from -1 to 1
  double costheta = 2.*rng.uniform() - 1.;

  // convert the angles to the new direction for your particle.
  double sintheta = 1. - costheta*costheta;
  v[0] = sintheta * cos(phi);
  v[1] = sintheta * sin(phi);
  v[2] = costheta;

  assert( sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]) >= 0);
}

//======//
// move //
//======//
// move a particle until time t
void move(Particle& p, RandomNumberGenerator& rng, double tend, double scatter_opacity){
  while(p.t < tend){
    // first, get a random distance to next scatter
    double d_scatter = randomDistance(rng, scatter_opacity);
    
    // move the appropriate distance
    double speed = sqrt(p.v[0]*p.v[0] + p.v[1]*p.v[1] + p.v[2]*p.v[2]);
    double dt = d_scatter/speed;
    p.t += dt;
    for(int i=0; i<3; i++){
      p.x[i] += p.v[i] * dt;
    }

    // change direction if scattering
    randomDirection(rng, p.v);
  }
}

int main(){
  const int nparticles = 10000;
  const double tend = 20;
  const double scatter_opacity = 200.0;
  const double rmax = 1;
  const int nr = 20;
  
  vector<Particle> particle_array(nparticles);
  RandomNumberGenerator rng(time(NULL));
  SphericalGrid grid(rmax, nr);

  // initialize the particles to start at the center with a random direction
  for(int i=0; i<particle_array.size(); i++){
    for(int j=0; j<3; j++){
      particle_array[i].x[j] = 0;
    }
    randomDirection(rng, particle_array[i].v);
    particle_array[i].t = 0;
  }

  // move every particle and record its final position
  for(int i=0; i<particle_array.size(); i++){
    move(particle_array[i], rng, tend, scatter_opacity);
    grid.tally(particle_array[i].x);
  }

  // write out the results
  grid.print(nparticles);
}
