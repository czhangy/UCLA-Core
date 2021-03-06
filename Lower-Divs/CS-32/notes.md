# COM SCI 32 - Winter '20 - Smallberg

## **1/6: Introduction**

- Start early, develop incrementally

    ```c++
    #include <iostream>
    #include <cstdlib>
    #include <cmath>
    using namespace std;

    const double PI = 4 * atan(1.0);

    class Circle {
        public:
            Circle(double x, double y, double r);
            void scale(double factor);
            void draw() const;
            double radius() const;
        private: // Class Invariants: m_r > 0
            double m_x;
            double m_y;
            double m_r;
    };

    double area(const Circle& x);

    Circle::Circle(double x, double y, double r) : m_x(x), m_y(y), m_r(r)) { // Member initialization list
        if (r <= 0) {
            cout << "Cannot create circle with radius " << r << endl;
            exit(1);
        }
    }

    bool Circle::scale(double factor) {
        if (factor <= 0) {
            return false;
        }
        m_r *= factor;
        return true;
    }

    void Circle::draw() const {
        // Code to draw the circle
    }

    double Circle::radius() const {
        return m_r;
    }

    double area(const Circle& x) {
        return PI * x.radius() * x.radius();
    }

    int main() { // Guaranteed to return 0 if no number specified
        Circle blah(8, -3, 3.7);
        Circle c(2, -5, 10);
        c.scale(2);
        c.draw();
        cout << area(c) << endl;
        cout << c.radius() << endl;
        // Other code
        double ff;
        cin >> ff;
        if (!c.scale(ff)) {
            // Error
        }
    }
    ```

- Interface (what we can do) vs. Implementation (how do we do it)

## **1/8: Linking**

- `myapp.cpp`:

    ```c++
    #include <iostream>
    using namespace std;

    void f(double x); // Needed to declare
    int main() { // Defines main
        double a = 3;
        f(a);
        cout << a;
    } // Needs f, cout, <<
    ```

- `stuff.cpp`:

    ```c++
    #include <cmath>
    using namespace std;

    void f(double x) { // Defines f
        // Other code
        sin(x)
        // Other code
    } // Needs sin
    ```

- Libraries - collections of object files with code for library functions
  - Defines `sin`, `cos`, `exponential`, `cout`, `cin`, `>>`, `<<`, etc.
  - Needs nothing
- Object files combine with libraries to create an executable file
  - Object file → executable is called the linker
- Nothing can be defined more than once → linker error
- Every need must be satisfied by some definition
- There must be exactly one main routine
- Convention - 2 files per C++ class
- `myapp.cpp`:

    ```c++
    #include "circle.h"

    int main() {
        Circle c(-2, 5, 10);
        c.draw();
    }
    ```

- `circle.h`:
  
    ```c++
    class Circle { // Class declaration
        public:
            Circle(/* Parameters */);
            void draw() const;
        private:
            double m_x;
    };

    double area(Circle x);
    ```

- `circle.cpp`:

    ```c++
    #include "circle.h"
    #include <cmath>
    using namespace std;

    // Implementation
    Circle::Circle(/* Parameters */) : /* Member initialization list */ {
        // Other code
    }

    Circle::void draw() const {
        // Other code
    }

    double area(Circle x) {
        // Other code
    }
    ```

- `-o myapp myapp.cpp stuff.cpp` (no header files listed)
- Don't `#include *.cpp`

## **1/13: Steps of Construction and Resource Management**

- Steps of construction:
  - *Something here*
  - Construct the data members, using the member initialization list; if a member is not listed:
    - If a data member is of a built in type, it is left uninitialized
    - If a data member is of a class type, the default constructor is called for it; error if there is none
      - If you declare no constructor for a class, the compiler writes a default constructor for you
  - Execute the body of the constructor

    ```c++
    class Circle {
        public:
            Circle(double x, double y, double r);
            // Other member functions
        private:
            double m_x;
            double m_y;
            double m_r;
    };

    Circle::Circle(double x, double y, double r) : m_x(x), m_y(y), m_r(r) {
        if (r <= 0) {
            cerr << "..." << endl;
            exit(1);
        }
    }

    class StickFigure {
        public:
            StickFigure(double bl, double headDiameter, string nm, double hx, double hy);
            // Other member functions
        private:
            string m_name;
            Circle m_head;
            double m_bodyLength;
    };

    StickFigure::StickFigure(double bl, double headDiameter, string nm, double hx, double hy) : m_name(nm), m_head(hx, hy, headDiameter/2), m_bodyLength(bl) {
    // Must have m_head in initialization list, since Circle has no default constructor, and will error out if in the body of the constructor
        if (bl <= 0) {
            cerr << "......" << endl;
            exit(1)
        }
    }
    ```

