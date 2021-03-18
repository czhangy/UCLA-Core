//
//  solutions.cpp
//  test
//
//  Created by Charles Zhang on 10/9/19.
//  Copyright © 2019 Charles Zhang. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <cctype>
#include <string>
using namespace std;

// Week 2 Problem 1
//
//int main() {
//    int speed;
//    int limitIncrease = 0;
//    cout << "What was your speed? ";
//    cin >> speed;
//    cin.ignore(123456, '\n');
//    cout << "Is it your birthday? ";
//    string ans;
//    getline(cin, ans);
//    if (ans == "yes") {
//        limitIncrease = 5;
//    }
//    if (speed <= 60 + limitIncrease) {
//        cout << "no ticket" << endl;
//    } else if (speed <= 80 + limitIncrease) {
//        cout << "small ticket" << endl;
//    } else {
//        cout << "big ticket"; << endl;
//    }
//}

// Week 2 Problem 2
//
//int main() { // I should've used a switch statement
//    char numeral;
//    cout << "Enter Roman numeral letter: ";
//    cin >> numeral;
//    numeral = toupper(numeral);
//    if(numeral == 'I') {
//        cout << "Its value is 1" << endl;
//    } else if (numeral == 'V') {
//        cout << "Its value is 5" << endl;
//    } else if (numeral == 'X') {
//        cout << "Its value is 10" << endl;
//    } else if (numeral == 'L') {
//        cout << "Its value is 50" << endl;
//    } else if (numeral == 'C') {
//        cout << "Its value is 100" << endl;
//    } else if (numeral == 'D') {
//        cout << "Its value is 500" << endl;
//    } else if (numeral == 'M') {
//        cout << "Its value is 1000" << endl;
//    } else {
//        cout << "Invalid input." << endl;
//}

// Week 2 Problem 3
//
//int main() {
//    int x1;
//    int x2;
//    string command;
//    cout << "Enter the first number: ";
//    cin >> x1;
//    cout << "Enter the second number: ";
//    cin >> x2;
//    cin.ignore(132324, '\n');
//    cout << "Enter the command: ";
//    getline(cin, command);
//    if (command == "add") {
//        cout << x1 + x2 << endl;
//    } else if (command == "subtract") {
//        cout << x1 - x2 << endl;
//    } else if (command == "multiply") {
//        cout << x1 * x2 << endl;
//    } else if (command == "divide") {
//        cout << x1 / x2 << endl;
//    } else {
//        cout << "u fukd up lol" << endl;
//    }
//}

// Week 2 Problem 4
//
//int main() {
//    double x1;
//    double x2;
//    double x3;
//    cout << "Number: ";
//    cin >> x1;
//    cout << "Number: ";
//    cin >> x2;
//    cout << "Number: ";
//    cin >> x3;
//    cout << (x1 + x2 + x3) / 3 << endl;
//}

// Week 2 Problem 5
//
//int main() {
//    double x1;
//    double x2;
//    double x3;
//    cout << "Number: ";
//    cin >> x1;
//    cout << "Number: ";
//    cin >> x2;
//    cout << "Number: ";
//    cin >> x3;
//    // im lazy i dont wanna write the median code
//}

// Week 2 Problem 6
//
//int main() {
//    int year;
//    cout << "Year: ";
//    cin >> year;
//    if (year % 4 == 0) {
//        if (year % 100 == 0 && year % 400 != 0) {
//            cout << year << " is not a leap year" << endl;
//        }
//        cout << year << " is a leap year" << endl;
//    } else {
//        cout << year << " is not a leap year" << endl;
//    }
//}

// Week 3 Problem 1
//
//int main() {
//    int num;
//    int sum = 0;
//    cout << "Enter a number: ";
//    cin >> num;
//    while (num != 0) {
//        sum += num % 10;
//        num /= 10;
//    }
//    cout << sum << endl;
//}

// Week 3 Problem 2
//
//int main() {
//    int num;
//    double sum = 0.0;
//    int x;
//    cout << "How many numbers do you want to average? ";
//    cin >> num;
//    for (int i = 0; i < num; i++) {
//        cout << "Number: ";
//        cin >> x;
//        sum += x;
//    }
//    cout << "The average is " << round(sum / num) << endl;
//}

// Week 3 Problem 3
//
//int main() {
//    int n;
//    cout << "Enter a number: ";
//    cin >> n;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if (j > i) {
//                cout << ".";
//            } else {
//                cout << i + j;
//            }
//        }
//        cout << endl;
//    }
//}

