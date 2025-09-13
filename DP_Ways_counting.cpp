//counting
//https://codeforces.com/contest/2027/problem/D2
void add(int &x, int y) {
  if ((x += y) >= M) {
    x -= M;
  }
}

struct ft {
  int n;
  vector<long long> s;
  vector<int> cnt;
  ft() = default;
  ft(int n): n(n), s(n + 2, inf), cnt(n + 2) {};
  void upd(int i, long long x, int y) {
    for (++i; i > 0; i -= i & -i) {
      if (s[i] > x) {
        s[i] = x;
        cnt[i] = y;
      } else if (s[i] == x) {
        add(cnt[i], y);
      }
    }
  }
  pair<long long, int> qry(int i) {
    long long res = inf;
    int c = 0;
    for (++i; i <= n + 1; i += i & -i) {
      if (res > s[i]) {
        res = s[i];
        c = cnt[i];
      } else if (res == s[i]) {
        add(c, cnt[i]);
      }
    }
    return {res, c};
  }
};

void solve() {
  int n, m; cin >> n >> m;
  vector<long long> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    a[i] += a[i - 1];
  }
  vector<int> b(m);
  for (int &x : b) {
    cin >> x;
  }
  vector<ft> tree(m);
  for (int i = 0; i < m; ++i) {
    tree[i] = ft(n);
    tree[i].upd(0, 0, 1);
  }
  vector<int> ptr(m);
  long long lx;
  int ly;
  for (int i = 1; i <= n; ++i) {
    lx = inf, ly = 0;
    for (int j = 0; j < m; ++j) {
      int &l = ptr[j];
      while (a[i] - a[l] > b[j]) {
        ++l;
      }
      auto [x, y] = tree[j].qry(l);
      x += m - j - 1;
      if (lx > x) {
        lx = x;
        ly = y;
      } else if (x == lx) {
        add(ly, y);
      }
      tree[j].upd(i, lx, ly);
    }
  }
  if (lx == inf) {
    cout << -1 << "\n";
  } else {
    cout << lx << " " << ly << "\n";
  }
}

