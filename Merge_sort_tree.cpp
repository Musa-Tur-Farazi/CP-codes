int n,q,a[N];
vector<int> tr[4*N+5];
//build merge sort tree
void build(int node,int l,int r){
    //if range length is 1 there's only one element to add and no children
    if (l==r){
        tr[node].push_back(a[l]);
        return;
    }int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    int i=0,j=0;
    // use two pointers to merge the two vectors in O(r-l+1)
    while (i<tr[node*2].size() && j<tr[node*2+1].size()){
        if (tr[node*2][i]<tr[node*2+1][j]) tr[node].push_back(tr[node*2][i++]);
        else tr[node].push_back(tr[node*2+1][j++]);
    }
    while (i<tr[node*2].size()) tr[node].push_back(tr[node*2][i++]);
    while (j<tr[node*2+1].size()) tr[node].push_back(tr[node*2+1][j++]);
    return;
}
//query ....
int query(int node,int l,int r,int lx,int rx,int x){
    //if outside -> 0
    if (l>rx || r<lx) return 0;
    //if inside do binary search
    if (l>=lx && r<=rx){
        int L=0,R=tr[node].size()-1,mid,ans=0;
        while (L<=R){
            mid=(L+R)/2;
            if (tr[node][mid]<x){
                ans=mid+1;
                L=mid+1;
            }else R=mid-1;
        }return ans;
    }
    int mid=(l+r)/2;
    return query(node*2,l,mid,lx,rx,x)+query(node*2+1,mid+1,r,lx,rx,x);
}