// Week 3 Problem 4
//
//int main() {
//    int test;
//    int total = 0;
//    cout << "Enter a number: ";
//    cin >> test;
//    for (int i = 1; i < test; i++) {
//        if (test % i == 0) {
//            total += i;
//        }
//    }
//    if (total == test) {
//        cout << "awioufbenilwubf" << endl;
//    } else {
//        cout << "bitch" << endl;
//    }
//}

// Week 3 Problem 5
//
//int main() {
//    int num;
//    cout << "Enter a number: ";
//    cin >> num;
//    for (int i = 1; i < num; i++) {
//        if (num % i == 0) {
//            cout << i << ",";
//        }
//    }
//    cout << num << endl;
//}

// Week 3 Problem 6
//
//int main() {
//    int exp = 1;
//    int n;
//    cout << "Enter a number: ";
//    cin >> n;
//    if (n < 0) {
//        cout << "fuck you" << endl;
//        return 0;
//    }
//    while (pow(2, exp + 1) < n) {
//        exp++;
//    }
//    if (pow(2, exp + 1) > n) {
//        cout << exp << endl;
//    } else {
//        cout << "fuck" << endl;
//    }
//}

// Week 3 Problem 7
//
//int main() {
//    int n;
//    int first = 1;
//    int second = 1;
//    int x;
//    int counter = 2;
//    cout << "Enter a number: ";
//    cin >> n;
//    if (n <= 0) {
//        cout << "You fucked it up" << endl;
//    } else if (n == 1) {
//        cout << "0" << endl;
//    } else if (n == 2) {
//        cout << "1" << endl;
//    } else {
//        do {
//            x = second;
//            second = first + second;
//            first = x;
//            counter++;
//        } while (counter != n);
//        cout << second << endl;
//    }
//}

// Week 4 Problem 1
//
//void changeString(string str1, string str2);
//
//int main() {
//    changeString("Helatelmylcookie", "l");
//    changeString("ShouldeHIstartemylab?", "He");
//}
//
//void changeString(string str1, string str2) {
//    for (int i = 0; i < str1.size(); i++) {
//        for (int j = 0; j < str2.size(); j++) {
//            if (str1[i] == str2[j]) {
//                str1[i] = ' ';
//            }
//        }
//    }
//    cout << str1 << endl;
//}

// Week 4 Problem 2
//
//bool isPalindrome(string str);
//bool isPalindrome2(string str);
//
//int main() {
//    cout << isPalindrome("abcba");
//    cout << isPalindrome("skt_will_win");
//    cout << isPalindrome("z");
//    cout << isPalindrome("");
//    cout << isPalindrome2("ggnore ero n g g");
//    cout << isPalindrome2("abcba");
//    cout << isPalindrome2("skt_will_win");
//    cout << isPalindrome2("z");
//    cout << isPalindrome2("");
//}
//
//bool isPalindrome(string str) {
//    for (int i = 0; i < str.size(); i++) {
//        if (str[i] != str[str.size() - i - 1]) {
//            return false;
//        }
//    }
//    return true;
//}
//
//bool isPalindrome2(string str) {
//    int i = 0;
//    int j = str.size() - 1;
//    while (i < j) {
//        if (str[i] == ' ') {
//            i++;
//        } else if (str[j] == ' ') {
//            j--;
//        } else if (str[i] != str[j]) {
//            return false;
//        } else {
//            i++;
//            j--;
//        }
//    }
//    return true;
//}

// Week 4 Problem 3
//
//char findRun(string str);
//char findRun2(string str);
//
//int main() {
//    cout << findRun("abbccccdda") << endl;
//    cout << findRun("aaaabcbbbbcbcbcbcbcb") << endl;
//    cout << findRun("aAaabcbbbbcb") << endl;
//    cout << findRun2("aAaabcbbbbcb") << endl;
//}
//
//char findRun(string str) {
//    int record = 0;
//    char holder;
//    char test;
//    int tracker = 0;
//    for (int i = 0; i < str.size(); i++) {
//        test = str[i];
//        tracker = 0;
//        for (int j = i + 1; str[j] == test && j < str.size(); j++) {
//            tracker++;
//        }
//        if (tracker > record) {
//            record = tracker;
//            holder = test;
//        }
//    }
//    return holder;
//}
//
//char findRun2(string str) {
//    int record = 0;
//    char holder;
//    char test;
//    int tracker = 0;
//    for (int i = 0; i < str.size(); i++) {
//        test = tolower(str[i]);
//        tracker = 0;
//        for (int j = i + 1; tolower(str[j]) == test && j < str.size(); j++) {
//            tracker++;
//        }
//        if (tracker > record) {
//            record = tracker;
//            holder = test;
//        }
//    }
//    return holder;
//}

