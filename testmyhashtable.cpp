#include "myhashtable.h"
using namespace my;

#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    using my::pair;
    hashtable<int, pair<int,int> > iht(50);

    cout << iht.size() << endl;
    cout << iht.bucket_count() << endl;
    cout << iht.max_bucket_count() << endl;

    iht.insert_unique(pair<int, int>(3, 59));
    iht.insert_unique(pair<int, int>(4, 63));
    iht.insert_unique(pair<int, int>(1, 108));
    iht.insert_unique(pair<int, int>(1, 2));
    iht.insert_equal(pair<int, int>(1, 53));
    iht.insert_unique(pair<int, int>(5, 55));
    cout << iht.size() << endl;

    hashtable<int, pair<int,int> >::iterator it = iht.begin();

    for (int i = 0; i < iht.size(); ++i, ++it)
        cout << (*it).second << ' ';
    cout << endl;

    for (int i = 0; i < iht.bucket_count(); ++i)
    {
        int n = iht.elems_in_bucket(i);
        if (n != 0)
            cout << "bucket[" << i << "] has " << n << " elmes." << endl;
    }

    for (int i = 0; i <= 47; i++)
        iht.insert_equal(pair<int, int>(i, i));
    cout << iht.size() << endl;
    cout << iht.bucket_count() << endl;
    for (int i = 0; i < iht.bucket_count(); ++i)
    {
        int n = iht.elems_in_bucket(i);
        if (n != 0)
            cout << "bucket[" << i << "] has " << n << " elmes." << endl;
    }

    for (int i = 0; i < iht.size(); ++i, ++it)
        cout << (*it).second << ' ';
    cout << endl;

    cout << iht.find(2)->second << endl;
    cout << iht.count(2) << endl;
    return 0;
}
//#include <iostream>
//#include <map>
//#include <utility>
//
//using namespace std;
//
//int main()
//{
//   map<int, int> Employees;
//
//   // 1) Assignment using array index notation
//   Employees[5234] = 1;
//   Employees[3374] = 2;
//   Employees[1923] = 3;
//   Employees[7582] = 4;
//   Employees[5328] = 5;
//
//   cout << "Employees[3374]=" << Employees[3374] << endl << endl;
//
//   cout << "Map size: " << Employees.size() << endl;
//
//   for( map<int,int>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii)
//   {
//       cout << (*ii).first << ": " << (*ii).second << endl;
//   }
//}
