#include <iostream>
#include <string>
#include "initial_conditions.h"
#include "boundary_conditions.h"
#include "reconstruct.h"
#include "EOS.h"
#include "Conservative_Primitive.h"
#include "flux.h"
#include "HLL.h"
using namespace std;

void print_success(bool success){
  if(success) cout << "\033[1;32mSUCCESS\033[0m" << endl;
  else        cout << "\033[1;31mFAIL\033[0m" << endl;
}

template<int nx, typename T>
void print_array(array<T,nx> input){
  cout << "[";
  for(int i=0; i<nx-1; i++) cout << input[i] << ", ";
  cout << input[nx-1] << "]" << endl;
}

bool floateq(double a, double b){
  bool iseq = abs(a-b) <= 1e-10 * (abs(a)+abs(b));
  if(!iseq) cout << a << " " << b << " " << a-b << endl;

  return iseq;
}

const int nx = 10;
const int nghost = 3;


int main(){
  bool passing;
  array<double,3> primitive, conservative;

  //====================//
  // Initial Conditions //
  //====================//
  cout << "Initial Conditions: ";
  passing = true;
  array<double,nx> rho, Eint, px;
  set_initial_conditions<nx,nghost>(3,3,rho, 3,3,Eint, 3,3,px);
  for(int i=nghost; i<nx-2*nghost; i++){
    passing = passing && floateq(rho [i],3);
    passing = passing && floateq(Eint[i],3);
    passing = passing && floateq(px  [i],3);
  }
  print_success(passing);
  if(!passing){
    print_array<nx,double>(rho);
    print_array<nx,double>(Eint);
    print_array<nx,double>(px);
  }

  //=====================//
  // Boundary Conditions //
  //=====================//
  cout << "Boundary Conditions: ";
  passing = true;
  for(int i=0; i<nx; i++) rho[i] = i;
  reflecting_boundary_conditions<double,nx,nghost>(rho);
  passing = passing && floateq(rho[0],5);
  passing = passing && floateq(rho[1],4);
  passing = passing && floateq(rho[2],3);
  passing = passing && floateq(rho[3],3);
  passing = passing && floateq(rho[4],4);
  passing = passing && floateq(rho[5],5);
  passing = passing && floateq(rho[6],6);
  passing = passing && floateq(rho[7],6);
  passing = passing && floateq(rho[8],5);
  passing = passing && floateq(rho[9],4);
  print_success(passing);
  if(!passing){
    print_array<nx,double>(rho);
  }

  //================//
  // Reconstruction //
  //================//
  cout << "Reconstruction: ";
  passing = true;
  for(int i=0; i<nx; i++) rho[i] = i;
  array< array<double,nx-1>, 2> rhoLR = piecewise_constant_reconstruct<double,nx>(rho);
  passing = passing && floateq(rhoLR[0][0],0.) && floateq(rhoLR[1][0],1.);
  passing = passing && floateq(rhoLR[0][1],1.) && floateq(rhoLR[1][1],2.);
  passing = passing && floateq(rhoLR[0][2],2.) && floateq(rhoLR[1][2],3.);
  passing = passing && floateq(rhoLR[0][3],3.) && floateq(rhoLR[1][3],4.);
  passing = passing && floateq(rhoLR[0][4],4.) && floateq(rhoLR[1][4],5.);
  passing = passing && floateq(rhoLR[0][5],5.) && floateq(rhoLR[1][5],6.);
  passing = passing && floateq(rhoLR[0][6],6.) && floateq(rhoLR[1][6],7.);
  passing = passing && floateq(rhoLR[0][7],7.) && floateq(rhoLR[1][7],8.);
  passing = passing && floateq(rhoLR[0][8],8.) && floateq(rhoLR[1][8],9.);
  print_success(passing);
  if(!passing){
    print_array<nx-1,double>(rhoLR[0]);
    print_array<nx-1,double>(rhoLR[1]);
  }

  //=====//
  // EOS //
  //=====//
  cout << "EOS: ";
  passing = true;
  EOS eos;
  eos.gamma = 2.;
  passing = passing && floateq(eos.internal_energy_density(2.,3.),3./2.);
  passing = passing && floateq(eos.pressure(2.,3.),6.);
  passing = passing && floateq(eos.soundspeed(2.,3.),sqrt(3.));
  print_success(passing);
  
  //=========//
  // PrimCon //
  //=========//  
  primitive = array<double,3>{2,2,2};
  conservative = array<double,3>{2,4,6};
  array<double,3> tmp;
  eos.gamma = 2.;

  cout << "Primitive-->Conservative: ";
  passing = true;
  tmp = get_conservative(primitive, eos);
  for(int i=0; i<3; i++)
    passing = passing && floateq(tmp[i],conservative[i]);
  print_success(passing);
  if(!passing) print_array<3,double>(tmp);

  cout << "Conservative-->Primitive: ";
  passing = true;
  tmp = get_primitive(conservative, eos);
  for(int i=0; i<3; i++)
    passing = passing && floateq(tmp[i],primitive[i]);
  print_success(passing);
  if(!passing) print_array<3,double>(tmp);

  cout << "Flux: ";
  passing = true;
  tmp = conservative_flux(primitive, conservative);
  passing = passing && floateq(tmp[0],4.);
  passing = passing && floateq(tmp[1],10.);
  passing = passing && floateq(tmp[2],16.);
  print_success(passing);
  if(!passing) print_array<3,double>(tmp);

  //================//
  // Riemann Solver //
  //================//
  cout << "HLL Wave Speeds: ";
  passing = true;
  array<double,2> wavespeedLR;
  primitive = array<double,3>{1,-4,2};
  wavespeedLR = HLL_wave_speeds(primitive,primitive, eos);
  passing = passing && floateq(wavespeedLR[0],-6.);
  passing = passing && floateq(wavespeedLR[1],-2.);
  print_success(passing);
  if(!passing) print_array<2,double>(wavespeedLR);

  cout << "HLL Flux: ";
  passing = true;
  array< array<double,3>, 2> primitiveLR, conservativeLR;
  array<double,3> riemann_flux = HLL_flux(primitiveLR, conservativeLR, wavespeedLR);
  print_success(passing);
  
  return 0;
}