// Week 4 Problem 4
//
//int integerDivide(int num1, int num2);
//
//int main() {
//    cout << integerDivide(6, 2) << endl;
//    cout << integerDivide(100, 10) << endl;
//    cout << integerDivide(1, 1) << endl;
//    cout << integerDivide(3, 2) << endl;
//}
//
//int integerDivide(int num1, int num2) {
//    int count = 1;
//    while (num2 * count < num1) {
//        count++;
//    }
//    if (num2 * count != num1) {
//        count--;
//    }
//    return count;
//}

// Week 4 Problem 5
//
//int findLastLength(string str);
//
//int main() {
//    cout << findLastLength("Misfits should have won against SKT") << endl;
//    cout << findLastLength(" ") << endl;
//}
//
//int findLastLength(string str) {
//    int count = 0;
//    for (int i = str.size() - 1; i >= 0 && str[i] == ' '; i--) {
//        if (str[i] == ' ') {
//            str.erase(str.size() - 1, 1);
//        }
//    }
//    for (int i = 0; i < str.size(); i++) {
//        if (str[i] == ' ') {
//            count = 0;
//        } else {
//            count++;
//        }
//    }
//    return count;
//}

// Week 4 Problem 6
//
//bool intPalindrome(int int1, int int2);
//
//int main() {
//    cout << intPalindrome(62, 26) << endl;
//    cout << intPalindrome(154, 451) << endl;
//    cout << intPalindrome(10, 101) << endl;
//    cout << intPalindrome(25, 56) << endl;
//}
//
//bool intPalindrome(int int1, int int2) {
//    string str1 = to_string(int1);
//    string str2 = to_string(int2);
//    if (str1.size() != str2.size()) {
//        return false;
//    }
//    for (int i = 0; i < str1.size(); i++) {
//        if (str1[i] != str2[str2.size() - 1 - i]) {
//            return false;
//        }
//    }
//    return true;
//}

// Week 4 Problem 7
//
//string pigLatin(string str);
//string convert(string str);
//bool isVowel(char ch);
//
//int main() {
//    cout << pigLatin("David Smallberg is my favorite professor.") << endl;
//}
//
//string pigLatin(string str) {
//    string placeholder = "";
//    string output = "";
//    int i = 0;
//    while (i < str.size() - 1) {
//        placeholder = "";
//        while (str[i] != ' ' && i < str.size() - 1) {
//            placeholder += str[i];
//            i++;
//        }
//        output += convert(placeholder) + " ";
//        i++;
//    }
//    output.erase(output.size() - 1, 1);
//    output += '.';
//    return output;
//}
//
//string convert(string str) {
//    string conversion = "";
//    if (isVowel(str[0])) {
//        conversion = str + "ay";
//    } else {
//        char ch = tolower(str[0]);
//        conversion = str.substr(1, str.size() - 1) + ch + "ay";
//    }
//    if (isupper(str[0])) {
//        conversion[0] = toupper(conversion[0]);
//    }
//    return conversion;
//}
//
//bool isVowel(char ch) {
//    return tolower(ch) == 'a' || tolower(ch) == 'e' || tolower(ch) == 'i' || tolower(ch) == 'o' || tolower(ch) == 'u';
//}

// Week 4 Problem 8
//
//string reverseLowercaseVowels(string str);
//bool isVowel(char ch);
//
//int main() {
//    cout << reverseLowercaseVowels("haha reax only") << endl;
//
//}
//
//bool isVowel(char ch) {
//    if (tolower(ch) == 'a' || tolower(ch) == 'i' || tolower(ch) == 'e' || tolower(ch) == 'u' || tolower(ch) == 'o') {
//        return true;
//    } else {
//        return false;
//    }
//}
//
//string reverseLowercaseVowels(string str) {
//    char ch1;
//    char ch2;
//    int pos1 = -1;
//    int pos2 = str.size();
//    bool change1 = false;
//    bool change2 = false;
//    while (pos1 < pos2) {
//        change1 = false;
//        change2 = false;
//        for (int i = pos1 + 1; i < str.size(); i++) {
//            if (islower(str[i]) && isVowel(str[i])) {
//                ch1 = str[i];
//                pos1 = i;
//                change1 = true;
//                break;
//            }
//        }
//        for (int j = pos2 - 1; j >= 0; j--) {
//            if (islower(str[j]) && isVowel(str[j])) {
//                ch2 = str[j];
//                pos2 = j;
//                change2 = true;
//                break;
//            }
//        }
//        if (change1 && change2) {
//            char placeholder = toupper(str[pos1]);
//            str[pos1] = toupper(str[pos2]);
//            str[pos2] = placeholder;
//        } else {
//            break;
//        }
//    }
//    return str;
//}

