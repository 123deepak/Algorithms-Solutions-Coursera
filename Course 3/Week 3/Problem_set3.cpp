#
include < bits / stdc++.h >
  using namespace std;

int main() {
  FILE * fp = freopen("mwis.txt", "r", stdin);
  int nodes = 0;
  scanf("%d", & nodes);

  int we[nodes + 1];
  we[0] = 0;
  int w;
  for (int i = 1; i <= nodes; i++) {
    scanf("%d", & w);
    we[i] = w;
  }

  int arr[nodes + 1];
  arr[0] = 0;
  arr[1] = we[1];

  for (int i = 2; i <= nodes; ++i) {
    arr[i] = max(arr[i - 1], arr[i - 2] + we[i]);
  }
  int i = nodes;
  map < int, int > mp;
  mp[1] = mp[2] = mp[3] = mp[4] = mp[17] = mp[117] = mp[517] = mp[997] = 0;

  map < int, int > ::iterator it;

  for (int n = nodes; n > 1;) {
    if (arr[i - 2] + we[i] > arr[i - 1]) {

      if (mp.find(i) != mp.end())
        mp[i] = 1;

      cout << i << " , ";

      i = i - 2;

      if (i == 1) {
        cout << 1 << endl;
        mp[1] = 1;
        break;
      }
    } else {
      i = i - 1;
    }
  }
  cout << mp[1] << mp[2] << mp[3] << mp[4] << mp[17] << mp[117] << mp[517] << mp[997] << endl;
  return 0;
}
