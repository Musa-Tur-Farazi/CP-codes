
struct AggStack {
    stack<pair<int, int>> st;
    void push(int x) {
        int cur = st.empty() ? x : min(st.top().second, x);
        st.push({x, cur});
    }
    void pop() {
        st.pop();
    }
    int agg() const {
        return st.top().second;
    }
};
struct AggQueue {
    AggStack in, out;
    void push(int x) {
        in.push(x);
    }

    void pop() {
        if (out.st.empty()) {
            while (!in.st.empty()) {
                int v = in.st.top().first;
                in.pop();
                out.push(v);
            }
        }
        out.pop();
    }

    // Query the current minimum.
    int query() const {
        if (in.st.empty()) return out.agg();
        if (out.st.empty()) return in.agg();
        return min(in.agg(), out.agg());
    }
}
