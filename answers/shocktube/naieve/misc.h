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
void print(ofstream& output, int it, double t, double dt, const array<double,nx>& x, const array<double,nx>& rho, const array<double,nx>& px, const array<double,nx>& Eint){
  for(int ix=0; ix<nx; ix++){
    output << it << "\t" << t << "\t" << ix << "\t" << x[ix] << "\t" << rho[ix] << "\t" << px[ix] << "\t" << Eint[ix] + px[ix]*px[ix]/(2.*rho[ix]) << endl;
  }
}