- Common to use member initialization lists to do as much of the initialization as possible

    ```c++
    void f(String t) {
        String u("Wow");
        // Other code
    }
    void h() {
        String s = "Hello";
        f(s); // Constructing a String using another String, needs a copy constructor
        // Other code
    }

    int main() {
        String t;
        for (/* Iteration bound */)
            h();
        // Other code
    }

    class String {
        public:
            String(const char* value = ""); // Makes value "" if there is no argument
            provided (default parameter value), only works for parameters at the end
            String(const String& other); // Copy constructor
            String& operator=(const String& rhs);
            ~String();
        private: // Class Invariants: m_text points to a dynamically allocated array of
            m_len+1 characters
            m_len >= 0
            m_text[m_len] == ‘\0'
            char* m_text;
            int m_len;
    };

    String::String(const char* value) { // Do not repeat the default parameter value(s) here
        m_len = strlen(value);
        m_text = new char[m_len + 1]; // must dynamically allocate a new array to avoid changing the original array
        strcpy(m_text, value);
    }

    String::String(const String& other) {
        m_len = other.m_len; // Allowed
        m_text = new char [m_len+1];
        strcpy(m_text, other.m_text)
    }

    String& String::operator=(const String& rhs) { // by convention, this returns the new value of the left hand side, return a reference to the object
        delete [] m_text;
        m_len = rhs.m_len;
        m_text = new char[m_len+1];
        strcpy(m_text, rhs.m_text);
        return *this;
    }

    String::~String() { // Ensure all dynamically allocated objects are deleted when their local counterparts move out of scope
        delete [] m_text; // Make sure you match the form of delete to the form of new used (plain vs. array)
    }
    ```

## **1/15: Copy Constructors and Assignment Operators**

- If you don't declare a copy constructor for a type, the compiler writes one for you
  - This copy constructor is made by copying all of the members
  - Creates problems with pointers:
    - Changing a value being pointed to inside a function that uses a copy also changes the original object
    - When other functions return, the destructor is called, and the value being pointed at is destructed
- If you write a destructor for a class, you likely have to write a copy constructor and assignment operator too
- Ok for any member functions to access private members of other objects of that class
- The copy constructor cannot be passed by value, as passing by value uses the copy constructor
- Assignment is not the same as the copy constructor

## **1/17: Discussion 1**

