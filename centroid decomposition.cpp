// C++ program for centroid decomposition of Tree
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100007 ;

struct centroidDecompostion {

    vector<int> tree[MAXN];
    vector<int> centroidTree[MAXN];
    int par[MAXN] ;
    bool centroidMarked[MAXN];
    void addEdge(int u, int v) {
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    void DFS(int src, bool visited[], int subtree_size[], int* n) {
        visited[src] = true;
        *n += 1;
        subtree_size[src] = 1;
        vector<int>::iterator it;
        for (it = tree[src].begin(); it!=tree[src].end(); it++)
            if (!visited[*it] && !centroidMarked[*it]) {
                DFS(*it, visited, subtree_size, n);
                subtree_size[src]+=subtree_size[*it];
            }
    }

    int getCentroid(int src, bool visited[], int subtree_size[], int n) {
        bool is_centroid = true;
        visited[src] = true;
        int heaviest_child = 0;
        vector<int>::iterator it;
        for (it = tree[src].begin(); it!=tree[src].end(); it++)
            if (!visited[*it] && !centroidMarked[*it]) {
                if (subtree_size[*it]>n/2)
                    is_centroid=false;
                if (heaviest_child==0 ||
                        subtree_size[*it]>subtree_size[heaviest_child])
                    heaviest_child = *it;
            }

        if (is_centroid && n-subtree_size[src]<=n/2)
            return src;
        return getCentroid(heaviest_child, visited, subtree_size, n);
    }

    int getCentroid(int src) {
        bool visited[MAXN];
        int subtree_size[MAXN];
        memset(visited, false, sizeof visited);
        memset(subtree_size, 0, sizeof subtree_size);
        int n = 0;
        DFS(src, visited, subtree_size, &n);
        for (int i=1; i<MAXN; i++)
            visited[i] = false;
        int centroid = getCentroid(src, visited, subtree_size, n);
        centroidMarked[centroid]=true;
        return centroid;
    }
    int decomposeTree(int root) {
        int cend_tree = getCentroid(root);
        vector<int>::iterator it;
        for (it=tree[cend_tree].begin(); it!=tree[cend_tree].end(); it++) {
            if (!centroidMarked[*it]) {
                int cend_subtree = decomposeTree(*it);
                centroidTree[cend_tree].push_back(cend_subtree);
                par[cend_subtree] = cend_tree ;
            }
        }
        return cend_tree;
    }
};

