#include <bits/stdc++.h>
using namespace std;
#define INF 99999999
double length = 0.0;
void getdetails(int m, vector < pair < double, double > > & city, vector < int > & arr) {
  int n;
  for (int i = 0; i < m; i++) {
    double a, b;
    scanf("%d %lf %lf", & n, & a, & b);
    city.push_back(make_pair(a, b));
    arr[i] = 0;
  }
}
double euclidean(int current, int other, vector < pair < double, double > > & city) {
  double x = pow(city[current].first - city[other].first, 2);
  double y = pow(city[current].second - city[other].second, 2);
  double z = x + y;
  return z;
}
int nextchain(int m, int current, vector < pair < double, double > > & city, vector < int > & arr) {
  double nearest = INF;
  int next = -1;
  for (int j = 0; j < m; j++) {
    double dis = euclidean(current, j, city);
    if (dis < nearest && arr[j] == 0) {
      nearest = dis;
      next = j;
    }
  }
  length = length + sqrt(nearest);
  return next;
}

double TSP(int m, vector < pair < double, double > > & city, vector < int > & arr) {
  int current = 0;
  arr[current] = 1;
  for (int i = 1; i < m; i++) {
    arr[current] = 1;
    current = nextchain(m, current, city, arr);
  }
  double xx = pow(city[current].first - city[0].first, 2);
  double yy = pow(city[current].second - city[0].second, 2);
  length += sqrt(xx + yy);
  return length;
}
int main() {
  FILE * fp = freopen("nn.txt", "r", stdin);
  int m;
  scanf("%d", & m);
  vector < pair < double, double > > city;
  vector < int > arr(m, 0);
  getdetails(m, city, arr);
  cout << "Shortest Cycle=" << (long) TSP(m, city, arr) << endl;
}
