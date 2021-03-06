# COM SCI 131 - Winter '21 - Eggert

## **1/5: Introduction**

- Core of this class
  - Principles and limitations of programming tools
  - Notations for these models, design + use + support for the above
  - How to evaluate strengths + weaknesses in various contexts
- Donald Knuth - word problem
  - Starting in the 1960s - wanted to write the computer programming textbook
    - Seven volumes → volume 1 (1969)
  - Addison-Wesley had trouble producing the book to high enough quality
  - Side project:
    - Write a book formatter, so he could format the way he liked
      - Beautiful math, beautiful code, images, text → designed his own font
    - TeX - classic high-quality formatter
      - He used this to produce the book’s second edition + future versions
    - Side project: The TeXbook - book about TeX’s design and algorithms, detailed internal doc. about TeX
      - `tex.pas` - the TeX source code, written in Pascal
      - `texbook.tex` - the TeXbook source code, written in TeX
      - Keeping these 2 files in sync is a pain
        - Side side project: Literate Programming
          - Basic idea: don’t separate documentation and source code, put the documentation in source code → easy to keep in sync
          - One file: `tex.tangled` → contains source code and documentation
            - `p1 <tex.tangled >tex.pas` → throws away documentation
            - `p2 <tex.tangled >texbook.tex` → throws away source code
            - Designed notation to tangled documentation and source code to allow for separation
            - How to tell people about Literate Programming?
              - “Read the TeXbook” → too long
              - Simple introduction to the idea as a short paper → approached CACM (leading research journal)
              - Solve the word problem in tangled Pascal using a new data structure called a “hash trie” + included the CACM paper
              - Succeeded → Literate Programming is now common (JDK documentation, etc.)
          - But, it was a set-up job → paper included an afterword by CACM editor which was a suggestion for a better solution using the - Unix shell
            - Find the words in the input: `tr -cs ‘A-Za-z’ ‘[\n*]’`
              - Takes the complement (`-c`) of the words and transliterates them into newlines
              - Squeezes out duplicates (`-s`)
            - Sort the resulting list: `tr -cs ‘A-Za-z’ ‘[\n*]’ | sort`
            - Find the duplicates and remove them: `tr -cs ‘A-Za-z’ ‘[\n*]’ | sort | uniq -c`
              - Count the duplicates (`-c`)
            - Sort the list in desired order: `tr -cs ‘A-Za-z’ ‘[\n*]’ | sort | uniq -c | sort -rn`
              - Sort in reverse order (`-r`)
              - Sort in numeric order (`-n`)
            - Eliminate the extra newline: `tr -cs ‘A-Za-z’ ‘[\n*]’ | sed 1d | sort | uniq -c | sort -rn`
              - `sed 1d` removes the first line, which is where the newline is located
            - One-line solution → do you really need Literate Programming?
              - Solution when the problem is so large that the language is scaling improperly
              - Keep stuff small → you don’t need Literate Programming anymore
- Choice of notation matters
- Related notion in north campus courses
  - Sapir-Whorf Hypothesis of natural languages
    - The structural diversity of natural languages is essentially limitless
    - The language we speak determines how we view the world/think to some extent
      - Is a factor in programming languages
- Language design issues
  - Idea - how to make decisions about which language to use, how to design a language, or how to improve it
  - Successful languages evolve
  - Orthogonality - comes from mathematics → orthogonal axes
    - Any choice made for one axis can be made without worrying about the other axes
    - In a language, you have multiple features, each of which requires a selection, and you can make any single selection without - worrying about the others
      - A design that is not orthogonal - in C/C++, functions cannot return arrays (arrays decay into pointers, array != pointer)

        ```c++
        int *f(...) { // ok - pointer to 0th element
            ...
        }
        ```

        ```c++
        struct s { 
            int a[10]; 
        };

        struct s g(...) { // ok - struct containing an array
            ...
        } 
        ```

        ```c++
        typedef int[10] trouble;
        trouble h(...) { // problem - you can't return the array
            ...
        }
        ```

        ```c++
        #include <x.h>
        
        x arr;
        x f(int x) { // will break if x is an array type, non-flexible implementation
            ...
        }
        ```

  - Runtime Efficiency (how long to run the program)
    - Could imply wall clock time, CPU time, RAM, I/O, network access latency, energy/power consumption, etc.
  - Compile-time Efficiency (how long to build the software)
  - Development-time Efficiency (how long to write the code)
    - More verbose code takes longer to write and read
    - Code that’s too concise can be unreadable
  - Safety
    - What happens if you violate the rules of the language? How much damage is caused?
      - Ex) Undefined behavior
    - Static checking vs. dynamic checking
      - Static (C/C++):
        - Are identifiers declared properly?
        - Do all the types match?
      - Dynamic:
        - Dereference a null pointer
        - Subscript error
        - Stack overflow
  - Concurrency
  - Exception Handling
  - Mutability/Evolvability

## **1/5: Programming Languages**

- 4 main types:
  - Imperative (C) - marked by iteration and assignment
  - Functional (ML, Lisp) - marked by recursion and single-value variables
  - Logic Programming (Prolog) - marked by rules of logical inference
  - Object-Oriented (Java) - Builds upon the hallmarks of imperative languages with objects, bundles of data that can perform - operations on itself
  - There are more types, and some languages are so unique they don’t fit into any given type (Forth, APL, etc.), while others - combine attributes of multiple other types (Python, Ruby, etc.)
- Language controversies
  - Debates over virtues of given languages
  - Language development usually governed by international committees, who work slow and endure a lot of conflict
  - Debate over basic definitions
    - Ex) Object-oriented
    - Lean towards more informal definitions
- Evolution of languages
  - Development of a new language accompanied with lack of burden to make existing code compatible
  - New languages provide idea and foundation for the next generation
  - Language invention is slow and incremental
    - Almost all languages evolve multiple dialects, each interpreting the standard differently
  - Not feasible to make use of a single language forever
  - Language evolution drives and is driven by hardware evolution
- Language and Practices
  - Programming languages and programming practices affects the development of both
  - Languages guide programmers toward particular programming styles
    - Object-oriented languages guide developers to use objects
    - Functional languages guide developers to use many small functions
    - Logic languages guide programmers to express problems as searches in a logically defined space of solutions
  - Possible to write in a conflicting style, but not a good idea → language will be working against you
  - Practice can guide programmers to new ideas
    - Recursion and conditionals added to Lisp because they were needed for AI apps
  - Operating systems interact closely with language systems

## **1/5: Defining Program Syntax**

- The syntax of a programming language is the part of the language definition that says how programs look: their form and structure
  - What does an expression/statement/function definition look like?
  - How are comments delimited?
  - Where does the semicolon go?
- The semantics of a programming language is the part of the language definition that says what programs do: their behavior and meaning
  - What does a given expression/statement/function do?
  - How does it work?
  - What can go wrong when it runs?
- Languages can be broken up into parse trees based on the rules of the language given
  - Ex) `<exp> ::= <exp> + <exp> | <exp> * <exp> | (<exp>) | a | b | c`
    - `a`, `b`, and `c` are variables
    - Leads to an infinite parse tree
  - Language systems must parse every program they run
  - Sometimes multiple parse trees may represent the same string
  - As long as a string can be generated by at least one parse tree using the language’s rules, that string is in the language
- Grammar has 4 parts:
  - Set of tokens
    - These are the smallest units of syntax
    - Strings and symbols that we choose to not think of as consisting of smaller parts
    - Keywords, names, operators, etc. in programming languages
  - Set of non-terminal symbols
    - Enclosed in angle brackets by convention
    - Correspond to different kinds of language constructs
    - Sentences, noun phrases, etc. in English
    - Statements, expressions, etc. in programming
  - Set of productions
    - Consists of a left-hand side, `::=` separator, and a right-hand side by convention
    - The LHS is a single non-terminal symbol
    - The RHS is a sequence of one or more things, which can each be a token or non-terminal symbol
    - Permits the LHS to have the symbols on the RHS as its children in the parse tree
    - Can abbreviate productions with matching LHSs using the `|` symbol for convenience
  - A non-terminal symbol called the start symbol
    - Designated as the root of the parse tree
  - Special `<empty>` non-terminal symbol can be used where the grammar needs to generate an empty string
    - Ex) Optional else clause in an `if-else` statement
  - The form was developed in 1960, called Backus-Naur Form (BNF)
- Writing grammar
  - A grammar is a finite, structured, mechanical thing that specifies a potentially infinite language
    - You must be able to imagine how the productions you are crafting will unfold when parse trees are built
  - Most important method is divide and conquer
  - Very important to break problems down into simpler subproblems
    - Take Java variable declaration as an example:

    ```java
    float a;
    boolean a, b, c;
    int a = 1, b, c = 1 + 2;
    ```

    - Statements consist of a type name followed by 1+ variable names being declared
    - Start simple: `<var-dec> ::= <type-name> <declarator-list> ;`
    - Type names → just use the primitive types for now
      - `<type-name> ::= boolean | byte | short | int | long | char | float | double`
      - Full functionality would require class names, interface names, and array types
    - Declarator list is more complicated, divide problem again
      - `<declarator-list> ::= <declarator> | <declarator> , <declarator-list>`
      - Recursive rule provides at least one `<declarator>` and enforces the commas between them
      - Now address the smaller problem of defining a declarator
        - `<declarator> ::= <variable-name> | <variable-name> = <expr>`
        - Follow up with definitions of legal variable names, expressions, other declarations, etc.
  - Test grammar as you would test a program
- Lexical structure
  - Currently, we have a structure to use tokens to generate a grammar
  - This structure is incomplete, a we’ve only defined the phrase structure of a language, that is, how to construct parse trees with tokens at the leaves
    - We have no methodology for constructing the tokens themselves, using a lexical structure to divide program text into tokens
    - Could be overcome by writing a single grammar that has individual characters as token → almost never done due to readability
    - Most modern languages specify the phrase structure and lexical structure independently → makes languages easier to write/ implement
      - Phrase structure defined down to the token level, lexical structure defined down to the character level
      - Some old languages have features that make this separation challenging
  - These structures are parsed by different components
    - The scanner/lexer reads an input file and converts it to a stream of tokens, discarding white-space, comments, etc.
    - The parser reads the stream of tokens and forms the parse tree
  - Some old languages place importance on the column number that a character lies on
    - New languages treat newlines as essentially white-space → free-format
    - Old languages that give special meanings to column numbers → fixed-format
    - This distinction is trivial today since the vast majority of modern languages are free-format
      - Good style still dictates that newlines are needed to indicate the structure of the program
      - This styling is sometimes incorporated into the formal part of a language’s definition (Python)
