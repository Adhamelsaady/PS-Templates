/*
 * Chinese Remainder Theorem
 *
 * What this file does:
 * Combines several equations x = r (mod m) into one equivalent congruence. This class supports adding equations and solving them, including compatible non-coprime moduli.
 *
 * Typical problem to recognize:
 * CRT means Chinese Remainder Theorem: compatible congruences have one solution modulo the least common multiple.
 *
 * Complexity / constraints:
 * Typically O(number of equations * log modulus) apart from vector storage.
 *
 * Main variables:
 * r = residue; m = modulus; equations = all input congruences; x = combined residue; result modulus = lcm of the input moduli.
 *
 * Variable guide for names used in this implementation:
 * i: loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

class ChineseRemainderTheorem {
    typedef long long vlong;
    typedef pair<vlong,vlong> pll;

    /** CRT Equations stored as pairs of vector. See addEqation()*/
    vector<pll> equations;

public:
    // Function: clear().
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    void clear() {
        equations.clear();
    }
    // Function: ext_gcd(vlong a, vlong b, vlong& x, vlong& y).
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    vlong ext_gcd(vlong a, vlong b, vlong& x, vlong& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        vlong x1, y1;
        vlong d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }
    /** Add equation of the form x = r (mod m)*/
    // Function: addEquation(vlong r, vlong m).
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    void addEquation( vlong r, vlong m ) {
        equations.push_back({r, m});
    }
    // Function: solve().
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    pll solve() {
        if (equations.size() == 0) return {-1,-1}; /// No equations to solve

        vlong a1 = equations[0].first;
        vlong m1 = equations[0].second;
        a1 %= m1;
        /** Initially x = a_0 (mod m_0)*/

        /** Merge the solution with remaining equations */
        for ( int i = 1; i < equations.size(); i++ ) {
            vlong a2 = equations[i].first;
            vlong m2 = equations[i].second;

            vlong g = __gcd(m1, m2);
            if ( a1 % g != a2 % g ) return {-1,-1}; /// Conflict in equations

            /** Merge the two equations*/
            vlong p, q;
            ext_gcd(m1/g, m2/g, p, q);

            vlong mod = m1 / g * m2;
            vlong x = ( (__int128)a1 * (m2/g) % mod *q % mod + (__int128)a2 * (m1/g) % mod * p % mod ) % mod;

            /** Merged equation*/
            a1 = x;
            if ( a1 < 0 ) a1 += mod;
            m1 = mod;
        }
        return {a1, m1};
    }
};
