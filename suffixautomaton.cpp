const int maxn = 2e6 + 5;
struct SA{
    struct Node{
        int len, fa;
        unordered_map<char,int>ch;
    }node[maxn];
    int tot = 1, last = 1;
    int f[maxn], c[maxn], id[maxn];

    SA(){
        clear();
    }

    int new_node(){
        ++tot;
        node[tot].len = node[tot].fa = 0;
        f[tot] = 0;
        return tot;
    }

    void clear(){
        tot = 0;
        last = new_node();
    }

    void extend(char c){
        int p = last, np = last = new_node();
        node[np].len = node[p].len + 1;
        for(; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
        if (!p) node[np].fa = 1;
        else{
            int q = node[p].ch[c];
            if (node[q].len == node[p].len + 1) node[np].fa = q;
            else{
                int nq = new_node();
                node[nq] = node[q], node[nq].len = node[p].len + 1;
                node[q].fa = node[np].fa = nq;
                for(; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
            }
        }
        f[last] += 1;
    }

    void topsort(){
        for(int i = 1; i <= tot; i++) c[i] = 0;
        for(int i = 1; i <= tot; i++) c[node[i].len]++;
        for(int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for(int i = tot; i >= 1; i--) id[c[node[i].len]--] = i;
        for(int i = tot; i >= 2; i--) f[node[id[i]].fa] += f[id[i]];
    }

    void build(const string &s){
        clear();
        for(auto c : s) extend(c);
        topsort();
    }
    int substr_count(string &p){
        int cur = 1;
        for(auto c : p){
            if(!node[cur].ch[c]) return 0;
            cur = node[cur].ch[c];
        }
        return f[cur];
    }

    void min_cyc(string &s){
        build(s+s);
        int cur = 1;
        for(auto c : s){
            cout << node[cur].ch.begin()->first;
            cur = node[cur].ch.begin()->second;
        }
    }
}sa;
