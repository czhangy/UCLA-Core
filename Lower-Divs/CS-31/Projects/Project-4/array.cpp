//
//  main.cpp
//  project4
//
//  Created by Charles Zhang on 11/2/19.
//  Copyright © 2019 Charles Zhang. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

int main() {
    string g[1] = { "1" }; // single string array
    string h[10] = { "hi", "my", "name", "is", "charles" }; // odd length array
    string j[2] = { "1", "1" }; // 2 string array, 1 run
    string k[4] = { "1", "2", "3", "4" }; // even length array
    string l[3] = { "1", "1", "2" }; // 2 runs
    string m[0] = { }; // empty array
    string n[1] = { "1" }; // identical to g
    string o[7] = { "1", "hi", "my", "name", "is", "charles", "7" }; // test for subsequence
    
    // lookup Tests
    assert(lookup(g, -1, "1") == -1); // fails if n is a negative number
    assert(lookup(g, 1, "1") == 0); // successful test
    assert(lookup(g, 1, "2") == -1); // fails if the value is not found
    assert(lookup(k, 4, "3") == 2); // successful test
    
    // positionOfMax Tests
    assert(positionOfMax(g, -1) == -1); // fails if n is a negative number
    assert(positionOfMax(g, 1) == 0); // successful test
    assert(positionOfMax(k, 4) == 3); // successful test
    assert(positionOfMax(h, 5) == 2); // successful test
    
    // countRuns Tests
    assert(countRuns(g, -1) == -1); // fails if n is a negative number
    assert(countRuns(g, 1) == 1); // successful test on 1 run
    assert(countRuns(h, 5) == 5); // successful test on 5 runs, 1 long
    assert(countRuns(j, 2) == 1); // successful test on 1 run, 2 long
    assert(countRuns(l, 3) == 2); // successful test on 2 runs, varying lengths
    assert(countRuns(m, 0) == 0); // successful test on 0 runs
    
    // differ Tests
    assert(differ(g, -1, n, 1) == -1); // fails if n1 is negative
    assert(differ(g, 1, n, -1) == -1); // fails if n2 is negative
    assert(differ(g, 1, n, 1) == 1); // success on equivalent strings
    assert(differ(j, 2, l, 3) == 2); // returns lower value when one string runs out
    assert(differ(j, 2, k, 4) == 1); // returns correct position on different strings
    assert(differ(h, 5, j, 2) == 0); // returns correct position on different strings
    
    // subsequence Tests
    assert(subsequence(l, -1, j, 2) == -1); // fails when n1 is negative
    assert(subsequence(l, 3, j, -1) == -1); // fails when n2 is negative
    assert(subsequence(l, 3, j, 2) == 0); // successful test
    assert(subsequence(h, 5, j, 2) == -1); // fails when no sequence found
    assert(subsequence(j, 2, n, 1) == 0); // returns first occurrence on successful test
    assert(subsequence(o, 7, h, 5) == 1); // successful test
    assert(subsequence(m, 0, m, 0) == 0); // empty array is a subsequence of itself
    assert(subsequence(o, 7, m, 0) == 0); // empty array is a subsequence of another array
    
    // lookupAny Tests
    assert(lookupAny(g, -1, h, 5) == -1); // fails if n1 is negative
    assert(lookupAny(g, 1, h, -1) == -1); // fails if n2 is negative
    assert(lookupAny(g, 1, h, 5) == -1); // fails if none of a2 is in a1
    assert(lookupAny(o, 7, h, 5) == 1); // successful test
    
    // appendToAll Tests
    assert(appendToAll(g, -1, "!") == -1); // fails if n is a negative number
    assert(appendToAll(g, 1, "!") == 1); // correct return value
    assert(g[0] == "1!"); // correct value at position 0
    // g = { "1!" }
    
    // rotateLeft Tests
    assert(rotateLeft(g, -1, 0) == -1); // fails if n is negative
    assert(rotateLeft(g, 1, -1) == -1); // fails if pos is negative
    assert(rotateLeft(g, 1, 0) == 0); // returns correct value
    assert(g[0] == "1!"); // string at position 0 is correct
    assert(rotateLeft(k, 4, 0) == 0); // returns correct value
    assert(k[0] == "2"); // string at position 0 is correct
    assert(k[3] == "1"); // string at position 3 is correct
    assert(rotateLeft(m, 0, 0) == -1); // returns correct value for empty array
    // k = { "2", "3", "4", "1" }
    
    // flip Tests
    assert(flip(m, -1) == -1); // fails if n is negative
    assert(flip(m, 0) == 0); // returns correct value for empty array
    flip(g, 1);
    assert(flip(k, 4) == 4); // returns correct value
    flip(l, 3);
    assert(g[0] == "1!"); // successful on array with length 1
    assert(k[2] == "3"); // successful on array with even length
    assert(l[0] == "2"); // successful on array with odd length
    
    // separate Tests
    assert(separate(m, -1, "d") == -1); // fails if n is negative
    assert(separate(m, 0, "d") == 0); // successful on empty array
    assert(separate(h, 5, "j") == 3); // successful return value
    assert(h[0] == "hi" && h[1] == "is" && h[2] == "charles"); // correct array values
    
    cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value) {
    if (n < 0) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        a[i] += value;
    }
    return n;
}

int lookup(const string a[], int n, string target) {
    if (n < 0) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n) {
    if (n <= 0) {
        return -1;
    }
    string greatest = a[0];
    int val = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > greatest) {
            val = i;
            greatest = a[i];
        }
    }
    return val;
}

int rotateLeft(string a[], int n, int pos) {
    if (n <= 0 || pos < 0) {
        return -1;
    }
    string placeholder = a[pos];
    for (int i = pos; i + 1 < n; i++) {
        a[i] = a[i + 1];
    }
    a[n - 1] = placeholder;
    return pos;
}

int countRuns(const string a[], int n) {
    if (n < 0) {
        return -1;
    }
    int numSequences = 0;
    int skip;
    for (int i = 0; i < n; i++) {
        skip = 0;
        for (int j = i; j < n && a[j] == a[j + 1]; j++) {
            skip++;
        }
        i += skip;
        numSequences++;
    }
    return numSequences;
}

int flip(string a[], int n) {
    if (n < 0) {
        return -1;
    }
    int i = 0;
    string placeholder;
    while (i < n - i - 1) { // -1 needed to account for diffence between # of elements
        placeholder = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = placeholder;
        i++;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    for (int i = 0; i < n1 && i < n2; i++) {
        if (a1[i] != a2[i]) {
            return i;
        }
    }
    if (n1 > n2) {
        return n2;
    } else {
        return n1;
    }
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    if (n2 == 0) {
        return 0;
    }
    bool sequence = false;
    int pos = -1;
    for (int i = 0; i < n1; i++) {
        if (a1[i] == a2[0]) {
            pos = i;
            sequence = true;
            for (int j = 0; j < n2 && i < n1; j++) {
                if (a1[i] != a2[j]) {
                    sequence = false;
                    pos = -1;
                    break;
                }
                i++;
            }
            if (sequence == true) {
                break;
            }
        }
    }
    return pos;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (a1[i] == a2[j]) {
                return i;
            }
        }
    }
    return -1;
}

int separate(string a[], int n, string separator) {
    if (n < 0) {
        return -1;
    }
    int endLimit = n;
    string placeholder;
    for (int i = 0; i < endLimit; i++) {
        if (a[i] > separator) {
            rotateLeft(a, n, i);
            endLimit--;
            i--;
        }
    }
    for (int j = 0; j < n; j++) {
        if (a[j] >= separator) {
            return j;
        }
    }
    return n;
}
