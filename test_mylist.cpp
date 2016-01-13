
#include <stdio.h>
#include <string>
#include <string.h>

//#define STD

#ifdef STD
#include <list>
#include <vector>
using namespace std;
#else
#include "mylist.h"
#include "myvector.h"
using namespace my;
#endif  // STD

std::string getstring()
{
    return std::string("abc");
}

int main(int argc, const char *argv[])
{
    list<int> ilist(5, 9);
    printf("ilist.size() is %d\n", ilist.size());
    for (list<int>::iterator it = ilist.begin();
            it != ilist.end(); ++it)
        printf("%d\n", *it);
    ilist.push_back(5);
    ilist.push_back(1);
    printf("ilist.size() is %d\n", ilist.size());
    ilist.insert(ilist.begin(), 3);
    ilist.insert(ilist.begin(), 2);
    printf("ilist.size() is %d\n", ilist.size());
    for (list<int>::iterator it = ilist.begin();
            it != ilist.end(); ++it)
        printf("%d\n", *it);
    list<int>::iterator it = ilist.insert(ilist.begin(), 6);
    printf("ilist.size() is %d\n", ilist.size());
    printf("begin() is %d, after insert() is %d\n", *ilist.begin(), *it);
    it = ilist.erase(ilist.begin());
    printf("ilist.size() is %d\n", ilist.size());
    printf("begin() is %d, after erase() is %d\n", *ilist.begin(), *it);


    list<int> ilist2;
    ilist2.push_back(7);
    ilist2.push_back(8);
    ilist2.push_back(9);
    ilist2.push_back(9);
    ilist2.push_back(5);

    ilist2.unique();
    ilist2.reverse();
//    ilist.swap(ilist2);
//    printf("after splice ilist2 at begin()\n");
//    ilist.splice(ilist.begin(), ilist2);
//    printf("after merge ilist2 at \n");
//    ilist.merge(ilist2);
//    printf("after merge ilist2.size() is %d\n", ilist2.size());
    for (list<int>::iterator it = ilist.begin();
            it != ilist.end(); ++it)
        printf("%d\n", *it);

//    ilist2.insert(ilist2.begin(), ilist.begin(), ilist.end());
//    ilist2.insert(ilist2.begin(), 7);
//    ilist2.insert(ilist2.begin(), 8);
//    ilist2.insert(ilist2.begin(), 9);
    printf("insert ilist at begin() on ilist2\n");
    printf("ilist2.size() is %d\n", ilist2.size());
    for (list<int>::iterator it = ilist2.begin();
            it != ilist2.end(); ++it)
        printf("%d\n", *it);
    ilist2.clear();
    printf("ilist2 size after clear() is %d\n", ilist2.size());
    return 0;
}
