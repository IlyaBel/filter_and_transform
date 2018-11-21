#include "filter_and_transform.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    std::vector<int> v = {-2, 5, 0, 1, 2, 8, 6, -1, 3};
    FilterView filter(v, [](int x){ return x>2;});
    TransformView transform(filter, [](int x){ return x*x;});

    cout << "Filtered elements:" << endl;

    for (auto elt : filter)
        cout << elt << " ";
    cout << endl;

    cout << "Transformed elements:" << endl;

    for (  auto elt : transform)
        cout << elt << " ";
    cout << endl;

    return 0;
}
