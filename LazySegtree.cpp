template<typename T>
struct segtree{

    struct node{
        int num;           // change if needed
    };

    node NEUTRAL = {0};     // change for calc
    int size;
    vector<node> tree;
    vector<node> lazy;
    node single(T v){ return {v}; }

/**************For updating *************/
    node update_op(node a,node b,int len){
         return {a.num + b.num*len};         // change what we update
    }
    node calc_update_op(node a,node b){
        return {a.num + b.num};     // change what we query
    }

    void apply_update(node &a, node b,int len){
        a = update_op(a,b,len);
    }
/*******************************************/

    void update_build(int x,int lx,int rx){
        if(rx == lx + 1){
            lazy[x] = single(0); //Base of tree..
            return;
        }
        int m = (lx + rx)/2;
        update_build(2*x + 1, lx , m);
        update_build(2*x + 2, m , rx);
        lazy[x] = calc_update_op(lazy[2*x + 1],lazy[2*x + 2]);

    }


    void update_init(int n){
        size = 1;
        while(size<n) size*=2;
        tree.assign(2*size,{0});     //change
        lazy.assign(2*size,{0});
        update_build(0,0,size);
    }


    void update(int l,int r,T v,int x,int lx,int rx){
        if(lx >=r || l >= rx) return;
        if(lx >= l && rx <=r){
            apply_update(tree[x],single(v),1);
            apply_update(lazy[x],single(v),rx-lx);
            return;
        }

        int m = (lx+rx)/2;
        update(l,r,v,2*x+1, lx, m);
        update(l,r, v, 2*x+2, m,rx);
        lazy[x] = calc_update_op(lazy[2*x+1],lazy[2*x+2]);
        apply_update(lazy[x],tree[x],rx-lx);
    }

    inline void update(int l,int r,T v){ update(l,r+1,v,0,0,size); }

    node update_query(int l,int r,int x,int lx,int rx){
        if(lx >= r || l>=rx) return NEUTRAL;     // change;
        if(lx >= l && rx<=r) return lazy[x];
        int m = (lx + rx)/2;
        node s1 = update_query(l,r,2*x+1,lx,m);
        node s2 = update_query(l,r,2*x+2,m,rx);
        auto res = calc_update_op(s1,s2);
        apply_update(res,tree[x],min(rx,r)-max(lx,l));
        return res;
    }

    inline node update_query(int l,int r){ return update_query(l,r+1,0,0,size); }

};

// All ranges are from l to r in 0-based Array indexing
// nodes represent the complex data type
