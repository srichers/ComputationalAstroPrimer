#ifndef MISC_H
#define MISC_H

//=======//
// print //
//=======//
// output current variables to file
// call with:
//     print<nx>(output, it, t, primitive, conservative);
template<size_t nx>
void print(ofstream& output, int it, double t, double dx,
	   const array<array<double,nx>,3>& primitive,
	   const array<array<double,nx>,3>& conservative){
  for(int ix=0; ix<nx; ix++){
    output << it << "\t" << t << "\t" << ix << "\t" << (ix+0.5)*dx <<"\t";
    //for(int v=0; v<3; v++) output << primitive[v][ix] << "\t";
    for(int v=0; v<3; v++) output << conservative[v][ix] << "\t";
    output << endl;
  }
  output << endl;
}

#endif
