#include <bits/stdc++.h>
using namespace std;

#define ll long long


// ============================================================================
// Lowest Common Ancestor (LCA) USING BINARY LIFTING
// ============================================================================
struct LCA {
    int n;
    int LOG;
    vector<vector<int>> up;
    vector<vector<int>> adj;
    vector<int> depth;

    LCA(int n) {
        this->n = n;
        LOG = log2(n) + 1;
        adj.assign(n+1,{});
        up.assign(n+1, vector<int>(LOG));
        depth.assign(n+1,0);
    }

    void addEdge(int u,int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int node,int par) {
        up[node][0] = par;
        for(int i=1;i<LOG;i++) {
            up[node][i] = up[ up[node][i-1] ][i-1];
        }

        for(auto child : adj[node]) {
            if(child == par)
                continue;

            depth[child] = depth[node] + 1;
            dfs(child,node);
        }
    }

    void build(int root=1) {
        dfs(root,root);
    }

    int jump(int node,int k) {
        for(int i=0;i<LOG;i++) {
            if(k & (1<<i)) {
                node = up[node][i];
            }
        }
        return node;
    }

    int getLCA(int a,int b) {
        if(depth[a] < depth[b])
            swap(a,b);

        a = jump(a, depth[a]-depth[b]);

        if(a == b)
            return a;

        for(int i=LOG-1;i>=0;i--) {
            if(up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }

        return up[a][0];
    }
};
