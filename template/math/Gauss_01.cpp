int Gauss(vector<bitset<200>>& e) {
    int n = e.size();
    int rank = 0;
    for (int i = 0, j = 0; j < n; j++) {
        int id = i;
        for (int k = i; k < n; k++) {
            if (e[k][j]) {
                id = k;
                break;
            }
        }
        if (!e[id][j]) continue;
        swap(e[i], e[id]);
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            if (e[k][j]) {
                e[k] ^= e[i];
            }
        }
        rank++;
        i++;
    }
    return n - rank;
}