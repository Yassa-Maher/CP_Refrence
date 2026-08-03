#include <bits/stdc++.h>
using namespace std;

#define ll long long


// ============================================================================
// Sparse Table
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

