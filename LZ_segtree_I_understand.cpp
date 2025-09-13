template<class T>
struct segtree1{
	vector<int> tr, lz;
	segtree1(){}
	segtree1(int n){ tr.resize(n<<2,1); lz.resize(n<<2,1);}
	void push(int i,int l,int r) {
		if(lz[i]==1) return;
		tr[i] = (tr[i]*pw(lz[i],(r-l+1)))%mod;  // here
		if(l!=r) {
			lz[2*i+1]=(lz[2*i+1]*lz[i])%mod;
			lz[2*i+2]=(lz[2*i+2]*lz[i])%mod;
		}
		lz[i]=1;              //here
	}

	void upd(int ql,int qr,int v,int i=0,int l=0,int r=n-1) {
		push(i,l,r);
		if (l > r || r < ql || qr < l) return;
		if (ql <= l && r <= qr) {
			lz[i] = (lz[i]*v)%mod;        //here
			push(i,l,r);
			return;
		}
		int m = (l+r)/2;
		upd(ql,qr,v,2*i+1,l,m);
		upd(ql,qr,v,2*i+2, m+1,r);
		tr[i]=(tr[2*i+1]*tr[2*i+2])%mod;   //here
	}
	int qry(int ql,int qr,int i=0,int l=0,int r=n-1) {
		push(i,l,r);
		if (l > r || r < ql || qr < l) return 1;
		if (ql <= l && r <= qr) return tr[i];
		int m = (l+r)/2;
		int q1 = qry(ql,qr,2*i+1,l,m);
		int q2 = qry(ql,qr,2*i+2,m+1,r);
		return (q1*q2)%mod;
	}
};

template<class T>
struct segtree2{
	vector<int> tr, lz;
	segtree2(){}
	segtree2(int n){ tr.resize(n<<2); lz.resize(n<<2);}
	void push(int i,int l,int r) {
		if(lz[i]==0) return;
		tr[i]|=lz[i];
		if(l!=r) {
			lz[2*i+1]=(lz[2*i+1]|lz[i]);
			lz[2*i+2]=(lz[2*i+2]|lz[i]);
		}
		lz[i]=0;
	}

	void upd(int ql,int qr,int v,int i=0,int l=0,int r=n-1) {
		push(i,l,r);
		if (l > r || r < ql || qr < l) return;
		if (ql <= l && r <= qr) {
			lz[i]|=v;
			push(i,l,r);
			return;
		}
		int m = (l+r)/2;
		upd(ql,qr,v,2*i+1,l,m);
		upd(ql,qr,v,2*i+2,m+1,r);
		tr[i]=(tr[2*i+1]|tr[2*i+2]);
	}
	int qry(int ql,int qr,int i=0,int l=0,int r=n-1) {
		push(i,l,r);
		if (l > r || r < ql || qr < l) return 0;
		if (ql <= l && r <= qr) return tr[i];
		int m = (l+r)/2;
		int q1 = qry(ql,qr,2*i+1,l,m);
		int q2 = qry(ql,qr,2*i+2,m+1,r);
		return (q1|q2);
	}
};
