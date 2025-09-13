
//nlog n
    int n;
    cin >> n;
    vector<int>a(n+1),b(n+1);
    vector<int>mp(n+1),f(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        mp[a[i]] = i;
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
        f[i] = inf;
    }

    int res = 0;
    f[0] = 0;
    for(int i=1;i<=n;i++){
        int l = 0, r = res, mid;
        if(mp[b[i]] > f[res]) f[++res] = mp[b[i]];
        else{
            while(l+1 < r){
                mid = (l + r)/2;
                if(f[mid] > mp[b[i]]) r = mid-1;
                else l = mid + 1;
            }
            f[l] = min(mp[b[i]],f[l]);
        }

    }
