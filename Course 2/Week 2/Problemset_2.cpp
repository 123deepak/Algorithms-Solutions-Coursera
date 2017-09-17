//Deepak Dodeja
//Look at the row 1, where all neighbours can be seen, if not present put 100000 in the output
#include<iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include<stdlib.h>
#include<queue>
#include <algorithm>
#include<ctime>
using namespace std;

vector < vector < pair < int, int > > > graph(200);

vector < long int > wt(200);

priority_queue < pair < long int, int > , vector < pair < long int, int > > , greater < pair < long int, int > > > queue1;

int main() {
    int m = 1;
    int ver;
    ifstream fin;
    ofstream ofs("output.txt", ofstream::out);
    fin.open("dijkstraData.txt");
    char ch[300];
    string s;
    while (!fin.eof()) {
        fin.getline(ch, 300, '\n');
        stringstream ss(ch);
        while (1) {
            int n, z;
            char s;
            if (m == 1)
                ss >> n;
            else
                ss >> n >> s >> z;
            if (!ss) {
                m = 1;
                break;
            }
            if (m == 1) {
                m++;
                ver = n;
                wt.at(ver - 1) = 100000;
            } else {
                graph[ver - 1].push_back(make_pair(n, z));
                ofs << n << "," << z << " ";
            }
        }
        ofs << endl;
    }
    wt.at(0) = 0;
    queue1.push(make_pair(0, 1));
    while (!queue1.empty()) {
        int ver = queue1.top().second;
        int w = queue1.top().first;
        for (int i = 0; i < graph[ver - 1].size(); i++) {
            int tempv = graph[ver - 1].at(i).first;
            if (wt.at(tempv - 1) > w + graph[ver - 1].at(i).second) {
                queue1.push(make_pair(w + graph[ver - 1].at(i).second, graph[ver - 1].at(i).first));
                wt.at(tempv - 1) = w + graph[ver - 1].at(i).second;
            }
        }

        queue1.pop();
    }
    for (int i = 1; i < wt.size(); i++)
        if (i == 7 || i == 37 || i == 59 || i == 82 || i == 99 || i == 115 || i == 133 || i == 165 || i == 188 || i == 197)
            ofs << wt.at(i - 1) << ",";
    return 0;
}
