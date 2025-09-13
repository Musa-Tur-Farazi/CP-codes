int n,k; cin >> n >> k;
    int pos[k][n];
    int a[k][n];
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            cin >> a[i][j];
        }
    }
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            pos[i][a[i][j]-1] = j;
        }
    }
   // memset(dp,1,sizeof(dp));
    for(int i=0;i<n;i++){
        dp[i] = 1;
        for(int j=0;j<i;j++){
            bool ok = true;
            for(int u = 0;u<k;u++){
                if(pos[u][a[0][j]-1] > pos[u][a[0][i]-1]){
                    ok = false;
                    break;
                }
            }
            if(ok){
                dp[i] = max(dp[i],1+dp[j]);
            }
        }
    }
    int res = 0;
    for(int i=0;i<n;i++) res = max(res,dp[i]);
    cout << res << '\n';