- Other grammar forms
  - EBNF - extended BNF
    - Can add metasymbols to BNF to address common patterns of language definition
      - Metasymbols - symbols that are part of the language of the definition, not the language being defined (`::=,` `|`, etc.)
    - `[ ]` → indicates something is optional
    - `{ }` → indicates something can be repeated 0 or more times
    - `( )` → groups things on the RHS to prevent ambiguity
    - Make grammar much easier to read than plain BNF
    - Adds new issue of new cases where it is necessary to distinguish between metasymbols and tokens
      - When metasymbols are used as a token, they must be enclosed in single quotes
  - Syntax diagrams - graphical expression of a grammar
    - Uses a directional graph to show productions for each non-terminal symbol
    - A path through the graph is a legal way to add children to the parse tree
    - Sometimes call railroad diagrams
    - Can contain skips, multiple paths, loops, etc. to represent the various features of BNF/EBNF
    - Easy for beginner representations, hard to formulate the final parse tree
  - Formal grammars
    - Context-free grammars - children of a node of a parse tree are only dependent on that node, not on neighboring nodes
    - Regular grammars - less expressive
    - Context-sensitive grammars - more expressive
- Many variations of representations for programming language grammars → underlying concept is generally the same
- Consider your audience
  - Novices - just want to find out what a legal program looks like
  - Advanced/language-system implementers - need an exact detailed definition to work from
  - Automatic tools - derive other programs from your grammar automatically
- Languages with simple, readable, short grammars have simple, memorable phrase structures, allowing for easier learning and usage

## **1/6: First Look at ML**

- ML operates in interactive mode - prompts an expression, type an expression, evaluates the expression, prints the value, repeat
- ML attempts to infer the type of an expression’s result
- ML maintains a variable called it, which contains the value of the last expression’s result

    ```ml
    - 1 + 2 * 3;
    val it = 7 : int
    ```

- `-` : prompt for next expression
- `=` : prompt to finish current expression
  - Happens if the semicolon is not included
- Types
  - 2 numeric types: `int` and `real`
  - ML uses `~` for negation rather than `-`
  - ML maintains a `bool` type with `true` and `false` values
    - ML is case-sensitive
  - Other basic types are `string` and `char`
  - Strings are enclosed in double quotes

    ```ml
    - “fred”;
    val it = “fred” : string
    ```

  - Can use escape sequences for special characters
    - `\t` = tab, `\n` = newline, `\”` for quotes, etc.
  - Use `#”X”` to get a character constant rather than a string

    ```ml
    - #”H”;
    val it = #”H” : char
    ````

- Operators
  - Operators for addition, subtraction, and multiplication are standard
  - Division is divided into the `div` and `mod` operators
    - `div` calculates the integer quotient
    - `mod` returns the remainder of the integer division

        ```ml
        - ~ 1 + 2 - 3 * 4 div 5 mod 6;
        val it = ~1 : int
        ```

    - `/` exists as an operator for real-division

        ```ml
        - ~1.0 + 2.0 - 3.0 * 4.0 / 5.0;
        val it = ~1.4 : real
        ```

  - `^` is used as a string concatenation operator

    ```ml
    - “Hello “ ^ “World”;
    val it = “Hello World” : string
    ```

  - Comparison operators remain standard and can be used on `string`s, `char`s, `int`s, or `real`s

    ```ml
    - 2 < 3;
    val it = true : bool
    - 1.0 <= 1.0;
    val it = true : bool
    - #”d” > #”c”;
    val it = true : bool
    - “abce” >= “abd”
    val it = false : bool
    ```

    - Test alphabetical order in strings
  - Equality test (`=`) and inequality test (`<>`) can only be used by ML’s equality types
    - `String`, `char`, and `int` are equality types
    - `real` is not an equality type due to the nature of computations on computer hardware
  - Logical values
    - Logical or is `orelse`
    - Logical and is `andalso`
    - Logical complement is `not`

        ```ml
        - 1 < 2 orelse 3 > 4;
        val it = true : bool
        - 1 < 2 andalso not (3 < 4);
        val it = false : bool
        ```

    - `orelse` and `andalso` don’t evaluate the second operand if the result is already decided by the first operand

        ```ml
        - true orelse 1 div 0 = 0;
        val it = true : bool
        ```

      - Called a short-circuiting operator
  - Precedence - (`not`, `~`), (`*`, `/`, `div`, `mod`), (`+`, `-`, `^`), (`<`, `>`, `<=`, `>=`, `=`, `<>`), (`andalso`), (`orelse`)
- Conditionals
  - if-then-else statements are transformed into if-then-else expressions
  - Have the form: `<conditional-expression> ::= if <expression> then <expression> else <expression>`
    - `<expression>` in the if part must be a `bool` and the `<expression>`s in the `then` and `else` parts must have matching types
    - Also short-circuiting

        ```ml
        - if 1 < 2 then #”x” else #”y”;
        val it = #”x” : char
        - if 1 > 2 then 34 else 56;
        val it = 56 : int
        - (if 1 < 2 then 34 else 56) + 1;
        val it = 35 : int
        ```

- Type Conversion and Functions
  - Many operators work on different types of pairs
    - You can add an `int` to an `int` and a `real` to a `real`
    - This means this operator is overloaded
    - Operators do not have a defined way to operate on a pair of different types
      - `- 1.0 * 2;` will cause a type error
      - Other languages will transform the operands automatically if possible, ML doesn’t
  - ML has functions that can be called to transform types
    - `real` - `int` → `real`
    - `floor` - `real` → `int` (rounding down)
    - `ceil` - `real` → `int` (rounding up)
    - `round` - `real` → `int` (round to nearest `int`)
    - `trunc` - `real` → `int` (rounds towards 0)
    - `ord` - `char` → `int` (gets ASCII code)
    - `chr` - `int` → `char` (uses ASCII code)
    - `str` - `char` → `string`

        ```ml
        - real(123);
        val it = 123.0 : real
        - floor(3.6);
        val it = 3 : int
        - floor 3.6;
        val it = 3 : int
        - str #”a”;
        val it = “a” : string
        ```

    - Preferred style is to avoid using parentheses in function call
      - `f(1)`, `(f)1`, `(f)(1)`, `(f 1)`, and `f 1` all call function `f` with the parameter `1`
      - Only use when modifying precedence or associativity
    - Function precedence is highest that we’ve seen so far
- Variable Definition
  - `val` is used to define a new variable and bind it to a keyword

    ```ml
    - val x = 1 + 2 * 3;
    val x = 7 : int
    - x;
    val it = 7 : int
    - val y = if x = 7 then 1.0 else 2.0;
    val y = 1.0 : real
    ```

  - Can be used to redefine an existing variable to a new value or type

    ```ml
    - val fred = 23;
    val fred = 23 : int
    - fred
    val it = 23 : int
    - val fred = true;
    val fred = true : bool
    - fred
    val it = true : bool
    ```

    - New definition of a variable doesn’t overwrite the old one, it just adds a new definition on top of the previous one
      - Any part of the program that used the old definition will still use the old definition afterwards → new definitions have no side - effects on older parts of the program
- Garbage collection - ML’s way of reclaiming pieces of memory that are no longer being used
  - `GC #0.0.0.0.1.3: (0 ms)`
- Tuples and Lists
  - Tuple - an ordered collection of values of different types
    - ML supports tuples as expressions anywhere

        ```ml
        - val barney = (1 + 2, 3.0 * 4.0, “brown");
        val barney = (3, 12.0, “brown”) : int * real * string
        - val point1 = (“red”, (300, 200));
        val point1 = (“red”, (300, 200)) : string * (int * int)
        ```

    - Tuples formed by putting 2+ expressions inside parens separated by commas
    - `*` symbol used as a type constructor
    - The `i`th element of a tuple can be extracted using `#i v`
      - Positions start counting from 1

        ```ml
        - #2 barney
        val it = 12.0 : real
        - #1 (#2 point1);
        val it = 300 : int
        ```

    - Tuples can have any length >1
  - List - ordered collection of values of the same type
    - Lists can contain any number of elements
    - Formed using `[ ]` instead of parens

        ```ml
        - [1, 2, 3];
        val it = [1, 2, 3] : int list
        - [1.0, 2.0];
        val it = [1.0, 2.0] : real list
        - [true];
        val it = [true] : bool list
        - [(1, 2), (1, 3)];
        val it = [(1, 2), (1, 3)] : (int * int) list
        - [[1, 2, 3], [1, 2]];
        val it = [[1, 2, 3], [1, 2]] : int list list
        ```

    - Empty list written as `nil` or `[]`

        ```ml
        - [];
        val it = [] : ‘a list
        - nil;
        val it = [] : ‘a list
        ```

      - ML cannot determine the type of the empty list
        - Give it a type beginning with an apostrophe - type variable
        - Type variables stand for types that are unknown
      - ML has predefined function `null` to determine if a list is empty

          ```ml
          - null [];
          val it = true : bool
          - null [1, 2, 3];
          val it = false : bool
          ```

        - Can also use an equality comparison, but null is preferred
    - `@` operator can concatenate 2 lists of the same type

        ```ml
        - [1, 2, 3] @ [4, 5, 6];
        val it = [1, 2, 3, 4, 5, 6] : int list
        ```

    - Construct/cons operator (`::`) glues an element to the front of a list

        ```ml
        - val x = #”c” :: [];
        val x = [#”c”] : char list
        - val y = #”b” :: x;
        val y = [#”b”, #”c”] : char list
        - val z = #”a” :: y;
        val; z = [#”a”, #”b”, #”c”] : char list
        ```

      - More efficient than @
      - Right-associative
    - `hd` and `tl` extract the first element and rest of a list, respectively

        ```ml
        - val z = 1 :: 2 :: 3 :: [];
        val z = [1, 2, 3] : int list
        - hd z;
        val it = 1 : int
        - tl z;
        val it = [2, 3] : int list
        - tl(tl z);
        val it = [3] : int list
        tl(tl(tl z));
        val it = [] : int list
        ```

      - Error to try and use `hd` or `tl` on an empty list
    - `explode` converts a `string` into a `char` list and `implode` reverses it

        ```ml
        - explode “hello”
        val it = [#”h”, #”e”, #”l”, #”l”, #”o”] : char list
        - implode [#”h”, #”i”];
        val it = “hi” : string
        ```

