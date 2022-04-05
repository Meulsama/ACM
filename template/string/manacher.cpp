/*
    字符串需要预处理为"#a#b#"的形式
*/
vector<int> manacher(string s) {
    int n = s.size();
    vector<int> d(n);
    for (int i = 0, l = 0, r = - 1; i < n; i++) {
        int j = i > r ? 1 : min(d[l + r - i], r - i + 1);
        while (i - j >= 0 && i + j < n && s[i - j] == s[i + j]) {
            j++;
        }
        d[i] = j--;
        if (i + j < n) {
            l = i - j;
            r = i + j;
        }
    }
    return d;
}