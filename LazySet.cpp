template<typename T>
struct segtree{

    struct node{
        int num;           // change if needed
    };

    node NO_OP = {inf};      // change if needed
    node NEUTRAL = {0};     // change for calc
    int size;
    vector<node> tree;
    vector<node> lazy;
    node single(T v){ return {v}; }

/***************For setting ****************/
    node set_op(node a,node b,int len){
        if(b.num == NO_OP.num) return a;
        b.num*=len;                                         //change what we set
        return b;
    }

    node calc_set_op(node a,node b){
        return {a.num+b.num};                          // change what we query
    }

    void apply_set(node &a , node b,int len){
        a = set_op(a,b,len);
    }
/******************************************/

     void set_build(int x,int lx,int rx){
        if(rx == lx + 1){
            lazy[x] = single(0);      // base of the tree as initial array
            return;
        }
        int m = (lx + rx)/2;
        set_build(2*x + 1, lx , m);
        set_build(2*x + 2, m , rx);
        lazy[x] = calc_set_op(lazy[2*x + 1],lazy[2*x + 2]);
    }

    void set_init(int n){
        size = 1;
        while(size<n) size*=2;
        tree.assign(2*size,{0});     //change
        lazy.assign(2*size,{0});
        set_build(0,0,size);
    }

    void propagate(int x, int lx,int rx){
        if(rx - lx == 1) return;
        int m = (lx + rx)/2;
        apply_set(tree[2*x + 1],tree[x],1);
        apply_set(lazy[2*x + 1],tree[x],m - lx);
        apply_set(tree[2*x + 2],tree[x],1);
        apply_set(lazy[2*x + 2],tree[x],rx-m);
        tree[x] = NO_OP;

    }

    void set(int l,int r,T v,int x,int lx,int rx){
        propagate(x,lx,rx);
        if(lx >=r || l >= rx) return;
        if(lx >= l && rx <=r){
            apply_set(tree[x],single(v),1);
            apply_set(lazy[x],single(v),rx-lx);
            return;
        }

        int m = (lx+rx)/2;
        set(l,r,v,2*x+1, lx, m);
        set(l,r, v, 2*x+2, m,rx);
        lazy[x] = calc_set_op(lazy[2*x+1],lazy[2*x+2]);
    }

    inline void set(int l,int r,T v){ set(l,r+1,v,0,0,size); }

    node set_query(int l,int r,int x,int lx,int rx){
        propagate(x,lx,rx);
        if(lx >= r || l>=rx) return NEUTRAL; // change;
        if(lx >= l && rx<=r) return lazy[x];
        int m = (lx + rx)/2;
        node s1 = set_query(l,r,2*x+1,lx,m);
        node s2 = set_query(l,r,2*x+2,m,rx);
        auto res = calc_set_op(s1,s2);
        return res;
    }

    inline node set_query(int l,int r){ return set_query(l,r+1,0,0,size); }

};

// All ranges are from l to r in 0-based Array indexing
// nodes represent the complex data type

