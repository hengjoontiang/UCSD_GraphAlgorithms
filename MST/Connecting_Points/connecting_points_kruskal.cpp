#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;
/*
 * 
 * for all u belongs V:
 * 		MakeSet(v)
 * X <-- empty set
 * sort the edges E by weight
 * for all {u,v} belonging to E in non-decreasing weight order:
 * 		if Find(u) != Find(v): //i.e they beong to different sets
 * 			add {u,v} to X
 * 			Union(u,v)
 * return X
 * 
 * 
 * */
double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