- Function definitions
  - Use `fun` to define a new function

    ```ml
    - fun firstChar s = hd (explode s);
    val firstChat = fn : string -> char
    - firstChar “abc”;
    val it = #”a” : char
    ```

    - `<fun-def> ::= fun <function-name> <parameter> = <expression> ;`
    - `a -> b` is the type for functions that take a parameter of type `a` and return a value of type `b`
    - Tuple parameters can be used for functions that take in more than 1 input value

        ```ml
        - fun quot(a, b) = a div b;
        val it = fn : int * int -> int
        - quot(6, 2);
        val it = 3 : int
        - val pair = (6, 2);
        val pair = (6, 2) : int * int
        - quot pair;
        val it = 3 : int
        ```

      - Every ML function is really just taking 1 parameter, but that parameter can be a tuple
  - Example of a factorial computing function
  
    ```ml
    - fun fact n =
    =   if n = 1 then 1
    =   else n * fact(n - 1);
    val fact = fn : int -> int
    - fact 5;
    val it = 120 : int
    ```

    - Can spread over 1+ lines, ML doesn’t care about line breaks → readability
    - Reflects ML’s heavy use of recursion
  - Example of a function that adds up all the elements of a list

    ```ml
    - fun listsum x =
    =   if null x then 0
    =   else hd x + listsum(tl x);
    val listsum = fn : int list -> int
    - listsum [1, 2, 3, 4, 5];
    val it = 12 : int
    ```

  - Example of an implementation of the predefined `length` function

    ```ml
    - fun length x =
    =   if null x then 0
    =   else 1 + length(tl x);
    val length = fn : ‘a list -> int
    - length [true, false, true];
    val it = 3 : int
    - length [4.0, 3.0, 2.0, 1.0];
    val it = 4 : int
    ```

    - Function can be called with parameters of different types → polymorphic function
      - No special trick was used, ML just determined this could be generalized as such
  - Types represented by `‘'a` reflect a need for equality types → use `null x` instead of `x = []`
  - Example of a function that reverses a list

    ```ml
    - fun reverse L =
    =   if null L then nil
    =else reverse(tl L) @ [hd L];
    val reverse = fn : ‘a list -> ‘a list
    - reverse [1, 2, 3]
    val it = [3, 2, 1] : int list
    ```

- Type Annotations
  - So far we have `int`, `real`, `bool`, `char`, and `string` as types and `*` (tuple), `list` (list), and `->` (function) as type constructors
    - `list` has highest precedence and `->` has lowest precedence
      - `int * int list` is the same as `int * (int list)`
  - ML defaults types to the default of the operators used (`+`, `-`, `*` all default to `int`)
    - Sometimes type annotations are needed

        ```ml
        - fun prod(a, b) = a * b;
        val prod = fn : int * int -> int
        - fun prod(a:real, b:real) : real = a * b;
        val prod = fn : real * real -> real
        ```

      - Establishes the types of `a`, `b`, and the return value
      - One hint is usually enough to satisfy the need for a type annotation, but opt for the most readable option
  - More important for larger projects

## **1/6: Second Look at ML**

- ML functions work based on patterns
  - Single parameter `n` is a pattern
  - Tuple list `(a, b)` is a pattern for a tuple of 2 items
  - Used to match data, which ML can then act on
  - Can also introduce new variable
    - Pattern that matches `n` also introduced the variable `n` that is bound to the value of the parameter
- Simple Patterns
  - Simplest pattern is `_`, which matches any pattern and doesn’t introduce a new variable

    ```ml
    - fun f _ = “yes”;
    val f = fn : ‘a -> string
    - f 34.5;
    val it = “yes” : string
    - f [];
    val it = “yes” : string
    ```

  - Can make a pattern that only matches a single constant

    ```ml
    - fun f 0 = “yes”;
    Warning: match nonexhaustive
        0 => ...
    val f = fn : int -> string
    - f 0;
    val it = “yes” : string
    - f 1;
    uncaught exception Match [nonexhaustive match failure]
    ```

    - `f` is undefined if passed anything other than `0`
    - Only equality-types can be used as constant patterns
- Complex Patterns
  - Any list of patterns is legal

    ```ml
    - fun f [a, _] = a;
    Warning: match nonexhaustive
    a :: _ :: nil => ...
    val f = fn : ‘a list -> ‘a
    - f [#”f”, #”g”];
    val it = #”f” : char
    ```

    - Nonexhaustive function definition - definition of a function that doesn’t cover the whole domain type
      - This function is only defined for lists with exactly 2 elements
  - Any cons of patterns is a legal pattern

    ```ml
    - fun f (x :: xs) = x;
    Warning: match nonexhaustive
        x :: xs => ...
    val f = fn : ‘a list -> ‘a
    - f [1, 2, 3];
    val it = 1 : int
    ```

    - Nonexhaustive because it fails on the empty list
- Pattern Summary
  - A variable is a pattern that matches anything and binds to it
  - An underscore (`_`) is a pattern that matches anything
  - A constant (of an equality type) is a pattern that matches only that constant value
  - A tuple of patterns is a pattern that matches any tuple of the right size, whose contents match the subpatterns
  - A list of patterns is a pattern that matches any list of the right size, whose contents match the subpatterns
  - A cons of patterns is a pattern that matches any non-empty list whose head and tail match the subpatterns
- Multiple Patterns for Functions
  - ML allows for the specification of multiple patterns for the parameter of a function, each with an alternative function body

    ```ml
    - fun f 0 = “zero” | f 1 = “one”
    ```

    - `<fun-def> ::= fun <fun-bodies> ;`
    - `<fun-bodies> ::=- <fun-body> | <fun-body> ‘|’ <fun-bodies>`
    - `<fun-body> ::= <fun-name> <pattern> = <expression>`
      - `<fun-name>` must be the same in each alternative
    - Can overlap patterns → ML tries the patterns in order they’re listed and uses the first one that matches

        ```ml
        - fun f 0 = “zero” | f _ = “non-zero”
        ```

- Pattern-Matching Style

    ```ml
    fun f 0 = “zero”
    |   f 1 = “non-zero”;

    fun f n =
        if n = 0 then “zero”
        else “non-zero”;
    ```

  - Above functions are equivalent, first uses pattern-matching style
  - Pattern-matching generally preferred for readability
  - Rewrite the factorial program:

    ```ml
    fun fact 0 = 1
    |   fact n = n * fact(n - 1);
    ```

    - Clearly separates base case from recursive case
  - Rewrite the reverse program

    ```ml
    fun reverse nil = nil
    |   reverse (first :: rest) = reverse rest @ [first];
    ```

    - Here, we can implicitly extract the head and tail using pattern-matching
      - More readable, same efficiency
  - Sum all the elements of a list

    ```ml
    fun f nil = 0
    |   f (first :: rest)  = first + f rest;
    ```

    - Very common structure for functions that visit all elements of a list
  - Count how many true values are in a `bool list`

    ```ml
    fun f nil = 0
    |   f (true :: rest) = 1 + f rest
    |   f (false :: rest) = f rest;
    ```

  - Make a new `int list` where each `int` is 1 greater than it was in the original list

    ```ml
    fun f nil = nil
    |   f(first :: rest) = first + 1 :: f rest;
    ```

  - Cannot use the same variable name more than once in a pattern
    - `fun f(a, a)` as a way to find pairs of equal elements is illegal
    - Only implementation is to abandon pattern-matching style

        ```ml
        fun f (a, b) =
            if (a = b) then ... 
            else ...
        ```

  - Can also use patterns in `val` definitions

    ```ml
    - val (a, b) = (1, 2.3);
    val a = 1 : int
    val b = 2.3 : real
    - val a :: b = [1, 2, 3, 4, 5];
    val a = 1 : int
    val b = [2, 3, 4, 5] : int list
    ```

- Local Variables
  - We can make local variable definitions in ML using the `let` expression
  - `<let-exp> ::= let <definintons> in <expression> end`
    - `<definitions>` is a sequence of any number of definitions that hold within the `<let-exp>`
    - `<expression>` is evaluated in an environment in which the given definitions hold

    ```ml
    - let val x = 1 val y = 2 in x + y end;
    val it = 3 : int;
    - x;
    Error: unbound variable or constructor: x
    ```

  - Helps break up long expressions and give meaningful names to intermediary pieces

      ```ml
      fun days2ms days = 
          let
              val hours = days * 24.0
              val minutes = hours * 60.0
              val seconds = minutes * 60.0
          in
              seconds * 1000.0
          end;
      ```

  - Function that halves a list

    ```ml
    fun halve nil = (nil, nil)
    |   halve [a] = ([a], nil)
    |   halve (a :: b :: cs) =
            let
                val (x, y) = halve cs
            in
                (a :: x, b :: y)
            end;
    ```

    - Expand function into merge-sort implementation

        ```ml
        fun merge (nil, ys) = ys
        |   merge (xs, nil) = xs
        |   merge (x :: xs, y :: ys) =
                if (x < y) then x :: merge (xs, y :: ys)
            else y :: merge (x :: xs, ys
        fun mergeSort nil = nil
        |   mergeSort [a] - [a]
        |   mergeSort theList =
            let
                val (x, y) = halve theList
            in
                merge (mergeSort x, mergeSort y)
            end;
        ```

- Nested Function Definitions
  - `halve` and `merge` from above aren’t useful on their own
  - In our interest to make it clear that they are only relevant in the context of `mergeSort`

    ```ml
      fun mergeSort nil = nil
      |   mergeSort [a] = [a]
      |   mergeSort theList =
              let
                  fun halve nil = (nil, nil)
                  |   halve [a] = ([a], nil)
                  |   halve (a :: b :: cs) =
                          let
                              val (x, y) = halve cs
                          in
                              (a :: x, b :: y)
                          end;
                  fun merge (nil, ys) = ys
                  |   merge (xs, nil) = xs
                  |   merge (x :: xs, y :: ys) =
                          if (x < y) then x :: merge (xs, y :: ys)
                          else y :: merge (x :: xs, ys);
                  val (x, y) = halve theList
              in
                  merge(mergeSort x, mergeSort y)
              end;
    ```

## **1/6: Third Look at ML**

- Pattern Matching
  - A rule is a part of ML syntax that takes the form `<rule> ::= <pattern> => <expression>`
  - A match consists of 1+ rules separated by the `|` token: `<match> ::= <rule> | <rule> ‘|’ <match>`
    - Each rule in a match must have the same type of expression on the RHS
  - Case-expressions use matches
    - `<case-exp> ::= case <expression> of <match>`

    ```ml
    - case 1 + 1 of
    =   3 => “three” |
    =   2 => “two” |
    =   _ => “hmm”;
    val it = “two” : string
    ```

    - Value of a case expression is the value of the expression in the first rule of the match whose pattern matches the value of expression
    - ML allows case expressions with general pattern matching, unlike `switch` statements in C++

        ```ml
        case x of
        _ :: _ :: c :: _ => c |
        _ :: b :: _ => b |
        a :: _ => a |
        nil => 0
        ```

      - Returns the 3rd element if it exists, or the 2nd element if it exists, or the 1st element if it exists, or `0` if the list is empty
    - `If-else`'s can be rewritten using case expressions

        ```ml
        case exp1 of
            true => exp2 |
            false => exp3
        ```

      - Should only use when you need the extra flexibility of the case expression → conditional more readable
