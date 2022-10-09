/*
    O(NloglogN)
*/
vector<bool> isPrime;
vector<int> primes;

void getPrime(int n) {
    isPrime.assign(n, true);
    isPrime[0] = isPrime[1] = false;
    primes.clear();
    for (int i = 2; i < n; i++) {
        if (!isPrime[i]) continue;
        primes.push_back(i);
        for (ll j = i * i; j < n; j += i) {
            isPrime[j] = false;
        }
    }
}