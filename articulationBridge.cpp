// A C++ program to find bridges in a given undirected graph
#include<bits/stdc++.h>
#define NIL -1
using namespace std;

vector < pair < int , int > > ans ;
bool visited[10005] ;
int disc[10004] ;
int low[10004] ;
int parent[10004] ;
// A class that represents an undirected graph
class Graph
{
    int V; // No. of vertices
    vector<int> adj[10004] ; // A dynamic array of adjacency lists
    void bridgeUtil(int v);
public:
    Graph(int V); // Constructor
    void addEdge(int v, int w); // to add an edge to graph
    void bridge(); // prints all bridges
};

Graph::Graph(int V)
{
    this->V = V;
    for( int i = 0 ; i < V ; i++ )
        adj[i].clear() ;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v); // Note: the graph is undirected
}

// A recursive function that finds and prints bridges using
// DFS traversal
// u --> The vertex to be visited next
// visited[] --> keeps tract of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
void Graph::bridgeUtil(int u )
{
    // A static variable is used for simplicity, we can
    // avoid use of static variable by passing a pointer.
    static int time = 0;

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices aadjacent to this
    for (int i  = 0 ; i < adj[u].size() ; ++i)
    {
        int v = adj[u][i] ; // v is current adjacent of u

        // If v is not visited yet, then recur for it
        if (!visited[v])
        {
            parent[v] = u;
            bridgeUtil(v);

            // Check if the subtree rooted with v has a
            // connection to one of the ancestors of u
            low[u] = min(low[u], low[v]);

            // If the lowest vertex reachable from subtree
            // under v is below u in DFS tree, then u-v
            // is a bridge
            //cout << "u " << u << " & " << " v " << v << endl ;

            if (low[v] > disc[u])
            {
                //cout << u <<" " << v << endl;
                if( u > v ) ans.push_back(make_pair(v,u)) ;
                else ans.push_back(make_pair(u,v)) ;

            }

        }

        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}

// DFS based function to find all bridges. It uses recursive
// function bridgeUtil()
void Graph::bridge()
{
    // Mark all the vertices as not visited
    // Initialize parent and visited arrays
    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
    }

    // Call the recursive helper function to find Bridges
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            bridgeUtil(i);
}

// Driver program to test above function
int t , cs , n ,  u , v , k ;

int main()
{
    // Create graphs given in above diagrams
    cin >> t ;
    while( cs < t )
    {
      //  cout << "sigh " << endl ;
        cs++ ;
        char x ;
        ans.clear() ;
        cin >> n ;
        Graph graph(n) ;
        for( int i = 1 ; i <= n ; i++ )
        {
            //cout << " i " << i << endl ;
            scanf("%d %c%d%c", &u , &x, &k, &x  ) ;
           // printf("u %d , k %d \n", u , k ) ;
            for( int j = 0 ; j < k ; j++ )
            {
                scanf("%d", &v ) ;
               // printf("v = %d\n", v ) ;
                if( u < v ) graph.addEdge(u,v) ;
            }
        }
        graph.bridge() ;
    printf("Case %d:\n", cs ) ;
    printf("%d critical links\n", ans.size() ) ;
    //cout << ans.size() << endl ;
    sort(ans.begin() , ans.end() ) ;
    for( int i = 0 ; i < ans.size() ; i++ )
        printf("%d - %d\n", ans[i].first , ans[i].second ) ;
        //cout << ans[i].first << " " << ans[i].second << endl ;

    }



    return 0;
}

/*

6
0 (1) 4
1 (0)
2 (1) 5
3 (1) 5
4 (2) 0 5
5 (3) 2 3 4

*/
