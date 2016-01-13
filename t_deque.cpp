#define MY

#ifdef MY
#include "mydeque.h"
#include "myalgo.h"
#include "myconstruct.h"
#include <stdio.h>
using namespace my;
#else
#include <deque>
#include <stdio.h>
#include <algorithm>
using namespace std;

#endif  // MY

int main(int argc, const char *argv[])
{
    deque<int> ideque;
    ideque.push_front(2);
    ideque.push_front(1);
    ideque.push_front(0);
    ideque.push_front(7);
    ideque.insert(ideque.begin(), 4);
    ideque.insert(ideque.end(), 4);
    ideque.insert(ideque.begin()+4, 11);
    ideque.push_back(3);
    ideque.push_back(4);
    ideque.push_back(5);
    ideque.push_back(5);
    ideque.push_back(6);
    deque<int>::iterator it = ideque.erase(ideque.end() - 1);
    printf("size = %d, *it = %d\n", ideque.size(), *it);
//
//    for (int i = 0; i < ideque.size(); ++i)
//        printf("%d ", ideque[i]);
//    printf("\n");
//
//    for (int i = 0; i < 4; i++)
//        ideque.push_back(i);
//
//    printf("size = %d\n", ideque.size());
    for (deque<int>::iterator it = ideque.begin(); it != ideque.end(); ++it)
        printf("%d ", *it);
    printf("\n");

    ideque.clear();
    printf("after clear(): size = %d\n", ideque.size());
    ideque.push_front(2);
    ideque.push_front(1);
    ideque.push_front(0);
    ideque.push_front(7);
    ideque.insert(ideque.begin(), 4);
    ideque.insert(ideque.end(), 4);
    ideque.insert(ideque.begin()+4, 11);
    ideque.push_back(3);
    ideque.push_back(4);
    ideque.push_back(5);
    ideque.push_back(5);
    ideque.push_back(6);
    it = ideque.erase(ideque.begin() + 5);
    printf("size = %d, *it = %d\n", ideque.size(), *it);
//    printf("size = %d\n", ideque.size());
    for (deque<int>::iterator it = ideque.begin(); it != ideque.end(); ++it)
        printf("%d ", *it);
    printf("\n");

    deque<int> ideque4(ideque);
    printf("ideque4 size = %d\n", ideque4.size());
    for (deque<int>::iterator it = ideque4.begin(); it != ideque4.end(); ++it)
        printf("%d ", *it);
    printf("\n");
//
    deque<int> ideque2(8, 5);
    printf("size = %d\n", ideque2.size());
    for (deque<int>::iterator it = ideque2.begin(); it != ideque2.end(); ++it)
        printf("%d ", *it);
    printf("\n");

    deque<int> ideque3(ideque.begin(), ideque.begin() + 5);
    printf("ideque3 size = %d\n", ideque3.size());
    for (deque<int>::iterator it = ideque3.begin(); it != ideque3.end(); ++it)
        printf("%d ", *it);
    printf("\n");
    ideque3.insert(ideque3.begin() + 3, ideque.begin() + 6, ideque.end());
    printf("size = %d\n", ideque3.size());
    for (deque<int>::iterator it = ideque3.begin(); it != ideque3.end(); ++it)
        printf("%d ", *it);
    printf("\n");
//
//    for (int i = 0; i < 5; i++)
//        ideque.push_front(i*2 + 1);
//    printf("size = %d\n", ideque.size());
//    for (deque<int>::iterator it = ideque.begin(); it != ideque.end(); ++it)
//        printf("%d ", *it);
//    printf("\n");
//
//    ideque.clear();
//    printf("size = %d\n", ideque.size());
////    deque<int>::iterator it = ideque.begin() + 5;
////    printf("it(5) is %d\n", *it);
    return 0;
}
