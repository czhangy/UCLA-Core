//
//  main.cpp
//  test
//
//  Created by Charles Zhang on 10/9/19.
//  Copyright © 2019 Charles Zhang. All rights reserved.
//

#include <iostream>
#include <iomanip>

#include <cmath>
#include <cassert>
#include <cctype>

#include <string>

#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Worksheet 1 Problem 2 - Finish the class
//
//class B; // to get rid of errors
//class A {
//    public:
//    A(int sz);
//    //...implement this!
//    A(const A& other);
//    //...implement this!
//    A& operator=(const A& other);
//    //...implement this!
//    //...other functions
//    ~A();
//    //...implement this!
//    private:
//    // one dynamically allocated B object; assume B has a default constructor, a copy constructor, and an assignment operator
//    B* b;
//    // dynamically allocated array
//    int* arr;
//    // size of arr (determined by a constructor)
//    int n;
//    string str;
//};
//
//A::A(int sz) : n(sz), str("") { // constructor
//    b = new B;
//    arr = new int[sz];
//}
//
//A::A(const A& other) { // copy constructor
//        n = other.n;
//        str = other.str;
//        b = other.b; // b has a functioning assignment operator
//        arr = new int[n];
//        for (int i = 0; i < n; i++)
//            arr[i] = other.arr[i];
//}
//
//A& A::operator=(const A& other) { // assignment operator
//    if (*this != other) {
//        delete [] arr; // use the array form of delete
//        n = other.n;
//        str = other.str;
//        delete b;
//        b = new B(other.b);
//        arr = new int[n];
//        for (int i = 0; i < n; i++)
//            arr[i] = other.arr[i];
//    }
//    return *this;
//}
//
//A::~A() { // destructor
//    delete b; // use the non-array form of delete
//    delete [] arr; // deallocate all dynamically allocated objects
//}

// Worksheet 1 Problem 3 - Find the 4 errors in the code
//
//class Account {
//    public:
//    Account(int x) {
//        cash = x;
//    }
//    int cash;
//} // semicolon after the class declaration
//
//class Billionaire {
//    public:
//    Billionaire(string n) {
//        account = Account(10000);
//        offshore = Account(1000000000); // assigning an Account to a variable that holds a pointer to Account
//        name = n;
//    }
//    Account account; // Account doesn't have a default constructor, it must be initialized in the member initialization list
//    Account* offshore;
//    string name;
//};
//
//int main() {
//    Billionaire jim = Billionaire("Jimmy");
//    cout << jim.name << " has " << jim.account.cash + jim.offshore->cash << endl; // should print "Jimmy has 1000010000"
//} // offshore is dynamically allocated, so it causes a memory leak

// Worksheet 1 Problem 4 - Clone Jim
//
//class Account {
//    public:
//    Account(int x) {
//        cash = x;
//    }
//    int cash;
//};
//
//class Billionaire {
//    public:
//    Billionaire(string n) : account(10000) {
//        account = Account(10000);
//        offshore = new Account(1000000000);
//        name = n;
//    }
//
//    ~Billionaire() { // destructor must delete offshore
//        delete offshore;
//    }
//
//    Billionaire(const Billionaire& other) : account(0), name(other.name) { // money must be 0
//        offshore = new Account(0); // must dynamically allocate a new object
//    }
//
//    Billionaire& operator=(const Billionaire& other) { // assignment operator
//        delete offshore; // must delete offshore to start
//        offshore = new Account(0);
//        name = other.name;
//        account = Account(0);
//        return *this;
//    }
//
//    Account account;
//    Account* offshore;
//    string name;
//};
//
//int main() {
//    Billionaire jim = Billionaire("Jimmy");
//    Billionaire jimClone = jim;
//    cout << jimClone.name << " has " << jimClone.account.cash + jimClone.offshore->cash << endl;
//    cout << jim.name << " has " << jim.account.cash + jim.offshore->cash << endl; // should output "Jimmy has 0 Jimmy has 1000010000"
//}

// Worksheet 1 Problem 6 - Compare a linked list and an array
//
//struct Node { // create a Node
//    int m_value;
//    Node* m_next;
//};
//
//int cmpr(Node* head, int* arr, int arr_size) {
//    int index = -1; // set default index
//    Node* ptr = head;
//    for (int i = 0; i < arr_size && ptr != nullptr && ptr->m_value == arr[i]; i++, ptr = ptr->m_next) {
//        index = i; // set index to last known match
//    }
//    return index;
//}
//
//int main() {
//    Node* ptr1 = nullptr; // construct test linked list
//    Node* ptr2 = nullptr;
//    Node* head = nullptr;
//    for (int i = 1; i != 7; i++) {
//        ptr1 = new Node;
//        if (i == 1) { // set head
//            head = ptr1;
//        }
//        if (i == 4) { // linked list doesn't contain 4
//            continue;
//        }
//        ptr1->m_value = i;
//        if (ptr2 != nullptr) {
//            ptr2->m_next = ptr1;
//        }
//        ptr2 = ptr1;
//    }
//    ptr1->m_next = nullptr;
//
//    int a[6] = {1, 2, 3, 4, 5, 6};
//    cout << cmpr(head, a, 6) << endl; // Should print 2
//    int b[7] = {1, 2, 3, 5, 6, 7, 5};
//    cout << cmpr(head, b, 7) << endl; // Should print 4
//    int c[3] = {5, 1, 2};
//    cout << cmpr(head, c, 3) << endl; // Should print -1
//    int d[3] = {1, 2, 3};
//    cout << cmpr(head, d, 3) << endl; // Should print 2
//}

// Worksheet 1 Problem 7 - Write a copy constructor for LL
//
//class LL {
//public:
//    LL();
//    LL(LL& other);
//private:
//    struct Node {
//        int val;
//        Node* next;
//    };
//    Node* head;
//};
//
//LL::LL() {
//    head = nullptr;
//}
//
//LL::LL(LL& other) {
//    if (other.head == nullptr) {
//        head = nullptr;
//    } else {
//        head = new Node; // create head
//        head->val = other.head->val;
//        head->next = other.head->next;
//        Node* thisptr = head;
//        Node* otherptr = other.head;
//        while (otherptr->next != nullptr) { // loop until last Node
//            thisptr->next = new Node;
//            thisptr->next->val = otherptr->next->val; // write the next Node's value/next
//            thisptr->next->next = otherptr->next->next;
//            thisptr = thisptr->next;
//            otherptr = otherptr->next;
//        }
//    }
//}

// Worksheet 1 Problem 8 - Implement a function to find the nth from last value of a linked list
//
//class LL {
//public:
//    LL();
//    void insert(int val); // not part of the problem, used for testing
//    void print() const; // not part of the problem, used for testing
//    int findNthFromLast(int n) const;
//private:
//    struct Node {
//        int val;
//        Node* next;
//    };
//    Node* head;
//};
//
//LL::LL() {
//    head = nullptr;
//}
//
//void LL::insert(int val) {
//    Node* newNode = new Node;
//    newNode->val = val;
//    if (head == nullptr) {
//        newNode->next = nullptr; // set as only item in list
//    } else {
//        newNode->next = head; // insert at front of list
//    }
//    head = newNode; // set front of list to new Node
//}
//
//int LL::findNthFromLast(int n) const {
//    int size = 0;
//    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) { // find size of list
//        size++;
//    }
//    size--; // account for starting at the first Node
//    if (n > size) return -1;
//    Node* valueptr = head;
//    for (int i = 0; i < size - n; i++) { // size - n is the desired index, position valueptr accordingly
//        valueptr = valueptr->next;
//    }
//    return valueptr->val;
//}
//
//void LL::print() const {
//    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
//        cout << ptr->val << endl;
//    }
//}
//
//int main() {
//    LL list;
//    for (int i = 5; i > 0; i--) { // create the desired list
//        list.insert(i);
//    }
//    cout << list.findNthFromLast(2) << endl; // should output 3
//    cout << list.findNthFromLast(6) << endl; // should output -1
//}

// Worksheet 1 Problem 9 - Implement a function that rotates a list left by n Nodes
//
//struct Node {
//    int val;
//    Node* next;
//};
//
//class LinkedList {
//public:
//    inline LinkedList() {head = nullptr;}
//    void rotateLeft(int n); // rotates head left by n
//    void insert(int val); // for testing
//    void print() const; // for testing
//private:
//    Node* head;
//};
//
//void LinkedList::insert(int val) {
//    Node* newNode = new Node;
//    newNode->val = val;
//    if (head == nullptr) {
//        newNode->next = nullptr; // set as only item in list
//    } else {
//        newNode->next = head; // insert at front of list
//    }
//    head = newNode; // set front of list to new Node
//}
//
//void LinkedList::print() const {
//    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
//        cout << ptr->val << endl;
//    }
//}
//
//void LinkedList::rotateLeft(int n) {
//    int size = 0;
//    for (Node* temp = head; temp != nullptr; temp = temp->next) { // find the size of the list
//        size++;
//    }
//    Node* newHead = head;
//    for (int i = 0; i < n; i++) { // position the new start of the list
//        newHead = newHead->next;
//    }
//    Node* ptr = newHead;
//    for (int i = 1; i < size; i++) { // connect the last item of the list to the first if necessary
//        if (ptr->next == nullptr) {
//            ptr->next = head;
//        }
//        ptr = ptr->next;
//    }
//    ptr->next = nullptr; // set the new last item
//    head = newHead; // set the new head
//}
//
//int main() {
//    LinkedList x;
//    x.insert(73);
//    x.insert(1);
//    x.insert(2);
//    x.insert(5);
//    x.insert(1);
//    x.insert(10);
//    x.print();
//    cout << endl;
//    x.rotateLeft(0);
//    x.print(); // should print 10, 1, 5, 2, 1, 73
//    x.rotateLeft(3);
//    cout << endl;
//    x.print(); // should print 2, 1, 73, 10, 1, 5
//}

