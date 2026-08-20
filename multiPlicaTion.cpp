#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// Function to multiply two large numbers represented as strings
string multiplyStrings(const string& num1, const string& num2) {
    int n1 = num1.size(), n2 = num2.size();
    vector<int> result(n1 + n2, 0);

    // Multiply digits
    for (int i = n1 - 1; i >= 0; i--) {
        for (int j = n2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];

            result[i + j] += sum / 10;
            result[i + j + 1] = sum % 10;
        }
    }

    // Convert result to string
    string product;
    for (int num : result) {
        if (!(product.empty() && num == 0))
            product.push_back(num + '0');
    }

    return product.empty() ? "0" : product;
}

int main() {
    string num1, num2;

    // Take input from user
    cout << "Enter first large number: ";
    cin >> num1;
    cout << "Enter second large number: ";
    cin >> num2;

    // Validate input (optional)
    if (!all_of(num1.begin(), num1.end(), ::isdigit) || 
        !all_of(num2.begin(), num2.end(), ::isdigit)) {
        cout << "Invalid input. Only digits are allowed." << endl;
        return 1;
    }

    string result = multiplyStrings(num1, num2);

    cout << "\nProduct:\n" << result << endl;

    return 0;
}
