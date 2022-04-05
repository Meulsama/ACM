vector<int> primes;
vector<bool> isPrime;

void getPrime(int n){
    isPrime.assign(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) primes.emplace_back(i);
        for (auto p : primes) {
            if (i * p > n) break;
            isPrime[i * p] = false;
            if (i % p == 0) break;
        }
    }
}