// Worksheet 1 Problem 10 - Write a function that works like strcmp(), but for linked lists
//
//struct Node {
//    char ch;
//    Node* next;
//};
//class LinkedList {
//public:
//    inline LinkedList() {head = nullptr;}
//    void insert(char ch); // for testing
//    void print() const; // for testing
//    Node* getHead() const; // for testing
//private:
//    Node* head;
//};
//
//void LinkedList::insert(char ch) {
//    Node* newNode = new Node;
//    newNode->ch = ch;
//    if (head == nullptr) {
//        newNode->next = nullptr; // set as only item in list
//    } else {
//        newNode->next = head; // insert at front of list
//    }
//    head = newNode; // set front of list to new Node
//}
//
//void LinkedList::print() const {
//    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
//        cout << ptr->ch << endl;
//    }
//}
//
//Node* LinkedList::getHead() const {
//    return head;
//}
//
//int compare(Node* list1, Node* list2) {
//    Node* ptr1 = list1;
//    Node* ptr2 = list2;
//    for(; ptr1 != nullptr && ptr2 != nullptr && ptr1->ch == ptr2->ch; ptr1 = ptr1->next, ptr2 = ptr2->next) {}
//    if (ptr1 == nullptr && ptr2 == nullptr) { // if "strings" are equal
//        return 0;
//    } else if (ptr1 == nullptr) { // if first list is shorter
//        return -1;
//    } else if (ptr2 == nullptr) { // if second list is shorter
//        return 1;
//    } else if (ptr1->ch < ptr2->ch) { // if second list is greater
//        return -1;
//    } else { // if first list is greater
//        return 1;
//    }
//}
//
//int main() {
//    LinkedList list1; // is "ant"
//    LinkedList list2; // is "ark"
//    LinkedList list3; // is "a"
//    LinkedList list4; // is "a"
//    list1.insert('t');
//    list1.insert('n');
//    list1.insert('a');
//    list2.insert('k');
//    list2.insert('r');
//    list2.insert('a');
//    list3.insert('a');
//    list4.insert('a');
//    cout << compare(list1.getHead(), list2.getHead()) << endl; // should print -1, second list > first list
//    cout << compare(list2.getHead(), list1.getHead()) << endl; // should print 1, first list > second list
//    cout << compare(list3.getHead(), list2.getHead()) << endl; // should print -1, first list is shorter
//    cout << compare(list1.getHead(), list3.getHead()) << endl; // should print 1, second list is shorter
//    cout << compare(list3.getHead(), list4.getHead()) << endl; // should print 0, lists are the same
//}

// Worksheet 1 Problem 11 - Write a function that reverses a linked list
//
//struct Node {
//    int val;
//    Node* next;
//};
//
//class LinkedList {
//public:
//    inline LinkedList() {head = nullptr;}
//    void insert(int val); // for testing
//    Node* getHead() const; // for testing
//private:
//    Node* head;
//};
//
//void LinkedList::insert(int val) {
//    Node* newNode = new Node;
//    newNode->val = val;
//    if (head == nullptr) {
//        newNode->next = nullptr; // set as only item in list
//    } else {
//        newNode->next = head; // insert at front of list
//    }
//    head = newNode; // set front of list to new Node
//}
//
//Node* LinkedList::getHead() const {
//    return head;
//}
//
//Node* reverse(Node* head) {
//    Node* current = head;
//    Node* prev = nullptr;
//    Node* next = nullptr;
//    while (current != nullptr) {
//        next = current->next; // set next pointer to the next Node
//        current->next = prev; // set current's next to the previous Node
//        prev = current; // set prev pointer to the current position
//        current = next; // set current pointer to the next Node
//    }
//    return prev;
//}
//
//int main() {
//    LinkedList x;
//    x.insert(1);
//    x.insert(2);
//    x.insert(3);
//    Node* ptr = reverse(x.getHead());
//    for (; ptr != nullptr; ptr = ptr->next) { // should print 1 2 3
//        cout << ptr->val << endl;
//    }
//}

// Worksheet 1 Problem 12 - Combine 2 sorted linked lists into 1
//
//struct Node {
//    int val;
//    Node* next;
//};
//
//class LinkedList {
//public:
//    inline LinkedList() {head = nullptr;}
//    void insert(int val); // for testing
//    Node* getHead() const; // for testing
//private:
//    Node* head;
//};
//
//void LinkedList::insert(int val) {
//    Node* newNode = new Node;
//    newNode->val = val;
//    if (head == nullptr) {
//        newNode->next = nullptr; // set as only item in list
//    } else {
//        newNode->next = head; // insert at front of list
//    }
//    head = newNode; // set front of list to new Node
//}
//
//Node* LinkedList::getHead() const {
//    return head;
//}
//
//void insertAtEnd(int val, Node*& head) { // inserts a value at the end of a linked list, helper function
//    Node* newNode = new Node;
//    newNode->val = val;
//    newNode->next = nullptr;
//    if (head == nullptr) { // checks if first element
//        head = newNode;
//    } else {
//        Node* ptr;
//        for (ptr = head; ptr->next != nullptr; ptr = ptr->next) {}
//        ptr->next = newNode;
//    }
//}
//
//Node* combine(Node* h, Node* h2) {
//    Node* ptr1 = h;
//    Node* ptr2 = h2;
//    Node* head = nullptr;
//    for (; ptr1 != nullptr && ptr2 != nullptr;) { // iterates through lists until one runs out
//        int x;
//        if (ptr1->val < ptr2->val) { // checks for smallest value remaining
//            x = ptr1->val;
//            ptr1 = ptr1->next;
//        } else {
//            x = ptr2->val;
//            ptr2 = ptr2->next;
//        }
//        insertAtEnd(x, head);
//    }
//    if (ptr1 == nullptr && ptr2 != nullptr) { // if list 1 ran out
//        for (; ptr2 != nullptr; ptr2 = ptr2->next) {
//            insertAtEnd(ptr2->val, head);
//        }
//    } else if (ptr1 != nullptr && ptr2 == nullptr) { // if list 2 ran out
//            for (; ptr1 != nullptr; ptr1 = ptr1->next) {
//            insertAtEnd(ptr1->val, head);
//        }
//    }
//    return head;
//}
//
//int main() {
//    LinkedList x;
//    LinkedList y;
//    x.insert(9);
//    x.insert(6);
//    x.insert(3);
//    x.insert(1);
//    y.insert(10);
//    y.insert(8);
//    y.insert(7);
//    Node* z = combine(x.getHead(), y.getHead());
//    for (Node* ptr = z; ptr != nullptr; ptr = ptr->next) { // should output 1 3 6 7 8 9 10
//        cout << ptr->val << endl;
//    }
//}

// Worksheet 2.1 Problem 1 - Use a stack to write a function that checks for valid strings
//
//bool isValid(string parens) {
//    stack<char> open;
//    for (int i = 0; i < parens.size(); i++) {
//        switch(parens[i]) {
//            case '(': // pushes the openers onto the stack
//            case '[':
//                open.push(parens[i]);
//                break;
//            case ')':
//                if (open.empty() || open.top() != '(') return false; // checks the top of the stack for a matchig closer
//                open.pop();
//                break;
//            case ']':
//                if (open.empty() || open.top() != '[') return false; // checks the top of the stack for a matchig closer
//                open.pop();
//                break;
//        }
//    }
//    return open.empty(); // if the stack isn't empty, the string is invalid
//}
//
//int main() {
//    string s1 = "[()([])[[([][])]]]"; // valid string
//    string s2 = "((([(]))))"; // invalid string
//    if (isValid(s1) && !isValid(s2)) {
//        cout << "u did it" << endl;
//    }
//}

// Worksheet 2.1 Problem 2 - Write a function that reverses a queue
//
//void reverseQueue(queue<int>& Q){
//    stack<int> temp;
//    while (!Q.empty()) {
//        temp.push(Q.front());
//        Q.pop();
//    }
//    while(!temp.empty()) {
//        Q.push(temp.top());
//        temp.pop();
//    }
//}
//
//int main() {
//    queue<int> test;
//    for (int i = 1; i < 11; i++) {
//        test.push(i * 10);
//    }
//    reverseQueue(test);
//    for (int i = 0; i < 10; i++) {
//        cout << test.front() << endl; // should print 100 90 80 70 60 50 40 30 20 10
//        test.pop();
//    }
//}

