string line;
getline(cin, line);

stringstream ss(line);
vector<int> arr;

int x;
while (ss >> x) {
    arr.push_back(x);
}