- Function Values and Anonymous Functions
  - Function names and operators are variables bound to functions

    ```ml
    - ~
    val it = fn : int -> int
    - val x = ~;
    val x = fn : int -> int
    - x 3
    val it = ~3 : int
    ```

  - The function `f` (imperative) → the function currently bound to the name `f` (ML)
  - Functions can be declared without a name using the `fn` keyword and a match → anonymous function

      ```ml
      - fun f x = x + 2;
      val f = fn : int -> int
      - f 1;
      val it = 3 : int
      - fn x => x + 2;
      val it = fn : int -> int
      - (fn x => x + 2) 1;
      val it = 3 : int
      ```

    - Useful for when the function is only needed in one place and you don’t want to clutter your program with an extra variable

        ```ml
        - fun intBefore (a, b) = a < b;
        val intBefore = fn : int * int -> bool
        - quicksort ([1, 4, 3, 2, 5], intBefore);
        val it = [1, 2, 3, 4, 5] : int list
        - quicksort ([1, 4, 3, 2, 5], fn (a, b) => a < b);
        val it = [1, 2, 3, 4, 5] : int list
        - quicksort ([1, 4, 3, 2, 5], fn (a, b) => a < b);
        val it = [5, 4, 3, 2, 1] : int list
        ```

  - We can extract the function denoted by an operator using the `op` keyword

    ```ml
    - quicksort ([1, 4, 3, 2, 5], op <);
    val it = [1, 2, 3, 4, 5] : int list
    - quicksort ([1, 4, 3, 2, 5], op >);
    val it = [5, 4, 3, 2, 1] : int list
    ```

- Higher-Order Functions and Currying
  - Every function has an order
    - A function that takes a function as a parameter or returns a function value has order `n + 1`, where `n` is the order of its - highest-order parameter or return value
    - A function of order `n` is called an `n`th order function
    - Any function with order `>1` is called a higher-order function
  - We’ve seen that functions only take 1 parameter
    - We get around this by passing a tuple as this parameter
    - We can also use currying - have 1 function take 1 parameter and return a function that will use a second parameter to get the - final result

        ```ml
        - fun f (a, b) = a + b;
        val f = fn : int * int -> int
        - fun g a = fn b => a + b
        val g = fn : int -> int -> int
        ```

      - `g` takes the first parameter and returns an anonymous function that takes the second parameter and returns the sum
      - We would call `f` with a tuple like normal, but `g` would be called with integer parameters due to ML’s left associativity of - functions
      - Biggest advantage of currying is we can call curried functions while only passing some of their parameters and leave the rest for later

        ```ml
        - val add2 = g 2;
        val add2 = fn : int -> int
        - add2 3;
        val it = 5 : int
        - add2 10;
        val it =  12 : int
        - val sortBackward = quicksort (op >);
        val sortBackward = fn : int list -> int list
        - sortBackward [1, 4, 3, 2, 5];
        val it = [5, 4, 3, 2, 1] : int list
        Currying creates more specialized versions of functions
        Can be generalized to any number of parameters
        Can be abbreviated
        fun g a = fn b = fn c => a + b +c;
        fun g a b c = a + b + c
        ```

- Predefined Higher-Order Functions
  - `map` function
    - Used to apply some function to every element of a list, collecting a list of the results

    ```ml
    - map ~ [1, 2, 3, 4];
    val it = [~1, ~2, ~3, ~4] : int list
    ```

    - Type is `(‘a -> ‘b) -> ‘a list -> ‘b list`
    - Result will always be a list of the same length as the input list
  - `foldr` function
    - Used to combine all the elements of a list into one value
    - Takes 3 parameters: function `f`, starting value `c`, and a list of values
      - Starts with the rightmost element, computes the result of `f` called on that element and `c`, and then folds in the next element - until all elements have been processed

      ```ml
      - foldr (op ^) “” [“abc”, “def”, “ghi”];
      val it = “abcdefghi” : string
      ```

    - Type is `(‘a * ‘b -> ‘b) -> ‘b -> ‘a list -> ‘b`
    - Commonly used by giving the first 2 parameters and not the third
      - Results in a function that takes a list and folds it with a fixes function and an initial value

        ```ml
        - val addup = foldr (op +) 0;
        val addup = fn : int list -> int
        - addup [1, 2, 3, 4, 5];
        val it = 15 : int
        ```

      ```ml
      foldr (fn (a, b) => function body) c x
      ```

      - `b`, `c`, the value returned by the anonymous function, and the value returned by `foldr` are all the same type
      - `a` is the same type as the elements of list `x`
    - Function that removes all negatives from a list

        ```ml
        fun thin L = foldr (fn (a, b) => if a < 0 then b else a::b) [] L;
        ```

  - `foldl` function
    - Used to combine all the elements of a list into one value
    - Starts from the leftmost element instead of the rightmost

    ```ml
    - foldl (op ^) “” [“abc”, “def”, “ghi”];
    val it = “ghidefabc” : string
    ```

## **1/6: Fourth Look at ML**

- `bool` is not a primitive in ML - it’s a defined type using the keyword `datatype`
- Enumerations

    ```ml
    - datatype day = Mon | Tue | Wed | Thu | Fri | Sat | Sun;
    datatype day = Fri | Mon | Sat | Sun | Thu | Tue | Wed
    - fun isWeekDay x = not (x = Sat orselse x = Sun)
    val isWeekDay = fn : day -> bool
    ```

  - Type inference of ML applies to new types
  - `day` in the example is called a type constructor and the member names are called data constructors
    - Data constructor names are capitalized by convention
  - ML doesn’t expose the underlying representation of values within an enumeration
    - Only operations that are permitted are comparisons for equality
  - Can use data constructors in patterns

    ```ml
    fun isWeekDay Sat = false |
        isWeekDay Sun = false |
        isWeekDay _ = true;
    ```

- Data Constructors with Parameters
  - Can add a parameter to a data constructor by adding the keyword `of` followed by the type of parameter

    ```ml
    datatype exint = Value of int | PlusInf | MinusInf
    ```

    - Each `Value` will contain an `int` → cannot treat `Value`s as `int`s

    ```ml
    - PlusInf;
    val it = PlusInf : exint
    - MinusInf;
    val it = MinusInf : exint
    - Value;
    val it = fn : int -> exint
    - Value 3;
    val it = Value 3 : exint
    ```

  - Can extract the parameter through pattern matching

      ```ml
      - val (Value y) = x;
      val y = 5 : int
      ```

  - This pattern is nonexhaustive

    ```ml
    - val s = case x of
    =   PlusInf => “infinity” |
    =   MinusInf => “-infinity” |
    =   Value y => Int.toString y;
    val s = “5” : string
    ```

- Type Constructors with Parameters
  - The parameters for a type constructor are type parameters and the result is a polymorphic type constructor
  - `option` type constructor is pre-defined in ML

    ```ml
    datatype ‘a option = NONE | SOME of ‘a;
    - SOME 4;
    val it = SOME 4 : int option
    - SOME 1.2;
    val it = SOME 1.2 : real option
    ```

    - Useful for functions with undefined results
    - Function to handle division by 0

        ```ml
        - fun optdiv a b =
        =   if b = 0 then NONE else SOME (a div b);
        val optdiv = fn : int -> int -> int option
        ```

    ```ml
    datatype ‘x bunch = One of ‘x | Group of ‘x list;
    - One 1.0
    val it = One 1.0 : real bunch
    - Group [true, false];
    val it = Group[true, false] : bool bunch
    ```

  - ML doesn’t always have to resolve the type of a `datatype`, it depends on the operators being applied to it
- Recursively Defined Type Constructors
  - In data constructors of a `datatype` definition, you can use the type constructor being defined

    ```ml
    datatype intlist = INTNIL | INTCONS of int * intlist
    fun intlistLength INTNIL = 0
    |   intlistLength (INTCONS(_, tail)) = 1 + (intlistLength tail);
    ```

    - This type is restricted to the type `list int` → not parametric

        ```ml
        datatype ‘element mylist = 
        NIL | 
        CONS of ‘element * ‘element mylist;
        ```

  - Polymorphic binary tree definition

    ```ml
    datatype ‘data tree =
        Empty |
        Node of ‘data tree * ‘data * ‘data tree;
    ```

    - Produce a list of all elements in a tree

        ```ml
        fun listall Empty = nil
        |   listall (Node(x, y, z)) = listall x @ y :: listall z;
        ```

## **1/7: Syntax**

- Last time
  - Orthogonality
  - Efficiency
  - Safety
- One more issue
  - Mutability - how easy it is to change or extend the language
    - Successful languages must evolve
    - BASIC was developed on the GE 225 mainframe
      - Interpreter - very slow
      - 40ms to add
      - 500ms to divide
      - 40 KiB RAM
      - 20 simultaneous users
      - Very stripped down language compared to modern languages
    - C was developed on the PDP 11/45 (1975)
      - 4ms to add
      - 1.2ms memory cycle time → memory faster than CPU
        - Uniform access to memory
        - Results in syntax like `*p`
          - Loads from/stores to memory → cheap
          - `a + b` looks bigger → is slower
        - Nowadays:
          - Memory access is considerably slower than computation
          - Caching is crucial
          - Language design for older machines is aging out → not a good design for modern machines
      - 16 KiB RAM
    - C and porting
      - In POSIX/Linux/Unix, close function called with an invalid file descriptor should return `-1` and set `errno` to `EBADF`
      - In MSVC, `close` function called with an invalid file descriptor throws an exception
      - Suppose you have a pile of code that assumes POSIX, but is run under MSVC
        - You don’t want to have to change all your code
        - Here’s what we did in GNUlib
          - Ordinary code:

            ```c++
            #include <unistd.h>
            int f (void) {
              if (close (fd) != 0 && errno == EBADF) return 1;
              else return 0;
            }
            ```

          - Our own `unistd.h`:

            ```c++
            #include next <unistd.h>
            #define close rpl_close
            ```

          - `workaround.h`:

            ```c++
            #ifdef MSVC
            #define TRY try {
            #define CATCH } catch {
            #define DONE }
            #else
            …
            #endif
            ```

          - Our own library

            ```c++
            #include <unistd.h>
            #include <workaround.h>
            int rpl_close (int fd) {
                TRY
                  int r = close (fd);
                CATCH
                  r = -1;
                  errno = EBADF;
                DONE
                  return r;
            }
            ```

      - Make C more portable
    - Another example of syntax mutability: Prolog
      - Lets you define your own operators

        ```prolog
        :-op(500, yfx, [+,-]).
        ```

        - `+` and `-` are operators with precedence 500, are binary operators, and are left associative

        ```prolog
        :-op(400, yfx. [*,/]).
        ```

        - `*` and `/` are operators with precedence 400, are binary operators, and are left associative
        - Lower number for precedence represents a higher priority
        - `f` = function symbol
        - `y` = operand of equal or lower-numbered precedence
        - `x` = operand of lower-number precedence

        ```prolog
        :-op(200, fy, [+,-]).
        ```

        - Can declare same operator to have a different meaning

        ```prolog
        :-op(200, xfy, [**])
        ```

        - Right-associative

        ```prolog
        :-op(700, xfx, [=, \=, ==, =<, >=, …]).
        ```

        - These are non-associative operators
        - `a >= b >= c` is a syntax error
        - Makes Prolog more useful/extensible
        - Typically present in languages catering to specialties with their own notation
          - Prolog → NLP
      - Harder to implement, worried about confusing programmers
        - You can overdo language customization