// Worksheet 2.1 Problem 3 - Implement the Stack class using queues
//
//using Type = int; // type aliasing
//
//class Stack {
//public:
//    bool empty() const;
//    size_t size() const;
//    Type top() const;
//    void push(const Type& val);
//    void pop();
//private:
//    queue<Type> m_queue;
//};
//
//bool Stack::empty() const {
//    return m_queue.empty();
//}
//
//size_t Stack::size() const {
//    return m_queue.size();
//}
//
//Type Stack::top() const { // front of the queue is the top of the Stack
//    if (m_queue.empty()) exit(1); // error if called on empty Stack
//    return m_queue.front();
//}
//
//void Stack::push(const Type& val) {
//    queue<Type> temp;
//    temp.push(val); // pushes the "top" as the front of the queue
//    while (!m_queue.empty()) { // pushes the rest of the queue into the new queue, preserving the order
//        temp.push(m_queue.front());
//        m_queue.pop();
//    }
//    m_queue = temp; // replaces the old queue with the new
//}
//
//void Stack::pop() {
//    if (m_queue.empty()) exit(1); // error if called on empty Stack
//    m_queue.pop();
//}
//
//int main() {
//    Stack s;
//    assert(s.empty()); // a new Stack must be empty
//    s.push(1);
//    s.push(2);
//    s.push(3);
//    assert(s.size() == 3); // the size of the Stack should be 3
//    while (!s.empty()) {
//        cout << s.top() << endl; // should print 3 2 1
//        s.pop();
//    }
//}

// Worksheet 2.1 Problem 4 - Implement the Queue class using stacks
//
//using Type = int;
//
//class Queue {
//public:
//    bool empty() const;
//    size_t size() const;
//    Type front() const;
//    Type back() const;
//    void push(const Type& val);
//    void pop();
//private:
//    stack<Type> m_stack;
//};
//
//bool Queue::empty() const {
//    return m_stack.empty();
//}
//
//size_t Queue::size() const {
//    return m_stack.size();
//}
//
//Type Queue::front() const {
//    if (m_stack.empty()) exit(1); // error if called on empty Queue
//    return m_stack.top();
//}
//
//Type Queue::back() const {
//    if (m_stack.empty()) exit(1); // error if called on empty Queue
//    stack<Type> temp = m_stack;
//    Type val = temp.top();
//    while (!temp.empty()) { // get last value in stack
//        val = temp.top();
//        temp.pop();
//    }
//    return val;
//}
//
//void Queue::push(const Type& val) {
//    stack<Type> temp;
//    stack<Type> reverse;
//    temp.push(val); // pushes new value to bottom of stack/back of Queue
//    while (!m_stack.empty()) { // reverses original stack
//        reverse.push(m_stack.top());
//        m_stack.pop();
//    }
//    while (!reverse.empty()) { // pushes the old stack in the correct order onto the new stack
//        temp.push(reverse.top());
//        reverse.pop();
//    }
//    m_stack = temp;
//}
//
//void Queue::pop() {
//    if (m_stack.empty()) exit(1); // error if called on an empty Queue
//    m_stack.pop();
//}
//
//int main() {
//    Queue q;
//    assert(q.empty()); // a new Queue must be empty
//    q.push(1);
//    q.push(2);
//    q.push(3);
//    assert(q.size() == 3); // the size of the Queue should be 3
//    assert(q.front() == 1 && q.back() == 3); // the front of the Queue should be 1 and the back should be 3
//    while (!q.empty()) {
//        cout << q.front() << endl; // should print 1 2 3
//        q.pop();
//    }
//}

// Worksheet 2.1 Problem 5 - Implement findNextInts
//
//void findNextInts(const int sequence[], int results[], int n) {
//    stack<int> nums;
//    for (int i = n - 1; i > 0; i--) { // pushes all values except the first into the stack
//        nums.push(sequence[i]);
//    }
//    stack<int> testVal = nums;
//    for (int i = 0; i < n - 1; i++) { // loops through all elements except the last
//        while (!testVal.empty() && sequence[i] > testVal.top()) { // while the test stack's next value is less than the target value, move to the next value
//            testVal.pop();
//        }
//        if (testVal.empty()) results[i] = -1; // if the test stack is empty, there is no such value
//        else results[i] = testVal.top(); // otherwise, value found
//        nums.pop(); // move to the next index
//        testVal = nums;
//    }
//    results[n - 1] = -1;
//}
//
//int main() {
//    int seq[] = {2, 6, 3, 1, 9, 4, 7 }; // Only positive integers!
//    int res[7];
//    findNextInts(seq, res, 7);
//    for (int i = 0; i < 7; i++) { // Should print: 6 9 9 9 -1 7 -1
//        cout << res[i] << " ";
//    }
//    cout << endl;
//}

// Worksheet 2.2 Problem 1 - Fix the inheritance issue
//
//class LivingThing {
//public:
//    virtual void intro() { cout << "I’m a living thing" << endl; } // add virtual to make this a virtual function
//};
//
//class Person : public LivingThing {
//public:
//    void intro() { cout << "I’m a person" << endl; }
//};
//
//class UniversityAdministrator : public Person {
//public:
//    void intro() { cout << "I’m a university administrator" << endl; }
//};
//
//class Chancellor : public UniversityAdministrator {
//public:
//    void intro() { cout << "I’m Gene" << endl; }
//};
//
//int main() {
//    LivingThing* thing = new Chancellor();
//    thing->intro();
//}

// Worksheet 2.2 Problem 2 - Complete the constructor implementations
//
//class Animal { // given code
//public:
//    Animal(string name);
//private:
//    string m_name;
//};
//
//class Cat : public Animal {
//public:
//    Cat(string name, int amountOfYarn);
//private:
//    int m_amountOfYarn;
//};
//
//class Himalayan : public Cat {
//public:
//    Himalayan(string name, int amountOfYarn);
//};
//
//class Siamese : public Cat {
//public:
//    Siamese(string name, int amountOfYarn, string toyName);
//private:
//    string m_toyName;
//};
//
//Animal::Animal(string name) : m_name(name) {} // my code
//
//Cat::Cat(string name, int amountOfYarn) : Animal(name), m_amountOfYarn(amountOfYarn) {}
//
//Himalayan::Himalayan(string name, int amountOfYarn) : Cat(name, amountOfYarn) {}
//
//Siamese::Siamese(string name, int amountOfYarn, string toyName) : Cat(name, amountOfYarn), m_toyName(toyName) {}
//
//int main() {
//    cout << "I compile now" << endl;
//}

// Worksheet 2.2 Problem 6 - Correct the errors in the code
//
//class LivingThing { // LivingThing needs a constructor to initialize age
//private:
//    int age;
//};
//
//class Person : public LivingThing {
//public:
//    Person(int a) { age = a; } // age is a private data member of LivingThing, Personmust be initialized with a call to a constructor of LivingThing
//    void birthday() { // member functions of Person cannot access private members of LivingThing, this function should be in the LivingThing class
//        age++;
//    }
//};

// Worksheet 3 Problem 2 - Use recursion to delete a singly-linked list
//
//struct Node {
//    int data;
//    Node* next;
//};
//
//class LL {
//public:
//    LL() { m_head = nullptr; }
//    void insert(int data); // for testing
//    void print(); // for testing
//    void deleteList(); // implement this function
//private: // additional helper allowed
//    Node* m_head;
//};
//
//void LL::insert(int data) {
//    Node* newNode = new Node;
//    newNode->data = data;
//    if (m_head == nullptr) {
//        newNode->next = nullptr;
//    } else {
//        newNode->next = m_head;
//    }
//    m_head = newNode;
//}
//
//void LL::print() {
//    for (Node* ptr = m_head; ptr != nullptr; ptr = ptr->next) {
//        cout << ptr->data << endl;
//    }
//}
//
//void LL::deleteList() {
//    if (m_head != nullptr) {
//        Node* ptr = m_head;
//        m_head = m_head->next;
//        delete ptr;
//        deleteList();
//    } else {
//        return;
//    }
//}
//
//int main() {
//    LL x;
//    LL y;
//    x.insert(1);
//    x.insert(2);
//    x.insert(3);
//    x.print(); // should print 3 2 1
//    x.deleteList();
//    y.deleteList();
//    x.print(); // shouldn't print anything
//    cout << "Success" << endl;
//}

// Worksheet 3 Problem 3 - Return the maximum value in an array recursively
//
//int getMax(int a[], int n) {
//    if (n <= 0) return 0;
//    if (a[0] > getMax(a + 1, n - 1)) return a[0];
//    return getMax(a + 1, n - 1);
//}
//
//int main() {
//    int arr[5] = {5, 8, 1, 3, 0};
//    int arr2[1] = {7};
//    assert(getMax(arr, 5) == 8 && getMax(arr2, 1) == 7);
//    cout << "Success" << endl;
//}

// Worksheet 3 Problem 4 - Use recursion to move all the 'x' chars to the end of the string
//
//string endX(string str) {
//    if (str.size() <= 1) return str;
//    if (str[0] == 'x') return endX(str.substr(1, str.size())) + 'x'; // move the x out
//    return str[0] + endX(str.substr(1, str.size())); // add the non-x char to the recursive call
//}
//
//int main() {
//    string s1 = "";
//    string s2 = "x";
//    string s3 = "xrxe";
//    assert(endX(s1) == "" && endX(s2) == "x" && endX(s3) == "rexx");
//    cout << "Success" << endl;
//}