- [LeetCode](https://leetcode.com/)
- Dynamic Memory Allocation
  - Static memory allocation is inflexible
  - Assigns memory when compiling
  - `new` will automatically allocate the sequential memory space for the requested data type and size and return the starting address of the allocated memory space
  - Variables allocated with `new` will remain in the memory until deleted with `delete`
  - Dynamically allocated objects do not get deleted by the default destructor
- Copy Constructors

    ```c++
    School::School(const School &aSchool) {
        m_name = aSchool.m_name;
        m_numStudents = aSchool.m_numStudents;
        m_students = new Students[m_numStudents]
        for (int i = 0; i < m_numStudents; i++)
            m_students[i] = aSchool.m_students[i];
    }
    ```

- Assignment Operator

    ```c++
    School& School::operator=(const School &aSchool) {
        if (this != &aSchool) {
            m_name = aSchool.m_name;
            m_numStudents = aSchool.m_numStudents;
            delete [] m_students;
            m_students = new m_students[m_numStudents]
            for (int i = 0; i < m_numStudents; i++)
                m_students[i] = aSchool.m_students[i];
        }
        return *this;
    }
    ```

## **1/22: Linked Lists**

- Arrays limited by methods of resizing and inserting items into the middle of the array

    ```c++
    struct Node {
        int value;
        Node* next;
    };

    Node* head;
    Node* ptr = head
    while (ptr != nullptr) {
        cout << ptr->value << endl;
        ptr = ptr->next;
    }
    for (Node* p = head; p != nullptr; p = p->next) {
        cout << p->value << endl;
    }
    ```

- Usually preceded by a pointer (`head`) to the first element of the list
- Square bracket operators not valid
- When following a pointer, make sure it has previously been given a value and make sure that `p` is not the `nullptr`

    ```c++
    Node* p;
    for (p = head; p != nullptr && p->value != 42; p = p->next) // Evaluate left to right
        ;
    if (p != nullptr) {
        cout << p->value << endl;
    } else {
        cout << "There's no 42" << endl;
    }
    ```

    ```c++
    Node* p;
    for (p = head; p != nullptr && p->value != 42; p = p->next)
        ;
    if (p != nullptr) {
        Node* newGuy = new Node
        newGuy->value = 37;
        newGuy->next = p->next;
        p->next = newGuy; // Order matters, set new node's values first
    }
    ```

## **1/24: Linked Lists and Aliasing**

- Check normal case (middle), empty list, and boundary cases (first and last)

    ```c++
    struct Node { // Doubly linked list
        int value;
        Node* next;
        Node* prev;
    }
    ```

    ```c++
    void transfer(Account& from, Account& to, double amt) {
        if (&from != &to) {
            if (from.balance >= amt) {
                from.debit(amt);
                to.credit(amt);
                if (amt >= 10000) {
                    fileForm();
                }
            } else {
                cout << "Message" << endl;
            }
        }
    }
    ```

## **1/27: Stacks and Queues**

- Stack/LIFO:
  - Create an empty `stack`
  - Push an item onto the `stack`
  - Pop an item from the `stack`, undefined on an empty `stack`
    - The top of the `stack` keeps the same position
  - Look at the top item in the `stack`, undefined on an empty `stack`
  - Is the `stack` empty?
  - Maybe:
    - How many items are in the `stack` (C++ has)
    - Look at any item in the `stack` (C++ doesn't have)

    ```c++
    #include <stack>
    using namespace std;

    int main() {
        stack<int> s;
        s.push(10);
        s.push(20); // Adds 20 to top of stack
        int n = s.top() // Returns the top item of the stack
        s.pop(); // Removes the top item of the stack, no return value
        if (!s.empty()) // Asks if the stack is empty
            cout << s.size() << endl;
    }
    ```

- Using a `stack` signifies that you are only using the top element
- Queue/FIFO:
  - Has a front/head and back/tail, 2 active ends
  - Create an empty `queue`
  - Enqueue an item (put it in the `queue`), can fail if there is a limited capacity
  - Dequeue an item (remove it from the `queue`), can fail if the `queue` is empty
  - Look at the front item in the `queue`
  - Is the `queue` empty?
  - Maybe:
    - How many items are in the `queue`?
    - Look at any item in the `queue`?

    ```c++
    #include <queue>
    using namespace std

    int main() {
        queue<int> q;
        q.push(10); // Enqueues item
        q.push(20);
        int n = q.front(); // n is 10
        q.pop();
        if(!q.empty())
        cout << q.size() << endl;
        cout << q.back() << endl;
    }
    ```

- Queues and stacks have no limited capacity in C++
- String → numerical operations
  - Convert infix to postfix
    - If you hit an operand you append it to the result sequence
    - If you hit an operator and the operator `stack` is empty, push it onto the `stack`
      - Else if the top of the `stack` is an open parenthesis, push the operator
      - Else if the precedence of the current operator is greater than the operator at the top of the `stack`, push it
      - Else pop the top of the `stack`, appending it to the result sequence, and check again
    - Open parenthesis: always push
    - Close parenthesis: while top of `stack` is not an open parenthesis (operator) pop it and append it to the result sequence
      - Pop the open parenthesis
    - At end, pop each operator and append it to the sequence
  - Push operands onto a `stack`
    - When you hit an operator, you pop the operands and then push the result onto the `stack`

## **1/29: Inheritance**

- Linked List vs. Array implementation of stacks
  - Harder to expand capacity with the array version
  - The array version takes up less memory
  - List version takes part in a lot of allocations and deallocations
- Linked List vs. Array implementation of queues
  - Use a doubly linked list for list implementation
  - Array:
    - Head and a tail (1 past the last element)
      - Number of items in `queue` is tail - head
    - When hit end of array, you can shift everything back to the beginning of the array
      - Downside if there are a lot of items constantly, many shifts
      - Can also wrap around to beginning of array - circular array
        - Head = tail if the list is empty or full
        - Make a size variable
  - Lists are easier when implemented as a doubly linked list
- Circular doubly linked lists are better for when you need to be able to insert/remove anywhere
  - Every node was guaranteed to have a node before and after it
  - Not very beneficial for queue implementation
- Inheritance:

    ```c++
    class Circle {
        void move(double xnew, double ynew);
        void draw() const;
        double m_x;
        double m_y;
        double m_r;
    };

    class Rectangle {
        void move(double xnew, double ynew);
        void draw() const;
        double m_x;
        double m_y;
        double m_dx;
        double m_dy
    };

    void f(Circle& x) {
        x.move(10, 20);
        x.draw();
    }

    void f(Rectangle& x) {
        x.move(10, 20);
        x.draw();
    }

    int main() {
        Circle ca[100];
        Rectangle ra[100];
        for (/* Iteration bounds */)
            ca[i].draw();
        for (/* Iteration bounds */)
            ra[i].draw();
    }
    ```

- This code contains a lot of duplicate code, and adding new classes is tedious and error prone

    ```c++
    class Shape { // Shape is a superclass/base class of Circle and Rectangle
        void move(double xnew, double ynew);
        void draw() const;
        double m_x;
        double m_y;
    };

    class Circle : public Shape { // Circle and Rectangle are a subclass/derived classes of Shape
        void draw() const;
        double m_r;
    };

    class Rectangle : public Shape {
        void draw() const;
        double m_dx;
        double m_dy
    };

    void Shape::move(double xnew, double ynew) {
        m_x = xnew;
        m_y = ynew;
    }

    int main() {
        Shape* pic[100];
        pic[0] = new Circle; // If you have a pointer/reference of a derived type, it can be automatically converted to a pointer/reference of the base type
        pic[1] = new Rectangle;
        pic[2] = new Circle; // Heterogeneous collection
        for (int i = 0; i <...; i++) {
            pic[i]->draw();
        }
        Circle c;
        f(c); // x has to be another name for a Shape object
        c.move(30, 40); // Circle doesn't have a move function, compiler moves up and searches its base class
    }
    ```

## **1/31: Discussion 2**

- Linked Lists
  - Minimum:
    - Key component as unit: `Node` with a value and pointer to the next `Node`
    - Head pointer → points to the first term
    - Loop-free (except in circular linked list)
  - Regular Operations:
    - Insertion, Search, Removal
  - Pros and cons:
    - Efficient insertion, flexible memory allocation, simple implementation
      - Arrays have to occupy contiguous memory locations
    - High complexity of search
  - Insertion:
    - Steps: Create a new `Node`, make its next pointer point to the first item, make the `head` pointer point to the new `Node`
  - Search:
    - Steps: Find matching `Node` and return, if no match then return
  - Removal:
    - Remember to set the previous `Node`'s next pointer to point to the `Node` following the deleted `Node`
    - Consider what happens if the selected `Node` is the head or the last `Node` in the list
  - Suggestions:
  - Draw pictures and carefully trace through your code
  - Check any operations for the beginning of the list, end of the list, empty lists, and one-element lists
- Stack
  - FILO: First in, last out
  - A standard `stack` implementation:
    - `push()` and `pop()`
    - Other methods: `top()`, `count()`
  - Applications:
    - Stack memory: function call
    - Check expressions: matching brackets
    - Depth-first graph search
  - How do you implement `stack`s with linked lists?
    - `push()`: Insert `Node` before `head`
    - `pop()`: Remove `head` and return the `head` value
    - `top()`: Read `head` `Node`
    - `count()`: Maintain a private `int` data member to keep track
- Queue
  - FIFO: First in, first out
  - Basic methods:
    - `enqueue()`, `dequeue()`
    - `front()`, `back()`
    - `count()`
  - Applications:
    - Data streams
    - Process scheduling (DMV service request)
    - Breadth-first graph search
  - How to implement `queue` with linked lists?
- Suggestions on `stack`s and `queue`s
  - Draw pictures and carefully trace the code
  - Infix to postfix conversion is very important
  - `stack`s and `queue`s can be applied to trees/graphs
  - You can use the given Standard Template Library to implement `stack`s and `queue`s

## **2/3: Inheritance**

- Every derived object has a base object embedded in it
  - Base object is constructed first
- Calling a member function of a derived object in a function that takes a base object as the parameter will not compile
  - These kind of functions can only access functions that the base object can definitely access

  ```c++
  void Shape::draw() const {
      // Draw a cloud centered at (m_x, m_y) --> not the right implementation for derived objects
  }

  void Circle::draw() const {
      // Draw a circle of radius m_r centered at (m_x, m_y)
  }

  void f(Shape& x) {
      x.move(10, 20);
      x.draw();
  }
  ```

- Static binding vs. dynamic binding
  - Connecting the name and the function
  - Static binding - function decided in compile time - uses `Shape`'s `draw()`
    - C++ default
  - Dynamic binding - function decided in runtime - uses derived type's `draw()`
- Use `virtual` to make function dynamically bound

    ```c++
    class Shape {
        void move(double xnew, double ynew);
        virtual void draw() const;
        double m_x;
        double m_y;
    }

    Shape::move(/* Code */) // Calling the base class' function

    class Rectangle : public Shape {
        void draw() const;
        virtual double diag() const;
        double m_dx;
        double m_dy;
    }

    double Rectangle::diag() const {
        return sqrt(m_x*m_x + m_y*m_y);
    }

    class Shape {
        void move(double xnew, double ynew);
        virtual void draw() const = 0; // Function introduced as virtual, but not implemented, pure virtual function
        double m_x;
        double m_y;
    }
    ```

- You cannot create objects that have pure virtual functions
  - You can create pointers to these objects
  - If an object has at least one pure virtual function, it is an abstract class cannot be constructed
- Abstract classes still have objects, they are just never created by themselves

    ```c++
    class Shape {
        // Implementation
    };

    class Polygon : public Shape {
        ~Polygon() // Necessary for Polygon, not Shape
        Node* head;
        // Other implementation
    };

    int main() {
        Shape* sp;
        sp = new Polygon;
        delete sp; // calls the Shape destructor, not Polygon's, must declare Shape to have a virtual destructor (must also be implemented)
    }
    ```

- Destruction: 1) execute the body of the destructor, 2) destroy the data members, 3) destroy the base part
- If a class is designed to be a base class, declare and implement a virtual destructor for that class

    ```c++
    class Shape {
        public:
            Shape(double x, double y)
            // Other member functions
        private:
            double m_x;
            double m_y;
    };

    Shape::Shape(double x, double y) : m_x(x), m_y(y) {
        // Code
    }

    class Circle : public Shape {
        public:
            Circle(double x, double y, double r);
            // Other member functions
        private:
            double m_r;
    };

    Circle::Circle(double x, double y, double r) : m_x(x), m_y(y), m_r(r) {} // Doesn't compile, m_x and m_y are private members of Shape
    ```

