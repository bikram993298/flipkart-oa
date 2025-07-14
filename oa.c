Tunnel Problem
Thoerem - Articulation Point in Graph

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> disc, low;
vector<bool> isAP;
int timer;

void dfs(int u, int parent) {
    disc[u] = low[u] = timer++;
    int children = 0;
    for (int v : adj[u]) {
        if (disc[v] == -1) {
            // Tree edge
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            // non‐root articulation point condition
            if (parent != -1 && low[v] >= disc[u])
                isAP[u] = true;
        }
        else if (v != parent) {
            // back‐edge
            low[u] = min(low[u], disc[v]);
        }
    }
    // root articulation point condition
    if (parent == -1 && children > 1)
        isAP[u] = true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    adj.assign(n, {});
    // read full n×n adjacency matrix
    vector<vector<int>> A(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];
    // build undirected adjacency list (avoid double‐adding)
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (A[i][j] == 1) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    // read maintenance costs
    vector<long long> cost(n);
    for (int i = 0; i < n; i++)
        cin >> cost[i];

    // init articulation‐point arrays
    disc.assign(n, -1);
    low.assign(n, -1);
    isAP.assign(n, false);
    timer = 0;

    // run DFS from each unvisited node
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1)
            dfs(i, -1);
    }

    // sum up the costs of all articulation points
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (isAP[i])
            ans += cost[i];
    }

    cout << ans << "\n";
    return 0;
}

Candy Problem
Greedy

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    int M = 0;
    for(int i = 0; i < N; i++){
        cin >> A[i];
        M = max(M, A[i]);
    }

    // freq[x] = how many varieties produce exactly x candies per batch
    vector<int> freq(M+1, 0);
    for(int x : A){
        freq[x]++;
    }

    long long answer = 0;
    // for each possible box-size k = 1..M,
    // count how many A[i] are multiples of k
    for(int k = 1; k <= M; k++){
        int count = 0;
        // sum freq[k], freq[2k], freq[3k], ...
        for(int multiple = k; multiple <= M; multiple += k){
            count += freq[multiple];
            // early exit if we know count*k cannot beat current answer
            // (optional optimization)
            // if ((long long)count * k <= answer && count >= 2) break;
        }
        if(count >= 2){
            // we can send exactly one box of size k for each
            // of these 'count' varieties → total = k * count
            answer = max(answer, (long long)k * count);
        }
    }

    cout << answer << "\n";
    return 0;
}

Geeta Problem
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,X,Y;
    cin>>n>>X>>Y;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    int p=0,c=0,j;
    for(j=0;j<n;j++){
        int d=a[j]-p;
        if(d>0){
            if(d>Y)break;
        } else {
            if(-d>X)break;
        }
        p=a[j];
        c++;
    }
    if(j==n){
        int d=0-p;
        if((d>0?d:-d)<= (d>0?Y:X)) {
            cout<<c+1;
            return 0;
        }
    }
    cout<<2*c;
    return 0;
}

virus causing illness

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> g(n), m(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> m[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (m[i][j])
                g[i].push_back(j);

    vector<bool> v(n);
    vector<int> d(n), l(n), p(n, -1);
    set<int> a;
    int t = 0;

    function<void(int)> dfs = [&](int u) {
        v[u] = true;
        d[u] = l[u] = ++t;
        int c = 0;
        for (int w : g[u]) {
            if (!v[w]) {
                ++c;
                p[w] = u;
                dfs(w);
                l[u] = min(l[u], l[w]);
                if ((p[u] == -1 && c > 1) ||
                    (p[u] != -1 && l[w] >= d[u]))
                    a.insert(u);
            } else if (w != p[u]) {
                l[u] = min(l[u], d[w]);
            }
        }
    };

    for (int i = 0; i < n; ++i)
        if (!v[i])
            dfs(i);

    set<int> r;
    for (int u : a)
        for (int w : g[u])
            if (!a.count(w))
                r.insert(w);

    bool f = true;
    for (int w : r) {
        if (!f) cout << ' ';
        cout << w;
        f = false;
    }
    cout << "\n";
    return 0;
}



daniel
akash

