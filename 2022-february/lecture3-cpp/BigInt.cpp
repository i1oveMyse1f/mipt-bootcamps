#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <random>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

const int LOG = 1000;
const int RADIX = 1e9;

struct BigInt {
private:
	int len;
	int a[LOG] = {}; // числа от 0 до 10^9000

	int operator[](int i) const {
		return a[i];
	}

	int& operator[](int i) {
		return a[i];
	}

public:
	BigInt(int x = 0) {
		a[0] = x;
		len = 1;
	}

	BigInt operator+(const BigInt& other) const {
		BigInt res;
		res.len = max(len, other.len);

		int c = 0;
		for (int i = 0; i < res.len || c; ++i) {
			int t = a[i] + other[i] + c;
			res[i] = t % RADIX;
			c = t / RADIX;
			res.len = max(res.len, i + 1);
		}

		return res;
	}

	BigInt operator*(const BigInt& other) const {
		BigInt res;

		for (int i = 0; i < len; ++i) {
			int c = 0;
			for (int j = 0; j < other.len || c; ++j) {
				long long d = res[i + j] + a[i] * 1LL * other[i] + c;
				res[i + j] = d % RADIX;
				c = d / RADIX;
				res.len = max(res.len, i + j + 1);
			}
		}

		return res;
	}

	BigInt& operator+=(const BigInt& other) {
		return *this = *this + other;
	}

	bool operator<(const BigInt& other) const {
		// a < b => !(b < a)
		// a < b, b < c => a < c
		// !(a < a)

		if (len < other.len)
			return true;
		if (len > other.len)
			return false;
		for (int i = len - 1; i >= 0; --i) {
			if (a[i] < other[i])
				return true;
			if (a[i] > other[i])
				return false;
		}

		return false;
	}

	friend istream& operator>>(istream& in, BigInt& x) {
		string s;
		in >> s;

		x.len = 0;
		memset(x.a, 0, sizeof x.a);

		for (int i = s.size() - 1; i >= 0; i -= 9) {
			if (i - 9 >= 0)
				x[x.len++] = stoi(s.substr(i - 8, 9));
			else
				x[x.len++] = stoi(s.substr(0, i + 1));
		}

		return in;
	}

	friend ostream& operator<<(ostream& out, const BigInt& x);

	friend static int length(BigInt x);
};

int length(BigInt x) {
	return x.len;
}

ostream& operator<<(ostream& out, const BigInt& x) {
	out << x[x.len - 1];

	for (int i = x.len - 2; i >= 0; --i) {
		out << setfill('0') << setw(9) << x[i];
	}

	return out;
}

BigInt operator+(int a, const BigInt& b) {
	return b + a;
}

template <class T>
istream& operator>>(istream& in, vector<T>& a) {
	for (T& x : a) {
		in >> x;
	}
	return in;
}

pair<int, int> g() {
	return { 1, 2 };
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	ifstream cin("input.txt");

	int n;
	cin >> n;
	vector<vector<int>> a(n, vector<int>(n));
	cin >> a;

}
