#include <bits/stdc++.h>
using namespace std;

#define ll long long

// ============================================================================
// 1. Lowest Common Ancestor (LCA) USING BINARY LIFTING
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

// ============================================================================
// 2. Sparse Table
// ============================================================================
struct SparseTable {
    int n;
    int LOG;
    vector<vector<ll>> st;

    SparseTable(vector<ll>& a) {
        n = a.size();
        LOG = log2(n) + 1;
        st.assign(LOG, vector<ll>(n));

        for(int i = 0; i < n; i++)
            st[0][i] = a[i];

        for(int k = 1; k < LOG; k++) {
            for(int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = merge(
                    st[k-1][i],
                    st[k-1][i + (1 << (k-1))]
                );
            }
        }
    }

    ll merge(ll a, ll b) {
        return min(a,b);
        // max:
        // return max(a,b);
    }

    ll query(int l,int r) {
        int len = r - l + 1;
        int k = log2(len);

        return merge(
            st[k][l],
            st[k][r - (1 << k) + 1]
        );
    }
};

// ============================================================================
// 3. Segment Tree With Lazy Propagation (Node Struct included)
// ============================================================================
struct LazyNode {
    ll val;
    ll lazy;
    bool isLazy;

    LazyNode() {
        val = 0;
        lazy = 0;
        isLazy = false;
    }

    LazyNode(ll v) {
        val = v;
        lazy = 0;
        isLazy = false;
    }

    void merge(LazyNode l, LazyNode r) {
        val = l.val + r.val;
    }

    void apply(ll x, int len) {
        val += x * len;
        lazy += x;
        isLazy = true;
    }
};

class LazySegTree {
public:
    int size;
    vector<LazyNode> tree;

    LazySegTree(vector<ll>& a) {
        size = 1;
        while(size < a.size())
            size *= 2;

        tree.assign(2 * size, LazyNode());
        build(a,0,0,size);
    }

    void build(vector<ll>& a,int x,int lx,int rx) {
        if(rx-lx==1) {
            if(lx < a.size())
                tree[x] = LazyNode(a[lx]);
            return;
        }

        int mid = (lx+rx)/2;
        build(a,2*x+1,lx,mid);
        build(a,2*x+2,mid,rx);
        tree[x].merge(tree[2*x+1],tree[2*x+2]);
    }

    void push(int x,int lx,int rx) {
        if(!tree[x].isLazy)
            return;

        int mid = (lx+rx)/2;
        tree[2*x+1].apply(tree[x].lazy, mid-lx);
        tree[2*x+2].apply(tree[x].lazy, rx-mid);
        tree[x].lazy = 0;
        tree[x].isLazy = false;
    }

    void update(int l,int r,ll v,int x,int lx,int rx) {
        if(lx>=r || rx<=l)
            return;

        if(lx>=l && rx<=r) {
            tree[x].apply(v,rx-lx);
            return;
        }

        push(x,lx,rx);
        int mid = (lx+rx)/2;
        update(l,r,v,2*x+1,lx,mid);
        update(l,r,v,2*x+2,mid,rx);
        tree[x].merge(tree[2*x+1],tree[2*x+2]);
    }

    void update(int l, int r, ll v) {
        update(l, r, v, 0, 0, size);
    }

    LazyNode query(int l,int r,int x,int lx,int rx) {
        if(lx>=r || rx<=l)
            return LazyNode ();

        if(lx>=l && rx<=r)
            return tree[x];

	push(x,lx,rx); // only the diff in lazy query

        int mid = (lx+rx)/2;
        LazyNode left = query(l,r,2*x+1,lx,mid);
        LazyNode right = query(l,r,2*x+2,mid,rx);

        LazyNode ans;
        ans.merge(left,right);
        return ans;
    }

    ll query(int l,int r) {
        return query(l,r,0,0,size).val;
    }
};

// ============================================================================
// 4. Normal Segment Tree (Node Struct included)
// ============================================================================
struct Node {
    ll val;

    Node() {
        val = 0;
    }

    Node(ll v) {
        val = v;
    }

    void merge(Node l, Node r) {
        val = l.val + r.val;
    }
};

class SegTree {
public:
    int size;
    vector<Node> tree;

    SegTree(vector<ll>& a) {
        size = 1;
        while(size < a.size())
            size *= 2;

        tree.assign(2 * size, Node());
        build(a,0,0,size);
    }

    void build(vector<ll>& a,int x,int lx,int rx) {
        if(rx-lx==1) {
            if(lx < a.size())
                tree[x] = Node(a[lx]);
            return;
        }

        int mid = (lx+rx)/2;
        build(a,2*x+1,lx,mid);
        build(a,2*x+2,mid,rx);
        tree[x].merge(tree[2*x+1],tree[2*x+2]);
    }

    void set(int i,ll v,int x,int lx,int rx) {
        if(rx-lx==1) {
            tree[x] = Node(v);
            return;
        }

        int mid = (lx+rx)/2;
        if(i < mid)
            set(i,v,2*x+1,lx,mid);
        else
            set(i,v,2*x+2,mid,rx);

        tree[x].merge(tree[2*x+1],tree[2*x+2]);
    }

    Node query(int l,int r,int x,int lx,int rx) {
        if(lx>=r || rx<=l)
            return Node();

        if(lx>=l && rx<=r)
            return tree[x];

        int mid = (lx+rx)/2;
        Node left = query(l,r,2*x+1,lx,mid);
        Node right = query(l,r,2*x+2,mid,rx);

        Node ans;
        ans.merge(left,right);
        return ans;
    }

    void set(int i,ll v) {
        set(i,v,0,0,size);
    }

    ll query(int l,int r) {
        return query(l,r,0,0,size).val;
    }
};

