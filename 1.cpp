#include <iostream>
#include <omp.h>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }
    void addEdge(int s, int d)
    {
        adj[s].push_back(d);
        adj[d].push_back(s);
    }

    void BFS(int source)
    {
        queue<int> q;
        vector<bool> visited(V, false);
        q.push(source);
        visited[source] = true;

        while (!q.empty())
        {

#pragma omp shared(visited, q)
            {
                int front;
#pragma omp single
                {
                    front = q.front();
                    q.pop();
                }
                cout<<front<<" ";
#pragma omp parallel for
                for (int i = 0; i < adj[front].size(); i++)
                {
                    int u = adj[front][i];
                    if (!visited[u])
                    {
#pragma omp critical
                        {
                            visited[u] = true;
                            q.push(u);
                        }
                    }
                }
            }
        }

    }

    void DFSUtil(vector<bool> &visited,int source){
        #pragma omp critical
        {
        visited[source]=true;
        }
        cout<<source<<" ";
        #pragma omp parallel for
        for(int i=0;i<adj[source].size();i++){
            int u=adj[source][i];
            if(!visited[u]){
                DFSUtil(visited,u);
            }
        }
    };
    void DFS(int source){
        vector<bool> visited(V,false);
        DFSUtil(visited,source);
    }
};


int main(){
     Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "Parallel Breadth First Search (BFS) starting from vertex 0: ";
    g.BFS(0);
cout<<endl;
    cout << "Parallel Depth First Search (BFS) starting from vertex 0: ";
    g.DFS(0);
    cout << endl;
}