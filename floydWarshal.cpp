// Floyd-Warshall Algorithm
// Computes all-pairs shortest paths in a weighted graph
// n = number of vertices (1-indexed or 0-indexed)
// adj[i][j] = weight of edge i->j, INF if no edge

const int INF = 1e9;  // or 1e18 for long long

void floydWarshall(int n, vector<vector<int>>& adj) {
    // initialize distances
    vector<vector<int>> dist = adj; // copy adjacency matrix

    for(int k = 0; k < n; k++) {           // intermediate vertex
        for(int i = 0; i < n; i++) {       // start vertex
            for(int j = 0; j < n; j++) {   // end vertex
                if(dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // dist[i][j] now contains the shortest distance from i to j
}
