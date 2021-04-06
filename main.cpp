#include <iostream>
#include "SkipList.h"

int main() {
    // Seed random number generator
    srand((unsigned)time(0));

    // create SkipList object with MAXLVL and P
    SkipList lst(3, 0.5);

    lst.insert(3);
    lst.insert(6);
    lst.insert(7);
    lst.insert(9);
    lst.insert(12);
    lst.insert(19);
    lst.insert(17);
    lst.insert(26);
    lst.insert(21);
    lst.insert(25);
    lst.print();

    cout<<endl<<endl;

    lst.find(9);
    lst.find(5);

    cout<<endl<<endl;

    lst.remove(19);
    lst.remove(9);
    lst.remove(5);
    lst.print();
}