- Construction: 1) construct the base part, 2) construct the data members, 3) execute the body of the constructor

    ```c++
    Circle::Circle(double x, double y, double r) : Shape(x, y), m_r(r) {} // Fixed
    ```

## **2/5: Recursion**

- Base cases: can be solved without making a recursive call
- Recursive cases: make one or more recursive calls for strictly smaller (closer to a base case) instances of the problem
- Verify there's at least one base case and that each recursive call works towards that base case

    ```c++
    int arr[5];
    // Other code
    sort(arr, 0, 5);

    void sort(int a[], int b, int e) { // Sort a[b] to a[e - 1]
        if (e - b > 1) {
            int mid = (b + e) / 2;
            sort(a, b, mid); // Sort left half
            sort(a, mid, e); // Sort right half
            merge(a, b, mid, e); // Merges sequences b → mid and mid → e that produces a sorted final array
        }
    }
    ```

- If tracing code, start tracing small, the problem should appear early on
- Divide and conquer - solve the problem by breaking it up (see above)
- The first and the rest - divide collection into first and the rest, then solve and combine
  - Sometimes more convenient to do last and the rest

  ```c++
  bool has(const int a[], int n, int target) {
      if (n <= 0) return false;
      if (a[0] == target) return true;
      return has(a + 1, n - 1, target)
  }
  ```

