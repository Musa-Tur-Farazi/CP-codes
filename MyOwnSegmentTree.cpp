template<typename T>
struct segtree{
    //O-based
    struct node{
        int num; // change
    };

    node NEUTRAL = {0}; //change
    int sz;
    vector<node> tree;
    void init(int n){
        sz = 1;
        while(sz<n) sz*=2;
        tree.resize(2*sz);
    }
    node combine(node a,node b){
        return {a.num+b.num}; // change
    }
    node single(T v){ return {v}; }//change , it requires for base of the tree..}

    void build(vector<T> &a,int x,int lx,int rx){
        if(rx-lx == 1){
            if(lx < a.size()) tree[x] = single(a[lx]);
            return;
        }
        int m = (lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        tree[x] = combine(tree[2*x+1],tree[2*x+2]);  //change
    }

    inline void build(vector<T>&a){ init((int32_t)a.size()); build(a,0,0,sz); }

    void set(int i,T v,int x,int lx,int rx){
        if(rx-lx == 1){
            tree[x] = single(v);
            return;
        }
        int m = (lx+rx)/2;
        if( i < m) set(i,v,2*x+1, lx, m);
        else set(i, v, 2*x+2, m,rx);
        tree[x] = combine(tree[2*x+1],tree[2*x+2]);
    }

    inline void set(int i,T v){ set(i,v,0,0,sz); }

    void inc(int i,T v,int x,int lx,int rx){
        if(rx-lx == 1){
            tree[x].num += single(v).num;
            return;
        }
        int m = (lx+rx)/2;
        if( i < m) inc(i,v,2*x+1, lx, m);
        else inc(i, v, 2*x+2, m,rx);
        tree[x] = combine(tree[2*x+1],tree[2*x+2]);
    }
    inline  void inc(int i,T v){ inc(i,v,0,0,sz); }

    node query(int l,int r,int x,int lx,int rx){
        if(lx >= r || l>=rx) return NEUTRAL; // change;
        if(lx >= l && rx<=r) return tree[x];
        int m = (lx + rx)/2;
        node s1 = query(l,r,2*x+1,lx,m);
        node s2 = query(l,r,2*x+2,m,rx);
        return combine(s1,s2); //change
    }

    inline node query(int l,int r){ return query(l,r+1,0,0,sz); }

    node kth_one(int k,int x,int lx,int rx){
        if(rx-lx==1) return {lx};
        int m = (lx+rx)/2;
        int sl = tree[2*x+1].num;
        if(k < sl) return kth_one(k,2*x+1,lx,m);
        return kth_one(k-sl,2*x+2,m,rx);
    }
    inline node kth_one(int k){ return kth_one(k,0,0,sz);  }

    node first_greater(int v,int l,int x,int lx,int rx){
        if(tree[x].num < v) return {-1};
        if(rx<=l) return {-1};
        if(rx-lx==1) return {lx};
        int m = (lx+rx)/2;
        int res = first_greater(v,l,2*x+1,lx,m).num;
        if(res==-1) res = first_greater(v,l,2*x+2,m,rx).num;
        return {res};
    }
    // first >= starting from pos = l
    inline node first_greater(int v,int l){ return first_greater(v,l,0,0,sz); }
};

