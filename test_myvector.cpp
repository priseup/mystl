#include <iostream>
#include <stdlib.h>

//#define STD

#ifdef STD
#include <vector>
using namespace std;
#else
#include "myvector.h"
using namespace my;
#endif  // STD

//int a()
//{return 3;}

int main()
{
    int a = 3;

    const int &b = a;
//    int c = a(); 变量与函数的名字是不可重复的。。编译器无法对此进行区分
    vector<int> aa(1, 2);
    aa.resize(3);
    aa.push_back();
    std::cout << aa.size() << '\t' << aa.capacity() << std::endl;
    for (int i = 0; i < aa.size(); i++)
        std::cout << aa[i] << std::endl;
//    std::cout << std::endl;

    aa.insert(aa.end(), 3);
    aa.insert(aa.end(), 5);
    aa.insert(aa.end(), 7);
    std::cout << aa.size() << '\t' << aa.capacity() << std::endl;
    for (int i = 0; i < aa.size(); i++)
        std::cout << aa[i] << std::endl;
    aa.erase(aa.begin() + 1);
    aa.erase(aa.end()-1);
    std::cout << aa.size() << '\t' << aa.capacity() << std::endl;
    for (int i = 0; i < aa.size(); i++)
        std::cout << aa[i] << std::endl;
    std::cout << std::endl;


    vector<int>::const_reverse_iterator constrs;
    vector<int>::reverse_iterator rs = aa.rbegin();
    constrs = rs;
    std::cout << "rbegin" << std::endl;
    for (vector<int>::const_reverse_iterator rs = aa.rbegin();
    rs != aa.rend(); ++rs)
        std::cout << *rs << std::endl;
    std::cout << "rend" << std::endl;
    std::cout << *aa.rend() << std::endl;
    std::cout << *(aa.rend()-2) << std::endl;

//aa.assign();
    std::cout << "Hello World!" << std::endl;
    vector<int> iv2;
    iv2 = aa;
    std::cout << iv2.size() << '\t' << iv2.capacity() << std::endl;
    for (vector<int>::const_iterator it = iv2.begin();
    it != iv2.end(); ++it)
        std::cout << *it << std::endl;

    return 0;
}

//template <class T>
//class shit
//{
//public:
//    shit() : _t(0) {}
//    shit(T t) : _t(t) {}
//    shit(const shit& t) : _t(t._t) {}
//
//    template <class C>
//    shit(const shit<C>& t) : _t(static_cast<T>(t.gett())) {}    // _t(t._t) error
//
//    T gett() const{return _t;}
//private:
//    T _t;
//};
//
//int main()
//{
////    shit<float> fshit = 3;
////    shit<int> ishit = fshit;
//
//
//    list<int> tt;
//    tt.push_back(5);
//    tt.push_back(1);
//    tt.push_back(1);
//    tt.push_back(3);
//    tt.push_back(4);
//    tt.push_back(4);
//    tt.push_back(2);
//    tt.push_back(4);
// //   tt.push_front(6);
////    tt.insert(++tt.begin(), 7);
//
////1 2 3 4
//    list<int>::iterator it = tt.end();
//    int a = *it;
//    ++it;
//    a = *it;
//    it = tt.insert(it, 8);
//    a = *it;
//    ++it;
//    a = *it;
//
//    it = tt.erase(it);
//    a = *it;
////    static_cast<>it._M_node->
//
//
//    printf("size: %d\n", tt.size());
//    list<int> tcopy;
//  tcopy.push_front(21);
//  tcopy.push_front(22);
//  tcopy.push_back(10);
//  tt.merge(tcopy);
//  int size = tcopy.size();
////  tt.sort();
////  for (it = tcopy.begin(); it != tcopy.end(); ++it)
////      printf("%d\n", *it);
////   tt.splice(tt.begin(), tcopy);
////    tt.assign(2, 11);
//   printf("size tt: %d\tsizse tcopy:%d\n", tt.size(), tcopy.size());
////    tcopy.assign(it, tt.end());
////    ++it
////    printf("%d\n", *((--it).operator ->()));
////    printf("%d\n", tt.front());
////    printf("%d\n", tt.size());
////    tt.
//   tt.push_back(3);
//   tt.push_back(9);
//   tt.unique();
//   tt.reverse();
////   tt.swap()
//
//    for (it = tt.begin(); it != tt.end(); ++it)
//        printf("%d\n", *it);
//
//
//
////    int i = 0;
////    while (i < 9)
////    {
////        printf("%d\n", *it);
////        ++it; ++i;
////    }
//}