- When you have a function returning a `bool` using recursion above (returning the recursive call), make sure the `return` is not left off

    ```c++
    bool solve(start, goal) { // base cases: at the goal or surrounded by walls
        if (start == goal) return true;
        // Mark this position as visited
        // For each direction:
            // If moving one step in that direction is possible and hasn't been visited:
                // If (solve(pos reached by moving, goal) then return true
        // Return false
    }
    ```

## **2/10: Template Functions and Class Templates**

- Consider this:

    ```c++
    int minimum(int a, int b) {
        if (a < b) return a;
        else return b;
    }

    double minimum(double a, double b) { // Effectively the same code as the int minimum at the C++ language level
        if (a < b) return a;
        else return b;
    }

    int main() {
        int k;
        cin >> k;
        cout << minimum(k, 10) / 2;
        double x;
        // Other code
        double y = 3 * minimum(x * x, x + 10);
        // Other code
        int z = minimum(0, 3 * k - k + 4);
    }
    ```

    ```c++
    template<typename T> // Declare T to be used in template, T is now a placeholder for a typename
    T minimum(T a, T b) { // Both functions fit into this template
        if (a < b) return a;
        else return b;
    } // This function can replace both the int and double declarations above
    ```

- "Instantiate the template"
  - You have to match some template
  - The instantiated template compiles
  - The instantiated template has to do what you want
