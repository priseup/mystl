#define MY

#ifdef MY
#include "myvector.h"
#include "myheap.h"
using namespace my;
#else
#include <vector>
#include <algorithm>
#endif  

#include <iostream>
using namespace std;

void printvec(const vector<int>& ivec)
{
    for (int i = 0; i < ivec.size(); ++i)
        cout << ivec[i] << ' ';
    cout << endl;
}

int main(int argc, const char *argv[])
{
    {
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    vector<int> ivec(ia, ia+9);
//    int ia[5] = {3, 3, 1, 2, 0};
//    vector<int> ivec(ia, ia+5);
    printvec(ivec);

    make_heap(ivec.begin(), ivec.end());
    printvec(ivec);

    ivec.push_back(7);
    push_heap(ivec.begin(), ivec.end());
    printvec(ivec);

    pop_heap(ivec.begin(), ivec.end());
    cout << ivec.back() << endl;
    ivec.pop_back();
    printvec(ivec);

    sort_heap(ivec.begin(), ivec.end());
    printvec(ivec);
    }

    {
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    make_heap(ia, ia+9);

    sort_heap(ia, ia+9);
    for (int i = 0; i < 9; ++i)
        cout << ia[i] << ' ';
    cout << endl;

    make_heap(ia, ia+9);
    pop_heap(ia, ia+9);
    cout << ia[8] << endl;
    }

    {
    int ia[6] = {4, 1, 7, 6, 2, 5};
    make_heap(ia, ia+6);
    for (int i = 0; i < 6; ++i)
        cout << ia[i] << ' ';
    cout << endl;
    }
    return 0;
}
