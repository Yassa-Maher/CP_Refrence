#include <bits/stdc++.h>
using namespace std;

#define ll long long

// ============================================================================
// Normal Segment Tree (Node Struct included)
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
