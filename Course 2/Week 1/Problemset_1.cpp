//Deepak Dodeja
//Basic architecture taken from Geeks for Geeks
//Modified the solution acc. to problem
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <iostream>
#include <list>
#include <stack>
using namespace std;
int z;
class Graph
{
    int V;   
    list<int> *adj;    
    void fillOrder(int v, bool vis[], stack<int> &Stack);
    void Utility(int v, bool vis[]);
	public:
	    Graph(int V);
    	void addEdge(int v, int w);
    	void printSCCs();
 		Graph getTranspose();
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::Utility(int v, bool vis[])
{
    vis[v] = true;
    z++;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!vis[*i])
            Utility(*i, vis);
}
 
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); 
}
 
void Graph::fillOrder(int v, bool vis[], stack<int> &Stack)
{
    vis[v] = true;
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!vis[*i])
            fillOrder(*i, vis, Stack);
    Stack.push(v);
}
void Graph::printSCCs()
{
    stack<int> Stack;
 
    bool *vis = new bool[V];
    for(int i = 0; i < V; i++)
        vis[i] = false;
    for(int i = 0; i < V; i++)
        if(vis[i] == false)
            fillOrder(i, vis, Stack);
    Graph gr = getTranspose();
    for(int i = 0; i < V; i++)
        vis[i] = false;
    while (Stack.empty() == false)
    {
        int v = Stack.top();
        Stack.pop();
        if (vis[v] == false)
        {
        	z=0;
            gr.Utility(v, vis);
            ofstream ofs("file.txt", ofstream::out);
	  	    ofs<<z<<endl;	 
        }
    }
}
int main()
{
    FILE* fp=freopen("SCC.txt","r",stdin);
    Graph g(5); 
 	int head, tail;
  	while (scanf("%d %d", &head, &tail) > 0) {
    		  g.addEdge(head, tail);
    }
    fclose(fp);
    g.printSCCs();
    cout<<"Above .txt file will be having all the sizes of Strongly connected components, just sort them in descending order in excel, you will get your top 5 SCC sizes";
    return 0;
}