// Worksheet 3 Problem 5 - Use recursion to determine if ax + by = c is solvable
//
//bool isSolvable(int x, int y, int c) {
//    if (c < 0) return false;
//    if (x == c || y == c) return true;
//    return (isSolvable(x, y, c - x) || isSolvable(x, y, c - y)); // subtract from c instead of incrementing x and y
//}
//
//int main() {
//    assert(isSolvable(7, 5, 45));
//    assert(isSolvable(1, 3, 40));
//    assert(!isSolvable(9, 23, 112));
//    cout << "Success" << endl;
//}

// Worksheet 3 Problem 6 - Use recursion to determine if the robot can climb the stairs
//
//bool isClimbableHelper(int stairs[], bool visited[], int length, int pos) {
//if (pos < 0) return false;
//if (pos >= length) return true;
//if (stairs[pos] == 0 || visited[pos]) return false;
//visited[pos] = true;
//return isClimbableHelper(stairs, visited, length, pos - stairs[pos]) || isClimbableHelper(stairs, visited, length, pos + stairs[pos]);
//}
//
//bool isClimbable(int stairs[], int length) {
//    if (length < 0) return false;
//    bool* visited = new bool[length];
//    for (int x = 0; x < length; x++) visited[x] = false;
//    bool res = isClimbableHelper(stairs, visited, length, 0);
//    delete[] visited;
//    return res;
//}
//
//int main() {
//    int a1[5] = {2, 0, 3, 0, 0};
//    int a2[6] = {1, 2, 4, 1, 0, 0};
//    int a3[8] = {4, 0, 0, 1, 2, 1, 1, 0};
//    assert(isClimbable(a1, 5));
//    assert(isClimbable(a2, 6));
//    assert(!isClimbable(a3, 8));
//    cout << "Success" << endl;
//}

// Worksheet 3 Problem 7 - Use recursion to sum up all the digits in a given number
//
//int sumOfDigits(int num) {
//    if (num == 0) return 0;
//    return (num % 10) + sumOfDigits(num / 10);
//}
//
//int main() {
//    assert(sumOfDigits(176) == 14);
//    assert(sumOfDigits(111111) == 6);
//    cout << "Success" << endl;
//}

// Worksheet 3 Problem 8 - Use recursion to determine if the string is a palindrome
//
//bool isPalindrome(string foo) {
//    if (foo.size() <= 1) return true;
//    if (foo[0] != foo[foo.size() - 1]) return false;
//    return isPalindrome(foo.substr(1, foo.size() - 2));
//}
//
//int main() {
//    assert(isPalindrome("kayak"));
//    assert(isPalindrome("stanley yelnats"));
//    assert(!isPalindrome("LAs rock"));
//    cout << "isPalindrome success" << endl;
//}

// Worksheet 3 Problem 9 - Use recursion to implement linked list functions
//
//struct Node {
//    int data;
//    Node* next;
//};
//
//    //inserts a value in a sorted linked list of integers, returns list head
//Node* insertInOrder(Node* head, int value) {
//    Node* newNode = new Node; // initialize Node
//    newNode->data = value;
//    newNode->next = nullptr;
//    if (head == nullptr) { // value is the only item in list
//        return head;
//    }
//    if (head->next == nullptr) { // head is last value in list
//        head->next = newNode;
//        head = newNode;
//        return head;
//    }
//    if (head->next->data > value) { // insertion point found
//        newNode->next = head->next;
//        head->next = newNode;
//        return head;
//    }
//    delete newNode; // if not correct index, delete the Node
//    return insertInOrder(head->next, value);
//}
//
//    // deletes all nodes whose keys/data == value, returns list head
//Node* deleteAll(Node* head, int value) {
//    if (head == nullptr) return head; // if empty list
//    if (head->next == nullptr) return head->next; // check next isn't nullptr
//    if (head->next->data == value) {
//        Node* ptr = head->next; // delete next Node
//        head->next = ptr->next;
//        delete ptr;
//        return deleteAll(head, value); // recheck current index if delete occurred
//    }
//    return deleteAll(head->next, value); // move on to next list element
//}
//
//  // prints the values of a linked list backwards
//void reversePrint(Node* head) {
//    if (head == nullptr) return;
//    reversePrint(head->next);
//    cout << head->data; // prints after all recursive calls have run
//}
//
//void print(Node* head) { // for testing purposes
//    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
//        cout << ptr->data << endl;
//    }
//}
//
//int main() {
//    Node* start = new Node; start->data = 1; start->next = nullptr;
//    insertInOrder(start, 3); insertInOrder(start, 5); insertInOrder(start, 7); insertInOrder(start, 15);
//    insertInOrder(start, 8);
//    insertInOrder(start, 8);
//    print(start); // should print 1 → 3 → 5 → 7 → 8 → 8 → 15
//    deleteAll(start, 8);
//    print(start); // should print 1 → 3 → 5 → 7 → 15
//    reversePrint(start); // should print 157531
//}

// Worksheet 3 Problem 10 - Use recursion to determine if a given integer is a prime number
//
//int primeHelper(int num, int factor) {
//    if (factor == 1) return 0; // is prime if 1 is reached
//    if (num % factor == 0) return -1; // is not prime if a factor found
//    return primeHelper(num, factor / 2);
//}
//
//bool isPrime(int num) {
//    return primeHelper(num, num / 2) == 0;
//}
//
//int main() {
//    assert(isPrime(2));
//    assert(isPrime(17));
//    assert(!isPrime(16));
//    cout << "isPrime success" << endl;
//}

// Worksheet 3 Problem 11 - Use recursion to reverse a doubly-linked list
//
//struct Node {
//    int val;
//    Node* next;
//    Node* prev;
//};
//
//void print(Node* head) { // for testing purposes
//    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
//        cout << ptr->val << endl;
//    }
//}
//
//void insert(Node* head, int val) { // for testing purposes
//    Node* newNode = new Node;
//    newNode->val = val;
//    if (head == nullptr) {
//        newNode->next = nullptr; // set as only item in list
//        newNode->prev = nullptr;
//    } else {
//        newNode->next = nullptr;
//        Node* ptr = head;
//        for (; ptr->next != nullptr; ptr = ptr->next) {} // insert at end of list
//        newNode->prev = ptr;
//        ptr->next = newNode;
//    }
//}
//
//Node* reverse(Node* head) {
//    if (head == nullptr) return head;
//    Node* temp = head->next; // switch next and prev pointers
//    head->next = head->prev;
//    head->prev = temp;
//    if (head->prev == nullptr) return head; // end of list hit
//    return reverse(head->prev); // recursive call to the "next" Node
//}
//
//int main() {
//    Node* start = new Node;
//    start->prev = nullptr;
//    start->next = nullptr;
//    start->val = 2;
//    insert(start, 4);
//    insert(start, 8);
//    insert(start, 10);
//    print(start);
//    Node* newStart = reverse(start);
//    print(newStart); // should print 10 8 4 2
//}

// Worksheet 3 Problem 12 - Use recursion to find the longest subsequence between 2 strings
//
//string longestCommonSubsequence(string s1, string s2) {
//    if (s1.empty() || s2.empty()) return "";
//    if (s1[0] == s2[0]) { // if first chars are equal
//        return s1[0] + longestCommonSubsequence(s1.substr(1), s2.substr(1)); // check rest
//    }
//    string x = longestCommonSubsequence(s1.substr(1), s2);
//    string y = longestCommonSubsequence(s1, s2.substr(1));
//    if (x.length() > y.length()) return x;
//    return y;
//}
//
//int main() {
//    string res = longestCommonSubsequence("smallberg", "nachenberg");
//    assert(res == "aberg");
//    res = longestCommonSubsequence("los angeles", "computers");
//    assert(res == "oes");
//    cout << "longestCommonSubsequence success" << endl;
//}

// Worksheet 3 Problem 13 - Use recursion to merge 2 singly-linked lists without allocating any new Nodes
//
//struct Node {
//    int val;
//    Node* next;
//};
//
//void print(Node* head) { // for testing purposes
//    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
//        cout << ptr->val << endl;
//    }
//}
//
//void insert(Node* head, int val) { // for testing purposes
//    Node* newNode = new Node;
//    newNode->val = val;
//    if (head == nullptr) {
//        newNode->next = nullptr;
//    } else {
//        Node* ptr = head;
//        for (; ptr->next != nullptr; ptr = ptr->next) {}
//        newNode->next = nullptr;
//        ptr->next = newNode;
//    }
//}
//
//Node* merge(Node* l1, Node* l2) {
//    if (l2 == nullptr) return l1; // if l2 is empty, return l1 (completed list)
//    if (l1->next == nullptr) { // if at end of l1, merge rest of l2
//        Node* ptr = l2->next;
//        l1->next = l2;
//        l2->next = nullptr;
//        return merge(l2, ptr);
//    }
//    if (l1->next->val > l2->val) { // l2 should be before l1 if it is less than l1
//        Node* ptr = l2->next;
//        l2->next = l1->next;
//        l1->next = l2;
//        return merge(l2, ptr);
//    }
//    return merge(l1->next, l2); // move to next Node in l1
//}
//int main() {
//    Node* start1 = new Node;
//    Node* start2 = new Node;
//    start1->next = nullptr;
//    start2->next = nullptr;
//    start1->val = 1;
//    insert(start1, 4);
//    insert(start1, 6);
//    insert(start1, 8);
//    start2->val = 3;
//    insert(start2, 9);
//    insert(start2, 10);
//    print(start1);
//    cout << endl;
//    print(start2);
//    cout << start1->val << endl << endl;
//    merge(start1, start2);
//    cout << endl;
//    print(start1); // should print 1 3 4 6 8 9 10
//}

