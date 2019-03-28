#include <iostream>
#include <string>
#include "initial_conditions.h"
#include "boundary_conditions.h"
#include "reconstruct.h"
#include "EOS.h"
#include "Conservative_Primitive.h"
#include "flux.h"
//#include "HLL.h"
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
  // [variable index][radial index]
  array<array<double,nx>, 3> primitive, conservative;
  // [0=left 1=right][variable index][radial index]
  array< array< array<double,nx-1>, 3>, 2> conservativeLR, primitiveLR;
  
  //====================//
  // Initial Conditions //
  //====================//
  cout << "Initial Conditions: ";
  passing = true;
  set_initial_conditions<nx,nghost>(3,3, 3,3, 3,3, primitive);
  for(int i=nghost; i<nx-2*nghost; i++){
    passing = passing && floateq(primitive[0][i],3); // rho
    passing = passing && floateq(primitive[1][i],3); // vx
    passing = passing && floateq(primitive[2][i],3); // pressure
  }
  print_success(passing);
  if(!passing){
    print_array<nx,double>(primitive[0]);
    print_array<nx,double>(primitive[1]);
    print_array<nx,double>(primitive[2]);
  }

  //=====================//
  // Boundary Conditions //
  //=====================//
  cout << "Boundary Conditions: ";
  passing = true;
  for(int i=0; i<nx; i++) primitive[0][i] = i;
  reflecting_boundary_conditions<nx,nghost>(primitive);
  passing = passing && floateq(primitive[0][0],5);
  passing = passing && floateq(primitive[0][1],4);
  passing = passing && floateq(primitive[0][2],3);
  passing = passing && floateq(primitive[0][3],3);
  passing = passing && floateq(primitive[0][4],4);
  passing = passing && floateq(primitive[0][5],5);
  passing = passing && floateq(primitive[0][6],6);
  passing = passing && floateq(primitive[0][7],6);
  passing = passing && floateq(primitive[0][8],5);
  passing = passing && floateq(primitive[0][9],4);
  print_success(passing);
  if(!passing){
    print_array<nx,double>(primitive[0]);
  }

  //================//
  // Reconstruction //
  //================//
  cout << "Reconstruction: ";
  passing = true;
  for(int i=0; i<nx; i++) primitive[0][i] = i;
  conservativeLR = piecewise_constant_reconstruct<nx>(primitive);
  passing = passing && floateq(conservativeLR[0][0][0],0.) && floateq(conservativeLR[1][0][0],1.);
  passing = passing && floateq(conservativeLR[0][0][1],1.) && floateq(conservativeLR[1][0][1],2.);
  passing = passing && floateq(conservativeLR[0][0][2],2.) && floateq(conservativeLR[1][0][2],3.);
  passing = passing && floateq(conservativeLR[0][0][3],3.) && floateq(conservativeLR[1][0][3],4.);
  passing = passing && floateq(conservativeLR[0][0][4],4.) && floateq(conservativeLR[1][0][4],5.);
  passing = passing && floateq(conservativeLR[0][0][5],5.) && floateq(conservativeLR[1][0][5],6.);
  passing = passing && floateq(conservativeLR[0][0][6],6.) && floateq(conservativeLR[1][0][6],7.);
  passing = passing && floateq(conservativeLR[0][0][7],7.) && floateq(conservativeLR[1][0][7],8.);
  passing = passing && floateq(conservativeLR[0][0][8],8.) && floateq(conservativeLR[1][0][8],9.);
  print_success(passing);
  if(!passing){
    print_array<nx-1,double>(conservativeLR[0][0]);
    print_array<nx-1,double>(conservativeLR[1][0]);
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
  primitive[0][0] = 2;
  primitive[1][0] = 2;
  primitive[2][0] = 2;
  conservative[0][0] = 2;
  conservative[1][0] = 4;
  conservative[2][0] = 6;
  array<array<double,nx>,3> tmp;
  eos.gamma = 2.;

  cout << "Primitive-->Conservative: ";
  passing = true;
  tmp = get_conservative<nx>(primitive, eos);
  for(int i=0; i<3; i++)
    passing = passing && floateq(tmp[i][0],conservative[i][0]);
  print_success(passing);
  if(!passing){
    print_array<nx,double>(tmp[0]);
    print_array<nx,double>(tmp[1]);
    print_array<nx,double>(tmp[2]);
  }

  cout << "Conservative-->Primitive: ";
  passing = true;
  tmp = get_primitive<nx>(conservative, eos);
  for(int i=0; i<3; i++)
    passing = passing && floateq(tmp[i][0],primitive[i][0]);
  print_success(passing);
  if(!passing){
    print_array<nx,double>(tmp[0]);
    print_array<nx,double>(tmp[1]);
    print_array<nx,double>(tmp[2]);
  }

  cout << "Flux: ";
  passing = true;
  tmp = conservative_flux<nx>(primitive, conservative);
  passing = passing && floateq(tmp[0][0],4.);
  passing = passing && floateq(tmp[1][0],10.);
  passing = passing && floateq(tmp[2][0],16.);
  print_success(passing);
  if(!passing){
    print_array<nx,double>(tmp[0]);
    print_array<nx,double>(tmp[1]);
    print_array<nx,double>(tmp[2]);
  }

  // //================//
  // // Riemann Solver //
  // //================//
  // cout << "HLL Wave Speeds: ";
  // passing = true;
  // array<double,2> wavespeedLR;
  // primitive = array<double,3>{1,-4,2};
  // wavespeedLR = HLL_wave_speeds(primitive,primitive, eos);
  // passing = passing && floateq(wavespeedLR[0],-6.);
  // passing = passing && floateq(wavespeedLR[1],-2.);
  // print_success(passing);
  // if(!passing) print_array<2,double>(wavespeedLR);

  // cout << "HLL Flux: ";
  // passing = true;
  // array<double,3> riemann_flux = HLL_flux(primitiveLR, conservativeLR, wavespeedLR);
  // print_success(passing);
  
  return 0;
}