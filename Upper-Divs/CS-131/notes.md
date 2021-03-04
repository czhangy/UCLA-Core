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
        x f(int x) {// will break if x is an array type, non-flexible implementation
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
    - Context-free grammars - children of a node of a parse tree are only dependant on that node, not on neighboring nodes
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

  - Comparison operators remain standard and can be used on strings, chars, ints, or reals

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
    - `round` - `real` → `int` (round to nearest int)
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