// Worksheet 3 Problem 14 - Use recursion to sum the elements of the array until the sum hits a threshold
//
//int sumOverThreshold(int x[], int length, int threshold, int sum) {
//    if (sum > threshold) return sum;
//    if (length <= 0) return -1;
//    sum += x[0];
//    return sumOverThreshold(x + 1, length - 1, threshold, sum);
//}
//
//int main() {
//    int x[3] = {1, 14, 80};
//    assert(sumOverThreshold(x, 3, 14, 0) == 15);
//    assert(sumOverThreshold(x, 3, 10000, 0) == -1);
//    assert(sumOverThreshold(x, 3, 0, 0) == 1);
//    cout << "sumOverThreshold success" << endl;
//}

// Worksheet 4 Problem 1 - Write a function that removes all odd-sum-lists from a set
//
//int deleteOddSumLists(set<list<int>*>& s) {
//    int num = 0;
//    for (set<list<int>*>::iterator p = s.begin(); p != s.end(); p++) {
//        int sum = 0;
//        for (list<int>::iterator q = (*p)->begin(); q != (*p)->end(); q++) { // check for sums
//            sum += *q;
//        }
//        if (sum % 2 == 1) { // erase and reiterate if odd sum
//            s.erase(*p);
//            p--;
//        }
//    }
//    return num;
//}
//
//int main() {
//    list<int> a; list<int> b; list<int> c; list<int> d; list<int> e;
//    list<int>* l1 = &a; list<int>* l2 = &b; list<int>* l3 = &c; list<int>* l4 = &d; list<int>* l5 = &e;
//    l1->push_back(1); l2->push_back(2); l3->push_back(3); l4->push_back(4); l5->push_back(5);
//    set<list<int>*> s;
//    s.insert(l1); s.insert(l2); s.insert(l3); s.insert(l4); s.insert(l5);
//    deleteOddSumLists(s);
//    for (set<list<int>*>::iterator p = s.begin(); p != s.end(); p++) {
//        cout << (*p)->front() << endl; // should print 4 2
//    }
//}

// Worksheet 4 Problem 2 - Find the 3 errors
//
//class Potato {
//public:
//    Potato(int in_size) : size(in_size) {}
//    int getSize() const { return size; }
//private:
//    int size;
//};
//
//int main() {
//    set<Potato> potatoes; // set requires Potato to have a user defined > operator
//    Potato p1(3);
//    Potato p2(4);
//    Potato p3(5);
//    potatoes.insert(p1);
//    potatoes.insert(p2);
//    potatoes.insert(p3);
//    set<Potato>::iterator it = potatoes.begin();
//    while (it != potatoes.end()) {
//        it = potatoes.erase(it);; // erase must reassign the iterator
//    }
//    for (it = potatoes.begin(); it != potatoes.end(); it++) {
//        cout << (*it).getSize() << endl; // it needs to be the value at the iterator, not the iterator itself
//    }
//}

// Worksheet 4 Problem 3 - Remove all 0s from a list and a vector
//
//void removeAllZeroes(list<int>& x) {
//    for (list<int>::iterator p = x.begin(); p != x.end();) { // iterate through the list
//        if (*p == 0) p = x.erase(p); // erase 0s and reassign iterator
//        else p++;
//    }
//}
//
//void removeAllZeroes(vector<int>& x) {
//    for (vector<int>::iterator p = x.begin(); p != x.end();) {
//        if (*p == 0) p = x.erase(p);
//        else p++;
//    }
//}
//
//int main() {
//    list<int> l;
//    l.push_back(1); l.push_back(0); l.push_back(0); l.push_back(1); l.push_back(0);
//    vector<int> v;
//    v.push_back(1); v.push_back(0); v.push_back(0); v.push_back(1); v.push_back(0);
//    removeAllZeroes(l);
//    removeAllZeroes(v);
//    for (list<int>::iterator p = l.begin(); p != l.end(); p++) {
//        cout << *p << endl; // should print 1 1
//    }
//    for (vector<int>::iterator p = v.begin(); p != v.end(); p++) {
//        cout << *p << endl; // should print 1 1
//    }
//}

// Worksheet 4 Problem 6 - Use a template to implement a Stack class using a linked list
//
//template<typename T>
//
//class Stack {
//public:
//    Stack();
//    ~Stack();
//    void push(T x);
//    void pop();
//    T top();
//    bool isEmpty();
//private:
//    struct Node {
//        T data;
//        Node* next;
//    };
//    Node* m_head;
//};
//
//template<typename T>
//Stack<T>::Stack() {
//    m_head == nullptr;
//}
//
//template<typename T>
//Stack<T>::~Stack() {
//    for (Node* ptr = m_head; ptr != nullptr; ptr = m_head) {
//        m_head = m_head->next;
//        delete ptr;
//    }
//}
//
//template<typename T>
//void Stack<T>::push(T x) {
//    Node* newNode = new Node;
//    newNode->data = x;
//    if (m_head == nullptr) {
//        newNode->next = nullptr;
//    } else {
//        newNode->next = m_head->next;
//    }
//    m_head = newNode;
//}
//
//template<typename T>
//void Stack<T>::pop() {
//    if (m_head == nullptr) return;
//    Node* ptr = m_head;
//    m_head = m_head->next;
//    delete ptr;
//}
//
//template<typename T>
//T Stack<T>::top() {
//    return m_head->data;
//}
//
//template<typename T>
//bool Stack<T>::isEmpty() {
//    return m_head == nullptr;
//}
//
//int main() {
//    cout << "I compile" << endl;
//}

// Worksheet 4 Problem 7 - Use a template to implement a Vector class
//
//template<typename T>
//
//class Vector {
//public:
//    Vector();
//    ~Vector();
//    void push_back(T x);
//private:
//    int m_size;
//    int m_capacity;
//    T* m_arr[];
//};
//
//template<typename T>
//Vector<T>::Vector() : m_size(0), m_capacity(10) {
//    m_arr = new T[10];
//}
//
//template<typename T>
//Vector<T>::~Vector() {
//    delete [] m_arr;
//}
//
//template<typename T>
//void Vector<T>::push_back(T x) {
//    if (m_size == m_capacity) { // reallocate a larger array
//        T* temp = new T[m_capacity + 10];
//        for (int i = 0; i < m_capacity; i++) {
//            temp[i] = m_arr[i];
//        }
//        delete m_arr;
//        m_arr = temp;
//    }
//    m_arr[m_size] = x;
//    m_size++;
//}
//
//int main() {
//    cout << "I compile" << endl;
//}

// Worksheet 5 Problem 6
//
//void sort(int arr[], int n) {
//    int counts[100] = {}; // need to initialize as empty array
//    for (int i = 0; i < n; i++) { // count occurences of each number in the given array
//        counts[arr[i] - 1]++;
//    }
//    int index = 0;
//    for (int i = 0; i < 100; i++) { // replace original array values with number found in earlier step
//        for (; counts[i] > 0; counts[i]--, index++) {
//            arr[index] = i + 1;
//        }
//    }
//}
//
//int main() {
//    int test[100];
//    for (int i = 100; i > 0; i--) {
//        test[100 - i] = i;
//    }
//    sort(test, 100);
//    for (int i = 0; i < 100; i++) {
//        cout << test[i] << endl;
//    }
//}

// Worksheet 6 Problem 1 - Use a hash table to print out all numbers in a given range that are not in a given array
//
//void inRange(int arr[], int size, int low, int high) {
//    int numBuckets = high - low + 1;
//    list<int>* hashTable = new list<int>[numBuckets]; // create hash table with desired number of buckets
//    for (int i = 0; i < size; i++) {
//        if (arr[i] - low >= 0 && arr[i] - low < numBuckets) // loop thru the array
//            hashTable[arr[i] - low].push_back(0); // set all buckets that the array contains to have a value
//    }
//    string output; // initialize output string
//    for (int i = 0; i < numBuckets; i++) {
//        if (hashTable[i].empty()) {
//            output += to_string(i + low); // create string
//            output += ", ";
//        }
//    }
//    cout << output.substr(0, output.size() - 2) << endl; // cut off the extra comma
//    delete [] hashTable; // clean up
//}
//
//int main() {
//    int arr1[4] = {10, 12, 11, 15};
//    inRange(arr1, 4, 10, 15); // should print 13, 14
//    int arr2[5] = {1, 14, 11, 51, 55};
//    inRange(arr2, 5, 50, 55); // should print 50, 52, 53, 54
//}

