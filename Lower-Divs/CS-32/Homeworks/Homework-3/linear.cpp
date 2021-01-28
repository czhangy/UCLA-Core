//
//  linear.cpp
//  hw3
//
//  Created by Charles Zhang on 2/7/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include <cassert>
#include <iostream>
using namespace std;

bool somePredicate(double x) { // returns true if negative
    return x < 0;
}

    // Return true if the somePredicate function returns false for at
    // least one of the array elements; return false otherwise.
  bool anyFalse(const double a[], int n)
  {
      if (n <= 0) return false; // if end of array reached without satisfying condition
      if (!somePredicate(a[n - 1])) return true; // last and the rest
      return anyFalse(a, n - 1);
  }

    // Return the number of elements in the array for which the
    // somePredicate function returns true.
  int countTrue(const double a[], int n)
  {
      if (n <= 0) return 0; // if end of array or somePredicate is false
      if (!somePredicate(a[n - 1])) return countTrue(a, n - 1);
      return countTrue(a, n - 1) + 1; // if was true, add 1
  }

    // Return the subscript of the first element in the array for which
    // the somePredicate function returns true.  If there is no such
    // element, return -1.
  int firstTrue(const double a[], int n)
  {
      if (n <= 0) return -1; // if end of array reached with no true elements
      if (somePredicate(a[0])) return 0;
      if (firstTrue(a + 1, n - 1) == -1) { // if the next value is a failure, this is a failure
          return -1;
      } else return firstTrue(a + 1, n - 1) + 1; // otherwise increment the subscript
  }

    // Return the subscript of the smallest element in the array (i.e.,
    // return the smallest subscript m such that a[m] <= a[k] for all
    // k from 0 to n-1).  If the function is told to examine no
    // elements, return -1.
  int positionOfSmallest(const double a[], int n)
  {
      if (n <= 0) return -1; // if n is 0 or negative/end of array
      if (positionOfSmallest(a, n - 1) == -1) { // if next recursive call is end of array
          return n - 1;
      }
      if (a[n - 1] < a[positionOfSmallest(a, n - 1)]) return n - 1; // compare last subscript with rest of array
      return positionOfSmallest(a, n - 1);
  }

    // If all n2 elements of a2 appear in the n1 element array a1, in
    // the same order (though not necessarily consecutively), then
    // return true; otherwise (i.e., if the array a1 does not contain
    // a2 as a not-necessarily-contiguous subsequence), return false.
    // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
    // For example, if a1 is the 7 element array
    //    10 50 40 20 50 40 30
    // then the function should return true if a2 is
    //    50 20 30
    // or
    //    50 40 40
    // and it should return false if a2 is
    //    50 30 20
    // or
    //    10 20 20
  bool contains(const double a1[], int n1, const double a2[], int n2)
  {
      if (n2 <= 0) return true;
      if (n1 <= 0) return false;
      if (a1[0] == a2[0]) return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
      return contains(a1 + 1, n1 - 1, a2, n2);
  }

