namespace Fact {
   vector<char> isPrime;
   vector<int> Prime,OneFac;
   void GetPrime(int n){
       for(int i=0;i<n;++i) isPrime[i]=1;isPrime[1]=1;
       for(int i=2;i<=n;i++){
            if(isPrime[i])Prime.push_back(i);
            for(int j:Prime){
                if(i*j>n) break;
                isPrime[i*j]=0;
                OneFac[i*j]=j;
                if(i%j==0)break;
            }
        }
    }
    void Fac_dfs(int x,int y,vector<int>& ans,vector<pair<int,int>>& FacList){
        if(x==(long long)(FacList.size())){ ans.push_back(y); return; }
        int k=1;
        for(int i=0;i<=FacList[x].second;++i){
            Fac_dfs(x+1,y*k,ans,FacList);
            k*=FacList[x].first;
        }
    }

    vector<pair<int,int>>GetPrimeFac(int a){
       vector<pair<int,int>>answer;
       if(isPrime[a]) return(vector<pair<int,int>>{pair<int,int>{a,1}});
       answer.push_back({OneFac[a],1});
       a/=OneFac[a];
       while(!isPrime[a]){
            if(OneFac[a]==answer.back().first)answer.back().second++;
                else answer.push_back({OneFac[a],1});
                a/=OneFac[a];
        }
        if(a==answer.back().first)answer.back().second++;
        else answer.push_back({a,1});return(answer);
    }

    vector<int>GetFacList(int a){
       vector<int> ans;
       vector<pair<int,int>>FacList=GetPrimeFac(a);
       Fac_dfs(0,1,ans,FacList);
       return(ans);
    }
   void init(int n){ isPrime.resize(n+2); OneFac.resize(n+2); GetPrime(n); }
   void init(){ init(10000005); }
};


