/**
 * Big-integer utilities using decimal strings.
 *
 * Includes decimal addition, subtraction, multiplication, division, comparison
 * and decimal -> base conversion. Most operations avoid fixed-width integer
 * overflow by storing the number as a string.
 *
 * NOTE: convertToBase currently supports digit values only through 9 because
 * digits="0123456789". For bases > 10, extend the digit alphabet.
 * NOTE: toDecimal is not fully arbitrary-precision internally because it uses
 * long long for powers of the base; use a string-based multiplication/addition
 * approach if very large bases/powers are required.
 */
#include <bits/stdc++.h>

using namespace std;
// Add two non-negative decimal integers represented as strings.
#define int long long

string add(string a, string b) {
    int len = max(a.size(), b.size());

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    while (a.size() < len) a += '0';
    while (b.size() < len) b += '0';

    string ans;
    int carry = 0;
    for (int i = 0; i < len; ++i) {
        int current = carry + (a[i] - '0') + (b[i] - '0');
        ans.push_back(char(current % 10 + '0'));
        carry = current / 10;
    }

    if (carry > 0) ans += char(carry + '0');
    reverse(ans.begin(), ans.end());
    return ans;
// Long-divide a decimal string by `base`; return quotient and store remainder.
}

string divideWithBase(const string &num, int base, int &remain) {
    string quotient;
    quotient.reserve(num.size());
    int carry = 0;
    for (char c: num) {
        int d = c - '0';
        int current = carry * 10 + d;
        int q = current / base;
        carry = current % base;
        if (not quotient.empty() or q != 0) {
            quotient.push_back(char('0' + q));
        }
    }
    remain = carry;
    return quotient.empty() ? "0" : quotient;
// Repeatedly divide by base; remainders, reversed, form the target representation.
}

string convertToBase(const string &decimal, int base) {
    if (decimal == "0") return "0";
    static auto digits = "0123456789";
    string n = decimal, result;
    while (n != "0") {
        int remain;
        n = divideWithBase(n, base, remain);
        result.push_back(digits[remain]);
    }
    reverse(result.begin(), result.end());
    return result;
// Convert a base representation to decimal. This implementation uses long long
// for powers, so it is not fully arbitrary-precision for very large inputs.
}

string toDecimal(string &x, int base) {
    int f = 1;
    string ans = "0";
    reverse(x.begin(), x.end());
    for (int i = 0; i < x.size(); ++i, f *= base) {
        int t = 1LL * (x[i] - '0') * f;
        string y = to_string(t);
        ans = add(ans, y);
    }
    return ans;
// Normalize a non-negative decimal string by removing leading zeroes.
}

string removeLeadingZeros(const string &num) {
    int i = 0, n = num.length();
    while (i < n && num[i] == '0') i++;
    if (i == n) return "0";
    return num.substr(i);
// Compare two non-negative decimal strings: 1 if a>b, 0 if equal, -1 if a<b.
}

int compare(const string &a, const string &b) {
    string aClean = removeLeadingZeros(a);
    string bClean = removeLeadingZeros(b);
    if (aClean.length() > bClean.length()) return 1;
    if (aClean.length() < bClean.length()) return -1;
    for (int i = 0; i < aClean.length(); ++i) {
        if (aClean[i] > bClean[i]) return 1;
        if (aClean[i] < bClean[i]) return -1;
    }
    return 0;
// Subtract decimal strings and preserve a leading minus sign when the result is negative.
}

string subtract(string a, string b) {
    a = removeLeadingZeros(a);
    b = removeLeadingZeros(b);
    bool minus = compare(a, b) < 0;
    if (minus) swap(a, b);

    int i = a.size() - 1;
    int j = b.size() - 1;
    int borrow = 0;
    string res;

    while (i >= 0 or j >= 0) {
        int digit1 = i >= 0 ? a[i--] - '0' : 0;
        int digit2 = j >= 0 ? b[j--] - '0' : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) diff += 10, borrow = 1;
        else borrow = 0;
        res.push_back(diff + '0');
    }

    while (!res.empty() && res.back() == '0')
        res.pop_back();

    reverse(res.begin(), res.end());
    res = removeLeadingZeros(res);
    if (minus) res = '-' + res;
    return res.empty() ? "0" : res;
}

// Grade-school O(n*m) multiplication of two decimal strings.
// works on decimals
string multiply(string &a, string &b) {
    if (a == "0" || b == "0") return "0";

    vector<int> c(a.size() + b.size());
    for (int i = a.size() - 1; i >= 0; --i) {
        for (int j = b.size() - 1; j >= 0; j--) {
            c[i + j + 1] += (a[i] - '0') * (b[j] - '0');
            c[i + j] += c[i + j + 1] / 10;
            c[i + j + 1] %= 10;
        }
    }

    int i = 0;
    string ans = "";
    while (c[i] == 0) i++;
    while (i < c.size()) ans += to_string(c[i++]);
    return ans;
}

// Multiply a decimal string by one decimal digit.
string multiply(string num, char digit) {
    if (digit == '0') return "0";
    reverse(num.begin(), num.end());
    int carry = 0;
    string ans;
    for (char c: num) {
        int product = (c - '0') * (digit - '0') + carry;
        carry = product / 10;
        ans.push_back((product % 10) + '0');
    }
    if (carry > 0) ans.push_back(carry + '0');
    reverse(ans.begin(), ans.end());
    ans = removeLeadingZeros(ans);
    return ans.empty() ? "0" : ans;
// Long division of two decimal strings; returns {quotient, remainder}.
}

pair<string, string> divide(string dividend, string divisor) {
    // divisor == "0"

    dividend = removeLeadingZeros(dividend);
    divisor = removeLeadingZeros(divisor);

    if (dividend == "0") return {"0", "0"};

    int cmp = compare(dividend, divisor);
    if (cmp < 0) return {"0", dividend};
    if (cmp == 0) return {"1", "0"};

    string quotient;
    string seg;
    int pos = 0;
    int len = dividend.size();

    while (pos < len) {
        seg += dividend[pos];
        ++pos;
        seg = removeLeadingZeros(seg);

        while (pos < len and compare(seg, divisor) < 0) {
            seg += dividend[pos];
            pos++;
            quotient.push_back('0');
            seg = removeLeadingZeros(seg);
        }

        if (compare(seg, divisor) < 0) {
            quotient.push_back('0');
            continue;
        }

        char q_digit = '0';
        for (char trial = '9'; trial >= '1'; --trial) {
            string product = multiply(divisor, trial);
            if (compare(product, seg) <= 0) {
                q_digit = trial;
                break;
            }
        }

        quotient.push_back(q_digit);
        string product = multiply(divisor, q_digit);
        seg = subtract(seg, product);
        seg = removeLeadingZeros(seg);
    }

    quotient = removeLeadingZeros(quotient);
    if (quotient.empty()) quotient = "0";

    return {quotient, seg.empty() or seg == "0" ? "0" : seg};
}