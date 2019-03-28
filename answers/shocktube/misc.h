template<size_t nx>
void print(ofstream& output, int it, double t,
	   const array<array<double,nx>,3>& primitive,
	   const array<array<double,nx>,3>& conservative){
  for(int i=0; i<nx; i++){
    output << it << "\t" << t << "\t" << i << "\t";
    for(int v=0; v<3; v++) output << primitive[v][i] << "\t";
    for(int v=1; v<3; v++) output << primitive[v][i] << "\t";
    output << endl;
  }
}