// Worksheet 6 Problem 2 - Given an input array, find if 2 numbers in the array can be summed to reach a target number (must be O(N))
//
//bool twoSum(int arr[], int n, int target) {
//    list<int>* hashTable = new list<int>[n]; // create hash table using array size as number of buckets
//    for (int i = 0; i < n; i++) { // O(N)
//        int temp = arr[i] % n; // hash
//        hashTable[temp].push_back(arr[i]); // insert into hash table
//    }
//    for (int i = 0; i < n; i++) { // O(N)
//        int desiredVal = target - arr[i]; // get value that is needed to reach sum for each value in the array
//        int bucketNum = desiredVal % n; // get hash of desiredVal
//        for (auto iter = hashTable[bucketNum].begin(); iter != hashTable[bucketNum].end(); iter++) { // loop thru the selected bucket, O(1)
//            if (*iter == desiredVal) return true; // value found
//        }
//    }
//    delete [] hashTable;
//    return false;
//}
//
//int main() {
//    int arr1[7] = {4, 8, 3, 7, 9, 2, 5};
//    int arr2[5] = {1, 3, 5, 2, 4};
//    assert(twoSum(arr1, 7, 15)); // should return true (8 + 7 = 15)
//    assert(twoSum(arr2, 5, 10)); // should return false
//    cout << "twoSum success" << endl;
//}

// Worksheet 6 Problem 3 - Given a vector of strings, group anagrams together (lowercase letters only)
//
//int calculateHash(string word) { // given hash function
//    int primes[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
//    int hashVal = 1;
//    for (int i = 0; i < word.size(); i++) // multiplying by prime numbers ensures that all words with the same characters will have the same product
//        hashVal *= primes[word[i]-'a'];
//    return hashVal;
//}
//
//vector<vector<string>> groupAnagrams(vector<string> strs) {
//    list<string>* hashTable = new list<string>[strs.size()]; // make hash table with given vector size as number of buckets
//    for (int i = 0; i < strs.size(); i++) { // loop thru vector
//        int bucketNum = calculateHash(strs[i]) % strs.size(); // hash and insert into hash table
//        hashTable[bucketNum].push_back(strs[i]);
//    }
//    vector<vector<string>> result;
//    for (int i = 0; i < strs.size(); i++) { // loop thru hash table
//        if (!hashTable[i].empty()) { // if bucket has contents
//            vector<string> temp;
//            for (auto iter = hashTable[i].begin(); iter != hashTable[i].end(); iter++) // pushes all strings in a given bucket into an inner vector
//                temp.push_back(*iter);
//            result.push_back(temp); // pushes the inner vector into the outer vector
//        }
//    }
//    delete [] hashTable;
//    return result;
//}
//
//int main() {
//    vector<string> v = {"eat", "tea", "tan", "ate", "nat", "bat"};
//    vector<vector<string>> result = groupAnagrams(v);
//    for (int i = 0 ; i < result.size(); i++) { // should print [ate eat tea] [nat tan] [bat] (order doesn't matter)
//        for (int j = 0; j < result[i].size(); j++)
//            cout << result[i][j] << " ";
//        cout << endl;
//    }
//}

// Worksheet 6 Problem 4 - Given a string, use a hash table to find the first character in it that only appears once
//
//int firstUniqueChar(string s) {
//    list<char> hashTable[26]; // make a hash table with enough buckets to account for all letters
//    for (int i = 0; i < s.size(); i++) // loop thru all chars
//        hashTable[s[i] - 'a'].push_back(s[i]); // hash each char
//    for (int i = 0; i < s.size(); i++) { // loop thru string
//        if (hashTable[s[i] - 'a'].size() == 1) // if char is unique
//            return i;
//    }
//    return -1;
//}
//
//int main() {
//    string s1 = "leetcode";
//    string s2 = "loveleetcode";
//    string s3 = "oo";
//    assert(firstUniqueChar(s1) == 0);
//    assert(firstUniqueChar(s2) == 2);
//    assert(firstUniqueChar(s3) == -1);
//    cout << "firstUniqueChar success" << endl;
//}

// Worksheet 6 Problem 5 - Return whether or not an array represents a binary max heap
//
//bool isMaxHeap(int* arr, int len) {
//    for (int i = 0; i < len; i++) { // loop thru the array
//        int left = 2 * i + 1; // get the left index
//        int right = left + 1; // get the right index
//        if (left < len && arr[left] > arr[i]) // left is greater than parent
//            return false;
//        if (right < len && arr[right] > arr[i]) // right is greater than parent
//            return false;
//    }
//    return true;
//}
//
//int main() {
//    int heap[10] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
//    int notHeap[5] = {4, 15, 6, 7, 3};
//    assert(isMaxHeap(heap, 10));
//    assert(!isMaxHeap(notHeap, 5));
//    cout << "isMaxHeap success" << endl;
//}

// Worksheet 6 Problem 6 - Given the head of a binary tree, return whether or not it represents a min heap
//
//struct Node { // given struct
//    int val;
//    Node* left;
//    Node* right;
//};
//
//Node constructNode(int value, Node* l, Node* r) { // for testing
//    Node temp;
//    temp.val = value;
//    temp.left = l;
//    temp.right = r;
//    return temp;
//}
//
//bool isMinHeap(Node* head) {
//    if (head == nullptr) return true; // base case
//    if (head->left == nullptr && head->right != nullptr) return false; // completeness unsatisfied
//    if (head->left != nullptr && head->left->val < head->val) return false; // left node doesn't satisfy min heap
//    if (head->right != nullptr && head->right->val < head->val) return false; // right node doesn't satisfy min heap
//    return (isMinHeap(head->left) && isMinHeap(head->right));
//}
//
//int main() {
//    Node n6 = constructNode(8, nullptr, nullptr);
//    Node n5 = constructNode(9, nullptr, nullptr);
//    Node n4 = constructNode(5, nullptr, nullptr);
//    Node n3 = constructNode(6, &n6, nullptr);
//    Node n2 = constructNode(3, &n4, &n5);
//    Node n1 = constructNode(1, &n2, &n3);
//    assert(isMinHeap(&n1));
//    cout << "isMinHeap success" << endl;
//}

// Worksheet 6 Problem 7 - Use a given array to construct a binary max heap
//
//struct Node {
//    int val;
//    Node* left;
//    Node* right;
//};
//
//Node* helperFunc(int a[], int n, int i) { // helper function for recursive calls
//    if (i >= n) return nullptr; // end of array
//    Node* root = new Node;
//    root->val = a[i];
//    root->left = helperFunc(a, n, 2 * i + 1); // get correct position of left/right nodes
//    root->right = helperFunc(a, n, 2 * i + 2);
//    return root;
//}
//
//Node* makeMaxHeap(int a[], int n) {
//    return helperFunc(a, n, 0);
//}
//
//int main() {
//    int maxHeap[10] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
//    Node* root = makeMaxHeap(maxHeap, 10);
//    assert(root->val == 16);
//    assert(root->left->val == 14);
//    assert(root->right->right->val == 3);
//    assert(root->right->right->right == nullptr);
//    cout << "makeMaxHeap success" << endl;
//}

// Worksheet 6 Problem 8 - Given an array, return if there are exactly 3 elements in the array that add up to 0
//
//bool sum3(const int* arr, int n) {
//    unordered_set<int> hashTable; // create hash table
//    for (int i = 0; i < n; i++) // 0(N)
//        hashTable.insert(arr[i]);
//    for (int i = 0; i < n; i++) { // O(N^2)
//        for (int j = i + 1; j < n; j++) { // O(N)
//            int targetNum = (arr[i] + arr[j]) * -1;
//            if (targetNum != arr[i] && targetNum != arr[j] && hashTable.find(targetNum) != hashTable.end()) // if if in hash table and not one of the current test values
//                return true;
//        }
//    }
//    return false;
//}
//
//int main() {
//    int arr1[6] = {1, 2, 3, 4, 5, 6};
//    int arr2[4] = {1, -1, 2, -2};
//    int arr3[5] = {1, 2, -3, 6, 8};
//    assert(!sum3(arr1, 6));
//    assert(!sum3(arr2, 4));
//    assert(sum3(arr3, 5));
//    cout << "sum3 success" << endl;
//}

// Worksheet 6 Problem 9 - Create the Bank class with O(N) search/insertion
//class Bank {
//public:
//    void insert(int amount, int userId, int accountId);
//    int search(int userId, int accountId);
//private:
//    unordered_map<int, unordered_map<int, int>> outerMap;
//};
//
//void Bank::insert(int amount, int userId, int accountId) {
//    auto user = outerMap.find(userId);
//    if (user != outerMap.end()) { // if user already in map
//        auto account = user->second;
//        account.insert({accountId, amount});
//        outerMap[userId] = account;
//    } else {
//        unordered_map<int, int> innerMap;
//        innerMap.insert({accountId, amount});
//        outerMap.insert({userId, innerMap});
//    }
//}
//
//int Bank::search(int userId, int accountId) {
//    auto user = outerMap.find(userId);
//    if (user == outerMap.end()) return -1; // user id not found in map
//    unordered_map<int, int> innerMap = user->second; // get the hash table of accounts
//    auto account = innerMap.find(accountId);
//    if (account != innerMap.end()) return account->second;
//    else return -1; // account not found in map
//}
//
//int main() {
//    Bank B;
//    B.insert(10, 765, 937);
//    assert(B.search(765, 937) == 10);
//    cout << "Bank success" << endl;
//}