int main() {

    double empty[10] = {};
    double baseCase1[1] = {-1};
    double baseCase2[1] = {2};
    double noNegatives[10] = {1, 3, 5, 6, 2, 8, 9, 10, 4, 7};
    double someNegatives[10] = {1, 3, 5, -6, 2, 8, 9, -7, 4, -10};
    double allNegatives[10] = {-1, -3, -5, -6, -2, -8, -9, -10, -4, -7};
    double hasDuplicates[5] = {1, 2, 3, 3, 1};

    double baseCase3[1] = {1};
    double containsArrays[10] = {1, 3, 5, 6, 2, 8, 9, 10, 6, 7};
    double isContainedIn[3] = {5, 9, 7};
    double isNotContainedIn[3] = {-3, -6, -9};
    double outOfOrder[3] = {3, 10, 2};
    double containedDuplicates[3] = {1, 6, 6};

    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;

    //////////////////////////
    // anyFalse
    //////////////////////////
    cerr << "anyFalse() tests:" << endl;
    assert(!anyFalse(empty, 0));
    cerr << "anyFalse returns correctly when passed an empty array" << endl;
    assert(!anyFalse(empty, -1));
    cerr << "anyFalse returns correctly when passed a negative n value" << endl;
    assert(!anyFalse(baseCase1, 1));
    assert(anyFalse(baseCase2, 1));
    cerr << "anyFalse returns correctly when passed one element arrays" << endl;
    assert(!anyFalse(allNegatives, 10));
    cerr << "anyFalse returns correctly when there are no positives" << endl;
    assert(anyFalse(noNegatives, 10));
    assert(anyFalse(someNegatives, 10));
    cerr << "anyFalse returns correctly when there are positives" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;

    //////////////////////////
    // countTrue
    //////////////////////////
    cerr << "countTrue() tests:" << endl;
    assert(countTrue(empty, 0) == 0);
    cerr << "countTrue returns correctly when passed an empty array" << endl;
    assert(countTrue(empty, -1) == 0);
    cerr << "countTrue returns correctly when passed a negative n value" << endl;
    assert(countTrue(baseCase1, 1) == 1);
    assert(countTrue(baseCase2, 1) == 0);
    cerr << "countTrue returns correctly when passed one element arrays" << endl;
    assert(countTrue(allNegatives, 10) == 10);
    assert(countTrue(someNegatives, 10) == 3);
    assert(countTrue(noNegatives, 10) == 0);
    cerr << "countTrue returns correctly on normal cases" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;

    //////////////////////////
    // firstTrue
    //////////////////////////
    cerr << "firstTrue() tests:" << endl;
    assert(firstTrue(empty, 0) == -1);
    cerr << "firstTrue returns correctly when passed an empty array" << endl;
    assert(firstTrue(empty, -1) == -1);
    cerr << "firstTrue returns correctly when passed a negative n value" << endl;
    assert(firstTrue(baseCase1, 1) == 0);
    assert(firstTrue(baseCase2, 1) == -1);
    cerr << "firstTrue returns correctly when passed one element arrays" << endl;
    assert(firstTrue(allNegatives, 10) == 0);
    assert(firstTrue(someNegatives, 10) == 3);
    assert(firstTrue(noNegatives, 10) == -1);
    cerr << "firstTrue returns correctly on normal cases" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;

    //////////////////////////
    // positionOfSmallest
    //////////////////////////
    cerr << "positionOfSmallest() tests:" << endl;
    assert(positionOfSmallest(empty, 0) == -1);
    cerr << "positionOfSmallest returns correctly when passed an empty array" << endl;
    assert(positionOfSmallest(empty, -1) == -1);
    cerr << "positionOfSmallest returns correctly when passed a negative n value" << endl;
    assert(positionOfSmallest(baseCase1, 1) == 0);
    cerr << "positionOfSmallest returns correctly when passed a one element array" << endl;
    assert(positionOfSmallest(allNegatives, 10) == 7);
    cerr << "positionOfSmallest returns correctly on normal cases" << endl;
    assert(positionOfSmallest(noNegatives, 10) == 0);
    assert(positionOfSmallest(someNegatives, 10) == 9);
    cerr << "positionOfSmallest returns correctly on the boundaries of the array" << endl;
    assert(positionOfSmallest(hasDuplicates, 5) == 0);
    cerr << "positionOfSmallest returns correctly when duplicates are present" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;

    //////////////////////////
    // contains
    //////////////////////////
    cerr << "contains() tests:" << endl;
    assert(contains(containsArrays, 10, empty, 0));
    assert(!contains(empty, 0, isContainedIn, 3));
    cerr << "contains returns correctly when passed an empty array" << endl;
    assert(contains(empty, 0, empty, 0));
    cerr << "contains returns correctly when passed two empty arrays" << endl;
    assert(contains(baseCase3, 1, baseCase3, 1));
    assert(!contains(baseCase3, 1, baseCase2, 1));
    cerr << "contains returns correctly when passed one element arrays" << endl;
    assert(contains(containsArrays, 10, isContainedIn, 3));
    assert(!contains(containsArrays, 10, isNotContainedIn, 3));
    cerr << "contains returns correctly on normal cases" << endl;
    assert(!contains(containsArrays, 10, outOfOrder, 3));
    cerr << "contains returns correctly when passed an array with elements out of order" << endl;
    assert(contains(containsArrays, 10, containedDuplicates, 3));
    cerr << "contains returns correctly when passed a test array with duplicate elements" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;

    cerr << endl;
    cerr << "***********************" << endl << "ALL LINEAR TESTS PASSED" << endl << "***********************" << endl;
}
