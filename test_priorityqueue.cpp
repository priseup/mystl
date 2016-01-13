#define MY

#ifdef MY
#include "myqueue.h"
using namespace my;
#else
#include <queue>
#include <algorithm>
#endif

#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    my::greater<int> g;
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    make_heap(ia, ia+9, g);
    for (int i = 0; i < 9; ++i)
        cout << ia[i] << ' ';
    cout << endl;
    sort_heap(ia, ia+9, g);
    for (int i = 0; i < 9; ++i)
        cout << ia[i] << ' ';
    cout << endl;
    priority_queue<int, vector<int>, my::greater<int> > ipq(ia, ia+9, g);
    cout << "size=" << ipq.size() << endl;

    for (int i = 0; i < ipq.size(); ++i)
        cout << ipq.top() << ' ';
    cout << endl;

    while (!ipq.empty())
    {
        cout << ipq.top() << ' ';
        ipq.pop();
    }
    cout << endl;
    return 0;
}
