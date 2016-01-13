#define MY

#ifdef MY
#include "mystack.h"
#include "myqueue.h"
using namespace my;

#else
#include <stack>
#include <queue>
#endif

#include <iostream>
using namespace std;

int main()
{
    stack<int> istack;
    queue<int> iqueue;

    istack.push(1); iqueue.push(1);
    istack.push(3); iqueue.push(3);
    istack.push(5); iqueue.push(5);
    istack.push(7); iqueue.push(7);
    istack.push(9); iqueue.push(9);

    cout << "size before pop(): " << istack.size() << '\t' << iqueue.size() << endl;

    cout << istack.top() << '\t' << iqueue.front() << endl;
    istack.pop(); iqueue.pop();
    cout << istack.top() << '\t' << iqueue.front() << endl;

    cout << istack.top() << '\t' << iqueue.front() << endl;
    istack.pop(); iqueue.pop();
    cout << istack.top() << '\t' << iqueue.front() << endl;

    cout << istack.top() << '\t' << iqueue.front() << endl;
    istack.pop(); iqueue.pop();
    cout << istack.top() << '\t' << iqueue.front() << endl;

    cout << istack.top() << '\t' << iqueue.front() << endl;
    istack.pop(); iqueue.pop();
    cout << istack.top() << '\t' << iqueue.front() << endl;

    cout << "size after pop(): " << istack.size() << '\t' << iqueue.size() << endl;
}

