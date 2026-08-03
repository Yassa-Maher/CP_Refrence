priority_queue<int> pq; // Max Heap 

priority_queue<int, vector<int>, greater<int>> pq; // Min Heap

priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // min pair


// max with special sort

auto cmp = [](pair<int,int> a, pair<int,int> b){
    return a.second > b.second;
};

priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

pq.push({1,50});
pq.push({2,10});
pq.push({3,30});

cout << pq.top().second << " "; // 10