// Worksheet 6 Problem 10 - Write a function that takes in a list of flights and prints the travel itinerary
//
//void travelItinerary(map<string, string> tickets) {
//    unordered_map<string, string> revMap;
//    for (auto iter = tickets.begin(); iter != tickets.end(); iter++) // make reverse map
//        revMap[iter->second] = iter->first;
//    string start;
//    for (auto iter = tickets.begin(); iter != tickets.end(); iter++) { // find the start of the flight path
//        if (revMap.find(iter->first) == revMap.end()) {
//            start = iter->first;
//            break;
//        }
//    }
//    for (auto iter = tickets.find(start); iter != tickets.end(); iter = tickets.find(iter->second)) { // loop thru tickets in order
//        cout << iter->first << " --> " << iter->second << endl;
//    }
//}
//
//int main() {
//    map<string, string> map;
//    map["Bali"] = "Tokyo";
//    map["London"] = "Bangkok";
//    map["Dubai"] = "Bali";
//    map["Bangkok"] = "Dubai";
//    travelItinerary(map); // should print London --> Bangkok, Bangkok --> Dubai, Dubai --> Bali, Bali --> Tokyo
//}

// Worksheet 6 Problem 11 - Check if a linked list has a cycle in it
//
//struct Node { // given
//    int val;
//    Node* next;
//};
//
//bool hasCycle(Node* head) {
//    unordered_set<Node*> visited;
//    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
//        if (visited.find(ptr) != visited.end()) // if already in map
//            return true;
//        else // put new Node into map
//            visited.insert(ptr);
//    }
//    return false;
//}
//
//int main() {
//    Node n1;
//    Node n2;
//    Node n3;
//    n1.next = &n2;
//    n2.next = &n3;
//    n3.next = &n1;
//    assert(hasCycle(&n1));
//    n3.next = nullptr;
//    assert(!hasCycle(&n1));
//    cout << "hasCycle success" << endl;
//}

// Worksheet 7 Problem 1 - Find if a number is in a tree
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//bool treeContains(Node* head, int n) {
//    if (head == nullptr) return false; // end of tree path
//    if (head->val == n) return true; // value found
//    return (treeContains(head->left, n) || treeContains(head->right, n)); // check left and right subtrees, if in either (or), function returns true
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5;
//    n1.nodeConstruct(1, &n2, &n3);
//    n2.nodeConstruct(2, nullptr, &n4);
//    n3.nodeConstruct(3, &n5, nullptr);
//    n4.nodeConstruct(4, nullptr, nullptr);
//    n5.nodeConstruct(5, nullptr, nullptr);
//    assert(treeContains(&n1, 3) && treeContains(&n1, 4) && !treeContains(&n1, 6));
//    cout << "treeContains success" << endl;
//}

// Worksheet 7 Problem 2 - Reverse the tree using recursion
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//void reverse(Node* root) {
//    if (root == nullptr) return; // base case
//    Node* temp = root->left; // swap left and right pointers
//    root->left = root->right;
//    root->right = temp;
//    reverse(root->left); // recursive call with the left subtree and right subtree
//    reverse(root->right);
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5, n6, n7;
//    n1.nodeConstruct(5, &n2, &n3);
//    n2.nodeConstruct(2, &n4, &n5);
//    n3.nodeConstruct(7, &n6, &n7);
//    n4.nodeConstruct(1, nullptr, nullptr);
//    n5.nodeConstruct(3, nullptr, nullptr);
//    n6.nodeConstruct(4, nullptr, nullptr);
//    n7.nodeConstruct(6, nullptr, nullptr);
//    reverse(&n1);
//    assert(n1.val == 5 && n1.left->val == 7 && n1.right->val == 2);
//    assert(n1.left->left->val == 6 && n1.left->right->val == 4);
//    assert(n1.right->left->val == 3 && n1.right->right->val == 1);
//    cout << "reverse success" << endl;
//}

// Worksheet 7 Problem 3 - Count the number of leaves in a tree (not binary)
//
//struct Node { // given
//    int val;
//    vector<Node*> children;
//};
//
//int countLeaves(Node* root) {
//    if (root == nullptr) return 0; // base case
//    int curLeafs = 0;
//    for (auto iter = root->children.begin(); iter != root->children.end(); iter++) { // find how many leaf nodes from current node
//        if (!(*iter)->children.empty()) // if not a leaf node
//            curLeafs += countLeaves(*iter); // count leaf nodes in child
//        else curLeafs++; // else increment current leaves
//    }
//    return curLeafs;
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12;
//    vector<Node*> v1; vector<Node*> v2; vector<Node*> v3; vector<Node*> v4;
//    v1.push_back(&n2); v1.push_back(&n3);
//    v2.push_back(&n4); v2.push_back(&n5); v2.push_back(&n6); v2.push_back(&n7);
//    v3.push_back(&n8); v3.push_back(&n9); v3.push_back(&n10);
//    v4.push_back(&n11); v4.push_back(&n12);
//    n1.children = v1; n2.children = v2; n3.children = v3; n4.children = v4;
//    assert(countLeaves(&n1) == 8);
//    cout << "countLeaves success" << endl;
//}

// Worksheet 7 Problem 4 - Print out a level-order traversal of the tree
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//int getHeight(Node* root) {
//    if (root == nullptr) return 0; // base case
//    int left = getHeight(root->left) + 1; // check height of left tree
//    int right = getHeight(root->right) + 1; // check height of right tree
//    if (left > right) return left; // return learger height
//    else return right;
//}
//
//void printLevel(Node* curr, int level) {
//    if (curr == nullptr) return;
//    if (level == 1) cout << curr->val << " "; // if leaf, print, current node first, then children
//    else { // print left and right
//        printLevel(curr->left, level - 1);
//        printLevel(curr->right, level - 1);
//    }
//}
//
//void levelOrder(Node* root) {
//    if (root == nullptr) return; // empty tree
//    int height = getHeight(root);
//    for (int i = 1; i <= height; i++) { // for the height of the tree
//        printLevel(root, i);
//        cout << endl; // enter between levels
//    }
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5, n6, n7, n8, n9;
//    n1.nodeConstruct(1, &n2, &n3);
//    n2.nodeConstruct(2, &n4, &n5);
//    n3.nodeConstruct(3, nullptr, &n6);
//    n4.nodeConstruct(4, &n7, &n8);
//    n5.nodeConstruct(5, &n9, nullptr);
//    n6.nodeConstruct(6, nullptr, nullptr);
//    n7.nodeConstruct(7, nullptr, nullptr);
//    n8.nodeConstruct(8, nullptr, nullptr);
//    n9.nodeConstruct(9, nullptr, nullptr);
//    levelOrder(&n1); // should print 1, 2 3, 4 5 6, 7 8 9
//}

// Worksheet 7 Problem 5 - Print out a level-order traversal of the tree using queues
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//void levelOrder(Node* root) {
//    if (root == nullptr) return; // edge case
//    queue<Node*> data;
//    data.push(root);
//    while (!data.empty()) {
//        size_t numNodes = data.size(); // tracks how many nodes in the current level
//        while (numNodes > 0) {
//            Node* cur = data.front();
//            data.pop(); // node evaluated
//            cout << cur->val << " "; // print data
//            if (cur->left != nullptr) data.push(cur->left); // push left child onto queue
//            if (cur->right != nullptr) data.push(cur->right); // push right child onto queue
//            numNodes--;
//        }
//        cout << endl; // return between levels
//    }
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5, n6, n7, n8, n9;
//    n1.nodeConstruct(1, &n2, &n3);
//    n2.nodeConstruct(2, &n4, &n5);
//    n3.nodeConstruct(3, nullptr, &n6);
//    n4.nodeConstruct(4, &n7, &n8);
//    n5.nodeConstruct(5, &n9, nullptr);
//    n6.nodeConstruct(6, nullptr, nullptr);
//    n7.nodeConstruct(7, nullptr, nullptr);
//    n8.nodeConstruct(8, nullptr, nullptr);
//    n9.nodeConstruct(9, nullptr, nullptr);
//    levelOrder(&n1); // should print 1, 2 3, 4 5 6, 7 8 9
//}

// Worksheet 7 Problem 6 - Implement the 3 main depth-first search traversals
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//void inOrderHelper(Node* root, vector<int>& vec) { // enables recursive implementation
//    if (root == nullptr) return; // base case
//    inOrderHelper(root->left, vec); // address the child on the left first
//    vec.push_back(root->val); // address current node
//    inOrderHelper(root->right, vec); // address the child on the right last
//}
//
//vector<int> inorderTraversal(Node* root) {
//    vector<int> v;
//    inOrderHelper(root, v); // build the vector
//    return v;
//}
//
//void preOrderHelper(Node* root, vector<int>& vec) { // enables recursive implementation
//    if (root == nullptr) return; // base case
//    vec.push_back(root->val); // address current node first
//    preOrderHelper(root->left, vec); // address the child on the left next
//    preOrderHelper(root->right, vec); // address the child on the right last
//}
//
//vector<int> preorderTraversal(Node* root) {
//    vector<int> v;
//    preOrderHelper(root, v); // build the vector
//    return v;
//}
//
//void postOrderHelper(Node* root, vector<int>& vec) { // enables recursive implementation
//    if (root == nullptr) return; // base case
//    postOrderHelper(root->left, vec); // address the child on the left first
//    postOrderHelper(root->right, vec); // address the child on the right next
//    vec.push_back(root->val); // address current node last
//}
//
//vector<int> postorderTraversal(Node* root) {
//    vector<int> v;
//    postOrderHelper(root, v); // build the vector
//    return v;
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5;
//    n1.nodeConstruct(1, &n2, &n3);
//    n2.nodeConstruct(2, &n4, &n5);
//    n3.nodeConstruct(3, nullptr, nullptr);
//    n4.nodeConstruct(4, nullptr, nullptr);
//    n5.nodeConstruct(5, nullptr, nullptr);
//    vector<int> inOrder = inorderTraversal(&n1);
//    vector<int> preOrder = preorderTraversal(&n1);
//    vector<int> postOrder = postorderTraversal(&n1);
//    for (int i = 0; i < 5; i++) // should print [4, 2, 5, 1, 3]
//        cout << inOrder[i] << " ";
//    cout << endl;
//    for (int i = 0; i < 5; i++) // should print [1, 2, 4, 5, 3]
//        cout << preOrder[i] << " ";
//    cout << endl;
//    for (int i = 0; i < 5; i++) // should print [4, 5, 2, 3, 1]
//        cout << postOrder[i] << " ";
//    cout << endl;
//}

