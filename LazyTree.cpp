#include <bits/stdc++.h>
using namespace std;

#define ll long long

// ============================================================================
// Segment Tree With Lazy Propagation (Node Struct included)
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