- Syntax
  - Definition - form independent of meaning
    - Worried about what the programming language looks like without worrying about what it means
    - Ambiguity is sometime desirable in English, but not in programming languages
  - Why you should prefer one syntax to another
    - It’s what people are already used to (why Java looks like C++)
    - It’s simple and regular (Lisp)
    - It’s readable
      - Leibniz’s criterion: a proposition’s form should mirror its meaning
    - It’s writable/concise
    - It’s redundant - prefer redundancy to catch mistakes
    - It’s unambiguous
- Syntax technical issues
  - 2 levels of syntax is very common
    - Lower level: tokenization - easy - still matters + performance
    - Higher level: parsing
  - Tokenization - split up input into tokens
    - Some stuff gets thrown away during tokenization
      - Comments
      - Whitespace
    - Issue: do you allow whitespace within tokens?
    - Tokenizers are greedy - they take the longest sequence of characters that would be a valid token → fast
    - Issue: loss of information
      - Token - which syntactic category
      - Lexeme - token + extra info needed for semantics
    - Issue: keywords vs. identifiers
      - C and C++ have reserved words - look like identifiers, but are not
        - There are certain strings like `“if”` that cannot be used as identifiers
      - Makes extending the language harder

          ```c++
          int class = 29; // ok in C, not in C++
          ```

      - Some languages avoid this problem by not having reserved words (PL/I)
        - Easier to extend the language
        - Rules for tokenization are more complicated
      - The C solution to this problem
        - Reserves all identifiers beginning with `_` and then a capital letter or `_`
        - New keywords in C all begin with `_` and a capital letter

          ```c++
          _Noreturn void f(void) {
            ...
          } // f never returns
          ```

  - Parsing
    - Assumption is input is a finite sequence of tokens
    - `“terminal symbol”` - token
    - We need to specify the language in order to figure out how to parse it
      - Context-Free Grammar (CFG) is the typical way it's done
      - FORTRAN and Python are counterexamples
    - Terminology:
      - Terminal symbol - one of a chosen finite set (dozens to hundreds)
      - String - finite sequence of terminal symbols
      - Parser is given a string and asked to parse it
      - How to generate a string that belongs to a particular language
        - Language - set of strings
        - CFG - set of terminal symbols + set of nonterminal symbols each representing a phrase + set of grammar rules + start symbol - (one of your nonterminal symbols)
        - Rules - LHS (nonterminal symbol) and a RHS (finite sequence of symbols)
        - Example:

          ```json
          S => Sa
          S => Sb
          S => c
          ```

      - Sentence - member of a language

## 1/12: **Ambiguity**

- Usage of grammars
  - Computer science theory
    - Language definitions
    - How to automatically process languages
  - Take a simple grammar

    ```json
    S -> S a
    S -> b
    S -> ( S )
    ```

    - This allows us to define a language
    - Also allows us to parse sentences in the language
      - Want the parser to be able to prove to us that a given string is in the language
        - Leftmost derivation proof:
          - We have a string of symbols, initially, just a single string containing just the start symbol
          - Step: replace the leftmost nonterminal with a right-hand side of a rule which has that nonterminal as its left-hand side
          - Keep repeating this step as long as there is any nonterminal left in the string

            ```json
            S 3
            ( S ) 1
            ( S a ) 1
            ( S a a ) 2
            ( b a a )
            ```

            - Can express as 3 1 1 2 in shorthand
          - Don’t necessarily know which rule to use, just need to run it and check
      - Parse tree representation
        - Same power as derivations
        - Easier to read for more complex grammars
        - Multiple parse trees can exist for the same string
          - If the grammar is unambiguous, every parseable sentence has a unique parse tree
        - A tree where leaves are all terminals, interior nodes are all nonterminals, each interior node matches a rule (LHS is node, RHS is children)
- Problems that you can run into with grammars
  - Nonterminals that are used but not defined

    ```json
    S -> T b
    S -> S a
    S -> c
    ```

    - No definition for T despite use in rule 1
  - Nonterminals that are defined but never used

    ```json
    S -> S a
    S -> c
    T -> S b
    ```

    - No use of T despite definition in rule 3
  - Nonterminals that can never be reached from the start symbol

    ```json
    S -> S a
    S -> c
    T -> U d
    U -> T e
    ```

    - T and U are both useless despite being used and defined
  - Useless loops

    ```json
    S-> S a
    S -> c
    S -> S
    ```

    - Last rule is useless/counterproductive by introducing ambiguity for no reason
  - Problems are similar to what you find in your ordinary programs
  - Bugs like these in your grammar is likely to cause a similar bug in the corresponding parser
  - Syntactic constraints that your grammar doesn’t capture
    - Example from natural languages - small subset of English

      ```json
      N { dog, cats }
      V { barks, meow }
      Adj { brown, black }
      Adv { loudly, quietly }
      S -> NP VP .
      NP -> N
      NP -> Adj NP
      VP -> V
      VP -> VP Adv
      ```

      ```json
      dog barks loudly
      brown cats meow
      dog meow softly
      ```

      - Should be bad → need to distinguish between singular and plural
    - Grammar size grows exponentially with the number of attributes
      - Typically not done
  - Your grammar tries to capture too much detail
    - Typically people lean towards leaving stuff out
  - Ambiguity
    - Can come up in seemingly reasonable grammars

        ```json
        E -> E + E
        E -> E * E
        E -> ID
        E -> NUM
        E -> ( E )
        ```

      - Ambiguous for `a + b * c` → will result in 2 different interpretations
        - `(a + b) * c`
        - `a + (b * c)`
        - Doesn’t capture precedence/associativity
      - Fix this ambiguity

        ```json
        E -> E + T
        E -> T
        T -> T * F
        T -> F
        F -> ID
        F -> NUM
        F -> ( E )
        ```

    - Ex) Subset of C programming language

      ```json
      STMT -> ;
      STMT -> EXPR ;
      STMT -> return ;
      STMT -> return EXPR ;
      STMT -> break ;
      STMT -> continue ;
      STMT -> while (EXPR) STMT
      STMT -> do STMT while (EXPR) ;
      STMT -> if (EXPR) STMT
      STMT -> if (EXPR) STMT else STMT
      STMT -> for (EXPROPT ; EXPROPT ; EXPROPT) STMT
      STMT -> switch (EXPR) STMT
      STMT -> {STMTS}
      EXPROPT -> EXPR
      EXPROPT ->
      STMTS ->
      STMTS -> STMTS STMT
      ```

      - Why do `STMT -> return EXPR ;` and not `STMT -> return (EXPR) ;`
        - C designers didn’t want to clutter code with unnecessary parentheses
          - Not going to be ambiguous without them, semicolon is good enough
        - `STMT while (EXPR) STMT` instead of `STMT -> while EXPR STMT`
          - C would be ambiguous otherwise → `while x < y ++x;`
          - Hard to figure out where expression stops and where statement starts
          - Trickled down to `do-while` due to consistency, despite not being necessary for ambiguity
      - `If-then-else` ambiguity
        - `if (EXPR) if (EXPR) STMT else STMT`
          - Entire `if-else` nested, or just the `if` nested?
          - `else` matches closest `if` that it can
          - Fix:

            ```json
            STMT -> if (EXPR) STMT
            STMT -> if (EXPR) LSTMT else STMT
            LSTMT can be anything except an else-less if → doubles the grammar size
            STMT -> LSTMT
            STMT -> if (EXPR) STMT
            ```

            - Replace all other `STMT` rules with `LSTMT`
    - Avoiding ambiguity clutters your grammar, and may people don’t want to bother
      - Concrete - the unambiguous grammar
      - Abstract - ambiguous grammar
        - Parsers prefer this due to simplicity and speed
- Alternate notations for grammars
  - `E -> E + E`
  - `<E> ::= <E> + <E>`
  - `expr: expr + expr`
  - Internet RFCs (Request for Comments)

    ```json
    msg-id = “<” id-left “@” id-right “>”
    id-left = dot-atom-text / obs-id-left
    id-right = dot-atom-text / no-fold-literal / obs-id-right
    no-fold-literal = “[“ *dtext “]”
    ```

    - Rule: LHS = RHS
    - Nonterminals are `id-left`, `id-right`
    - Terminals are quoted
    - Example `msg-id`: `Message-ID: <11232143.fsf@cs.ucla.edu>`
    - This set of rules is an extended version of the rules we’ve seen so far, in that `*X` in the RHS is shorthand for 0+ occurrences of `X`

## **1/14: Functional Programming**

- We can turn our grammars into regular expressions
  - Can you do this with any BNF grammar? No
  - Regular expressions can’t count, they can’t deal with nesting
    - Impossible:

      ```json
      Expr -> “(“ Expr “)”
      Expr -> ...
      ```

    - Possible:

      ```json
      Seq -> Unit
      Seq -> Unit Seq
      ```

      - Doable because it only performs tail recursion
- ISO standard for EBNF
  - International Standardization Organization
  - CS applications tend to use different EBNF notations → hard to read
    - Basic idea is to have an ISO standard for EBNF
  - Double/single quote terminal symbols
  - Nonterminal symbols can contain spaces
  - `(A)` - Can parenthesize to override precedences
  - `[A]` - 0 or 1 of a nonterminal
  - `{A}` - 0 or more of a nonterminal
  - `N*A` - `N` or more `A`s
  - `A - B` - `A` but not `B`
  - `A, B` - `A` concatenated with `B`
  - `A | B` - `A` or `B`
  - `id = A` - rules
  - Used a grammar to formally specify the syntax of ISO EBNF, used ISO EBNF

      ```json
      syntax = syntax rule, {syntax rule}
      syntax rule = meta id, ‘=’, defns list, ‘;’;
      defns list = defn, {‘|’, defn};
      defn = term, {‘,’, term};
      term = factor, [‘-’, exception];
      exception = factor;
      factor = [integer, ‘*’], primary
      ...
      ```

  - Philosophically in trouble:
    - We’ve defined ISO EBNF by using ISO EBNF
- Syntax graphs/syntax diagrams
  - Used in manuals/documentation for big languages
    - SQL - used for database queries
      - Many suppliers provide extensions to SQL
      - They need to document the syntax for their extensions
      - Diagrams can simplify the description of the syntax
    - Shorter example - Scheme
      - Example is a simple one → may not be motivating
