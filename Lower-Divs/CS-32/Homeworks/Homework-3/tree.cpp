//
//  tree.cpp
//  hw3
//
//  Created by Charles Zhang on 2/7/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include <cassert>
#include <iostream>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
// 10 50 40 20 50 40 30
// then for this value of a2     the function must return
// 10 20 40                      1
// 10 40 30                      2
// 20 10 40                      0
// 50 40 30                      3
// can't call comparison operators more than factorial(n1+1) / (factorial(n2)*factorial(n1+1-n2)) times
int countContains(const double a1[], int n1, const double a2[], int n2) {
    if (n2 <= 0){
        return 1;
    }
    if (n1 <= 0) {
        return 0;
    }
    if (a1[0] == a2[0]) {
        return countContains(a1 + 1, n1 - 1, a2, n2) + countContains(a1 + 1, n1 - 1, a2 + 1, n2 - 1); // if match found, return the sum of the calls of moving both arrays forward and only one array forward
    }
    return countContains(a1 + 1, n1 - 1, a2, n2); // if not a match, move a1 forwards
}

// Exchange two doubles
void exchange(double& x, double& y) {
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator, int& firstNotGreater, int& firstLess) {
    if (n < 0)
        n = 0;
   
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > separator
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //  == separator
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < separator
   
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess) {
       if (a[firstUnknown] < separator) {
           firstLess--;
           exchange(a[firstUnknown], a[firstLess]);
       } else {
           if (a[firstUnknown] > separator) {
               exchange(a[firstNotGreater], a[firstUnknown]);
               firstNotGreater++;
           }
           firstUnknown++;
       }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n) {
    if (n <= 1) return;
    int x, y;
    separate(a, n, a[0], x, y);
    order(a, x + 1);
    order(a + y, n - y);
}

int main() {
    
    double empty[0] = {};
    double oneElement[1] = {5};
    double containsArrays[7] = {10, 50, 40, 20, 50, 40, 30};
    double test1[3] = {10, 20, 40};
    double test2[3] = {10, 40, 30};
    double test3[3] = {20, 10, 40};
    double test4[3] = {50, 40, 30};
    double test5[6] = {8, 2, 4, 1, 6, 9};
    double test6[4] = {1, 3, 5, 7};
    double test7[5] = {6, 3, 9, 0, 2};
    //////////////////////////
    // countContains
    //////////////////////////
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "countContains() tests:" << endl;
    assert(countContains(containsArrays, 7, empty, -1) == 1);
    assert(countContains(empty, -1, test1, 3) == 0);
    cerr << "countContains returns correctly when passed a negative index" << endl;
    assert(countContains(containsArrays, 7, empty, 0) == 1);
    assert(countContains(empty, 0, test1, 3) == 0);
    cerr << "countContains returns correctly when passed an empty array" << endl;
    assert(countContains(empty, 0, empty, 0) == 1);
    cerr << "countContains returns correctly when passed two empty arrays" << endl;
    assert(countContains(containsArrays, 7, test1, 3) == 1);
    assert(countContains(containsArrays, 7, test2, 3) == 2);
    assert(countContains(containsArrays, 7, test3, 3) == 0);
    assert(countContains(containsArrays, 7, test4, 3) == 3);
    cerr << "countContains returns correctly on normal cases" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;
    
    //////////////////////////
    // order
    //////////////////////////
    cerr << "order() tests:" << endl;
    order(empty, 0);
    cerr << "order succeeds when passed an empty array" << endl;
    order(empty, -1);
    cerr << "order succeeds when passed a negative index" << endl;
    order(oneElement, 1);
    assert(oneElement[0] == 5);
    cerr << "order succeeds when passed a one element array" << endl;
    order(test5, 6);
    assert(test5[0] == 9 && test5[1] == 8 && test5[2] == 6 && test5[3] == 4 && test5[4] == 2 && test5[5] == 1);
    order(test6, 4);
    assert(test6[0] == 7 && test6[1] == 5 && test6[2] == 3 && test6[3] == 1);
    cerr << "order succeeds on normal cases" << endl;
    order(test7, 5);
    assert(test7[0] == 9 && test7[1] == 6 && test7[2] == 3 && test7[3] == 2 && test7[4] == 0);
    cerr << "order succeeds on arrays with an odd-numbered length" << endl;
    
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;
    
    cerr << endl;
    cerr << "***********************" << endl << "ALL TREE TESTS PASSED" << endl << "***********************" << endl;
}
