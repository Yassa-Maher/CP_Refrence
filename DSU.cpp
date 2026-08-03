#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> parent, sz;

public:
    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);

        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]); // Path Compression
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        // Union by Size
        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};

struct Edge {
    int u, v, w;

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

class MST {
private:
    int n;
    vector<Edge> edges;

public:
    MST(int n) {
        this->n = n;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    pair<int, vector<Edge>> kruskal() {
        sort(edges.begin(), edges.end());

        DSU dsu(n);

        int totalWeight = 0;
        vector<Edge> mstEdges;

        for (auto &e : edges) {
            if (dsu.unite(e.u, e.v)) {
                totalWeight += e.w;
                mstEdges.push_back(e);
            }
        }

        return {totalWeight, mstEdges};
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    MST mst(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        mst.addEdge(u, v, w);
    }

    auto [cost, edges] = mst.kruskal();

    cout << "MST Cost = " << cost << '
';

    cout << "Edges:
";

    for (auto &e : edges) {
        cout << e.u << " " << e.v << " " << e.w << '
';
    }
}

// mapping for move node from set to another, (virtual node)