- Functional programming
  - Motivations
    - Clarity - traditional programming languages use non-mathematical notation
      - Build on top of mathematicians’ work instead of reinventing it
      - Also a problem of performance
    - Performance - parallelizability
      - C++, Python, etc. force you to think/write code sequentially
      - Compilers often can’t optimize code through parallelization
  - Key idea: avoid side effects
    - A side effect is a change to the machine state because a statement was executed
      - Changing contents of visible storage
      - Do I/O
    - Code free of side effects has better modularity
    - Avoiding side effects avoids the problem of the same name meaning different things to different people
      - No assignment statements
      - Better clarity and better caching
      - Technical term - referential transparency
  - Many functional languages - ML, OCaml, F#, Scala, etc.
    - Used for scientific programming (number crunching, needed parallelization)
    - Functional programming makes it easier to write programs that reason about other programs
      - Side effects get in the way of this sort of reasoning
  - OCaml vs. ML
    - OCaml is more popular at UCLA
      - Little more flexible and more support
    - Minor syntactic differences
    - Floating point arithmetic is more of a pain
  - Basic properties of OCaml
    - Static type checking using type inferencing
      - Like C++, Java, etc.
    - You need not write down types all the time
      - Like Python, Scheme, etc.
    - No need to worry about storage management - has a garbage collector
      - Like Java, Python, Scheme, etc.
    - Good support for higher-order functions
    - Operates on a REPL
    - `If-then-else` branches must be the same type
    - Tuples can be heterogeneous, lists cannot
      - Lists can be flexible in length, tuples cannot
    - `‘a` is a type variable, makes a generic type for type inference
    - Everything is immutable in our subset of OCaml

## 1/19: **OCaml**

- Idea is to see how to explain OCaml in a basic core + add-ons
  - You see this all the time - C++ core language + libraries
  - OCaml also has core language + libraries/modules
- What’s the core of the OCaml language (add-ons will still be part of the language)
  - Our add-ons will be syntactic sugar - a nice way of writing something that’s an extra feature of the language that you could’ve - done without
    - C++: `i++` and `i += 1` and `i = i + 1`
  - In `val f : int -> int = <fun>` in OCaml REPL, the `<fun>` stands for the machine code to implement a function
  - Traditionally, every function needs a name
    - Functional languages introduce the idea of anonymous functions
      - Names and functions are orthogonal
    - Creeps into traditional languages as lambda functions
  - Every function in OCaml has 1 parameter
    - OCaml handles multi-parameter functions through currying → function takes 1 argument, then returns a function to take in the - next argument, and so on
    - Nowadays, this is not simply a notational convenience
    - Can also pass as a tuple
    - Currying more powerful → don’t need all of the parameters when the function is called
  - If you just write `x y z`, it’s parsed as 2 function calls
    - First is a call to `x`, then a call to whatever `x y` returns
    - OCaml’s optimizer optimizes away the excess `call` and `ret` instructions or uses cheaper versions of the instructions
    - When these execute, the code knows about the first parameter, how?
      - OCaml interpreter could clone the machine code and mentally substitutes the first parameter for all of its occurrences → now has a new machine code sequence for next function
      - Typically, OCaml interpreter creates a pointer that implements the next function
        - OCaml functions are represented by fat pointers
          - Pointer to the machine code
          - Pointer to the environment that the code executes in
      - You cannot do this in C/C++ - their pointers only point to machine code, they are single word pointers
        - You can achieve the effect by passing an extra environment argument to the function manually
  - OCaml has syntactic sugar for common operators
    - `3 + 4` vs. `(+) 3 4`
    - Operators are functions
- OCaml patterns are used in match expressions

  ```ocaml
  match l with
  | h::t -> 3::h::t
  | [] -> [4]
  ```

- Some OCaml patterns
  - `a` - matches anything, binds `a` to that value
  - `_` - matches anything, and discards it
  - `0` - matches only itself (any constant)
  - `P, Q` - matches any tuple with 2 elements, first matches `P`, second matches `Q`
  - `()` - matches any tuple with 0 elements
  - `[P;Q;R]` - matches any 3 element list whose components match `P`, `Q`, and `R` respectively
  - `P::Q` - matches any list whose head matches `P` and tail matches `Q`
  - `T P` - matches any object built from constructor `T` with argument matching the pattern `P`
    - `::` is just another constructor (with 2 arguments)
- Higher order function that does pattern matching
  - Goal: find the maximum element in an `int list`

    ```ocaml
      let rec maxlist l = 
        match l with
        | h::t -> let mt = maxlist t in
            if mt < h then h else mt
        | _ -> -999999999
    ```

  - Let’s generalize it to list of anything

    ```ocaml
    let rec maxlist lt identity = function
      | h::t -> let mt = maxlist lt identity t in
          if lt mt h then h else mt
      | [] -> identity
    ```

- 2 keywords: `fun` and `function`
  - They operate differently (syntactic sugar in different ways)
  - `fun` is for currying

    ```ocaml
    fun x y -> x + y
    ```

  - `function` is for pattern matching

    ```ocaml
    function 
      | [] -> 0 
      | _::l -> f l
    ```

## **1/21: OCaml and Types**

- Simple OCaml function to reverse a list

  ```ocaml
  let rec reverse = function
    | [] -> []
    | h::t -> (reverse t) @ h
  ```

  - This is wrong, because the type is wrong

  ```ocaml
  let rec reverse = function
    | [] -> []
    | h::t -> (reverse t) @ [h]
  ```

  - Bad performance, `O(N^2)` due to repeated work with the `@` operator
  - Add an accumulator - an extra argument that accumulates the work you’ve already done

    ```ocaml
    let rec revall a l =
      match l with
      | [] -> a
      | h::t -> reverse h::a t
    let reverse l = revapp [] l
    ```

    - Can simplify further

      ```ocaml
      let reverse =
        let rec revapp a =
          match l with
          | [] -> a
          | h::t -> reverse h::a t
      ```

- You can debug your OCaml program by looking at types
- Translation environments
  - Compiler: translate from source code to machine code
    - Walks through parse tree and generates an intermediate representation
      - Set of instructions for a machine that doesn’t exist
      - Designed for compiler convenience
    - The intermediate representation is optimized
    - Then translated to assembly, `.o`, linking, executable, RAM, etc.
    - The software tools approach → you have a POSIX pipeline of programs
      - Used for low-level stuff (IoT)
      - Preprocess → compile to assembly → assembly to object → link to executable → run
    - The integrated development environment approach → single app that does it all
      - Do modularization of this app via object-oriented techniques rather than a POSIX style pipeline
      - Used more for high-level stuff
    - Hybrids
      - Dynamic linking - executable can run dynamic linker to bring code into RAM so that the executable can run the code
        - Self-modifying code
        - Performance implications
      - Just-in-time compilation - conventional system takes in a program and turns it into a `.class` file
        - Class file fed into the executable, which has a slow interpreter
        - Can speed up the interpreter by having a compiler that compiles bytecode into machine code
        - As the program is running, the working memory keeps track of how often each method is executed
          - Commonly executed code is translated from byte code to machine code to improve runtime at the cost of added complexity
  - Interpreter: keep source code analog in RAM, an interpreter executes the text of the program
    - Code is never translated to machine code, uses the interpreter’s machine code
    - Often converts to byte code for efficiency, a software-defined instruction set
    - Worse runtime performance than compiling, easier to debug

## **1/26: Types**

- Types in OCaml, Java, C++, etc.
  - We’ll start by looking at static type checking
- Why do we have types?
  - “Types are more trouble than they’re worth” - is that so?
- What is a type?
  - A type is a set of values
    - `int = { INT_MIN, …, -1, 0, 1, …, INT_MAX }`
    - There are set-oriented languages
      - Allows for countably and uncountably infinite sets through predicates
  - A type describes how objects are represented in memory

    ```c++
    struct s { 
      int a;
      char b[7];
      double c;
    } x;

    &x.b[0] - (char *) &x.a == sizeof (int)
    ```

    - Not exactly the same
      - `char *` and `int *` have the same representation on x86-64 → not guaranteed on non-byte-addressable platforms
    - Some details, but not all
  - A type is a set of objects and operations defined on those objects
    - Like C++ in which a `class` has everything private except for some constructors and methods
    - Probably the one gaining in popularity
  - (Research) a type is a set of objects, operations, and axioms about the objects
- Distinction between primitive and constructed types
  - Primitive types are built-in (`int`, `double`, `bool`, `char`, etc.)
  - Constructed types are defined by the programmer (`char b[7]`, `struct s {...};`, `char *const *p`, etc.)
- Primitive types have plenty of problems all by themselves
  - Portability issues
    - What are the set of integer values? It’s machine-dependent
      - 32-bit 2’s complement integers is most common
      - 16-bit or 36-bit, ones’ complement, signed magnitude, etc. still exist
    - `char` goes from `-128` to `127` if using `GCC`, other compilers may disagree
    - IEEE-754 floating point arithmetic
      - Set of objects for `float`s: 32-bit representation split into 1 bit sign, 8-bit exponent, and the 23-bit fraction
        - The number represented is `2**(e - 127) * 1.f`
        - `+`/`-` depends on the sign
        - `1.f` stands for the base-2 number
        - Only true if `0 < e < 255`
      - `e = 0 → 2**(-126) * 0.f` → denormalized value
        - The number `0` is in this category
        - All bits `0` represents `+0`, there is a `-0`, both are equal numerically
        - 2 distinct representations of `0` → issue
      - `e = 255` and `f = 0` → `+`/`-` `infinity`
        - `f` / `g` returns `infinity`, protects against overflow
        - `(f / g - f / g)` → no answer is mathematically valid, returns `NaN`
      - `+- NaN` if `e = 255`, `f != 0`

        ```c++
        float f = 0;
        f / f = NaN
        ```

        - How do you compare `NaN`s to numbers?

          ```c++
          float f = 0;
          float nan = f / f;
          if (nan < 5) // by convention, NaNs are never <, =, or > than anything
          float f = 0.0/0.0, g = f;
          f != g && memcmp (&f, &g, sizeof f) == 0;
          ```

          - `NaN` can’t be equal to anything, but `f` and `g` have the same bits
      - An axiom we’d like to be true:
        - `f != g` implies that `f - g != 0`
          - True of real numbers, is it true with floats? Yes because of tiny numbers
      - Common fallacy - never compare floating point values for equality
        - Not `if (f == g)`, should be `if (fabs(f - g) < 0.000001 * f)`
        - Not necessarily true
        - Perfectly valid to compare for equality with caution/knowledge of how type works
      - Note that there are no exceptions in conventional floating point arithmetic, special values used instead
        - An alternative approach would be to throw an exception if you over/underflow → no `NaN`s, just exceptions
        - Should you use exceptions or special values?
          - Partial functions vs. total functions
          - x86-64 hardware supports both models → hardly anybody does this
            - Due to inertia and the fact that lot’s of useful computations do better without it