// Random Factoring Problem
//#include <iostream>
//using namespace std;
//
//void factor(long long int x, long long int y);
//
//int main() {
//    int n;
//    int m;
//    cout << "1: ";
//    cin >> n;
//    cout << "2: ";
//    cin >> m;
//    factor(n, m);
//}
//
//void factor(long long int x, long long int y) {
//    bool prime = true;
//    for (; x <= y; x++) {
//        prime = true;
//        cout << x << ": 1, ";
//        for (long long int i = 2; i <= x / 2; i++) {
//            if (x % i == 0) {
//                cout << i << ", ";
//                prime = false;
//            }
//        }
//        cout << x;
//        if (prime == true) {
//            cout << " (Prime!)";
//        }
//        cout << endl;
//    }
//}

// Week 5 Problem 1
//
//bool charInsert(char str[], int n, int ind, char c) {
//    if (n < 0 || ind < 0 || ind > n || n >= strlen(str) - 1) {
//        return false;
//    }
//    char placeholder1 = str[ind];
//    char placeholder2;
//    str[ind] = c;
//    for (int i = ind + 1; str[i] != '\0'; i++) {
//        placeholder2 = str[i];
//        str[i] = placeholder1;
//        placeholder1 = placeholder2;
//    }
//    return true;
//}
//int main() {
//    char failure[6] = "aaaaa";
//    bool res = charInsert(failure, 6, 1, 'b'); // res should equal false
//    cout << failure << endl; // aaaaa
//    if (!res) {
//        cout << "yay";
//    }
//}

// Week 5 Problem 2
//
//void cReverse(char str[]) {
//    size_t len = strlen(str);
//    char ph;
//    for (int i = 0; i < len / 2; i++) {
//        ph = str[i];
//        str[i] = str[len - 1 - i];
//        str[len - 1 - i] = ph;
//    }
//}
//
//int main() {
//    char test[9] = "American";
//    cReverse(test); // test should now store “naciremA”
//    cout << test << endl;
//}

// Week 5 Problem 3
//
//void strcat(char str1[], char str2[]) { // this is actually such a bad implementation jeez
//    size_t nextPos = strlen(str1);
//    int j = 0;
//    for (int i = nextPos; str2[j] != '\0'; i++) {
//        str1[i] = str2[j];
//        j++;
//    }
//    str1[strlen(str1)] = '\0';
//}
//
//int main() {
//    char str1[20] = "Hello";
//    char str2[8] = " World!";
//    strcat(str1, str2);
//    cout << str1; << endl; // Hello World!
//}

// Week 5 Problem 4
//
//void eraseDuplicates(char str[]) {
//    int nextPos = 0;
//    char usedChars[strlen(str)];
//    for (int i = 0; str[i] != '\0'; i++) {
//        bool match = false;
//        for (int j = 0; j < nextPos; j++) {
//            if (str[i] == usedChars[j]) {
//                match = true;
//            }
//        }
//        if (match) {
//            for (int k = i; str[k] != '\0'; k++) {
//                str[k] = str[k + 1];
//            }
//            i--;
//        } else {
//            usedChars[nextPos] = str[i];
//            nextPos++;
//        }
//    }
//}
//
//int main() {
//    char test[50] = "memesformeforfree123";
//    eraseDuplicates(test); // test should now store "mesfor123"
//    cout << test << endl;
//}

// Week 5 Problem 5
//
//void wordShiftLeft(char str[]) {
//    for (int i = 0; i < strlen(str); i++) {
//        char firstChar = str[i];
//        for (int j = i; str[j] != '\0' && str[j] != ' '; j++) {
//            if (str[j + 1] == '\0' || str[j + 1] == ' ') {
//                str[j] = firstChar;
//                i = j + 1;
//            } else {
//                str[j] = str[j + 1];
//            }
//        }
//    }
//}
//
//int main() {
//    char test[] = "I.love.CS31";
//    wordShiftLeft(test);
//    cout << test << endl; // “.love.CS31I”
//    int i = 0;
//    while (test[i] != '\0') {
//        cout << i << endl;
//        i++;
//    }
//}

