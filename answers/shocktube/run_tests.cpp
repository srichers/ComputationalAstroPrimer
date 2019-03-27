#include <iostream>
#include <string>
#include "initial_conditions.h"
#include "boundary_conditions.h"
#include "reconstruct.h"
#include "EOS.h"
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

const int nx = 10;
const int nghost = 3;


int main(){
  bool passing;

  //====================//
  // Initial Conditions //
  //====================//
  cout << "Initial Conditions: ";
  passing = true;
  array<double,nx> rho, Eint, px;
  set_initial_conditions<nx,nghost>(3,3,rho, 3,3,Eint, 3,3,px);
  for(int i=nghost; i<nx-2*nghost; i++){
    passing = passing && (rho [i]==3);
    passing = passing && (Eint[i]==3);
    passing = passing && (px  [i]==3);
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
  passing = passing && (rho[0] == 5);
  passing = passing && (rho[1] == 4);
  passing = passing && (rho[2] == 3);
  passing = passing && (rho[3] == 3);
  passing = passing && (rho[4] == 4);
  passing = passing && (rho[5] == 5);
  passing = passing && (rho[6] == 6);
  passing = passing && (rho[7] == 6);
  passing = passing && (rho[8] == 5);
  passing = passing && (rho[9] == 4);
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
  passing = passing && (rhoLR[0][0] == 0) && (rhoLR[1][0] == 1);
  passing = passing && (rhoLR[0][1] == 1) && (rhoLR[1][1] == 2);
  passing = passing && (rhoLR[0][2] == 2) && (rhoLR[1][2] == 3);
  passing = passing && (rhoLR[0][3] == 3) && (rhoLR[1][3] == 4);
  passing = passing && (rhoLR[0][4] == 4) && (rhoLR[1][4] == 5);
  passing = passing && (rhoLR[0][5] == 5) && (rhoLR[1][5] == 6);
  passing = passing && (rhoLR[0][6] == 6) && (rhoLR[1][6] == 7);
  passing = passing && (rhoLR[0][7] == 7) && (rhoLR[1][7] == 8);
  passing = passing && (rhoLR[0][8] == 8) && (rhoLR[1][8] == 9);
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
  passing = passing && (eos.internal_energy_density(2.,3.) == 3./2.);
  passing = passing && (eos.pressure(2.,3.) == 6.);
  passing = passing && (eos.soundspeed(2.,3.)==sqrt(3.));
  print_success(passing);
  
  //==========//
  // Prim2Con //
  //==========//
  
  cout << "Prim2Con: " << endl;
  
  //==========//
  // Con2Prim //
  //==========//
  cout << "Con2Prim: " << endl;
  
  //================//
  // Riemann Solver //
  //================//
  cout << "Riemann Solver: " << endl;

  //========//
  // Fluxes //
  //========//
  cout << "Fluxes: " << endl;
  
  //========//
  // Update //
  //========//
  cout << "Update: " << endl;
  
  return 0;
}
