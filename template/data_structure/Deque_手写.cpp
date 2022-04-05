struct Deque {
    int head, tail;
    bool ok;
    vector<int> q;
    
    /*
        init(size)
        space : O(2 * n) 
    */
    
    Deque(int n): head(n), tail(n - 1), ok(false), q(2 * n + 1, 0) {}

    bool empty() {
        return tail < head;
    }

    int size() {
        return tail - head + 1;
    }

    int front() {
        return ok ? q[tail] : q[head];
    }

    int back() {
        return ok ? q[head] : q[tail];
    }

    void push_front(int x) {
        ok ? q[++tail] = x : q[--head] = x;
    }

    void push_back(int x) {
        ok ? q[--head] = x : q[++tail] = x;
    }

    void pop_front() {
        ok ? tail-- : head++;
    }

    void reverse() {
        ok ^= 1;
    }
};