// Worksheet 7 Problem 7 - Return all root to leaf paths in a binary tree
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//void rtlHelper(Node* root, vector<string>& vec, string cur) { // enables recursion
//    if (root == nullptr) return; // base case
//    if (root->left == nullptr && root->right == nullptr) { // at leaf node
//        vec.push_back(cur += to_string(root->val)); // push full path into vector
//        return;
//    }
//    cur += to_string(root->val) + "->"; // add current value and the arrow
//    rtlHelper(root->left, vec, cur); // continue with left subtree
//    rtlHelper(root->right, vec, cur); // continue with right subtree
//}
//
//vector<string> rootToLeaf(Node* head) {
//    vector<string> v; // initialize variables
//    string s = "";
//    rtlHelper(head, v, s);
//    return v;
//}
//
//int main() {
//    Node n1, n2, n3, n4;
//    n1.nodeConstruct(1, &n2, &n3);
//    n2.nodeConstruct(2, nullptr, &n4);
//    n3.nodeConstruct(3, nullptr, nullptr);
//    n4.nodeConstruct(5, nullptr, nullptr);
//    vector<string> v = rootToLeaf(&n1);
//    assert(v[0] == "1->2->5" && v[1] == "1->3");
//    cout << "rootToLeaf success" << endl;
//}

// Worksheet 7 Problem 8 - SKIPPED

// Worksheet 7 Problem 9 - Use recursion to determine if a tree is a subtree of another
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//bool isEqual(Node* n1, Node* n2) { // helper for further recursion
//    if (n1 == nullptr && n2 == nullptr) return true; // equal, but null
//    if (n1 == nullptr || n2 == nullptr) return false; // one is null, the other is not
//    return (n1->val == n2->val && isEqual(n1->left, n2->left) && isEqual(n1->right, n2->right)); // the values of the nodes are equal and their left/right subtrees are the same
//}
//
//bool isSubtree(Node* main, Node* potential) {
//    if (potential == nullptr) return true; // base case
//    if (main == nullptr) return false; // base case
//    if (isEqual(main, potential)) return true; // trees are equal
//    return (isSubtree(main->left, potential) || isSubtree(main->right, potential)); // rcheck main's left subtree and right subtree (terminates when subtrees no longer exist
//}
//
//int main() {
//    Node s1, s2, s3;
//    Node n1, n2, n3, n4, n5, n6;
//    s1.nodeConstruct(10, &s2, &s3);
//    s2.nodeConstruct(4, nullptr, nullptr);
//    s3.nodeConstruct(6, nullptr, nullptr);
//    n1.nodeConstruct(26, &n2, &n3);
//    n2.nodeConstruct(10, &n4, &n5);
//    n3.nodeConstruct(3, nullptr, &n6);
//    n4.nodeConstruct(4, nullptr, nullptr);
//    n5.nodeConstruct(6, nullptr, nullptr);
//    n6.nodeConstruct(17, nullptr, nullptr);
//    assert(isSubtree(&n1, &s1));
//    cout << "isSubtree success" << endl;
//}

// Worksheet 7 Problem 10 - Find the depth of a binary tree
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//int maxDepth(Node* root) {
//    if (root == nullptr) return -1; // edge case
//    if (root->left == nullptr && root->right == nullptr) return 1; // end of tree reached, accounts for original node
//    int leftDepth = maxDepth(root->left) + 1; // find depth of left subtree
//    int rightDepth = maxDepth(root->right) + 1; // find depth of right subtree
//    return leftDepth > rightDepth ? leftDepth : rightDepth; // return higher depth
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5, n6, n7, n8;
//    n1.nodeConstruct(1, &n2, &n3);
//    n2.nodeConstruct(4, &n4, &n5);
//    n3.nodeConstruct(8, &n6, &n7);
//    n4.nodeConstruct(2, &n8, nullptr);
//    n5.nodeConstruct(3, nullptr, nullptr);
//    n6.nodeConstruct(2, nullptr, nullptr);
//    n7.nodeConstruct(3, nullptr, nullptr);
//    n8.nodeConstruct(4, nullptr, nullptr);
//    assert(maxDepth(&n1) == 4);
//    cout << "maxDepth success" << endl;
//}

// Worksheet 7 Problem 11 - Find the value of the greatest path of a binary tree
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//int getGreatestPath(Node* head) {
//    if (head == nullptr) return 0; // edge case
//    int leftVal = getGreatestPath(head->left) + head->val; // get greatest value from left path
//    int rightVal = getGreatestPath(head->right) + head->val; // get greatest value from right path
//    return leftVal > rightVal ? leftVal : rightVal; // return the higher value
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5, n6, n7, n8;
//    n1.nodeConstruct(1, &n2, &n3);
//    n2.nodeConstruct(4, &n4, &n5);
//    n3.nodeConstruct(8, &n6, &n7);
//    n4.nodeConstruct(2, &n8, nullptr);
//    n5.nodeConstruct(3, nullptr, nullptr);
//    n6.nodeConstruct(2, nullptr, nullptr);
//    n7.nodeConstruct(3, nullptr, nullptr);
//    n8.nodeConstruct(4, nullptr, nullptr);
//    assert(getGreatestPath(&n1) == 12);
//    cout << "getGreatestPath success" << endl;
//}

// Worksheet 8 Problem 5a - Given a binary tree, return all root to leaf paths
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//void rtfHelper(Node* head, vector<string>& vec, string cur) { // enables recursion
//    if (head == nullptr) return; // edge case
//    if (head->left == nullptr && head->right == nullptr) { // leaf node found
//        vec.push_back(cur + to_string(head->val)); // insert last value into path
//        return;
//    }
//    rtfHelper(head->left, vec, cur + to_string(head->val) + "->"); // continue down left path
//    rtfHelper(head->right, vec, cur + to_string(head->val) + "->"); // continue down right path
//}
//
//vector<string> rootToLeaf(Node* head) {
//    vector<string> v;
//    rtfHelper(head, v, "");
//    return v;
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5;
//    n1.nodeConstruct(1, &n2, &n3);
//    n2.nodeConstruct(2, &n4, &n5);
//    n3.nodeConstruct(3, nullptr, nullptr);
//    n4.nodeConstruct(4, nullptr, nullptr);
//    n5.nodeConstruct(5, nullptr, nullptr);
//    vector<string> v = rootToLeaf(&n1);
//    assert(v[0] == "1->2->4" && v[1] == "1->2->5" && v[2] == "1->3");
//    cout << "rootToLeaf success" << endl;
//}

// Worksheet 8 Problem 10 - Determine if a given tree is in balance (should be < 30 lines of code)
//
//struct Node { // given
//    int val;
//    Node* left;
//    Node* right;
//    void nodeConstruct(int val, Node* left, Node* right);
//};
//
//void Node::nodeConstruct(int val, Node* left, Node* right) { // for testing
//    this->val = val;
//    this->left = left;
//    this->right = right;
//}
//
//bool balanceHelper(Node* root, int& sum) {
//    if (root == nullptr) { // base case
//        sum = 0;
//        return true;
//    }
//    int left = 0;
//    int right = 0;
//    if (balanceHelper(root->left, left) && balanceHelper(root->right, right)) { // if left/right subtrees are balances
//        if (left == right) { // if sums match
//            sum = left + right + root->val; // update sum
//            return true;
//        }
//    }
//    return false;
//}
//
//bool isInBalance(Node* root) {
//    int sum;
//    return balanceHelper(root, sum);
//}
//
//int main() {
//    Node n1, n2, n3, n4, n5, n6, n7, n8, n9;
//    n1.nodeConstruct(3, &n2, &n3);
//    n2.nodeConstruct(2, &n4, &n5);
//    n3.nodeConstruct(4, &n6, &n7);
//    n4.nodeConstruct(3, nullptr, nullptr);
//    n5.nodeConstruct(1, &n8, &n9);
//    n6.nodeConstruct(2, nullptr, nullptr);
//    n7.nodeConstruct(2, nullptr, nullptr);
//    n8.nodeConstruct(1, nullptr, nullptr);
//    n9.nodeConstruct(1, nullptr, nullptr);
//    assert(isInBalance(&n1));
//    cout << "isInBalance success" << endl;
//}
