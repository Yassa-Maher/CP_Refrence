#include <bits/stdc++.h>
using namespace std;

vector<int> get_previous_greater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pge(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }
        if (!st.empty()) {
            pge[i] = st.top();
        }
        st.push(i);
    }
    return pge;
}

vector<int> get_next_greater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n, n);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }
        if (!st.empty()) {
            nge[i] = st.top();
        }
        st.push(i);
    }
    return nge;
}
