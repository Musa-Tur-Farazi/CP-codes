int stree[25][400005];
int lazy[25][400005];

void build(int v, int tl, int tr, int b){
    if (tl == tr){
        if ((ar[tl] & (1 << b))){
            stree[b][v] = 1;
        }
        return;
    }
    int tm = (tl + tr) / 2;
    build(2 * v, tl, tm, b);
    build(2 * v + 1, tm + 1, tr, b);
    stree[b][v] = stree[b][2 * v] + stree[b][2 * v + 1];
}

void update(int v, int tl, int tr, int l, int r, int b){
    if (lazy[b][v]){
        stree[b][v] = tr - tl + 1 - stree[b][v];
        if (tl != tr){
            lazy[b][2 * v] ^= 1;
            lazy[b][2 * v + 1] ^= 1;
        }
        lazy[b][v] = 0;
    }
    if (tl > r || tr < l) return;
    if (tl >= l && tr <= r){
        stree[b][v] = (tr - tl + 1) - stree[b][v];
        if (tl != tr){
            lazy[b][2 * v] ^= 1;
            lazy[b][2 * v + 1] ^= 1;
        }
        lazy[b][v] = 0;
        return;
    }
    int tm = (tl + tr) / 2;
    update(2 * v, tl, tm, l, r, b);
    update(2 * v + 1, tm + 1, tr, l, r, b);
    stree[b][v] = stree[b][2 * v] + stree[b][2 * v + 1];
}

int query(int v, int tl, int tr, int l, int r, int b){
    if (lazy[b][v]){
        stree[b][v] = tr - tl + 1 - stree[b][v];
        if (tl != tr){
            lazy[b][2 * v] ^= 1;
            lazy[b][2 * v + 1] ^= 1;
        }
        lazy[b][v] = 0;
    }
    if (tl > r || tr < l) return 0;
    if (tl >= l && tr <= r){
        return stree[b][v];
    }
    int tm = (tl + tr) / 2;
    return query(2 * v, tl, tm, l, r, b) + query(2 * v + 1, tm + 1, tr, l, r, b);
}