- You cannot mix types in the example above (passing an `int` and a `double` doesn't work)

    ```c++
    template<typename T1, typename T2>
    bool isEqualTo(T1 a, T2 b) { // This function can take 2 different types as parameters
        return a == b;
    }

    template<typename T1, typename T2>
    /* Type? */ minimum(T1 a, T2 b) { // No way to give a correct return type
        if (a < b) return a;
        else return b;
    }
    ```

- Conversions:
  - `bool` compared to `int`/`double` → `bool` converted to `int`/`double`
  - `int` compared to `double` → `int` converted to `double`

    ```c++
    Chicken c1, c2; // Some class Chicken
    minimum(c1, c2); // How do you compare 2 chickens? Fits template but probably won't compile
    ```

    ```c++
    char ca1[100];
    char ca2[100];
    char* ca3 = minimum(ca1, ca2); // minimum would compare the addresses of the pointers, not the values they point to --> will compile, wouldn't do what you want
    ```

- Given a function vs. a template for a function, the language will choose the function
- Passing by `const&` is common

```c++
template<typename T>
T sum(const T a[], int n) {
    T total = 0; // Won't compile with string call, no conversion between string and int,
                 // Solution: [BUILT_IN_TYPE]() gives the "default" value, change to T total = T();
    for (int k = 0; k < n; k++) {
        total += a[k];
    }
    return total;
}

int main() {
    double da[100];
    // Other code
    cout << sum(da, 100);
    // Other code
    string sa[10] = {"This ", "is ", "a ", "test."};
    string s = sum(sa, 4)
}
```

## **2/12: STL**

- `<vector>`
  - `push_back(n)` - adds an index to the `vector` that contains `n`
  - `pop_back()` - deletes the last index of the `vector`
  - `.size()`, `.front()`, `.back()` - same as `queue`s
  - `[]` - access elements, undefined for subscripts out of range
  - `.at()` - access elements, throws an exception for subscripts out of range
  - `vector<double> vd(10)` - 10 `double`s, each is `0.0`
  - `vector<string> vs(10, "Hello")` - 10 `string`s, each is `"Hello"`
  - `vector<int> vx(a, a+5)` - `vx.size()` is `5`, `v[0]` is `10`, etc.
  - `vector<int>::iterator q = vi.insert(p, 40);` - inserts `40` before `p`, returns iterator to new element
    - `vector::iterators` support using `+=`/`-=` `i`
  - `p = vi.erase(q);` - erases the value at `q`, returns iterator to new element in that spot
- `<list>`

    ```c++
    list<int> li;
    li.push_back(20);
    li.push_back(30);
    li.push_front(10);
    cout << li.size(); // Writes 3
    cout << li.front(); // Writes 10
    cout <<li.back(); // Writes 30
    li.push_front(40);
    li.pop_front();
    for (list<int>::iterator p = li.begin(); p != li.end(); p++)
    cout << *p << endl; // Writes 10 20 30
    list<double> ld(10); // ld.size() is 10, each element is 0.0
    vector<string> ls(10, "Hello"); // ls.size() is 10, each element is "Hello"
    vector<string> vs(ls.begin(), ls.end()); // vs.size() is 10, each element is "Hello"
    list<int>::iterator p = li.end();
    p--;
    p--;
    p += 2 ; // Won't compile
    list<int>::iterator q = li.insert(p, 40); // Inserts 40 before p, returns iterator to new element
    list<int>::iterator q = li.erase(p); // Erases element at p and using p is now undefined, returns iterator to element after
    ```

- `<set>`

    ```c++
    set<string> s;
    s.insert("Fred");
    s.insert("Ethel");
    s.insert("Fred");
    cout << s.size(); // 2
    s.insert("Desi");
    s.erase("Ethel");
    for(set<string>::iterator ptr = s.begin(); p!= s.end(); p++) {
        cout << *p << endl; // Prints using < (Desi is first)
    }
    ```

```c++
template<typename T>
T* find(T* b, T* e, const T& target) {
    for (; b != e; b++) {
        if (*b == target) break;
    }
    return b;
}

int main() {
    int a[5] = {10, 40, 50, 20, 30};
    int k;
    cin >> k;
    int* p = find(a, a + 5, k);
    if (p == a + 5)
        // Code for not found case
    else
        // Code for found case, p points to the 1st element with that value
    string sa[4] = {"Lucy", "Ricky", "Fred", "Ethel"};
    string* sp = find(sa, sa + 4, "Fred") // Won't compile, "Fred" is a pointer to a char[]
}
```

```c++
template<typename Iter, typename T>
Iter find(Iter b, Iter e, const T& target) {
    for (; b != e; b++) {
        if (*b == target) {
            break;
        }
    }
    return b;
}

int main() {
    int a[5] = {10, 40, 50, 20, 30};
    int k;
    cin >> k;
    int* p = find(a, a+5, k);
    if (p == a+5)
        // Code for not found case
    else
        // Code for found case, p points to the 1st element with that value
    list<string> ls;
    list<string>::iterator q = find(ls.begin(), ls.end(), "Fred");
    if (q == ls.end())
        // Code for not found case
    vector<int> vi;
    vector<int>::iterator r = find(vi.begin(), vi.begin() + 5, 42);
    if (r == vi.begin() + 5)
        // Code for not found case
}
```

```c++
template<typename Iter, typename Func>
Iter find_if(Iter b, Iter e, Func f) {
    for (; b != e; b++) {
        if (f(*b)) break;
    }
    return b;
}

bool isNegative(int k) {
    return k < 0;
}

bool isEmpty(string s) {
    return s.empty();
}

int main() {
vector<int> vi;
    // Other code
    vector<int>::iterator p = find_if(vi.begin(), vi.end(), isNegative); // Function name by itself acts as a pointer to the function
    if (p == vi.end())
        // Code for not found case
    list<string> ls;
    // Other code
    list<string>::iterator q = find_if(ls.begin(), ls.end(), isEmpty)
}
```

## **2/24: Big-O**

```c++
for (int i = 0; i < N; i++) { // O(N)
    c[i] = a[i] * b[i]; // O(1)
}
```

- Work from the inside out

```c++
for (int i = 0; i < N; i++) { // O(N^2)
    a[i] *= 2; // O(1)
    for (int j = 0; j < N; j++) { // O(N)
        d[i][j] = a[i] * c[j]; // O(1)
    }
}

for (int i = 0; i < N; i++0 { // O(N)
a[i] *= 2; // O(1)
    for (int j = 0; j < 100; j++) { // O(1) → still a constant, not reliant on N
        d[i][j] = a[i] * c[j]; // O(1)
    }
}

for (int i = 0; i < N; i++) { // O(N^2)
a[i] *= 2; // O(1)
    for (int j = 0; j < i; j++) { // O(i) → proportional to 0 + 1 + 2 + ... + (N - 1) = N(N - 1) / 2
        d[i][j] = a[i] * c[j]; // O(1)
    }
}

for (int i = 0; i < N; i++) { // O(N^2)
    if (std::find(a, a + N, 10 * i != a + N) { // Takes time proportional to O(N)
        count++;
    }
}

for (int i = 0; i < N; i++) { // O(N^2 log N)
    a[i] *= 2;
    for (int j = 0; j < N; j++) { // O(N log N)
        d[i][j] = f(a, N); // Suppose f(a, N) is O(log N)
    }   
}

for (int i = 0; i < N; i++) { // O(RC log C)
    a[i] *= 2;
    for (int j = 0; j < N; j++) { // O(C log C)
        d[i][j] = f(C); // Suppose f(C) is O(log C)
    }
}
```

- Selection Sort: `O(N^2)`
- Bubble Sort:
  - Worst Case: `O(N^2)`
  - Average Case: `O(N^2)`
- Insertion Sort: `O(N^2)` → best of the `N^2` sorts
- Shell Sort: `O(N^1.47)`
- Merge Sort: `O(N log N)`

## **3/2: Hash Tables**

- Use a formula to set up a data structure that can contain a lot of data and is inexpensive to search/insert
- Always expect collisions
  - If `load factor (# of items/# of buckets) > 1`, there is guaranteed to be a collision
- Using a prime number of buckets allows there to be no common factor → more equal distribution
- Hash function:

    ```c++
    unsigned int hash(string s) { // Numbers greater than the max size for unsigned ints are just represented by their last 32? digits
        unsigned int h = 216613261U; // U makes the compiler treat it as an unsigned integer constant
        for (int i = 0; i != s.size(); i++) {
            h += s[i];
            h *= 16777619;
        }
        return h;
    }
    ```

- Hash table with `N` items: lookup/insert/erase for fixed # of buckets: `O(N)` with low constant of proportionality
- Hash table with `N` items + rehashing: lookup/insert/erase: `O(1)` on average
- `unordered_set`
- `unordered_multiset` --> allows duplicates
- `unordered_map`
- `unordered_multimap` --> allows duplicate keys

    ```c++
    #include <unordered_map>
    using namespace std;
    unordered_map<string, double> ious;
    string name;
    double amt;
    while (cin >> name >> amt) {
        ious[name] += amt;
    }
    if (ious.find("ricky") == ious.end()) {
        cout << "Ricky doesn't owe me anything" << endl;
    }
    ```

    ```c++
    #include <functional>
    #include <string>
    string s;
    cin >> s;
    unsigned int h = std::hash<std::string>()(s);
    unsigned int h2 = std::hash<double>()(3.75);
    unsigned int h3 = std::hash<string*>()(&s);
    ```

## **3/4: Binary Trees**

- Made up of nodes connected by edges, stemming from a root node, and paths that connect one node to another
  - There is a unique path from the root node to any other node in the tree
  - Nodes follow a parent/child relationship
  - A leaf node has no children, interior nodes do
  - The depth of a Node is determined by how many edges away from the root a node is
  - Any program with a tree that goes down multiple paths is most likely best implemented with recursion

    ```c++
    struct Node {
        string data;
        vector<Node*> children;
        Node* parent; // Not always necessary, returning to parent may or may not be relevant
    };

    Node* root;
    ```

    ```c++
    int count(const Node* p) { // Base cases: empty tree and leaf nodes
        if (p == nullptr) {
            return 0;
        }
        int total = 1; // Count self
        for (int k = 0; k != p->children.size(); k++) {
            total += count (p->children[k]);
        }
        return total;
    }

    cout << count(root) << endl;
    ```

    ```c++
    void printTree(const Node* p, int depth) {
        if (p == nullptr) {
            return;
        }
        cout << string(2 * depth, ‘ ‘) << p->data << endl;
        for (int i = 0; i < p->children.size(); i++) {
            printTree(p->children[i], depth + 1);
        }
    }
    ```

- Preorder traversal: process the node before you process the children
- Postorder traversal: process the node after you process the children
- A binary tree is either:
  - Empty
  - Or is a node with 2 binary subtrees (a left subtree and a right subtree)

    ```c++
    struct Node {
        string data;
        Node* left;
        Node* right;
    };
    ```

- A binary search tree (BST) is either:
  - Empty
  - A node with a left BST and a right BST such that the value at every node on the left subtree is < the value at this node, and every node in the right subtree is > the value at this node
    - Assuming no duplicates

```c++
set<string> visitors;
// Other code
string name;
// Other code
visitors.insert(name) // Inserts if name is not already in the set
// Other code
if (visitors.find("Ricky") == visitors.end();
    cout << "not found" << endl;
for (set<string>::iterator p = visitors.begin(); p!= visitors.end(); p++) {
    cout << *p << endl;
}
// Other code
set<string>::iterator p = visitors.find("Fred");
if (p != visitors.end()) {
    cout << "Bye, Fred" << endl;
    visitors.erase(p) // Harmless to pass erase the end iterator
}
// Other code
visitors.remove("Lucy");
```

- In-order traversal:

    ```c++
    void printTree(const Node* p) {
        if (p != nullptr) {
            printTree(p->left);
            cout << p->data << endl;
            printTree(p->right);
        }
    }
    ```

- Insertion/deletion/search - `O(log N)` in a relatively balanced BST
- Deletion:
  - Leaf node - delete the node
  - Node with one child - delete the node, move the child up
  - Node with two children - delete the node and take either the greatest value in the left subtree or the least value in the right subtree to replace it
- AVL Tree:
  - A BST where for every node, the height of the left subtree and the height of the right subtree differ by at most 1
  - Guarantees `log N` behavior
- 2-3 Tree:
  - Every node has 2 or 3 children
    - Nodes with 3 children contain 2 values, the 3rd child is between these 2 values
  - All leaf nodes have the same depth
- Red-black tree:
  - Used by STL for `set`, `map`, `multiset`, `multimap`
  - `log N` data structures
