#include <iostream>

#include "hashtable.h"

using namespace std;

int main()
{
    hashtable<int, string> hashtb;
    
    hashtb.put(1, "even");
    hashtb.put(2, "jessca");

    hashtb.put(10, "joh");
    hashtb.put(22, "jessca");

    string* p = hashtb.get(2);
    if (p != nullptr) {
        cout << "found, value:" << *p << endl;
    } else {
        cout << "not found" << endl;
    }
    
    system("pause");
    return 0;
}