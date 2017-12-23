#include <bits/stdc++.h>
using namespace std;

vector < int > back(3000001);

vector < int > front(3000001);

vector < long > finish(3000001);

int finish_time = 1;
bool satisfiable = true;

void compute(long temp, long track, vector < vector < int > > & graph, long index) {
  if (front[track] != 0)
    return;
  if (front[track] == 0) {

    front[track] = index;

    if (track > temp) {
      if (front[track - temp] == index)
        satisfiable = false;
    }

    if (track <= temp) {
      if (front[track + temp] == index)
        satisfiable = false;
    }

    for (int y = 0; y < graph[track].size(); y++)
      compute(temp, graph[track][y], graph, index);

    front[track] = index;

    return;
  }
}

void GraphRev(long r, vector < vector < int > > & graph_rev) {
  if (back[r] == 1)
    return;

  if (back[r] != 1) {
    back[r] = 1;

    for (int z = 0; z < graph_rev[r].size(); z++)
      GraphRev(graph_rev[r][z], graph_rev);

    finish[finish_time] = r;

    finish_time++;

    return;
  }
}

void readclauses(long temp, vector < vector < int > > & graph, vector < vector < int > > & graph_rev) {

  int temp1, temp2, firstedge, secondedge;

  for (int i = 1; i <= temp; i++) {

    scanf("%d %d", & temp1, & temp2);

    if (temp1 < 0)
      temp1 = temp + abs(temp1);

    if (temp2 < 0)
      temp2 = temp + abs(temp2);

    if (temp1 > temp)
      firstedge = temp1 - temp;
    else
      firstedge = temp + temp1;

    if (temp2 > temp)
      secondedge = temp2 - temp;
    else
      secondedge = temp + temp2;

    graph[firstedge].push_back(temp2);

    graph[secondedge].push_back(temp1);

    graph_rev[temp2].push_back(firstedge);

    graph_rev[temp1].push_back(secondedge);

  }
}

int main() {

  FILE * fp = freopen("2sat6.txt", "r", stdin);
  long temp;

  vector < vector < int > > graph, graph_rev;
  scanf("%ld", & temp);

  for (int i = 0; i <= 2 * temp; i++) {
    vector < int > row;
    graph.push_back(row);
    graph_rev.push_back(row);
  }

  readclauses(temp, graph, graph_rev);

  for (long i = 1; i < graph_rev.size(); i++)
    GraphRev(i, graph_rev);

  for (long i = finish_time - 1; i > 0; i--) {
    long track = finish[i];
    compute(temp, track, graph, i);
  }

  if (satisfiable == false)
    cout << "Not satisfiable" << endl;
  else
    cout << "Satisfiable" << endl;

  fclose(fp);

  return 0;
}
