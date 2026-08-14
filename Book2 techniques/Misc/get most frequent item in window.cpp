// Dynamic frequency / mode structure for a sliding window
// Problem: Maintain frequencies of inserted elements and retrieve an element with maximum frequency. `getBest()` returns the smallest value among ties.
// Use: Create `WindowFreq wf`; call `wf.add(x)` when an element enters the window and `wf.remove(x)` when it leaves; call `wf.getBest()` for the current mode.
// Variables: Key variables: freq[x]=current frequency of x; fte[f]=multiset of values whose frequency equals f; old=previous frequency; it/mit=map/set iterators used to remove stale entries.
// Idea: Terminology: the mode is the most frequent value. `fte` is a frequency-to-elements index, so the largest frequency is immediately available.
// Complexity: Complexity: O(log n) per add/remove, and O(1) for getBest aside from map iterator operations.

struct WindowFreq {
    map<int, int> freq;
    map<int, multiset<int>> fte;

    void add(int x) {
        int old = freq[x];
        if (old > 0) {
            auto it = fte.find(old);
            if (it != fte.end()) {
                auto mit = it->second.find(x);
                if (mit != it->second.end()) it->second.erase(mit);
                if (it->second.empty()) fte.erase(it);
            }
        }
        freq[x]++;
        fte[freq[x]].insert(x);
    }

    void remove(int x) {
        int old = freq[x];
        if (old == 0) return;

        auto it = fte.find(old);
        if (it != fte.end()) {
            auto mit = it->second.find(x);
            if (mit != it->second.end()) it->second.erase(mit);
            if (it->second.empty()) fte.erase(it);
        }

        freq[x]--;
        if (freq[x] == 0) {
            freq.erase(x);
            return;
        }
        fte[freq[x]].insert(x);
    }

    int getBest() const {
        if (fte.empty()) return -1;
        auto it = fte.rbegin();
        return *it->second.begin();
    }

    int uniqueCount() const {
        return (int)freq.size();
    }
};