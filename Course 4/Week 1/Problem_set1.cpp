#include <bits/stdc++.h>
using namespace std;
#define INF 99999
int main() {
  // Read the file	
  //FILE *fp = freopen("g1.txt","r",stdin);
  //FILE *fp = freopen("g2.txt","r",stdin);
  FILE * fp = freopen("g3.txt", "r", stdin);
  int v = 0;
  int s, w, d;
  int edges = 0;
  int cycle = 0;
  scanf("%d %d", & v, & edges);
  vector < vector < int > > arr(v + 1);
  for (int i = 1; i < (v + 1); i++) {
    arr[i].resize(v + 1, INF);
  }
  for (int i = 1; i < v + 1; i++) {
    for (int j = 1; j < v + 1; j++) {
      if (i == j)
        arr[i][j] = 0;
    }
  }
  for (int i = 1; i <= edges; i++) {
    scanf("%d %d %d", & s, & d, & w);
    arr[s][d] = w;
  }
  fclose(fp);
  for (int k = 1; k <= v; k++) {
    for (int i = 1; i <= v; i++) {
      for (int j = 1; j <= v; j++) {
        if (arr[i][k] + arr[k][j] < arr[i][j])
          arr[i][j] = arr[i][k] + arr[k][j];
      }
    }
  }
  for (int i = 1; i < v + 1; i++) {
    for (int j = 1; j < v + 1; j++) {
      if (i == j & arr[i][j] < 0) {
        cycle = 1;
      }
    }
  }

  if (cycle == 1) {
    cout << "Cycle is Found" << endl;
  } else {
    int min = INF;
    for (int i = 1; i < v + 1; i++) {
      for (int j = 1; j < v + 1; j++) {
        if (arr[i][j] < min) {
          min = arr[i][j];
        }
      }
    }
    cout << min << endl;
  }
  return 0;
}
