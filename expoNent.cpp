#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

// ----------- FFT ---------------------
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

// ----------- Multiplication using FFT ---------------------
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

    for (int i = 0; i + 1 < n; i++) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    while (result.size() > 1 && result.back() == 0)
        result.pop_back();

    string res;
    for (int i = result.size() - 1; i >= 0; i--)
        res += result[i] + '0';

    return res;
}

// ----------- Fast Exponentiation using FFT ---------------------
string powerFFT(string base, int exp) {
    string result = "1";

    while (exp > 0) {
        if (exp % 2 == 1)
            result = multiplyFFT(result, base);
        base = multiplyFFT(base, base);
        exp /= 2;
    }

    return result;
}

// ----------- Main ---------------------
int main() {
    string baseStr, expStr;
    cout << "Enter base (as string): ";
    cin >> baseStr;
    cout << "Enter exponent (as string): ";
    cin >> expStr;

    // Convert exponent string to int (if within safe bounds)
    int exponent = stoi(expStr); // WARNING: Works up to ~10^9

    string result = powerFFT(baseStr, exponent);

    cout << "\nResult (base^exponent) is:\n";
    cout << result << endl;

    return 0;
}
