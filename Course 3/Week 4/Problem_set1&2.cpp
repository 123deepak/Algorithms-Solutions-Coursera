#include <bits/stdc++.h>
using namespace std;
long long knapsack(vector < int > & we, vector < int > & value, int items, int W) {
  vector < vector < long long > > arr(2);

  for (int j = 0; j < 2; j++) {
    arr[j].resize(W + 1);
  }
  for (int j = 0; j <= W; j++)
    arr[0][j] = 0;

  for (int i = 1; i <= items; i++) {
    for (int x = 0; x <= W; x++) {
      if (x >= we[i])
        arr[1][x] = max(arr[0][x], arr[0][x - we[i]] + value[i]);
      else
        arr[1][x] = arr[0][x];
    }

    for (int j = 0; j <= W; j++)
      arr[0][j] = arr[1][j];
  }

  return arr[1][W];

}

int main() {
  //FILE *fp = freopen("knapsack_big.txt","r",stdin);
  FILE * fp = freopen("knapsack_small.txt", "r", stdin);
  int W = 0;
  int items = 0;
  scanf("%d %d", & W, & items);
  int v;
  int w;

  vector < int > we(items + 1);
  vector < int > value(items + 1);

  for (int i = 1; i <= items; i++) {
    scanf("%d %d", & v, & w);
    value[i] = v;
    we[i] = w;
  }
  fclose(fp);

  cout << knapsack(we, value, items, W) << endl;
  return 0;
}
