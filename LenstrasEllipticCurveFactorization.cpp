#include "bits/stdc++.h"
using namespace std;

#define int int64_t
#define trav(i, a) for(auto& i: a)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define si(a) ((int)(a).size())
#define ins insert
#define pb push_back
#define f first
#define s second

const int MOD = 1e9 + 7;
const int INF = 1e18;
const string nl = "\n";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
	return uniform_int_distribution<int>(a, b)(rng);
}

vector<int> primes;

void sieve(int limit) {
	vector<bool> prime(limit + 1, true);
	for(int i = 2; i <= limit; ++i) {
		if(prime[i]) {
			primes.pb(i);
			for(int j = i * 2; j <= limit; j += i) {
				prime[j] = false;
			}
		}
	}
}

array<int, 3> modinv(int a, int b) {
	if(b == 0) {
		return {1, 0, a};
	}
	int q = a / b;
	int r = a % b;
	array<int, 3> x = modinv(b, r);
	return {x[1], x[0] - q * x[1], x[2]};
}


array<int, 3> elliptic_add(array<int, 3> p, array<int, 3> q, int a, int b, int m) {
	int numerator = 0, denominator = 0;
	if(p[2] == 0) {
		return q;
	} else if(q[2] == 0) {
		return p;
	} else if(p[0] == q[0]) {
		if((p[1] + q[1]) % m == 0) {
			return {0, 1, 0};
		}
		numerator = (3 * p[0] * p[0] + a) % m;
		denominator = (2 * p[1]) % m;
	} else {
		numerator = (q[1] - p[1]) % m;
		denominator = (q[0] - p[0]) % m;
	}
	array<int, 3> x = modinv(denominator, m);
	if(x[2] > 1) {
		return {0, 0, denominator};
	}
	int y = (((numerator * x[0] * numerator * x[0] - p[0] - q[0]) % m + m) % m);
	//int y = (((((numerator * x[0]) % m) * ((numerator * x[0]) % m)) % m) - ((((p[0] + q[0]) % m + m)) % m));
	return {y, (((numerator * x[0] * (p[0] - y) - p[1]) % m + m) % m), 1};
}

array<int, 3> elliptic_mul(int k, array<int, 3> p, int a, int b, int m) {
	array<int, 3> r = {0, 1, 0};
	while(k > 0) {
		if(p[2] > 1) {
			return p;
		}
		if(k % 2 == 1) {
			r = elliptic_add(p, r, a, b, m);
		}
		k /= 2;
		p = elliptic_add(p, p, a, b, m);
	}
	return r;
}

int lenstra(int n, int limit) {
	int g = n, a = 0, b = 0;
	while(g == n) {
		array<int, 3> q = {rand(0, n - 1), rand(0, n - 1), 1};
		a = rand(0, n - 1);
		b = (((((q[1] * q[1]) % n) - ((q[0] * q[0] * q[0]) % n) + n) % n) - ((a * q[0]) % n) + n) % n;
		g = gcd(4 * a * a * a + 27 * b * b, n);
	}
	if(g > 1) {
		return g;
	}
	trav(p, primes) {
		int p_ = p;
		while(p_ < limit) {
			array<int, 3> q = elliptic_mul(p, q, a, b, n);
			if(q[2] > 1) {
				return gcd(q[2], n);
			}
			p_ *= p;
		}
	}
	return -1;
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);

	int n, limit;
	cin >> n >> limit;
	sieve(limit);
	cout << lenstra(n, limit) << nl;
}
