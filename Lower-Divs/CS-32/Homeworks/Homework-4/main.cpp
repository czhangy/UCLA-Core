//
//  main.cpp
//  hw4
//
//  Created by Charles Zhang on 2/29/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

//#include "Map.h"
//#include <iostream>
//#include <string>
//#include <cassert>
//
//using namespace std;
//
//void test()
//{
//    Map<int, double> mid;
//    Map<string, int> msi;
//    assert(msi.empty());
//    assert(msi.size() == 0);
//    assert(msi.insert("Hello", 10));
//    assert(mid.insert(10, 3.5));
//    assert(msi.update("Hello", 20));
//    assert(mid.update(10, 4.75));
//    assert(msi.insertOrUpdate("Goodbye", 30));
//    assert(msi.erase("Goodbye"));
//    assert(mid.contains(10));
//    int k;
//    assert(msi.get("Hello", k));
//    string s;
//    assert(msi.get(0, s, k));
//    Map<string, int> msi2(msi);
//    msi2.swap(msi);
//    msi2 = msi;
//    combine(msi,msi2,msi);
//    combine(mid,mid,mid);
//    reassign(msi,msi2);
//    reassign(mid,mid);
//}
//
//class Coord
//{
//  public:
//    Coord(int r, int c) : m_r(r), m_c(c) {}
//    Coord() : m_r(0), m_c(0) {}
//    double r() const { return m_r; }
//    double c() const { return m_c; }
//  private:
//    double m_r;
//    double m_c;
//};
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
