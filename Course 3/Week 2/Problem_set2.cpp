#include <bits/stdc++.h>
using namespace std;
struct problem {
  int parent;
  int rank;
};
int Findset(problem * subs, int i) {
  if (subs[i].parent != i)
    subs[i].parent = Findset(subs, subs[i].parent);

  return subs[i].parent;
}
void Unionset(problem * subs, int u, int v) {
  int x = Findset(subs, u);
  int y = Findset(subs, v);
  if (subs[x].rank == subs[y].rank) {
    subs[y].parent = x;
    subs[x].rank++;
  } else if (subs[x].rank < subs[y].rank)
    subs[x].parent = y;
  else subs[y].parent = x;
}
bool sortbysec(const pair < int, pair < int, int > > & a,
  const pair < int, pair < int, int > > & b) {
  return (a.first < b.first);
}
int main() {
  vector < pair < int, pair < int, int > > > graph;
  FILE * fp = freopen("clustering1.txt", "r", stdin);
  int nodes = 0;
  scanf("%d", & nodes);
  int begin;
  int end;
  int cost;
  while (scanf("%d %d %d", & begin, & end, & cost) > 0) {
    graph.push_back(make_pair(cost, make_pair(begin, end)));
  }
  sort(graph.begin(), graph.end(), sortbysec);
  problem subs[nodes + 1];
  for (int i = 1; i <= nodes; i++) {
    subs[i].parent = i;
    subs[i].rank = 0;
  }

  int count = 1;
  int j = 0;
  for (int j = 0; j < graph.size(); j++) {
    int x = Findset(subs, graph[j].second.first);
    int y = Findset(subs, graph[j].second.second);
    if (x != y) {

      if (count == 497) {
        cout << graph[j].first << endl;
        break;
      }
      Unionset(subs, x, y);

      count++;
    }
  }
  fclose(fp);
  return 0;
}