// Week 6 Problem 1
//
//char* ptrToChar; // pointer to char
//
//char* arrayOfPointers[10]; // array of 10 pointers to char
//
//const int* ptrToConstInt; // pointer to a const int

// Week 6 Problem 2
//
//void reverse(char* arr) { // reverse the C string, no [] allowed
//    char* ptr1 = arr; // set ptr1 to position 0 in arr
//    char* ptr2 = &arr[strlen(arr) - 1]; // set ptr2 to final position in arr
//    for (; ptr1 < ptr2; ptr1++, ptr2--) { // repeat until ptr1 passes ptr2
//        char temp = *ptr1; // basic swap
//        *ptr1 = *ptr2;
//        *ptr2 = temp;
//    }
//}
//
//int main() {
//    char arr1[6] = "hello";
//    reverse(arr1); // now arr1 should be "olleh"
//    for (int i = 0; i < 5; i++) {
//        cout << arr1[i];
//    }
//    cout << endl;
//    char arr2[5] = "ucla";
//    reverse(arr2); // now arr2 should be "alcu"
//    for (int i = 0; i < 4; i++) {
//        cout << arr2[i];
//    }
//    cout << endl;
//    char arr3[6] = "kayak";
//    reverse(arr3); // now arr3 should be "kayak"
//    for (int i = 0; i < 5; i++) {
//        cout << arr3[i];
//    }
//    cout << endl;
//}

// Week 6 Problem 3
//
//void minMax(int* arr, int n, int*& min, int*& max) { // points min and max to the minimum and maximum values in the array, only accesses each element once, [] not allowed
//    if (n < 1) { // exits function without changing pointers if array is empty or n is invalid
//        return;
//    }
//    min = arr; // initializes min and max to point at the first element
//    max = arr;
//    int* ptr = arr + 1; // initializes tracker pointer
//    for (int i = 1; i < n; i++, ptr++) { // starting at second element, loops until final element
//        if (*ptr < *min) { // checks for min
//            min = ptr;
//        } else if (*ptr > *max) { // checks for max
//            max = ptr;
//        }
//    }
//}
//
//int main() {
//    int arr[5] = {0, 5, 7, -10, 2};
//    int* pmin;
//    int* pmax;
//    minMax(arr, 5, pmin, pmax); // pmin should point to the -10, pmax should point to the 7
//    cout << *pmin << ", " << *pmax << endl;
//}

// Week 6 Problem 4
//
//void descSort(int* nums, int len) { // sorts nums into descending order, [] not allowed
//    int* ptr = nums; // initializes tracker pointer
//    for (int i = 0; i < len; i++) { // attempt at using selection sort
//        int* max = ptr + i; // initializes pointer to keep track of max value
//        for (int j = i; j < len; j++) { // points max at the highest value in the remainder of the array
//            if (*(ptr + j) > *max) {
//                max = ptr + j;
//            }
//        }
//        int temp = *(ptr + i); // basic swap of the maximum value in the rest of the array and the current value
//        *(ptr + i) = *max;
//        *max = temp;
//    }
//}
//
//int main() {
//    int a[10] = {3, 1, 4, 0, -1, 2, 3, 4, 1, 2};
//    descSort(a, 10); // a = {4, 4, 3, 3, 2, 2, 1, 1, 0, -1};
//    for (int i = 0; i < 10; i++) {
//        cout << a[i] << endl;
//    }
//}

