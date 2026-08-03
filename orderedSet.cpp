// ordered set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update>
ordered_set;

int main() {
ordered_set os;

int idx = os.order_of_key(4);      
auto it = os.find_by_order(idx); 
}

\\*************************************************************************************************************//

// oms
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

template<typename T>
using ordered_multiset = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

int main() {
    ordered_multiset oms;
   int idx = 0;
   oms.insert({5, idx++});

  auto it = oms.lower_bound({5,0}); 
  if(it != oms.end() && it->first==5) oms.erase(it);

// put while to erase all versions of 5
