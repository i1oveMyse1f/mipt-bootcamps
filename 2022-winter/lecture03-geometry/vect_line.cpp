#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

struct Vect {
	int x, y;
	Vect(int x = 0, int y = 0) : x(x), y(y) {}
	Vect(Vect a, Vect b) : x(b.x - a.x), y(b.y - a.y) {}

	Vect operator+(const Vect& other) const {
		return { x + other.x, y + other.y };
	}

	Vect operator-(const Vect& other) const {
		return { x - other.x, y - other.y };
	}

	long long operator*(const Vect& other) const {
		return x * 1LL * other.x + y * 1LL * other.y;
	}

	long long operator^(const Vect& other) const {
		return x * 1LL * other.y - y * 1LL * other.x;
	}

	long long size2() const {
		return x * 1LL * x + y * 1LL * y;
	}

	double size() const {
		return sqrt(x * 1LL * x + y * 1LL * y);
	}
};

istream& operator>>(istream& in, Vect& x) {
	return in >> x.x >> x.y;
}

ostream& operator<<(ostream& out, const Vect& x) {
	return out << x.x << ' ' << x.y;
}

struct Line {
	long long A, B, C;
	
	Line() {}
	Line(Vect a, Vect b) {
		A = b.y - a.y;
		B = a.x - b.x;
		C = b.x * 1LL * a.y - b.y * 1LL * a.x;
	}

	bool on_line(Vect p) {
		return (*this)(p) == 0;
	}

	long long operator()(Vect p) {
		return A * p.x + B * p.y + C;
	}

	double dist(Vect p) {
		return abs((*this)(p)) / sqrt(A * A + B * B);
	}
};