// Week 6 Problem 5
//
//void invert(int matrix[][3], int n) { // transposes an N x N matrix (in this case N = 3)
//    for (int i = 0; i < n; i++) { // iterates through the rows
//        for (int j = i; j < n; j++) { // iterates through the colums, j = i to ensure no entry will be changed twice
//            int* rowPointer = &matrix[i][j]; // initializes pointer that will iterate across a row
//            int* colPointer = &matrix[j][i]; // initializes a pointer that will iterate down a column
//            int temp = *rowPointer; // basic swap
//            *rowPointer = *colPointer;
//            *colPointer = temp;
//        }
//    }
//}
//
//int main() {
//    int foobar[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//    invert(foobar, 3); // foobar is now expected to be: {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}}
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            if (j != 2) {
//                cout << foobar[i][j] << ", ";
//            } else {
//                cout << foobar[i][j];
//            }
//        }
//        cout << endl;
//    }
//}

// Week 6 Problem 6
//
//void sum(int* list1, int list1_size, int* list2, int list2_size) { // print the numbers represented by list1 and list2
//    int totalSum = 0;
//    int* ptr1 = list1;
//    int* ptr2 = list2;
//    for (int i = list1_size; i > 0; i--, ptr1++) { // calculates first number
//        int multiplier = pow(10, i - 1); // finds the position of the number (thousandth, hundredth, tenth, etc.)
//        totalSum += *ptr1 * multiplier; // adds the value to the sum
//    }
//    for (int j = list2_size; j > 0; j--, ptr2++) { // calculates second number
//        int multiplier = pow(10, j - 1);
//        totalSum += *ptr2 * multiplier;
//    }
//    cout << totalSum << endl;
//
//}
//
//int main() {
//    int list1[] = { 8, 5, 3, 1 };
//    int list2[] = { 5, 3, 2, 9 };
//    sum(list1, 4, list2, 4); // prints 13860, the sum of 8531 and 5329
//    int list3[] = { 5, 3, 1 };
//    int list4[] = { 5, 3, 2, 9 };
//    sum(list3, 3, list4, 4); // prints 5860, the sum of 531 and 5329
//}

// Week 6 Problem 7 (not finished)
//
//void rotate(int* arr, int n) {
//    int* ptr;
//    int pos;
//    int copy[6];
//    for (int i = 0; i < 6; i++) {
//        copy[i] = arr[i];
//    }
//    for (int i = 0; i < 6; i++) {
//        ptr = &arr[i];
//        if (ptr + n > &arr[5]) {
//
//        }
//    }
//}
//
//int main() {
//    int a[6] = {1,2,3,4,5,6};
//    int b[6] = {1,2,3,4,5,6};
//    int c[6] = {1,2,3,4,5,6};
//    rotate(a, 4); // now a = {3,4,5,6,1,2};
//    rotate(b, -1); // now b = {2,3,4,5,6,1};
//    rotate(c, 8); // now c = {5,6,1,2,3,4};
//    for (int i = 0; i < 6; i++) {
//        cout << a[i] << " ";
//    }
//    cout << endl;
//    for (int i = 0; i < 6; i++) {
//        cout << b[i] << " ";
//    }
//    cout << endl;
//    for (int i = 0; i < 6; i++) {
//        cout << c[i] << " ";
//    }
//    cout << endl;
//}

// Week 8 Problem 2
//
//class Person {
//public:
//    Person();
//    Person(int ag, string phrase);
//    int getAge() const;
//    void haveBirthday();
//    void speak() const;
//private:
//    int m_age;
//    string m_catchphrase;
//};
//
//Person::Person() { // default constructor
//    m_age = 1;
//    m_catchphrase = "Hello";
//}
//
//Person::Person(int ag, string phrase) { // second constructor
//    if (ag > 0) { // check if valid age
//        m_age = ag;
//    } else {
//        m_age = 1;
//    }
//    m_catchphrase = phrase;
//}
//
//int Person::getAge() const { // return the Person's age
//    return m_age;
//}
//
//void Person::haveBirthday() { // increment the Person's age by 1
//    m_age++;
//}
//
//void Person::speak() const { // print the Person's catchphrase
//    cout << m_catchphrase << endl;
//}

// Week 8 Problem 3
//
//class Line {
//public:
//    Line(double m, double b);
//    double intersection(Line line);
//private:
//    double m_slope;
//    double m_yIntercept;
//    double m_xValue;
//};
//
//Line::Line(double m, double b) {
//    m_slope = m;
//    m_yIntercept = b;
//}
//
//double Line::intersection(Line line) {
//    if (this->m_slope == line.m_slope) { // returns 0 when parallel/same line
//        return 0;
//    }
//    return (this->m_yIntercept - line.m_yIntercept) / (line.m_slope - this->m_slope); // solved from m1x + b1 = m2x + b2
//}
//
//int main() {
//    double m1 = 2;
//    double b1 = 3;
//    double m2 = -2;
//    double b2 = 7;
//    Line line1(m1, b1);
//    Line line2(m2, b2);
//    cout.setf(ios::fixed);
//    cout.precision(1); // set to 1 decimal point in fixed notation
//    cout << line1.intersection(line2) << endl; // prints 1.0
//}

// Week 8 Problem 4
//
//class Person { // Person class from Problem 2
//public:
//    Person();
//    Person(int ag, string phrase);
//    int getAge() const;
//    void haveBirthday();
//    void speak() const;
//private:
//    int m_age;
//    string m_catchphrase;
//};
//
//Person::Person() { // default constructor
//    m_age = 1;
//    m_catchphrase = "Hello";
//}
//
//Person::Person(int ag, string phrase) { // second constructor
//    if (ag > 0) { // check if valid age
//        m_age = ag;
//    } else {
//        m_age = 1;
//    }
//    m_catchphrase = phrase;
//}
//
//int Person::getAge() const { // return the Person's age
//    return m_age;
//}
//
//void Person::haveBirthday() { // increment the Person's age by 1
//    m_age++;
//}
//
//void Person::speak() const { // print the Person's catchphrase
//    cout << m_catchphrase << endl;
//}
//
//int main() {
//    for (;;) { // repeatedly
//        int age;
//        cout << "Enter an age: "; // prompt for age
//        cin >> age;
//        cin.ignore(10000, '\n'); // clear newline
//        string catchphrase;
//        cout << "Enter a catchphrase: "; // prompt for catchphrase
//        getline(cin, catchphrase);
//        Person* p = new Person (age, catchphrase); // dynamic allocation
//        p->speak();
//        delete p; // deallocation
//    }
//}

// Week 8 Problem 5
//
//const int NAME_LEN = 100;
//
//class Cat {
//    int m_age;
//    char m_name[NAME_LEN];
//    string m_type;
//public: // (1) must classify constructor as public
//    Cat(int age, const char name[], string type) {
//        m_age = age;
//        strcpy(m_name, name); // (2) must change to C-string syntax
//        m_type = type;
//    }
//    void introduce() {
//        cout << "Hi! I am a " + m_type + " cat" << endl;
//    }
//};
//
//struct Sheep {
//    string m_name;
//    int m_age;
//    Sheep(int age) {
//        m_age = age;
//    }
//    void introduce() {
//        cout << "Hi! I am " + m_name + " the sheep" << endl;
//    }
//}; // (3) semicolon was missing
//
//int main() {
//    Cat* schrodinger = new Cat(5, "Schrodinger's cat", "Korat");
//    schrodinger->introduce();
//    cout << endl; // (4) m_age is a private variable, it cannot be accessed by non-member functions
//    Sheep dolly(6);
//    dolly.introduce(); // (5) dolly is the object itself, not a pointer, so use the dot operator
//    delete schrodinger;
//    // (6) dolly doesn't need to be deleted, it was created on the stack, not the heap
//}

// Week 8 Problem 6
//
//class Complex {
//public:
//    Complex();
//    Complex(int real, int imaginary);
//    void sum(Complex c1, Complex c2);
//    void print() const;
//private:
//    int m_real;
//    int m_imaginary;
//};
//
//Complex::Complex() { // default constructor
//    m_real = 0;
//    m_imaginary = 0;
//}
//
//Complex::Complex(int real, int imaginary) { // second constructor
//    m_real = real;
//    m_imaginary = imaginary;
//}
//
//void Complex::sum(Complex c1, Complex c2) { // sums 2 complex numbers
//    m_real = c1.m_real + c2.m_real; // adds real numbers
//    m_imaginary = c1.m_imaginary + c2.m_imaginary; // adds coefficients of i
//}
//
//void Complex::print() const { // prints the complex number
//    cout << m_real << " + " << m_imaginary << "i" << endl;
//}
//
//int main() {
//    Complex c1(5, 6);
//    Complex c2(-2, 4);
//    Complex* c3 = new Complex();
//    c1.print();
//    c2.print();
//    cout << "The sum of the two complex numbers is:" << endl;
//    c3->sum(c1, c2);
//    c3->print();
//    delete c3;
//    // prints 5 + 6i
//    //        -2 + 4i
//    //        The sum of the two complex numbers is:
//    //        3 + 10i
//}

// Week 8 Problem 7
//
//const char X = 'X'; // global variables
//const char O = 'O';
//
//class TicTacToe {
//public:
//    TicTacToe();
//    TicTacToe(bool Xstarts);
//    bool placePiece(int r, int c);
//    bool isXTurn() const;
//    bool isGameEnded() const;
//    char getWinner() const;
//    void clear(bool Xstarts);
//    void printBoard() const;
//private:
//    char m_turn;
//    char m_board[3][3];
//    char m_winner;
//    void emptyBoard();
//
//};
//
//void TicTacToe::emptyBoard() { // helper function, clears the board
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            m_board[i][j] = ' ';
//        }
//    }
//}
//
//void TicTacToe::printBoard() const { // helper function, prints the board
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            cout << m_board[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
//TicTacToe::TicTacToe() { // default constructor
//    emptyBoard();
//    m_turn = X;
//    m_winner = ' ';
//}
//
//TicTacToe::TicTacToe(bool Xstarts) { // second constructor
//    emptyBoard();
//    if (Xstarts) {
//        m_turn = X;
//    } else {
//        m_turn = O;
//    }
//    m_winner = ' ';
//}
//
//bool TicTacToe::placePiece(int r, int c) { // places pieces and checks for a winner
//    if (r < 1 || c < 1 || r > 3 || c > 3 || m_board[r - 1][c - 1] != ' ' || isGameEnded()) { // checks if position is valid
//        return false;
//    }
//    m_board[r - 1][c - 1] = m_turn; // sets the piece
//    if (m_turn == X) { // changes the turn
//        m_turn = O;
//    } else {
//        m_turn = X;
//    }
//    char test = m_board[r - 1][0]; // tests if there's 3 across
//    if (test == m_board[r - 1][1] && test == m_board[r - 1][2] && test != ' ') {
//        cout << "3 ACROSS" << endl;
//        m_winner = test;
//    }
//    test = m_board[0][c - 1]; // tests if there's 3 down
//    if (test == m_board[1][c - 1] && test == m_board[2][c - 1] && test != ' ') {
//        cout << "3 DOWN" << endl;
//        m_winner = test;
//    }
//    test = m_board[1][1]; // tests diagonals
//    if (((test == m_board[0][0] && test == m_board[2][2]) || (test == m_board[0][2] && test == m_board[2][0])) && (test != ' ')) {
//        cout << "3 DIAGONAL" << endl;
//        m_winner = test;
//    }
//    return true;
//}
//
//bool TicTacToe::isXTurn() const { // returns if it's X's turn
//    return m_turn == X;
//}
//
//bool TicTacToe::isGameEnded() const { // checks if the game has ended
//    if (m_winner != ' ') { // checks if there's a winner
//        return true;
//    }
//    for (int i = 0; i < 3; i++) { // checks board for empty spots
//        for (int j = 0; j < 3; j++) {
//            if (m_board[i][j] == ' ') {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//char TicTacToe::getWinner() const {
//    if (isGameEnded()) {
//        if (m_winner != ' ') {
//            return m_winner;
//        } else {
//            return '=';
//        }
//    } else {
//        return '?';
//    }
//}
//
//void TicTacToe::clear(bool Xstarts) {
//    emptyBoard(); // resets board
//    m_winner = ' '; // resets winner
//    if (Xstarts) { // sets turn
//        m_turn = X;
//    } else {
//        m_turn = O;
//    }
//}
//
//int main() { // play tic tac toe
//    TicTacToe game(true);
//    while(true) {
//        game.clear(true);
//        while(! game.isGameEnded()) {
//            game.printBoard();
//            if (game.isXTurn()) {
//                cout << "It is X's turn" << endl;
//            } else {
//                cout << "It is O's turn" << endl;
//            }
//            int r;
//            int c;
//            cout << "Enter a row number: ";
//            cin >> r;
//            cout << "Enter a column number: ";
//            cin >> c;
//            if( !game.placePiece(r, c)) {
//                cout << "Invalid position, try again" << endl;
//            }
//        }
//        game.printBoard();
//        cout << "The winner is: " << game.getWinner() << endl;
//        cout << endl;
//        cout << "NEW GAME" << endl;
//    }
//}

// Week 8 Problem 8
//
//struct Array {
//    int* vals;
//    int len;
//    int findMax() const;
//};
//
//int Array::findMax() const {
//    int max = *vals;
//    for (int* ptr = vals; ptr < vals + len; ptr++) { // iterates through the array to find the max value
//        if (*ptr > max) {
//            max = *ptr;
//        }
//    }
//    return max;
//}
//
//int findArrayWithMax(Array arr1, Array arr2, Array arr3) {
//    int num1 = arr1.findMax();
//    int num2 = arr2.findMax();
//    int num3 = arr3.findMax();
//    if (num1 > num2 && num1 > num3) {
//        return 1;
//    } else if (num2 > num1 && num2 > num3) {
//        return 2;
//    } else if (num3 > num1 && num3 > num2) {
//        return 3;
//    } else { // there's a tie
//        return -1;
//    }
//}
//
//int main() {
//    int a[5] = {3, 4, 5, 6, 1};
//    int b[2] = {1000, -1};
//    int c[9] = {23, 2, 1, 4, 65, 42, 10, -20, 7};
//
//    Array arr1 = { a, 5 };
//    Array arr2 = { b, 2 };
//    Array arr3 = { c, 9 };
//    int max = findArrayWithMax(arr1, arr2, arr3); // max = 2
//    cout << max << endl;
//}
