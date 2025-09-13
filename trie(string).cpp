struct Trie{
    struct Node{
        Node* child[26];
        int leaf, cnt;

        Node(){
            for(int i=0;i<26;i++) child[i] = NULL;
            leaf = cnt = 0;
        }
    };

    Node* root;
    Trie(){
        root = new Node();
    };

    void add(string& s){
        Node* p = root;
        for (auto f : s){
            int c = f - 'a';
            if(p->child[c] == NULL) p->child[c] = new Node();
            p = p->child[c];
            p->cnt++;
        }
        p->leaf++;
    }

    bool present(string& s){
        Node* p = root;
        for (auto f : s){
            int c = f - 'a';
            if(p->child[c] == NULL) return false;
            p = p->child[c];
        }
        return (p->leaf) > 0; //leaf = 1 -> end marker
    }

    int query(string &s){  //change accordingly.
        Node* p = root;
        for (auto f : s){
            int c = f - 'a';
            if(p->child[c] == NULL) return 0;
            p = p->child[c];
        }
        return p->cnt; //count of subtree(i.e. cnt of strings having s as pref)
    }

    bool rmv(Node* p, string &s, int i){
        if(i != (int)(s.size())){
            int c = s[i] - 'a';
            if(rmv(p->child[c],s,i+1))p->child[c] = NULL;
        }
        else p->leaf--;
        if(p != root){
            p->cnt--;
            if(p->cnt == 0) {
                delete(p);
                return true;
            }
        }
        return false;
    }

    void rmv(string &s) {
        if(!present(s)) return;
        rmv(root, s, 0);
    }
}tr;
