// A C++ program to find articulation points in a given undirected graph
#include<bits/stdc++.h>
#define NIL -1
#define SIZE 10004
using namespace std;

bool visited[SIZE];
int disc[SIZE], low[SIZE], parent[SIZE],  ap[SIZE] ;
int ans ;
// A class that represents an undirected graph
class Graph
{
    int V;    // No. of vertices
    vector < int > adj[10004] ;    // A dynamic array of adjacency lists
    void APUtil(int v );
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void AP();    // prints articulation points
};

Graph::Graph(int V)
{
    this->V = V;
    for( int i = 1 ; i <= V ; i++ )
        adj[i].clear() ;

}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

// A recursive function that find articulation points using DFS traversal
// u --> The vertex to be visited next
// visited[] --> keeps tract of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
// ap[] --> Store articulation points
void Graph::APUtil(int u )
{

    // A static variable is used for simplicity, we can avoid use of static
    // variable by passing a pointer.
    static int time = 0;

    // Count of children in DFS Tree
    int children = 0;

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices aadjacent to this
    for (int i = 0 ; i < adj[u].size() ; ++i)
    {
        int v = adj[u][i] ;  // v is current adjacent of u

        // If v is not visited yet, then make it a child of u
        // in DFS tree and recur for it
        if (!visited[v])
        {
            children++;
            parent[v] = u;
            APUtil(v);

            // Check if the subtree rooted with v has a connection to
            // one of the ancestors of u
            low[u]  = min(low[u], low[v]);

            // u is an articulation point in following cases

            // (1) u is root of DFS tree and has two or more chilren.
            if (parent[u] == NIL && children > 1)
               ap[u] = true;

            // (2) If u is not root and low value of one of its child is more
            // than discovery value of u.
            if (parent[u] != NIL && low[v] >= disc[u])
               ap[u] = true;
        }

        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
    }
}

// The function to do DFS traversal. It uses recursive function APUtil()
void Graph::AP()
{
    // Mark all the vertices as not visited
     // To store articulation points

    // Initialize parent and visited, and ap(articulation point) arrays
    for (int i = 0; i <= V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }

    // Call the recursive helper function to find articulation points
    // in DFS tree rooted with vertex 'i'
    for (int i = 1; i <= V; i++)
        if (visited[i] == false)
            APUtil(i);

    // Now ap[] contains articulation points, print them
    for (int i = 0; i <= V; i++)
        if (ap[i] == true)ans++ ;
            //cout << i << " ";
}

// Driver program to test above function



int t , cs , n ,  u , v , m ;

int main()
{
    // Create graphs given in above diagrams
    cin >> t ;
    while( cs < t )
    {
        //  cout << "sigh " << endl ;
        cs++ ;
        char x ;
        ans = 0  ;
        cin >> n >> m ;
        Graph graph(n) ;
        for( int i = 1 ; i <= m ; i++ )
        {
            scanf("%d %d", &u , &v ) ;
            graph.addEdge(u,v) ;
        }
        graph.AP() ;
        printf("Case %d: %d\n", cs, ans ) ;
    }



    return 0;
}
