int mnsum[4*N];
void push_up(int x){
   // mx[x] = max(mx[x<<1],mx[x<<1|1]);
    sum[x] = sum[x<<1] + sum[x<<1|1];
}

void build(int l,int r,int x){
    if(l==r){
        mx[x] = sum[x] = a[l];
        return;
    }
    int m = (l+r)/2;
    build(l,m,x<<1);
    build(m+1,r,x<<1|1);
    push_up(x);
}

void upd(int ql,int qr,int l,int r,int x){
    if(mx[x]<=2) return;
    if(l==r){
        mx[x] = sum[x] = d[mx[x]];
        return;
    }
    int m = (l+r)/2;
    if(qr<=m) upd(ql,qr,l,m,x<<1);
    else if(ql>m) upd(ql,qr,m+1,r,x<<1|1);
    else{
        upd(ql,m,l,m,x<<1);
        upd(m+1,qr,m+1,r,x<<1|1);
    }
    push_up(x);
}

int qry(int ql,int qr,int l,int r,int x){
    if(ql==l && qr==r) return sum[x];
    int m = (l+r)/2;
    if(qr<=m) return qry(ql,qr,l,m,x<<1);
    if(ql>m) return qry(ql,qr,m+1,r,x<<1|1);
    return qry(ql,m,l,m,x<<1) + qry(m+1,qr,m+1,r,x<<1|1);
}

