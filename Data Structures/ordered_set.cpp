#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<
    T,
    null_type,
    less_equal<T>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

void Erase(ordered_set<int> &s, int val) {
    int place = s.order_of_key(val);
    auto it = s.find_by_order(place);
    s.erase(it);
}