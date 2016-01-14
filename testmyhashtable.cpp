#include "myhashtable.h"
using namespace my;

#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    using my::pair;
    hashtable<int, pair<int,int> > iht(5);
//    hashtable<int, pair<int,int> > iht(20);

    cout << iht.size() << endl;
    cout << iht.bucket_count() << endl;
    cout << iht.max_bucket_count() << endl;

    iht.insert_unique(pair<int, int>(3, 59));
    iht.insert_unique(pair<int, int>(4, 63));
    iht.insert_unique(pair<int, int>(1, 108));
    iht.insert_unique(pair<int, int>(1, 2));
    iht.insert_equal(pair<int, int>(1, 2));
    iht.insert_unique(pair<int, int>(21, 2));
    iht.insert_equal(pair<int, int>(21, 53));
    cout << "bucket count() " << iht.bucket_count() << endl;
    iht.insert_unique(pair<int, int>(5, 55));
    cout << iht.size() << endl;

    hashtable<int, pair<int,int> >::iterator it = iht.begin();

    for (it; it != iht.end(); ++it)
        cout << (*it).second << ' ';
    cout << endl;

    cout << iht.find(1)->second << endl;
    cout << iht.count(1) << endl;
    pair<hashtable<int, pair<int,int> >::iterator, hashtable<int, pair<int,int> >::iterator> p = iht.equal_range(1);
    for (it = p.first; it != p.second; ++it)
        cout << (*it).second << ' ';
    cout << endl;

    iht.erase(1); // iht.erase(21);
    for (it = iht.begin(); it != iht.end(); ++it)
        cout << (*it).second << ' ';
    cout << endl;
    return 0;
}
