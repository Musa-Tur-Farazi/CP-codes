/// Every node works as a state
/// There can be at most 2*n states (nodes)  total in worst case
/// Every state holds len which is the longest of the all strings of a state
/// All strings of a state have same end_of_time in original string
/// Every state holds a parameter link which holds the address of that state which holds the longest suffix of w
/// where w is the longest string of current state
/// next mapping will hold the edges between states with level char

struct state {
    int len, link;
    map<char, int> next;
};

/// This should be declared globally
/// Number of states can be at most 2*n ,where n is the length of string
/// sz for pointer of number of states in SAM i.e. Suffix Automation

const int MAXLEN = 100000;
state st[MAXLEN * 2];
int dplex[2*MAXLEN];    ///For lex
int cntlex[2*MAXLEN];    ///For lex
int dp[12][2*MAXLEN];///dp[i][j],it will hold the longest common substring of state j of first string with ith string
int sz, last;
set<pair<int,int>>callex;

/// First state is the first one ,so len is zero
/// There is no suffix link of first state ,so link is -1
/// last is obviously zero for first state

void sa_init() {
    for(int i=0;i<=sz;i++) st[i].next.clear();
    st[0].len = 0;
    st[0].link = -1;
    sz = last = 1;
}

/// when we add new character then we will check by last pointer to which label with our new character c

void sa_extend(char c) {
    int cur = sz++;/// increase the size of sz
    st[cur].len = st[last].len + 1;/// it's obviously increasing by one as new charcter is adding
    cntlex[cur] = 1;                     ///Only for lexFor k-th lex unique substr no need these
    cal.insert(make_pair(st[cur].len,cur));  ///For k-th lex unique substr no need these
    int p = last;
    while (p != -1 && !st[p].next.count(c)) { /// finding that state from where a state remains with edge of character same character c
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) { /// If there is no state with such transition(edge) with character c , at last p will stop at first state
        st[cur].link = 1;
    } else {  /// state with label c has been found
        int q = st[p].next[c]; /// the state which has been attached to p by edge c has been stated by q
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else { /// create new state and make change of all suffix links of p whose edges are through label with c to q
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            cntlex[clone]=0;           ///For k-th lex unique substr no need these
            callex.insert(make_pair(st[clone].len,clone));  ///For k-th lex unique substr no need these
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

/// it is i.e. how many paths can be started from here + 1 (empty string)
/// So , when find kth string it will help us to find kth path as we know how many paths from here can be possible
void lex_calcul(int v) {
    if (dplex[v])
        return;
    dplex[v] = cntlex[v]; /// we previously on finding kth unique one , initialize with it one assuming that state occurs one time
    /// But here we have to take the occurrence of state should be taken into account
    ///For k-th lex unique substr , dp[v]=1
    for (map<int, int>::iterator it = st[v].next.begin(); it != st[v].next.end(); it++){
        lex_calcul(it->second);
        dplex[v] += dplex[it->second];
    }
}

/// For k-th lex unique substr no need this func
void lex_precal(){/// we apply the following operation for each v: cnt[link(v)] += cnt[v]
    set< pair<int,int> >::reverse_iterator it;
    for(it=cal.rbegin();it!=cal.rend();it++)
       cntlex[ st[ it -> second ].link ] += cntlex[ it->second ];
}


string find_kth_lexicographical(int k){
    string res="";
    int p=1;/// our starting node now start from 1 because string start from 1 0th is #
    while(k){
        int a=0;
        while( k>dplex[st[p].next[a]] && a<26 ){
           /// cout<<"k in"<<k<<endl;
           /// cout<<"a "<<a<<endl;
            if (st[p].next[a]) k-=dplex[st[p].next[a]];
             a++;/// it is increased till there is edge from p i.e. st[p].next[a] is not empty
        }
        res+=('a'+a);
        p=st[p].next[a];         ///For k-th lex unique substr just do k--

        if(k>=cnt[p]) {k=k-cntlex[p];}///when we find kth unique lexicographically string , then we subtract one from k assuming this string occurs one time
        else {break;}              /// But here , we have to care about duplicate strings ,so subtract occurrence of that string should be subtracted
        ///cout<<"k out"<<k<<endl;
    }
    return res;
}

void longest_commn_sbstrng(int caso,string t){
    int state_num=0,match=0;
    /// state_num holds for node number where longest string remains which is also suffix of prefix ending at i
    /// match is current matching with suffix ending with i
    /// length_of_lngst_mtch is amongst all of the match
    /// best_match_ending_point states the index of prefix of t whose suffix with length of length_of_lngst_mtch.

    for(int i=0;i<t.length();i++){
        while(state_num && !st[state_num].next.count(t[i]-'a')){
            state_num=st[state_num].link;
            match=st[state_num].len;
        }
        if(st[state_num].next.count(t[i]-'a')){
            state_num=st[state_num].next[t[i]-'a'];
            match++;
        }
        dp[caso][state_num]=max(dp[caso][state_num],match);/// take maximum one ,like maximum substring between two strings
    }
    for(int state=sz-1;state>=0;state--){
        if(dp[caso][state]){/// not equal zero ,then enter into this
            while(state){///not equal to zero i.e. root state
                state=st[state].link;
                dp[caso][state]=st[state].len;
            }
        }
    }
}

