#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

// FFT function
void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[i*2];
        a1[i] = a[i*2 + 1];
    }

    fft(a0, invert);
    fft(a1, invert);

    for (int i = 0; 2 * i < n; i++) {
        cd w = polar(1.0, 2 * PI * i / n * (invert ? -1 : 1));
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
    }

    if (invert)
        for (cd& x : a)
            x /= 2;
}

// FFT-based multiplication
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

// Compare two big strings (a < b)
bool isLess(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

// Divide big string by int and return remainder
int modBig(const string& num, int divisor) {
    int rem = 0;
    for (char ch : num) {
        rem = (rem * 10 + (ch - '0')) % divisor;
    }
    return rem;
}

// -------- Primality check --------
bool isPrime(const string& nStr) {
    if (nStr == "1") return false;
    if (nStr == "2") return true;

    int i = 2;
    string iStr = "2";

    while (true) {
        string square = multiplyFFT(iStr, iStr);
        if (isLess(nStr, square)) break;

        if (modBig(nStr, i) == 0) return false;

        i++;
        iStr = to_string(i);
    }

    return true;
}

// -------- Main Program --------
int main() {
    string n;
    cout << "Enter a number: ";
    cin >> n;

    if (isPrime(n))
        cout << "\nThe number is PRIME." << endl;
    else
        cout << "\nThe number is NOT prime." << endl;

    return 0;
}
