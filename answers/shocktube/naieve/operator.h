#include <array>
using namespace std;

template<size_t nx>
array<double,nx> operator*(const array<double,nx>& A, const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A[i] * B[i];
  return result;
}
template<size_t nx>
array<double,nx> operator/(const array<double,nx>& A, const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A[i] / B[i];
  return result;
}
template<size_t nx>
array<double,nx> operator+(const array<double,nx>& A, const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A[i] + B[i];
  return result;
}
template<size_t nx>
array<double,nx> operator-(const array<double,nx>& A, const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A[i] - B[i];
  return result;
}
template<size_t nx>
array<double,nx> operator-(const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = -B[i];
  return result;
}


template<size_t nx>
array<double,nx> operator*(const array<double,nx>& A, double B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A[i] * B;
  return result;
}
template<size_t nx>
array<double,nx> operator/(const array<double,nx>& A, double B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A[i] / B;
  return result;
}
template<size_t nx>
array<double,nx> operator+(const array<double,nx>& A, double B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A[i] + B;
  return result;
}
template<size_t nx>
array<double,nx> operator-(const array<double,nx>& A, double B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A[i] - B;
  return result;
}


template<size_t nx>
array<double,nx> operator*(double A, const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A * B[i];
  return result;
}
template<size_t nx>
array<double,nx> operator/(double A, const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A / B[i];
  return result;
}
template<size_t nx>
array<double,nx> operator+(double A, const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A + B[i];
  return result;
}
template<size_t nx>
array<double,nx> operator-(double A, const array<double,nx>& B){
  array<double,nx> result;
  for(int i=0; i<nx; i++) result[i] = A - B[i];
  return result;
}
