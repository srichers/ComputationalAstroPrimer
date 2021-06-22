#include <cassert>
#include <iostream> // cout, endl
using namespace std;

class SphericalGrid{
 public:
  
  vector<double> r_out;
  vector<int> count;
  
  // construct the grid with the maximum radius and the number of radial bins
  SphericalGrid(double rmax, int nr){
    assert(rmax > 0);
    assert(nr > 0);
    
    r_out.resize(nr);
    count.resize(nr);
    for(int i=0; i<r_out.size(); i++){
      r_out[i] = rmax * (i+1)/nr;
      count[i] = 0;
    }
  }

  // given a position, return the index of the radial zone
  // a value of -1 means it is off the grid
  int getIndex(const double x[3]){
    double r = sqrt(x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
    int index = -1;
    for(int i=0; i<r_out.size(); i++){
      if(r < r_out[i]){
	index = i;
	break;
      }
    }

    assert(index >= -1);
    assert(index <= (int)r_out.size());
    return index;
  }

  // add a particle to the zone
  void tally(const double x[3]){
    int index = getIndex(x);

    // if index<0 it's already off the grid.
    if(index >= 0){
      #pragma omp atomic
      count[index]++;
    }
  }

  // Write out the data. Make sure to use cell-centered coordinates
  void print(int nparticles){
    cout << "index \t radius \t count \t density" << endl;
    for(int i=0; i<r_out.size(); i++){
      double r_in = (i==0 ? 0 : r_out[i-1]);
      double r_mid = (r_in + r_out[i]) / 2.;
      double vol = 4.*M_PI/3. * (pow(r_out[i], 3) - pow(r_in, 3)); 
      cout << i << "\t" << r_mid << "\t" << count[i] << "\t" << count[i]/vol/(double)nparticles << endl;
    }
  }

};
