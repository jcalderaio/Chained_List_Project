#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"

bool same_string( const string&a, const string& b ) { // argument for contains()
    return (a == b);
}

int main(int argc, const char * argv[])
{
    
//    COP3530::SSLL<int> l;
//    l.push_back(0);
//    l.push_back(1);
//    l.push_back(3);
//    l.insert(4, 3);
//    l.print(cout);
//    cout << endl;
//    l.insert(2, 2);
//    l.print(cout);
//    cout << endl;
//    l.clear();
//    l.print(cout);
//    cout << endl << endl << endl;
//    
//    
//    COP3530::PSLL<string> p;
//    for(int i = 0; i<200; ++i ) {
//        p.push_back("asass");
//    }
//    for(int j = 0; j < 101; ++j) {
//        p.pop_back();
//    }
//    p.remove(55);
//    p.print(cout);
//    cout << endl;
//    cout << "List size: " << p.size() << endl;
//    cout << endl;
//    cout << endl;
//    
//    
//    
//    COP3530::SDAL<string> dl(500);
//    for(int i = 0; i<100; ++i ) {
//        dl.push_back("working");
//    }
//    for(int j = 0; j < 50; ++j) {
//        dl.pop_back();
//    }
//    dl.remove(5);
//    dl.print(cout);
//    cout << endl;
//    cout << "List size: " << dl.size() << endl;
//    cout << endl;
//    cout << endl;
//    
//    
//    
//    COP3530::PSLL<int> q;
//    q.push_back(1);
//    q.push_back(3);
//    q.push_back(6);
//    q.push_back(12);
//    q.push_front(0);
//    q.insert(2, 2);
//    q.insert(4, 4);
//    q.insert(5, 5);
//    q.insert(7, 7);
//    q.insert(8, 8);
//    q.insert(9, 9);
//    q.insert(10, 10);
//    q.insert(11,11);
//    
//    for(int i = 0; i < 2; ++i) {
//        q.insert(i, i);
//        q.push_back(i);
//        q.push_front(i);
//    }
//    cout << "Size: " << q.size() << endl;
//    
//    cout << endl;
//    
//    
//    q.print(cout);
    
    
    
    COP3530::CDAL<string> a;
    
    for(int i = 0; i < 100; ++i) {
        a.insert("a", i);
    }
    a.push_front("b");
    
    COP3530::CDAL<string> b(a);
    b.print(cout);
    a.print(cout);
    cout << endl;
    cout << a.contains("b", same_string);
    
}

