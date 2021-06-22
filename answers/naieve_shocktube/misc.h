const double NaN = 0./0.;

template<size_t nx>
array<double,nx> grad(const array<double,nx>& y, double dx){
  array<double,nx> result;
  result[0] = result[nx-1] = NaN;
  for(int i=1; i<nx-1; i++)
    result[i] = (y[i+1] - y[i-1]) / (2.*dx);

  return result;
}

template<size_t nx>
array<double,nx> div(const array<double,nx>& y, double dx){
  array<double,nx> result;
  result[0] = result[nx-1] = NaN;
  for(int i=1; i<nx-1; i++)
    result[i] = (y[i+1] - y[i-1]) / (2.*dx);

  return result;
}

template<size_t nx>
double sum(const array<double,nx>& y){
  double result = 0;
  for(int i=0; i<nx; i++) result += y[i];
  assert(result == result);
  return result;
}
template<size_t nx>
double max(const array<double,nx>& y){
  double result = y[0];
  for(int i=0; i<nx; i++) result = max(result,y[i]);
  assert(result==result);
  return result;
}

template<size_t nx>
void print(ofstream& output, int it, double t, double dt, const array<double,nx>& x, const array<double,nx>& rho, const array<double,nx>& Eint, const array<double,nx>& px){
  for(int i=0; i<nx; i++){
    output << it << "\t" << t << "\t" << dt << "\t" << i << "\t" << x[i] << "\t" << rho[i] << "\t" << Eint[i] << "\t" << px[i] << endl;
  }
}
