template<typename T = int>
struct Dinic{
    struct edge{
        int u, rev;
        T cap, flow;
    };

    int n, s, t;
    T flow;
    vector<int> lst;
    vector<int> d;
    vector<vector<edge>> g;

    Dinic() {}

    Dinic(int n, int s, int t) : n(n), s(s), t(t){
        g.resize(n);
        d.resize(n);
        lst.resize(n);
        flow = 0;
    }

    void add_edge(int v, int u, T cap, bool directed = true){
        g[v].push_back({u, (int)g[u].size(), cap, 0});
        g[u].push_back({v, (int)g[v].size() - 1, directed ? 0 : cap, 0});
    }

    T dfs(int v, T flow){
        if (v == t) return flow;
        if (flow == 0) return 0;
        T result = 0;
        for (; lst[v] < sz(g[v]); ++lst[v]){
            edge& e = g[v][lst[v]];
            if (d[e.u] != d[v] + 1) continue;
            T add = dfs(e.u, min(flow, e.cap - e.flow));
            if (add > 0){
                result += add;
                flow -= add;
                e.flow += add;
                g[e.u][e.rev].flow -= add;
            }
            if (flow == 0) break;
        }
        return result;
    }

    bool bfs(){
        fill(d.begin(), d.end(), -1);
        queue<int> q({s});
        d[s] = 0;
        while (!q.empty() && d[t] == -1){
            int v = q.front();
            q.pop();
            for (auto& e : g[v]){
                if (d[e.u] == -1 && e.cap - e.flow > 0){
                    q.push(e.u);
                    d[e.u] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    T calc(){
        T add;
        while (bfs()){
            fill(lst.begin(), lst.end(), 0);
            while((add = dfs(s,inf) > 0)
                    flow += add;
        }
        return flow;
    }
};
