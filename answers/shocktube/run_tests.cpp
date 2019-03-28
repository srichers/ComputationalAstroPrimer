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
  // [variable index][radial index]
  array<array<double,nx>, 3> primitive, conservative, tmp;
  // [0=left 1=right][variable index][radial index]
  array< array< array<double,nx-1>, 3>, 2> conservativeLR, primitiveLR;
  
  //====================//
  // Initial Conditions //
  //====================//
  cout << "Initial Conditions: ";
  passing = true;
  set_initial_conditions<nx>(3,3, 3,3, 3,3, primitive);
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
  primitive[0][0] = 2.;
  primitive[2][0] = 3.;
  tmp[0] = eos.internal_energy_density<nx>(primitive[0], primitive[2]);
  passing = passing && floateq(tmp[0][0],3./2.);
  primitive[1][0] = 3.; // using this for internal energy density
  tmp[0] = eos.pressure<nx>(primitive[0],primitive[1]);
  passing = passing && floateq(tmp[0][0],6.);
  tmp[0] = eos.soundspeed<nx>(primitive[0],primitive[2]);
  passing = passing && floateq(tmp[0][0],sqrt(3.));
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

  //================//
  // Riemann Solver //
  //================//
  cout << "HLL Wave Speeds: ";
  passing = true;
  array<array<double,nx-1>,2> wavespeedLR;
  for(int i=0; i<nx; i++){
    primitive[0][i] = 1;
    primitive[1][i] = -4;
    primitive[2][i] = 2;
  }
  conservative = get_conservative<nx>(primitive,eos);
  conservativeLR = piecewise_constant_reconstruct<nx>(conservative);
  for(int LR=0; LR<=1; LR++)
    primitiveLR[LR] = get_primitive<nx-1>(conservativeLR[LR],eos);
  wavespeedLR = HLL_wave_speeds<nx-1>(primitiveLR, eos);
  for(int i=0; i<nx-1; i++){
    passing = passing && floateq(wavespeedLR[0][i],-6.);
    passing = passing && floateq(wavespeedLR[1][i],-2.);
  }
  print_success(passing);
  if(!passing){
    print_array<nx-1,double>(wavespeedLR[0]);
    print_array<nx-1,double>(wavespeedLR[1]);
  }

  cout << "HLL Flux: ";
  passing = true;
  double max_wavespeed = 0;
  array<array<double,nx-1>,3> riemann_flux = HLL_flux<nx-1>(primitiveLR, conservativeLR, eos, &max_wavespeed);
  for(int i=0; i<nx-1; i++){
      passing = passing && floateq(riemann_flux[0][i],-4.);
      passing = passing && floateq(riemann_flux[1][i],18.);
      passing = passing && floateq(riemann_flux[2][i],-48.);
  }
  passing = passing && floateq(max_wavespeed,6.);
  print_success(passing);
  if(!passing){
    cout << max_wavespeed << endl;
    cout << "wavespeedL: ";
    print_array<nx-1,double>(wavespeedLR[0]);
    cout << "wavespeedR: ";
    print_array<nx-1,double>(wavespeedLR[1]);
    for(int v=0; v<3; v++){
      cout << "primitiveL " << v << ": ";
      print_array<nx-1,double>(primitiveLR[0][v]);
      cout << "primitiveR " << v << ": ";
      print_array<nx-1,double>(primitiveLR[1][v]);
      cout << "flux " << v << ": ";
      print_array<nx-1,double>(riemann_flux[v]);
    }
  }
  
  return 0;
}
