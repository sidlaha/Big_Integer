#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

// Recursive FFT
void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[i<<1];
        a1[i] = a[i<<1|1];
    }

    fft(a0, invert);
    fft(a1, invert);

    for (int i = 0; 2 * i < n; i++) {
        cd w = polar(1.0, 2 * PI * i / n * (invert ? -1 : 1));
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
    }

    if (invert) {
        for (cd &x : a) x /= 2;
    }
}

// Multiply large numbers using FFT
string multiplyFFT(const string &a, const string &b) {
    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

    int n = 1;
    while (n < A.size() + B.size()) n <<= 1;

    vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(n); fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());

    for (int i = 0; i < n; i++) {
        if (result[i] >= 10) {
            if (i + 1 == result.size()) result.push_back(0);
            result[i + 1] += result[i] / 10;
            result[i] %= 10;
        }
    }

    while (result.size() > 1 && result.back() == 0) result.pop_back();

    string res;
    for (int i = result.size() - 1; i >= 0; i--) res += result[i] + '0';
    return res;
}

int main() {
    string nStr;
    cout << "Enter a number (as string): ";
    cin >> nStr;

    int n = stoi(nStr);
    string fact = "1";

    for (int i = 2; i <= n; ++i) {
        fact = multiplyFFT(fact, to_string(i));
    }

    cout << "\nFactorial of " << n << " is:\n";
    cout << fact << endl;

    return 0;
}
