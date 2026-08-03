vector<long long> dijkstra(vector<vector<pair<long long,long long>>>& adj, long long src) {
    int V = adj.size();
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
    vector<long long> dist(V, 1e17);
    dist[src] = 0;
    pq.emplace(0, src);
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        long long d = top.first;
        long long u = top.second;
        if (d > dist[u])
            continue;
        for (auto &p : adj[u]) {
            long long v = p.first;
            long long w = p.second;
            if (dist[u] != 1e17 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}