- Some uses of types
  - Annotations (`int x` tells the programmer that `x` is an `int`)
    - Also tells the compiler useful information that allows it to generate better code
      - Makes compilers faster
  - Inference (`int i; float f; return i * f;` tells the programmer and compiler what types are returned
    - Annotations and inference kind of fight each other
    - OCaml is big on type inference
  - Checking
    - Static vs. dynamic type checking
      - This can be a spectrum
      - Some languages have both (C++/Java are primarily static, but have ways to do dynamic)
    - Static - done before the program starts (compile-time or linking-time)
    - Dynamic - at runtime, as the program runs
      - The same code can succeed sometimes and fail other times
    - Strongly typed - all operations are type-checked
      - C is not strongly typed → you can cast pointers
        - Can get you into undefined behavior
      - Favored for reliability
- Type equivalence
  - Two types `T` and `U` → does `T = U`?
  - 2 standard answers
    - Name equivalence - 2 types are the same if they have the same name
    - Structural equivalence - 2 types are the same if they’re laid out in memory the same
      - If they behave the same, as far as the ABI goes
        - ABI = Application Binary Interface
    - Example of name equivalence in C/C++

      ```c++
      struct s { int a; struct s*  next; };
      struct t { int a; struct t*  next; };
      ```

      - Different names = different types
    - Example of structural equivalence in C/C++

      ```c++
      typedef int s;
      typedef int t
      s x;
      t y = x; // this is OK
      ```

    - Suppose we wanted structural equivalence in C/C++

      ```c++
      struct s {
        int a;
        struct t* next; 
      };

      struct t {
        int a;
        struct s* next;
      };
      ```

- Subtypes
  - 2 types `T` and `U`, is `T` a subtype of `U`?
    - Assumption is that if `T` is a subtype of `U` and `U` is a subtype of `T`, then `T` and `U` are equivalent
  - Why do we need subtypes?
    - General idea: we have a specific value of type `T` that we want to pass as an argument of type `U` to a more general function
    - Should work regardless of equivalence type
  - Examples
    - Pascal:
      - `type lower_case_alpha = ‘a’...’z’;` is a subtype of the type `char`
    - Common Lisp:
      - `(declare (type (and integer (satisfies evenp)) x))` is a subtype of `integer` → set of all integers for which `(evenp i)` returns `true`
    - In class-based systems, a subclass is a subtype
      - `class C extends P { … }` → `C` is a subtype of `P`
    - Generally speaking, subtypes can have operations that supertypes lack
      - Subset of values implies superset of operations
    - C++
      - `char *` vs. `char const *`
      - Which of these is a subtype of the other?
        - Unrestricted pointer vs. restricted (only reads allowed) pointer
        - `char *` is a subtype of `char const *` → more operations available on `char *`
- Polymorphism
  - Occurs when you have some part of your program that has many types all at once
  - A function that accepts many forms is polymorphic
    - Many languages are polymorphic in this sense
    - Lisp : `(+ 3 4)` is based on `int`, `(+ 3.0 4)` is based on `int` and `float`
  - 2 major forms of ad hoc polymorphism in conventional languages
    - Overloading
      - Identifying which function to call by examining the types of its arguments (and sometimes the type of the context)
      - Arithmetic operators in C, C++, Java, etc.
      - In statically-compiled languages, this is often implemented by having several different functions at the machine level to - implement one source code function
        - `f = cos(y)` → `call cosf` (`float`), `call cosld` (`long double`)
      - This can even work in C++ where you can define your own overloaded functions via name mangling
        - Works as long as caller and callee agree on the name mangling convention
    - Coercion
      - Implicit type conversion
        - `double f = 0;` → uses coercion, different types
        - `double d = f + 1;` → no `+ : double -> int -> double`, only have homogeneous operators
          - Coerce `1` to `double` first, then use built-ins
        - Adds convenience, but also complexity
          - `double f(int, double)`
          - `double f(double, int)`
            - `f(1, 0)` is ambiguous in this situation
              - C++ rule is to disallow this
  - We want something better and cleaner than this if we can get it
- Parametric polymorphism
  - Want the polymorphism to be more structured than ad hoc
  - When a function’s type contains one or more type variables
  - Walk through a collection of strings and remove all the strings of length 1
    - Without:

      ```java
      static void remove1 (Collection C) {
        for (Iterator i = c.iterator(); i.hasNext(); )
          if (i.next().length() == 1)
            i.remove();
      }
      ```

      - Won’t compile without a case because `i.next()` returns `Object` and `Object` doesn’t have a `length()` method → cast result of `i.next()` to `String`
      - Slow and ugly → extra runtime check due to strong-typing of Java
      - Risk of crashing
    - With:

      ```java
      static void remove1 (Collection<String> c) {
        for (Iterator<String> i = c.iterator(); i.hasNext(); )
          if (i.next().length() == 1)
            i.remove();
      }
      ```

      - No cast needed, no runtime check
      - Code is safer → no runtime exception possible
  - 2 typical ways to do parametric polymorphism
    - Templates (C++, Ada) represent code that doesn’t exist yet, but it will exist once you instantiate it
      - Compiler can finish the job of compiling the code when say what the types actually are in a caller or user of the template
      - May require multiple copies of the machine code, one for each type of instantiation
    - Generics (OCaml, Java) - code is compiled and type-checked just once
      - Only one copy of the machine code needs to exist, it’ll work on any types of arguments
      - This works because all types smell the same in the language
        - Every object is represented via a 64-bit pointer

## **3/2: Storage Management**

- Storage management
  - Memory management of activation records last time
    - Usually on the stack
  - Stack management is easy: LIFO so you can put it into an array
    - `sp` tells you how much you're using
- Heap storage management
  - Not LIFO - objects can be deallocated "at random"
  - You can't easily use an array with just an `sp`
  - There will be gaps in your storage
- Think of the heap as being in an arena - a big array of memory
  - We're trying to manage storage within that arena
  - Sometimes we'll have multiple arenas, but just 1 for now
- Primitives to manipulate this heap:
  - `P = malloc(N)` - allocate a new `N`-byte piece of storage
  - `free(P)` - free the block of storage addressed by `P`
- Issues that come up when doing heap management
  - How to keep track of roots - outside-the-heap pointer that points into the heap
    - Where do roots reside?
      - Stack (local variable in some stack frame)
      - Static storage (global or static variables)
      - Machine registers ("invisible" to programming language, still important in generated code)
    - Why do we need to know where the roots are?
      - We have 2 kinds of heap managers:
        - Explicit `free` is required to free storage
          - C, C++, Ada, ... (lower-level, more efficient)
          - The programmer has to help the heap manager to avoid memory leaks
          - The programmer keeps track of the roots in the program that they write
            - More efficient if the programmer doesn't make mistakes
            - Traditional garbage collectors may take a while to run, which will make your program's performance jerky
        - No `free` operation - heap manager frees storage automatically
          - These have garbage collectors that do this
          - The heap manager keeps track of roots
          - More popular nowadays
            - Fewer dumb errors that can crash your program

              ```c++
              p = malloc(100);
              free(p);
              p->next = NULL; // ERROR
              free(p); // ERROR
              ```

            - Fewer dumb errors that can bloat your program

              ```c++
              p = malloc(100);
              p = malloc(200); // not an error, but 100 bytes wasted
              ```

      - The find the roots question is crucial for garbage collector-based systems
      - One way (very simple, but can be slow):
        - Have just 1 root (in static storage in a well-known location)
          - It points to a big object that contains all of your static variables, plus a pointer to the newest frame in your stack
      - Another way:
        - Get help from the compiler
          - The compiler records where the roots are in a (read-only) data structure that it puts into the program where the garbage collector can see it
          - This data structure could represent things like this:
            - "There's a root at location `12345678`"
            - "If the currently executing function is `F`, then `F`'s frame has a root at offset `28`"
            - "If the current `ip` is in the range `10000-11000`, then `%rbp` is a root
      - Other possibilities too
  - How do you keep track of the free space?
    - The heap manager needs this to implement `malloc(N)`
    - A simple solution: maintain a free list

      ```c++
      struct free {
        void *freeblock;
        size_t blocksize;
        struct free *next;
      };
      struct free *freelist
      ```

      - Create a linked list to represent the free areas
        - Here's how to allocate:

          ```c++
          void *malloc(size_t n) {
            for (struct free **p = &freelist; *p; p=&p->next)
              if ((*p)->blocksize >= n) {
                void *result = p;
                *p = (*p)->next;
                return result;
              }
            return NULL;
          }
          ```

        - Here's how to free:

          ```c++
          void free(void *p) {
            struct free *f = p;
            p->m ...
          }
          ```

        - Problem: where do we store the free list? In a separate heap somewhere?
          - No, there's a better place to store the free list
          - Store the free list objects into the free areas themselves:

            ```c++
            struct free {
              size_t blocksize;
              struct free *next;
            };
            struct free *freelist
            ```

            ```c++
            void *malloc(size_t n) {
              // This might take a while if N is large
              for (struct free **p = &freelist; *p; p=&p->next)
                if ((*p)->blocksize >= n) {
                  void *result = p;
                  *p = (*p)->next;
                  return result;
                }
              return NULL;
            }
            ```

            ```c++
            void free(void *p) {
              struct free *f = p;
              f->next = freelist;
              freelist = f;
            }
            ```

          - This sample code is too simple - its performance will be lacking
            - It wastes storage by allocating a big block even if the user wanted a small one
              - To fix this: we should split free blocks when the user asks for a small one and we have a big one
            - We need to coalesce adjacent free blocks
              - Free list can become more and more fragmented as we free
              - How can we coalesce adjacent free blocks efficiently?
                - The obvious algorithm is `O(length of the free list)`, too slow for large systems
                - The usual approach here, is for the memory manager to keep extra words before and/or after each block, that record the block's size
                  - These words are not visible to the user

                    ```c++
                    void free(void *p) {
                      size_t sp = p;
                      size_t object_size = sp[-1];
                      size_t previous_object_size = sp[-2];
                      ...
                    }
                    ```

                  - These extra words are invisible to the programmer, but are crucial for performance
                  - Has safety downsides for languages that don't support subscript checking
            - Now, `free` is fast - `O(1)`, but `malloc` is slow - `O(|free list|)`
              - There's a common problem here: small blocks at the start of the free list
                - If you start off with large blocks at the start of the free list, and the caller does a lot of `malloc(16)`s, you'll carve out 16 bytes from the first block, until it shrinks to 15 bytes or fewer
                  - You then do this to the 2nd block and 3rd block and etc.
                  - You end up with a bunch of small blocks at the start of the free list, so every call to `malloc(16)` will take a long time
                - One possible solution: make the free list a circular list and use a roving pointer for tour free list pointer
                  - Each time you call `malloc`, you start with `freelist` being where it was after the most recent `malloc`
                  - This avoids some of the problem, but not all
                - Fancier solutions:
                  - Walk away from the first-fit approach, but use a best-fit approach instead
                    - This complicates the data structure, need a way to find the best block
                - The basic issue here is fragmentation
                  - External fragmentation: you have 1MB of free space all in tiny separated blocks, so `malloc(1000000)` fails even though you have enough space
                  - Internal fragmentation: user does `malloc(3)`, but you require all allocations to be a multiple of 16 for your data structures
                  - Want to avoid fragmentation and we also want a good CPU efficiency
- Traditional garbage collection
  - Mark and sweep algorithm, 2 phases:
    - `MARK` - start at the roots and mark every object that the roots point at
      - Assume that all objects have a spare bit that's initially `0`
      - Marking turns that bit into a `1`
      - Then look at all the pointers in all the marked objects, and mark all the objects they point to
      - Keep doing this as long as you keep finding objects that you haven't marked before
      - Typically done as a DFS of a "tree", since you don't follow cycles due to the marked bits
        - Cost: `O(number of objects in use + number of roots)`
    - `SWEEP` - walk through all the objects in your system
      - If an object is not marked, free it
      - Otherwise, clear its mark bit
    - You can think of `MARK`+`SWEEP` as being 2 subroutines of `malloc`, it calls `SWEEP` right after calling `MARK`
    - Do this whenever storage gets low
    - Simple, easy to implement
    - Can cause `malloc(10)` to take a long time
      - To overcome this problem:
        - Do garbage collection in a separate thread
          - This introduces race conditions
        - Every `malloc` and `free` call does a bit of `MARK`+`SWEEP`
          - Real-time garbage collectors do this
          - Slows down you allocation
          - Allocation time becomes more predictable
        - Just live with the problem
          - Can often be the best if the unstable performance can be tolerated
        - Use reference counts
          - Basic idea: the memory manager keeps an extra word with each object
            - This word counts the number of pointers to that object

              ```python
              q = "def"
              p = "abc" # "abc"'s reference count is 1
              q = p # "abc"'s reference count is increased, "def"'s reference count is decreased
              ```

            - Whenever a reference count decreases to 0, the memory manager frees the object
          - This slows down pointer assignment
            - Python is slow anyways, so who cares?
          - You don't need a garbage collector's `MARK`+`SWEEP`
          - The memory manager can reclaim objects exactly when they become garbage
          - Problem: circular data structures

              ```python
              p = { "a": 1, "b": 2 } # reference count of the dict is 1
              p["c"] = p # reference count of the dict is 2
              p = "def" # reference count of the dict is 1, not 0 --> dict not freed
              ```

            - Python traditional answer to this:
              - Don't write programs like that
                - Avoid circular data structures if you can
                - If you create a circular data structure, code should explicitly break the cycle before it stops using the data structure
            - C Python has fixed this by adding a garbage collector as a backup when reference counting leaks
            - Other Python implementations use garbage collection only
    - Can you do garbage collection in an application written in C++ or C for reliability's sake?
      - `free` and `del` induce dangling pointer bugs
        - We want something like:

          ```c++
          #define free(p) ((void) 0) // This turns free into a no-op
          ```

      - We want the memory manager to figure out how to free things, without my advice
        - This is done in Emacs (C), GCC (C++), Chrome (C++), etc.
      - Conservative Garbage Collection
        - C++/C compilers don't tell the memory manager where the roots are
        - So a memory manager cannot do `MARK`, because root locations are unknown
        - The basic idea: memory manager knows only where roots might be
          - Static variables (containing pointers)
            - This is in a single area, typically not that large, containing both pointers and other data
          - Stack
            - This is in a single area, typically not that large, containing both pointers and other data
          - Machine registers
            - This is tiny, containing both pointers and other data
          - The memory manager looks at all words in these 3 areas
            - If it looks like it could be a pointer into the heap, treat it as if it were a pointer into the heap
            - Heap addresses tend to be large and unusual integers
            - Occasionally, this will make an error, but the error is merely a memory leak; it won't crash the program
            - This finds all pointers, as well as some values that aren't really pointers
        - This also works on object contents
        - So you can have a conservative `MARK` algorithm, your `SWEEP` algorithm will run as normal
- These approaches are popular, but they still have a performance problem
  - Allocation is still too slow for some users that like to allocate lots of small objects
    - Classic example is a Scheme program that calls `cons` a lot
    - `(cons a b)` allocates a 2-word object and it gets called a lot
    - We can speed this up by using a common trick: specialized allocators for certain common sizes
      - This works well in C/C++, but it's terrible for Java --> next time

## **3/4: Parameter Passing**

- Finishing up on storage management
- Generation-based copying garbage collection
  - Based on generations and copying
    - Generations - sections of the arena that is the heap
      - Older generations are allocated long ago and can be treated as relatively stable
        - There is little garbage here, don't waste time garbage collecting here
      - Newest generation, called the nursery, has a heap pointer `hp` and a limit pointer `lp`
        - From `hp` to `lp` is free space
        - The objects in the nursery are the newest objects
        - High percentage of garbage here
      - In terms of pointers that cross generations, they typically point from newer to older
        - If this assumption is made, we can simply follow our roots to our nursery/newer objects and garbage collect without worrying about dangling pointers
        - Handle the exceptional case where pointer point backward separately
          - Should be uncommon --> solution may be complex
      - Focus the garbage collector on the new area
      - No free list, space allocated by looking at the nursery --> check if enough space
        - Allocation is very cheap
        - If not enough space, we can either garbage collect or allocate a new nursery from the OS
          - Decision is based on efficiency (time vs. space)
    - To garbage collect a generation (nursery):
      - Look at the roots into the nursery
      - Allocate a new nursery and copy the objects in the order we find them into the new nursery
        - Has overhead
  - Cost is only proportional to number of reachable objects
    - `MARK`+`SWEEP` is proportional to number of total objects
  - Squishing objects together into similar spots makes better use of caching
  - You have to update references to moved objects
    - This includes pointers within the objects themselves
  - There's a Java-specific problem with this approach: the `finalize` method
    - `Object` class defines a `finalize` method that's called by the garbage collector whenever it discovers an object to be garbage
      - This is a hook from the garbage collector into your code to let you free stuff that isn't garbage collector-managed
      - One of the main advantages of a copying collector is it doesn't need to free objects; this saves CPU time and cache accesses
        - This means that the copying collector doesn't even know where the freed objects are --> what happens if one of these freed objects has a `finalize` method?
      - The reason we have `finalize` is because the `MARK`+`SWEEP` garbage collectors of the 1990s made it cheap
    - Common solution: have 2 garbage collectors
      - `MARK`+`SWEEP` for the objects that have `finalize`, use a copying collector for everyone else
- Another problem with allocation (true of `MARK`+`SWEEP` or nursery-based): multithreaded applications

  ```c++
  static lock_t lock;
  static char *hp, *lp // global variables, subject to races
  void *malloc(size_t n) {
    lock(&lock) // terrible performance, critical section is a bottleneck
    if (n <= lp - hp) {
      void *r = hp;
      hp += n;
      unlock(&lock);
      return r;
    } else expensive(); // this must unlock too
  }
  ```

  - Better solution: give each thread its own free list/nursery --> no locks needed
    - This complicates the garbage collector
      - Suppose an object in one nursery references an object in another nursery (rare)
- Object pooling or quick lists - your app maintains its own private free list for objects that it allocates and frees a lot
  - This can make allocation very fast in the common case where there's a correctly-sized object on the free list
  - In a copying collector, this approach can slow your program down
    - The garbage collector sees your free list pointer as a root, carefully copies all the free objects
      - Slow - we're copying garbage
    - Allocation from the nursery will be just as fast or faster than allocating from your private free list
- Parameter Passing
  - Syntactic issues (what a function call looks like)
    - How argument values are matched to function parameters
      - Positional (caller and callee agree about number/order of arguments)
      - Variable number of arguments?
        - In Scheme, `(list 3 4 #f)` => `(3 4 #f)`
          - Defined by `(define list (lambda x x))`
            - `x` is bound to a list of caller arguments
        - In C, `#include <stdarg.h>`
          - Lower-level languages have a harder time with this
        - In Python, `def make_tuple(*x)`
          - Arguments passed as a tuple
      - Keyword correspondence

        ```python
        def arctan(y, x):
          ...
        return arctan(x=27, y=15)
        ```

        ```python
        def foo(a, *b, **c): # positional correspondence for a, varargs go into b, keyword args go into c (a dictionary)
          ...
        foo(27, 19, "xy", a=19, b="zw") # a = 27, b = 19, c = { "a": 19, "b": "zw" }
        ```

  - Semantic issues (what does it mean/how does it work?) harder
    - We want 2 incompatible things here:
      - Efficiency - function calls are very common, often with large arguments
      - Clarity - this often wars with efficiency
    - Call by value - the most common, and it's simple (C, C++, OCaml, Python, Scheme, etc.)
      - Caller evaluates the argument, gets a value, passes copy to callee
      - Callee's modifications to its parameter are local to callee
      - Good isolation between caller and callee
      - Large objects make this slow --> copy required
      - Suppose callee doesn't use parameter's value --> caller has done unnecessary work
    - Call by reference (Fortran, C++ (as an option))
      - Caller evaluates the argument only to get its address (not its value), passes that address to the callee
      - Callee always accesses parameter indirectly, through that pointer
      - Large objects can be passed efficiently
      - Callee can modify caller's objects (which can simplify API)
      - Less isolation between caller and callee
      - Aliasing can be a big problem --> hurts optimization, forces compilers to be cautious

        ```c++
        int f (int &a, int &b) {
          a = 1;
          b = 2;
          return a + b;     
        }

        int m;
        int n = f(m, m); // value overwritten, common optimizations not possible
        ```

        - Hurts human readers (misunderstanding code or spend a lot of time reading it)
        - Because of these aliasing problems, there are alternatives that have less aliasing
    - Call by result (Ada)
      - Caller doesn't evaluate its argument; just says where it is
      - Callee must initialize the corresponding parameter
      - When the callee returns, it copies the parameter's value back to the caller
      - Classic example: `read` system call of C (C does this by call by value):

        ```c++
        read(0, buf, sizeof buf); // 2nd argument is call by result --> callee must set buf accordingly
        ```

        - Difference between C and Ada is the aliasing rules
          - In C, if 2 variables alias, the compiler must generate slow code that respects the aliasing
            - It cannot do optimizations that would require the variables be distinct
          - In Ada, call by result parameter is separate, so no aliasing, so the compiler can optimize better, code is clearer, etc.
    - Call by value-result (Ada)
      - Caller passes copy to callee
      - Callee can modify its copy
      - When it returns, it passes the copy back
    - Call by name
      - Call by name : call by reference :: function : pointers
      - Basic idea is that caller doesn't evaluate its argument; instead, it passes to the callee a think representing its argument
        - A thunk is a parameterless procedure that, when you call it, will return the value you're interested in
      - Whenever the callee needs to know the value of a parameter, it calls the thunk
      - This avoid unnecessary work if the callee doesn't use the parameter

        ```c++
        void printSummary(int nitems, int avg) {
          if (nitems == 0) // Protects the procedure from being called in call by name
            printf("no items");
          else
            printf("%d items, avg is %d\n", nitems, avg);
        }

        int sum = 0;
        int n = 0;
        printSummary(n, sum / n) // This will crash in call by value: division by 0
        ```

      - Downside: performance
        - Overhead to building thunks
        - Bigger deal is that you need a function call on every access to a parameter
    - Call by need (Haskell)
      - Like call by name, but you call a thunk at most once and cache its return value
      - "Lazy evaluation" vs. "Eager evaluation"
        - Don't evaluate an argument to a function until you actually need it
        - Big picture: the program never actually does anything, it constantly puts things off in its to-do list
          - Your code forces it to do something by having it do an action whose result you can see
          - The system does the minimal amount of work to satisfy your demand
      - For many functional applications, this can be a win, due to optimization
