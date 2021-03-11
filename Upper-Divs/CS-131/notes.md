# COM SCI 131 - Winter '21 - Eggert



[TOC]

## **Lecture 1: Introduction**

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
      - He used this to produce the book's second edition + future versions
    - Side project: The TeXbook - book about TeX's design and algorithms, detailed internal doc. about TeX
      - `tex.pas` - the TeX source code, written in Pascal
      - `texbook.tex` - the TeXbook source code, written in TeX
      - Keeping these 2 files in sync is a pain
        - Side side project: Literate Programming
          - Basic idea: don't separate documentation and source code, put the documentation in source code → easy to keep in sync
          - One file: `tex.tangled` → contains source code and documentation
            - `p1 <tex.tangled >tex.pas` → throws away documentation
            - `p2 <tex.tangled >texbook.tex` → throws away source code
            - Designed notation to tangled documentation and source code to allow for separation
            - How to tell people about Literate Programming?
              - “Read the TeXbook” → too long
              - Simple introduction to the idea as a short paper → approached CACM (leading research journal)
              - Solve the word problem in tangled Pascal using a new data structure called a “hash trie” + included the CACM paper
              - Succeeded → Literate Programming is now common (JDK documentation, etc.)
          - But, it was a set-up job → paper included an afterword by CACM editor which was a suggestion for a better solution using the Unix shell
            - Find the words in the input: `tr -cs 'A-Za-z' '[\n*]'`
              - Takes the complement (`-c`) of the words and transliterates them into newlines
              - Squeezes out duplicates (`-s`)
            - Sort the resulting list: `tr -cs 'A-Za-z' '[\n*]' | sort`
            - Find the duplicates and remove them: `tr -cs 'A-Za-z' '[\n*]' | sort | uniq -c`
              - Count the duplicates (`-c`)
            - Sort the list in desired order: `tr -cs 'A-Za-z' '[\n*]' | sort | uniq -c | sort -rn`
              - Sort in reverse order (`-r`)
              - Sort in numeric order (`-n`)
            - Eliminate the extra newline: `tr -cs 'A-Za-z' '[\n*]' | sed 1d | sort | uniq -c | sort -rn`
              - `sed 1d` removes the first line, which is where the newline is located
            - One-line solution → do you really need Literate Programming?
              - Solution when the problem is so large that the language is scaling improperly
              - Keep stuff small → you don't need Literate Programming anymore
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

        - ```c++
          int *f(...) { // Ok - pointer to 0th element
              // Other code
          }
          ```

        - ```c++
          struct s { 
              int a[10]; 
          };

          struct s g(...) { // Ok - struct containing an array
              // Other code
          } 
          ```

        - ```c++
          typedef int[10] trouble;
          trouble h(...) { // Problem - you can't return the array
              // Other code
          }
          ```

        - ```c++
          #include <x.h>
          
          x arr;
          x f(int x) { // Will break if x is an array type, non-flexible implementation
              // Other code
          }
          ```

  - Runtime Efficiency (how long to run the program)

    - Could imply wall clock time, CPU time, RAM, I/O, network access latency, energy/power consumption, etc.
  - Compile-time Efficiency (how long to build the software)
  - Development-time Efficiency (how long to write the code)
    - More verbose code takes longer to write and read
    - Code that's too concise can be unreadable
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

## **Reading 1: Programming Languages**

- 4 main types:
  - Imperative (C) - marked by iteration and assignment
  - Functional (ML, Lisp) - marked by recursion and single-value variables
  - Logic Programming (Prolog) - marked by rules of logical inference
  - Object-Oriented (Java) - Builds upon the hallmarks of imperative languages with objects, bundles of data that can perform - operations on itself
  - There are more types, and some languages are so unique they don't fit into any given type (Forth, APL, etc.), while others - combine attributes of multiple other types (Python, Ruby, etc.)
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

## **Reading 2: Defining Program Syntax**

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
  - As long as a string can be generated by at least one parse tree using the language's rules, that string is in the language
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
  
    - ```java
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
  - This structure is incomplete, a we've only defined the phrase structure of a language, that is, how to construct parse trees with tokens at the leaves
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
      - This styling is sometimes incorporated into the formal part of a language's definition (Python)
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

## **Reading 3: First Look at ML**

- ML operates in interactive mode - prompts an expression, type an expression, evaluates the expression, prints the value, repeat
- ML attempts to infer the type of an expression's result
- ML maintains a variable called `it`, which contains the value of the last expression's result

  - ```ocaml
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
  
  - ```ocaml
    - “fred”;
      val it = “fred” : string
    ```
  
  - Can use escape sequences for special characters

  - `\t` = tab, `\n` = newline, `\”` for quotes, etc.
  - Use `#”X”` to get a character constant rather than a string
  
    - ```ocaml
      - #”H”;
      val it = #”H” : char
      ```
  
- Operators
  - Operators for addition, subtraction, and multiplication are standard
  - Division is divided into the `div` and `mod` operators
    - `div` calculates the integer quotient
    - `mod` returns the remainder of the integer division

      - ```ocaml
        - ~ 1 + 2 - 3 * 4 div 5 mod 6;
        val it = ~1 : int
        ```

    - `/` exists as an operator for real-division

      - ```ocaml
        - ~1.0 + 2.0 - 3.0 * 4.0 / 5.0;
        val it = ~1.4 : real
        ```

  - `^` is used as a string concatenation operator

    - ```ocaml
      - “Hello “ ^ “World”;
      val it = “Hello World” : string
      ```

  - Comparison operators remain standard and can be used on `string`s, `char`s, `int`s, or `real`s

    - ```ocaml
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
  - Equality test (`=`) and inequality test (`<>`) can only be used by ML's equality types
    - `String`, `char`, and `int` are equality types
    - `real` is not an equality type due to the nature of computations on computer hardware
  - Logical values
    - Logical or is `orelse`
    - Logical and is `andalso`
    - Logical complement is `not`

      - ```ocaml
        - 1 < 2 orelse 3 > 4;
        val it = true : bool
        - 1 < 2 andalso not (3 < 4);
        val it = false : bool
        ```

    - `orelse` and `andalso` don't evaluate the second operand if the result is already decided by the first operand

      - ```ocaml
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

      - ```ocaml
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
      - Other languages will transform the operands automatically if possible, ML doesn't
  - ML has functions that can be called to transform types
    - `real` - `int` → `real`
    - `floor` - `real` → `int` (rounding down)
    - `ceil` - `real` → `int` (rounding up)
    - `round` - `real` → `int` (round to nearest `int`)
    - `trunc` - `real` → `int` (rounds towards 0)
    - `ord` - `char` → `int` (gets ASCII code)
    - `chr` - `int` → `char` (uses ASCII code)
    - `str` - `char` → `string`

      - ```ocaml
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
    - Function precedence is highest that we've seen so far
- Variable Definition
  - `val` is used to define a new variable and bind it to a keyword

    - ```ocaml
      - val x = 1 + 2 * 3;
      val x = 7 : int
      - x;
      val it = 7 : int
      - val y = if x = 7 then 1.0 else 2.0;
      val y = 1.0 : real
      ```

  - Can be used to redefine an existing variable to a new value or type

    - ```ocaml
      - val fred = 23;
      val fred = 23 : int
      - fred
      val it = 23 : int
      - val fred = true;
      val fred = true : bool
      - fred
      val it = true : bool
      ```

    - New definition of a variable doesn't overwrite the old one, it just adds a new definition on top of the previous one
      
      - Any part of the program that used the old definition will still use the old definition afterwards → new definitions have no side - effects on older parts of the program
- Garbage collection - ML's way of reclaiming pieces of memory that are no longer being used
  
  - `GC #0.0.0.0.1.3: (0 ms)`
- Tuples and Lists
  - Tuple - an ordered collection of values of different types
    - ML supports tuples as expressions anywhere

      - ```ocaml
        - val barney = (1 + 2, 3.0 * 4.0, “brown");
        val barney = (3, 12.0, “brown”) : int * real * string
        - val point1 = (“red”, (300, 200));
        val point1 = (“red”, (300, 200)) : string * (int * int)
        ```

    - Tuples formed by putting 2+ expressions inside parens separated by commas
    - `*` symbol used as a type constructor
    - The `i`th element of a tuple can be extracted using `#i v`
      - Positions start counting from 1

        - ```ocaml
          - #2 barney
          val it = 12.0 : real
          - #1 (#2 point1);
          val it = 300 : int
          ```

    - Tuples can have any length `> 1`
  - List - ordered collection of values of the same type
    - Lists can contain any number of elements
    - Formed using `[ ]` instead of parens

      - ```ocaml
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

      - ```ocaml
        - [];
        val it = [] : 'a list
        - nil;
        val it = [] : 'a list
        ```

      - ML cannot determine the type of the empty list
        - Give it a type beginning with an apostrophe - type variable
        - Type variables stand for types that are unknown
      - ML has predefined function `null` to determine if a list is empty

        - ```ocaml
          - null [];
          val it = true : bool
          - null [1, 2, 3];
          val it = false : bool
          ```

        - Can also use an equality comparison, but null is preferred
    - `@` operator can concatenate 2 lists of the same type

      - ```ocaml
        - [1, 2, 3] @ [4, 5, 6];
        val it = [1, 2, 3, 4, 5, 6] : int list
        ```

    - Construct/cons operator (`::`) glues an element to the front of a list

      - ```ocaml
        - val x = #”c” :: [];
        val x = [#”c”] : char list
        - val y = #”b” :: x;
        val y = [#”b”, #”c”] : char list
        - val z = #”a” :: y;
        val; z = [#”a”, #”b”, #”c”] : char list
        ```

      - More efficient than `@`
      - Right-associative
    - `hd` and `tl` extract the first element and rest of a list, respectively

      - ```ocaml
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

      - ```ocaml
        - explode “hello”
        val it = [#”h”, #”e”, #”l”, #”l”, #”o”] : char list
        - implode [#”h”, #”i”];
        val it = “hi” : string
        ```

- Function definitions
  - Use `fun` to define a new function

    - ```ocaml
      - fun firstChar s = hd (explode s);
      val firstChat = fn : string -> char
      - firstChar “abc”;
      val it = #”a” : char
      ```

    - `<fun-def> ::= fun <function-name> <parameter> = <expression> ;`
    - `a -> b` is the type for functions that take a parameter of type `a` and return a value of type `b`
    - Tuple parameters can be used for functions that take in more than 1 input value

      - ```ocaml
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
  
    - ```ocaml
      - fun fact n =
      =   if n = 1 then 1
      =   else n * fact(n - 1);
      val fact = fn : int -> int
      - fact 5;
      val it = 120 : int
      ```

      - Can spread over 1+ lines, ML doesn't care about line breaks → readability
      - Reflects ML's heavy use of recursion
  - Example of a function that adds up all the elements of a list

    - ```ocaml
      - fun listsum x =
      =   if null x then 0
      =   else hd x + listsum(tl x);
      val listsum = fn : int list -> int
      - listsum [1, 2, 3, 4, 5];
      val it = 12 : int
      ```

  - Example of an implementation of the predefined `length` function

    - ```ocaml
      - fun length x =
      =   if null x then 0
      =   else 1 + length(tl x);
      val length = fn : 'a list -> int
      - length [true, false, true];
      val it = 3 : int
      - length [4.0, 3.0, 2.0, 1.0];
      val it = 4 : int
      ```

      - Function can be called with parameters of different types → polymorphic function
        - No special trick was used, ML just determined this could be generalized as such
  - Types represented by `''a` reflect a need for equality types → use `null x` instead of `x = []`
  - Example of a function that reverses a list

    - ```ocaml
      - fun reverse L =
      =   if null L then nil
      =else reverse(tl L) @ [hd L];
      val reverse = fn : 'a list -> 'a list
      - reverse [1, 2, 3]
      val it = [3, 2, 1] : int list
      ```

- Type Annotations
  - So far we have `int`, `real`, `bool`, `char`, and `string` as types and `*` (tuple), `list` (list), and `->` (function) as type constructors
    - `list` has highest precedence and `->` has lowest precedence
      - `int * int list` is the same as `int * (int list)`
  - ML defaults types to the default of the operators used (`+`, `-`, `*` all default to `int`)
    - Sometimes type annotations are needed

      - ```ocaml
        - fun prod(a, b) = a * b;
        val prod = fn : int * int -> int
        - fun prod(a:real, b:real) : real = a * b;
        val prod = fn : real * real -> real
        ```

        - Establishes the types of `a`, `b`, and the return value
        - One hint is usually enough to satisfy the need for a type annotation, but opt for the most readable option
  - More important for larger projects

## **Reading 4: Second Look at ML**

- ML functions work based on patterns
  - Single parameter `n` is a pattern
  - Tuple list `(a, b)` is a pattern for a tuple of 2 items
  - Used to match data, which ML can then act on
  - Can also introduce new variable
    - Pattern that matches `n` also introduced the variable `n` that is bound to the value of the parameter
- Simple Patterns
  - Simplest pattern is `_`, which matches any pattern and doesn't introduce a new variable

    - ```ocaml
      - fun f _ = “yes”;
      val f = fn : 'a -> string
      - f 34.5;
      val it = “yes” : string
      - f [];
      val it = “yes” : string
      ```

  - Can make a pattern that only matches a single constant

    - ```ocaml
      - fun f 0 = “yes”;
      Warning: match nonexhaustive
          0 -> ...
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

    - ```ocaml
      - fun f [a, _] = a;
      Warning: match nonexhaustive
      a :: _ :: nil -> ...
      val f = fn : 'a list -> 'a
      - f [#”f”, #”g”];
      val it = #”f” : char
      ```

    - Nonexhaustive function definition - definition of a function that doesn't cover the whole domain type
      
      - This function is only defined for lists with exactly 2 elements
- Any cons of patterns is a legal pattern
  
  - ```ocaml
    - fun f (x :: xs) = x;
    Warning: match nonexhaustive
        x :: xs -> ...
    val f = fn : 'a list -> 'a
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

    - ```ocaml
      - fun f 0 = “zero” | f 1 = “one”
      ```

    - `<fun-def> ::= fun <fun-bodies> ;`
    - `<fun-bodies> ::=- <fun-body> | <fun-body> '|' <fun-bodies>`
    - `<fun-body> ::= <fun-name> <pattern> = <expression>`
      
      - `<fun-name>` must be the same in each alternative
- Can overlap patterns → ML tries the patterns in order they're listed and uses the first one that matches

  - ```ocaml
    - fun f 0 = “zero” | f _ = “non-zero”
    ```
  
- Pattern-Matching Style

  - ```ocaml
    fun f 0 = “zero”
    |   f 1 = “non-zero”;

    fun f n =
        if n = 0 then “zero”
        else “non-zero”;
    ```

    - Above functions are equivalent, first uses pattern-matching style
    - Pattern-matching generally preferred for readability
  - Rewrite the factorial program:

    - ```ocaml
      fun fact 0 = 1
      |   fact n = n * fact(n - 1);
      ```

      - Clearly separates base case from recursive case
  - Rewrite the reverse program

    - ```ocaml
      fun reverse nil = nil
      |   reverse (first :: rest) = reverse rest @ [first];
      ```

      - Here, we can implicitly extract the head and tail using pattern-matching
        - More readable, same efficiency
  - Sum all the elements of a list

    - ```ocaml
      fun f nil = 0
      |   f (first :: rest)  = first + f rest;
      ```

      - Very common structure for functions that visit all elements of a list
  - Count how many true values are in a `bool list`

    - ```ocaml
      fun f nil = 0
      |   f (true :: rest) = 1 + f rest
      |   f (false :: rest) = f rest;
      ```

  - Make a new `int list` where each `int` is 1 greater than it was in the original list

    - ```ocaml
      fun f nil = nil
      |   f(first :: rest) = first + 1 :: f rest;
      ```

  - Cannot use the same variable name more than once in a pattern
    - `fun f(a, a)` as a way to find pairs of equal elements is illegal
    - Only implementation is to abandon pattern-matching style

      - ```ocaml
        fun f (a, b) =
            if (a = b) then ...
            else ...
        ```

  - Can also use patterns in `val` definitions

    - ```ocaml
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

    - ```ocaml
      - let val x = 1 val y = 2 in x + y end;
      val it = 3 : int;
      - x;
      Error: unbound variable or constructor: x
      ```

  - Helps break up long expressions and give meaningful names to intermediary pieces

    - ```ocaml
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

    - ```ocaml
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

      - ```ocaml
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
  - `halve` and `merge` from above aren't useful on their own
  - In our interest to make it clear that they are only relevant in the context of `mergeSort`

    - ```ocaml
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

## **Reading 5: Third Look at ML**

- Pattern Matching
  - A rule is a part of ML syntax that takes the form `<rule> ::= <pattern> -> <expression>`
  - A match consists of 1+ rules separated by the `|` token: `<match> ::= <rule> | <rule> '|' <match>`
    
    - Each rule in a match must have the same type of expression on the RHS
  - Case-expressions use matches
  - `<case-exp> ::= case <expression> of <match>`
  
    - ```ocaml
      - case 1 + 1 of
      =   3 -> “three” |
      =   2 -> “two” |
      =   _ -> “hmm”;
      val it = “two” : string
      ```
  
    - Value of a case expression is the value of the expression in the first rule of the match whose pattern matches the value of expression
  - ML allows case expressions with general pattern matching, unlike `switch` statements in C++
  
    - ```ocaml
      case x of
      _ :: _ :: c :: _ -> c |
      _ :: b :: _ -> b |
      a :: _ -> a |
      nil -> 0
      ```
  
      - Returns the 3rd element if it exists, or the 2nd element if it exists, or the 1st element if it exists, or `0` if the list is empty
  - `If-else`'s can be rewritten using case expressions
  
    - ```ocaml
      case exp1 of
          true -> exp2 |
          false -> exp3
      ```
  
      - Should only use when you need the extra flexibility of the case expression → conditional more readable
- Function Values and Anonymous Functions
  - Function names and operators are variables bound to functions

    - ```ocaml
      - ~
      val it = fn : int -> int
      - val x = ~;
      val x = fn : int -> int
      - x 3
      val it = ~3 : int
      ```

  - The function `f` (imperative) → the function currently bound to the name `f` (ML)
  - Functions can be declared without a name using the `fn` keyword and a match → anonymous function

    - ```ocaml
      - fun f x = x + 2;
      val f = fn : int -> int
      - f 1;
      val it = 3 : int
      - fn x -> x + 2;
      val it = fn : int -> int
      - (fn x -> x + 2) 1;
      val it = 3 : int
      ```

    - Useful for when the function is only needed in one place and you don't want to clutter your program with an extra variable

      - ```ocaml
        - fun intBefore (a, b) = a < b;
        val intBefore = fn : int * int -> bool
        - quicksort ([1, 4, 3, 2, 5], intBefore);
        val it = [1, 2, 3, 4, 5] : int list
        - quicksort ([1, 4, 3, 2, 5], fn (a, b) -> a < b);
        val it = [1, 2, 3, 4, 5] : int list
        - quicksort ([1, 4, 3, 2, 5], fn (a, b) -> a < b);
        val it = [5, 4, 3, 2, 1] : int list
        ```

  - We can extract the function denoted by an operator using the `op` keyword

    - ```ocaml
      - quicksort ([1, 4, 3, 2, 5], op <);
      val it = [1, 2, 3, 4, 5] : int list
      - quicksort ([1, 4, 3, 2, 5], op >);
      val it = [5, 4, 3, 2, 1] : int list
      ```

- Higher-Order Functions and Currying
  - Every function has an order
    - A function that takes a function as a parameter or returns a function value has order `n + 1`, where `n` is the order of its - highest-order parameter or return value
    - A function of order `n` is called an `n`th order function
    - Any function with order `> 1` is called a higher-order function
  - We've seen that functions only take 1 parameter
    - We get around this by passing a tuple as this parameter
    - We can also use currying - have 1 function take 1 parameter and return a function that will use a second parameter to get the - final result

      - ```ocaml
        - fun f (a, b) = a + b;
        val f = fn : int * int -> int
        - fun g a = fn b -> a + b
        val g = fn : int -> int -> int
        ```

        - `g` takes the first parameter and returns an anonymous function that takes the second parameter and returns the sum
        - We would call `f` with a tuple like normal, but `g` would be called with integer parameters due to ML's left associativity of - functions
        - Biggest advantage of currying is we can call curried functions while only passing some of their parameters and leave the rest for later

          - ```ocaml
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
            ```

            - Currying creates more specialized versions of functions

            - Can be generalized to any number of parameters

            - Can be abbreviated

            - ```ocaml
              fun g a = fn b = fn c -> a + b +c;
              fun g a b c = a + b + c
              ```

- Predefined Higher-Order Functions
  - `map` function
    - Used to apply some function to every element of a list, collecting a list of the results

    - ```ocaml
      - map ~ [1, 2, 3, 4];
      val it = [~1, ~2, ~3, ~4] : int list
      ```

    - Type is `('a -> 'b) -> 'a list -> 'b list`
    - Result will always be a list of the same length as the input list
  - `foldr` function
    - Used to combine all the elements of a list into one value
    - Takes 3 parameters: function `f`, starting value `c`, and a list of values
      - Starts with the rightmost element, computes the result of `f` called on that element and `c`, and then folds in the next element - until all elements have been processed

      - ```ocaml
        - foldr (op ^) “” [“abc”, “def”, “ghi”];
        val it = “abcdefghi” : string
        ```

    - Type is `('a * 'b -> 'b) -> 'b -> 'a list -> 'b`
    - Commonly used by giving the first 2 parameters and not the third
      - Results in a function that takes a list and folds it with a fixes function and an initial value

        - ```ocaml
          - val addup = foldr (op +) 0;
          val addup = fn : int list -> int
          - addup [1, 2, 3, 4, 5];
          val it = 15 : int
          ```

      - ```ocaml
        foldr (fn (a, b) -> FUNCTION_BODY) c x
        ```

        - `b`, `c`, the value returned by the anonymous function, and the value returned by `foldr` are all the same type
        - `a` is the same type as the elements of list `x`
    - Function that removes all negatives from a list

      - ```ocaml
        fun thin L = foldr (fn (a, b) -> if a < 0 then b else a::b) [] L;
        ```

  - `foldl` function
    - Used to combine all the elements of a list into one value
    - Starts from the leftmost element instead of the rightmost

    - ```ocaml
      - foldl (op ^) “” [“abc”, “def”, “ghi”];
      val it = “ghidefabc” : string
      ```

## **Reading 6: Fourth Look at ML**

- `bool` is not a primitive in ML - it's a defined type using the keyword `datatype`
- Enumerations

  - ```ocaml
    - datatype day = Mon | Tue | Wed | Thu | Fri | Sat | Sun;
    datatype day = Fri | Mon | Sat | Sun | Thu | Tue | Wed
    - fun isWeekDay x = not (x = Sat orselse x = Sun)
    val isWeekDay = fn : day -> bool
    ```

  - Type inference of ML applies to new types
  - `day` in the example is called a type constructor and the member names are called data constructors
    
    - Data constructor names are capitalized by convention
  - ML doesn't expose the underlying representation of values within an enumeration
    
    - Only operations that are permitted are comparisons for equality
  - Can use data constructors in patterns

    - ```ocaml
      fun isWeekDay Sat = false |
          isWeekDay Sun = false |
          isWeekDay _ = true;
      ```

- Data Constructors with Parameters
  - Can add a parameter to a data constructor by adding the keyword `of` followed by the type of parameter

    - ```ocaml
      datatype exint = Value of int | PlusInf | MinusInf
      ```

      - Each `Value` will contain an `int` → cannot treat `Value`s as `int`s

        - ```ocaml
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

    - ```ocaml
      - val (Value y) = x;
      val y = 5 : int
      ```

  - This pattern is nonexhaustive

    - ```ocaml
      - val s = case x of
      =   PlusInf -> “infinity” |
      =   MinusInf -> “-infinity” |
      =   Val ue y -> Int.toString y;
      val s = “5” : string
      ```

- Type Constructors with Parameters
  - The parameters for a type constructor are type parameters and the result is a polymorphic type constructor
  - `option` type constructor is pre-defined in ML

    - ```ocaml
      datatype 'a option = NONE | SOME of 'a;
      - SOME 4;
      val it = SOME 4 : int option
      - SOME 1.2;
      val it = SOME 1.2 : real option
      ```

    - Useful for functions with undefined results
    - Function to handle division by 0

      - ```ocaml
        - fun optdiv a b =
        =   if b = 0 then NONE else SOME (a div b);
        val optdiv = fn : int -> int -> int option
        ```

    - ```ocaml
      datatype 'x bunch = One of 'x | Group of 'x list;
      - One 1.0
      val it = One 1.0 : real bunch
      - Group [true, false];
      val it = Group[true, false] : bool bunch
      ```

      - ML doesn't always have to resolve the type of a `datatype`, it depends on the operators being applied to it
- Recursively Defined Type Constructors
  - In data constructors of a `datatype` definition, you can use the type constructor being defined

    - ```ocaml
      datatype intlist = INTNIL | INTCONS of int * intlist
      fun intlistLength INTNIL = 0
      |   intlistLength (INTCONS(_, tail)) = 1 + (intlistLength tail);
      ```

      - This type is restricted to the type `list int` → not parametric

        - ```ocaml
          datatype 'element mylist = 
          NIL | 
          CONS of 'element * 'element mylist;
          ```

  - Polymorphic binary tree definition

    - ```ocaml
      datatype 'data tree =
          Empty |
          Node of 'data tree * 'data * 'data tree;
      ```

    - Produce a list of all elements in a tree

      - ```ocaml
        fun listall Empty = nil
        |   listall (Node(x, y, z)) = listall x @ y :: listall z;
        ```

## **Lecture 2: Syntax**

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
        - You don't want to have to change all your code
        - Here's what we did in GNUlib
          - Ordinary code:

            - ```c
              #include <unistd.h>
              int f (void) {
                if (close (fd) != 0 && errno == EBADF) return 1;
                else return 0;
              }
              ```

          - Our own `unistd.h`:

            - ```c
              #include next <unistd.h>
              #define close rpl_close
              ```

          - `workaround.h`:

            - ```c
              #ifdef MSVC
              #define TRY try {
              #define CATCH } catch {
              #define DONE }
              #else
              // Other code
              #endif
              ```

          - Our own library

            - ```c
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

        - ```prolog
          :-op(500, yfx, [+,-]).
          ```

          - `+` and `-` are operators with precedence 500, are binary operators, and are left associative

        - ```prolog
          :-op(400, yfx. [*,/]).
          ```

          - `*` and `/` are operators with precedence 400, are binary operators, and are left associative
          - Lower number for precedence represents a higher priority
          - `f` = function symbol
          - `y` = operand of equal or lower-numbered precedence
          - `x` = operand of lower-number precedence

        - ```prolog
          :-op(200, fy, [+,-]).
          ```

          - Can declare same operator to have a different meaning

        - ```prolog
          :-op(200, xfy, [**])
          ```

          - Right-associative

        - ```prolog
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
    - It's what people are already used to (why Java looks like C++)
    - It's simple and regular (Lisp)
    - It's readable
      - Leibniz's criterion: a proposition's form should mirror its meaning
    - It's writable/concise
    - It's redundant - prefer redundancy to catch mistakes
    - It's unambiguous
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

          - ```c
            int class = 29; // Ok in C, not in C++
            ```

      - Some languages avoid this problem by not having reserved words (PL/I)
        - Easier to extend the language
        - Rules for tokenization are more complicated
      - The C solution to this problem
        - Reserves all identifiers beginning with `_` and then a capital letter or `_`
        - New keywords in C all begin with `_` and a capital letter

          - ```c
            _Noreturn void f(void) { // f never returns
            	// Other code
            }
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
  
        - ```html
          S -> Sa
          S -> Sb
          S -> c
          ```
  
      - Sentence - member of a language

## **Lecture 3: Ambiguity**

- Usage of grammars
  - Computer science theory
    - Language definitions
    - How to automatically process languages
  - Take a simple grammar

    - ```html
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

            - ```html
              S 3
              ( S ) 1
              ( S a ) 1
              ( S a a ) 2
              ( b a a )
              ```

              - Can express as `3 1 1 2` in shorthand
          - Don't necessarily know which rule to use, just need to run it and check
      - Parse tree representation
        - Same power as derivations
        - Easier to read for more complex grammars
        - Multiple parse trees can exist for the same string
          - If the grammar is unambiguous, every parseable sentence has a unique parse tree
        - A tree where leaves are all terminals, interior nodes are all nonterminals, each interior node matches a rule (LHS is node, RHS is children)
- Problems that you can run into with grammars
  - Nonterminals that are used but not defined

    - ```html
      S -> T b
      S -> S a
      S -> c
      ```

      - No definition for `T` despite use in rule 1
  - Nonterminals that are defined but never used

    - ```html
      S -> S a
      S -> c
      T -> S b
      ```

      - No use of `T` despite definition in rule 3
  - Nonterminals that can never be reached from the start symbol

    - ```html
      S -> S a
      S -> c
      T -> U d
      U -> T e
      ```

      - `T` and `U` are both useless despite being used and defined
  - Useless loops

    - ```html
      S -> S a
      S -> c
      S -> S
      ```

      - Last rule is useless/counterproductive by introducing ambiguity for no reason
  - Problems are similar to what you find in your ordinary programs
  - Bugs like these in your grammar is likely to cause a similar bug in the corresponding parser
  - Syntactic constraints that your grammar doesn't capture
    - Example from natural languages - small subset of English

      - ```html
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

      - ```html
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
  
    - ```html
      E -> E + E
      E -> E * E
      E -> ID
      E -> NUM
      E -> ( E )
      ```
  
      - Ambiguous for `a + b * c` → will result in 2 different interpretations
        - `(a + b) * c`
        - `a + (b * c)`
      - Doesn't capture precedence/associativity
      - Fix this ambiguity
  
        - ```html
          E -> E + T
          E -> T
          T -> T * F
          T -> F
          F -> ID
          F -> NUM
          F -> ( E )
          ```

    - Ex) Subset of C programming language
  
      - ```html
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
        - C designers didn't want to clutter code with unnecessary parentheses
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
      
        - ```html
          STMT -> if (EXPR) STMT
          STMT -> if (EXPR) LSTMT else STMT
          LSTMT can be anything except an else-less if → doubles the grammar size
          STMT -> LSTMT
          STMT -> if (EXPR) STMT
          ```
             - Replace all other `STMT` rules with `LSTMT`
    - Avoiding ambiguity clutters your grammar, and may people don't want to bother
      - Concrete - the unambiguous grammar
      - Abstract - ambiguous grammar
        - Parsers prefer this due to simplicity and speed
- Alternate notations for grammars
  - `E -> E + E`
  - `<E> ::= <E> + <E>`
  - `expr: expr + expr`
  - Internet RFCs (Request for Comments)

    - ```html
      msg-id = “<” id-left “@” id-right “>”
      id-left = dot-atom-text / obs-id-left
      id-right = dot-atom-text / no-fold-literal / obs-id-right
      no-fold-literal = “[“ *dtext “]”
      ```

      - Rule: LHS = RHS
      - Nonterminals are `id-left`, `id-right`
      - Terminals are quoted
      - Example `msg-id`: `Message-ID: <11232143.fsf@cs.ucla.edu>`
      - This set of rules is an extended version of the rules we've seen so far, in that `*X` in the RHS is shorthand for 0+ occurrences of `X`

## **Lecture 4: Functional Programming**

- We can turn our grammars into regular expressions
  - Can you do this with any BNF grammar? No
  - Regular expressions can't count, they can't deal with nesting
    - Impossible:

      - ```html
        Expr -> “(“ Expr “)”
        Expr -> ...
        ```

    - Possible:

      - ```html
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
  
  - ```html
    syntax = syntax rule, {syntax rule}
    syntax rule = meta id, '=', defns list, ';';
    defns list = defn, {'|', defn};
    defn = term, {',', term};
    term = factor, ['-', exception];
    exception = factor;
    factor = [integer, '*'], primary
    ...
    ```
  
    - Philosophically in trouble:
      - We've defined ISO EBNF by using ISO EBNF
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
      - Build on top of mathematicians' work instead of reinventing it
      - Also a problem of performance
    - Performance - parallelizability
      - C++, Python, etc. force you to think/write code sequentially
      - Compilers often can't optimize code through parallelization
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
    - `'a` is a type variable, makes a generic type for type inference
    - Everything is immutable in our subset of OCaml

## **Lecture 5: OCaml**

- Idea is to see how to explain OCaml in a basic core + add-ons
  - You see this all the time - C++ core language + libraries
  - OCaml also has core language + libraries/modules
- What's the core of the OCaml language (add-ons will still be part of the language)
  - Our add-ons will be syntactic sugar - a nice way of writing something that's an extra feature of the language that you could've - done without
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
    - Currying more powerful → don't need all of the parameters when the function is called
  - If you just write `x y z`, it's parsed as 2 function calls
    - First is a call to `x`, then a call to whatever `x y` returns
    - OCaml's optimizer optimizes away the excess `call` and `ret` instructions or uses cheaper versions of the instructions
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

  - ```ocaml
    match l with
    | h:: t -> 3::h::t
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

    - ```ocaml
      let rec maxlist l = 
        match l with
        | h::t -> let mt = maxlist t in
            if mt < h then h else mt
        | _ -> -999999999
      ```

  - Let's generalize it to list of anything

    - ```ocaml
      let rec maxlist lt identity = function
        | h::t -> let mt = maxlist lt identity t in
            if lt mt h then h else mt
        | [] -> identity
      ```

- 2 keywords: `fun` and `function`
  - They operate differently (syntactic sugar in different ways)
  - `fun` is for currying

    - ```ocaml
      fun x y -> x + y
      ```

  - `function` is for pattern matching

    - ```ocaml
      function 
        | [] -> 0 
        | _::l -> f l
      ```

## **Lecture 6: OCaml and Types**

- Simple OCaml function to reverse a list

  - ```ocaml
    let rec reverse = function
      | [] -> []
      | h::t -> (reverse t) @ h
    ```

    - This is wrong, because the type is wrong

    - ```ocaml
      let rec reverse = function
        | [] -> []
        | h::t -> (reverse t) @ [h]
      ```

      - Bad performance, `O(N^2)` due to repeated work with the `@` operator
      - Add an accumulator - an extra argument that accumulates the work you've already done

        - ```ocaml
          let rec revall a l =
            match l with
            | [] -> a
            | h::t -> reverse h::a t
          let reverse l = revapp [] l
          ```

        - Can simplify further

          - ```ocaml
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
      - Set of instructions for a machine that doesn't exist
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
    - Code is never translated to machine code, uses the interpreter's machine code
    - Often converts to byte code for efficiency, a software-defined instruction set
    - Worse runtime performance than compiling, easier to debug

## **Lecture 7: Types**

- Types in OCaml, Java, C++, etc.
  
  - We'll start by looking at static type checking
- Why do we have types?
  
  - “Types are more trouble than they're worth” - is that so?
- What is a type?
  - A type is a set of values
    - `int = { INT_MIN, …, -1, 0, 1, …, INT_MAX }`
    - There are set-oriented languages
      - Allows for countably and uncountably infinite sets through predicates
  - A type describes how objects are represented in memory

    - ```c
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
    - What are the set of integer values? It's machine-dependent
      - 32-bit 2's complement integers is most common
      - 16-bit or 36-bit, ones' complement, signed magnitude, etc. still exist
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
      
    - ```c
      float f = 0;
      f / f = NaN
      ```
    
  
  - How do you compare `NaN`s to numbers?
    
          - ```c
            float f = 0;
            float nan = f / f;
            if (nan < 5) // by convention, NaNs are never <, =, or > than anything
            float f = 0.0/0.0, g = f;
            f != g && memcmp(&f, &g, sizeof f) == 0;
            ```
  
        - `NaN` can't be equal to anything, but `f` and `g` have the same bits
  - An axiom we'd like to be true:
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
        - Due to inertia and the fact that lot's of useful computations do better without it
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
    - Structural equivalence - 2 types are the same if they're laid out in memory the same
      - If they behave the same, as far as the ABI goes
        - ABI = Application Binary Interface
    - Example of name equivalence in C/C++

      - ```c++
        struct s { int a; struct s*  next; };
        struct t { int a; struct t*  next; };
        ```

        - Different names = different types
    - Example of structural equivalence in C/C++

      - ```c++
        typedef int s;
        typedef int t
        s x;
        t y = x; // this is OK
        ```

      - Suppose we wanted structural equivalence in C/C++

        - ```c++
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
      - `type lower_case_alpha = 'a'...'z';` is a subtype of the type `char`
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
  - When a function's type contains one or more type variables
  - Walk through a collection of strings and remove all the strings of length 1
    - Without:

      - ```java
        static void remove1 (Collection C) {
          for (Iterator i = c.iterator(); i.hasNext(); )
            if (i.next().length() == 1)
              i.remove();
        }
        ```

        - Won't compile without a case because `i.next()` returns `Object` and `Object` doesn't have a `length()` method → cast result of `i.next()` to `String`
        - Slow and ugly → extra runtime check due to strong-typing of Java
        - Risk of crashing
    - With:

      - ```java
        static void remove1 (Collection<String> c) {
          for (Iterator<String> i = c.iterator(); i.hasNext(); )
            if (i.next().length() == 1)
              i.remove();
        }
        ```

        - No cast needed, no runtime check
        - Code is safer → no runtime exception possible
  - 2 typical ways to do parametric polymorphism
    - Templates (C++, Ada) represent code that doesn't exist yet, but it will exist once you instantiate it
      - Compiler can finish the job of compiling the code when say what the types actually are in a caller or user of the template
      - May require multiple copies of the machine code, one for each type of instantiation
    - Generics (OCaml, Java) - code is compiled and type-checked just once
      - Only one copy of the machine code needs to exist, it'll work on any types of arguments
      - This works because all types smell the same in the language
        - Every object is represented via a 64-bit pointer

## **Lecture 8: More About Types**

- More about types

  - Generics vs. templates

- Non-generic example (list of objects)

  - Aside - Java has primitives and objects -> primitives for efficiency, but the language provides wrappers that relate them to objects

  - ```java
    List l = new LinkedList();
    l.add(new Integer(0));
    Integer n = l.iterator().next();
    ```

  - `Integer` is an object that contains an `int`

  - Code is wrong -> `l.iterator().next()` is of type `Object`, we're trying to assign it to a variable of type `Integer`

    - Fix by replacing with `(Integer) l.iterator().next();`

      - Cast involves a runtime check that the `Object` is actually of type `Integer` -> not efficient

    - Fix with new code:

      - ```java
        List<Integer> l - new LinkedList();
        l.add(new Integer(0));
        Integer n = l.iterator().next();
        ```

- Subtypes and generics

  - ```java
    List<String> ls = // Some value
    List<Object> lo = ls; // This is wrong
    lo.add(new Thread());
    String s = ls.get(); // Assigns a Thread value to s
    ```

    - Aside - all assignments in Java copy a reference
    - `List<String>` is not a subtype of `List<Object>`, even though `String` is a subtype of `Object`
      - There are some operations you can do on a `List<Object>` that you cannot do on a `List<String>` (`add()`)

  - Print every member of a collection

    - ```java
      void printAll(Collection<Object> c) {
      	for (Object i : c)
      		System.out.println(i);
      }
      ```

      - Won't work -> conversion to `Object` not allowed

      - Fix using a wildcard - type variable with no name

        - ```java
          void printAll(Collection<?> c) {
          	for (Object i : c)
          		System.out.println(i);
          }
          ```

        - Can also name type variables

          - ```java
            static <T> void convert(T[] a, Collection<T> b) {
            	// Some code
            }
            ```

            - Doesn't type check on mismatched types that should still work (`String[] a, Collection<Object> b`)

        - Bounded wildcards - type checks even for above example - more flexible

          - ```java
            static <T> void convert(T[] a, Collection<? super T> b) {
            	// Some code
            }
            ```

            - `<? super T>` - unknown type must be a supertype of`T`
            - `<? extends T>` - unknown type must be a subtype of `T`

- How are generics implemented?

  - Compile the code just once, generate bytecodes that'll work on any value of any type that the type variables can be instantiated to
    - This is called erasure - the runtime has less type information than the compile-time, it doesn't need all the details
    - Only compiles once and all type-checking is done
    - Creates extra runtime checks as execution continues

- Skeptical camp that says static type-checking has gone too far, is more trouble than it's worth

  - Rules too complicated, users don't understand them

- Dynamic type-checking - let the runtime worry about it

  - "Duck typing" - if the object waddles like a duck and quacks like a duck, it's a duck
    - Don't worry about an object's type, as long as it does what you want it to do, it's fine
    - Behavior > types
    - More flexibility, less reliability, more performance issues

- Java overview

  - Where Java came from
    - Engineers in Sun Microsystems
    - Looking forward to Internet of things - toaster on the Internet
    - Problems:
      - SPARC/x86/ARM not universal - manufacturers wanted to choose their own CPUs
      - C/C++ too unreliable
      - C/C++ executables are too big, take too long to download over the Internet
      - Reliability issues include memory bloating
    - First approach they took: C++ -> C+- (C++ cleaned up)
    - Stole ideas from Xerox PARC
      - Bitmapped display, machines on a network, mouse pointer, etc.
      - Stole Smalltalk
        - OOP environment
        - Bytecode interpreter
          - Different versions of interpreter on different machines, bytecode was the same
          - Bytecode was small - oriented towards language, not machine
        - Garbage collector
        - Runtime checking for null pointers, subscript errors, etc.
        - Downside:
          - Smalltalk has a weird syntax
          - Smalltalk uses dynamic type-checking, fought against reliability issues
      - Sun took good parts of Smalltalk and came up with Oak (renamed to Java)
        - Smalltalk core with C syntax added static type-checking

- Java basics

  - Statically checked for reliability
  - Uses a C++-like syntax
  - Types have 2 major categories
    - Primitive (small set)
      - `byte`, `short`, `int`, `long`, `char`, `boolean`, `float`, `double`
      - Types are all the same size on all platforms, makes doe more portable at cost of performance
    - Reference (larger set, can be user-defined)
      - Internally implemented via pointers to the actual values
      - No direct access to the pointers - not pointers in the C/C++ sense
        - No `&x` operation
  - Variables and object slots are always initialized (to 0)
    - No uninitialized variables
    - Reliability for performance
  - Arrays are objects
    - 0 origin
    - Contents for an array are always in the heap, no arrays on the stack
      - For reliability
    - Size of an array is fixed upon allocation
      - Can get the size of arrays
  - Classes are like C++ classes
    - No multiple inheritance

## **Lecture 9: Interfaces and Threads**

- Java is single inheritance

  - If we had only single inheritance, each class would have to live in its own subtree, even if its behavior were compatible with a subtree somewhere else

- Java has a substitute for multiple inheritance - interfaces

  - Declared like a class, except using the `interface` keyword

    - Provides no implementations

    - ```java
      public interface Stack {
      	void push(int);
      	int pop();
      }
      ```

      - Any object is of type `Stack` if its class implements the `Stack` interface

        - ```java
          public class ArrayStack implements Stack extends Array {
          	void push(int) { /* Implementation */ }
          	void pop() { /* Implementation */ }
          }
          ```

  - Java compiler can check that you implement interfaces properly

  - There is an interface hierarchy, but this hierarchy operates in a different way from the class hierarchy

    - If class `C` extends class `P` (inherits from `P`), then it inherits `P`'s code (that's wealth)
    - If class `C` implements interface `I`, then it inherits an obligation to implement the interface

- This idea of using interfaces is very common

  - ```java
    interface Runnable {
    	void run();
    }
    ```

  - It's so common that we often would have a class and a tightly-associated interface, except we use an abstract class

    - Supplies both wealth and obligations on its child classes

    - ```java
      abstract class A {
      	void push(int i) { /* Implementation */ }
      	abstract int pop(); // This is an obligation
      }
      ```

  - Actual implementation is straightforward - look up the parent chain

  - You cannot construct an object that is directly of an abstract class or interface

- The `Object` class in Java

  - `Object` is the root of the Java class hierarchy - even a class with no declared parent has `Object` as its parent

    - Hierarchy is a tree

  - It's an important class - concepts that are so important that every object has to support them

  - `public class Object`

    - `public Object();` - constructs an `Object`
    - `public boolean equals(Object obj);`
    - `public int hashCode();`
      - Needs to be compatible with `equals` -> if `equals` is `true`, the hash codes should be equal
    - `public String toString();`
      - Yields a `String` representation of the object
    - `public final Class getClass;`
      - Returns an object that represents the class
      - `final` - implementation is here, cannot be overridden
        - Prevents objects from lying about their class, increases efficiency of class access (Java objects have type fields -> `final` = directly across the type field)
        - `final` allows performance gain through inlining -> makes you stuck with the implementation, flexibility traded for optimization
    - `protected void finalize() throws Throwable;`
      - Called by the garbage collector before the object is reclaimed
      - Default implementation is empty
      - `protected` - only called by the garbage collector
      - `throws` - calling this method might not result in return, could result in an exception
    - `protected Object clone() throws CloneNotSupportedException`
      - Makes a copy of an object and returns the copy
    - Several more methods

  - ```java
    public class Class { // A description of a Java class
    	// Implementation
    }
    ```

  - Can be used in test cases to test for generality

- Threads

  - Processors - CPUs (or CPU cores) each with its own instruction pointer
    - Can run programs simultaneously, one per processor
  - Threads - a program being run by a processor, but it's sharing memory with all the other threads in the same prcoess
    - Race conditions are possible
    - Very fast to communicate from 1 thread to another via shared memory
  - Processes - a program being run by a processor, each with its own separate memory so they can't affect each other

- Java is thread-oriented

  - Thread's life cycle in Java
    - Creation via `new` - resulting thread state: `NEW`
      - `Thread t = new Thread();`
      - More commonly: `Runnable r = ...;`
    - `t.start();` - allocates OS resources, giving the thread virtual/real processor, so it has an IP and calls `t.run()` using that IP
      - Resulting thread state: `RUNNABLE`
    - If a thread is `RUNNABLE`, it can
      - Keep running (execute ordinary code) - `RUNNABLE`
      - `yield()` - `RUNNABLE`
        - Signal to the OS that some other thread can run if it needs to
        - Advice to the thread scheduler, which decides which threads get processors
      - `sleep(10)` - `TIMED_WAITING` - waiting for internal clock to expire before running again
      - `o.wait()` - `WAITING` - waiting for software to run
      - Do I/O - `BLOCKED`
      - Terminate the thread - `TERMINATED`
        - Simplest way: `run` returns
  - Bad part about threads
    - Race conditions that occur when 2 threads compete for the same location: one writes, the other reads/writes
      - Resulting behavior depends on who wins
    - Synchronization simple solution: the `synchronized` method
      - Implemented by internal locks, one lock per object
      - If you're in a `synchronized` method, you have exclusive access to that object
      - Can be done via spin locks (you keep the CPU busy while the object's locked), so the body of a `synchronized` method should be simple and fast so that other threads don't spin (waste CPU resources doing nothing useful)
    - We don't like this inefficiency
      - We have more sophisticated synchronization techniques
        - `o.wait()` - remove all spin locks held by this thread, wait until `o` becomes "available" (thread goes into `WAITING` state)
          - `o.wait(100)` - like `o.wait()`, but `TIMEDWAITING` for 100ms
        - `o.notify()` - marks `o` as available
          - Wakes up one of the waiting threads on `o` if there are any (at random/depending on the scheduler)
        - `o.notifyAll()` - wakes up all the threads waiting on `o`
          - Lets all the threads negotiate which one gets the object
          - Lets you control scheduling better than the scheduler

- Synchronization approaches built atop `wait`/`notify`

  - `Exchanger` - represents a rendezvous point
    - Thread that gets to the rendezvous point first waits for the second
  - `CountDownLatch`
    - Threads gather until all `N` threads are present
    - Threads are frozen until ready to start
  - `CyclicBarrier`
    - Repeated `CountDownLatch`
  - All these approaches still too slow - bottleneck introduced by needing to synchronize
    - We want to avoid these bottlenecks - no `synchronize`, no `o.wait()`, etc.

## **Lecture 10: JMM and Scope**

- Optimization

  - As-if optimization - compiler generates the same code you wrote, but more efficient
    - More aggressive optimization - can execute instructions in a different order than how they were written to make more optimal
    - An optimizer is allowed to generate code that does things in any order as long as the observed behavior is as if it were in the correct order
    - As-if rule applies not just to compilers, but also to hardware -> out-of-order execution
  - We are talking about a single thread of execution - what happens if we use the as-if rule individually to multiple threads?
    - Behavior breaks down -> as-if rule on every individual thread doesn't lead to as-if rule on the program as a whole
    - How can 1 thread communicate reliably to another if their writes to memory cannot reliably be seen by other's reads?
    - Optimizations gets in the way of reliable communication from 1 thread to another
      - 2 standard solutions to this in Java:
        - Declare a variable as `volatile` - tells the compiler not to optimize accesses to this variable
          - Every load/store into the variable must e reflected in the machine code
          - In Java, it doesn't make sense for a method's local variable to be `volatile` - no other thread can access that variable anyways
        - Declare a chunk of code to be `synchronized`
          - Grab a spin lock before entering a `synchronized` method
          - Accesses within the method all occur after the spin lock is grabbed and before it's released
          - Release the spin lock as you exit
        - Both approaches inhibit some optimizations and therefore slow down your program
          - Trade-off - you avoid race conditions
      - We need a good contract for exactly which optimizations are allowed and which are no
        - This contract is not that obvious

- Java Memory Model

  - A way to specify how we can reliably communicate with other threads and where the boundaries for safe/unsafe use are

    - What threads can influence us, what threads we can influence, what threads can't be influenced/influence us

  - Abstract machine has threads, each with its own instruction pointer

  - Each individual thread has semantics that are sequential, consist of leads and stores into memory, and entering and exiting `synchronized` code areas (monitors) + other stuff (adding, multiplying, etc.)

  - These semantics allow reordering of loads and stores and entering and exiting monitors, so long as the as-if rule is followed for that particular thread

    - You can't reorder arbitrarily, but you can reorder many accesses

  - These individual-thread semantics allow too much reordering, we want to place extra restrictions on when specific optimizations can be made

  - Table that tells us when we can reorder

    - `A` - normal loads/stores, `B` - enter monitor/volatile load, `C` - exit monitor/volatile store

      - |       |  A   |  B   |  C   |
        | :---: | :--: | :--: | :--: |
        | **A** |  Y   |  Y   |  N   |
        | **B** |  N   |  N   |  N   |
        | **C** |  Y   |  N   |  N   |

    - Table is a result of compromise between performance and safety

  - One more tricky thing about JMM

    - ```java
      class C {
      	C() {
              this.x = 10;
              g = this; // not allowed - g might be visible to another thread
              this.y = 20;
          }
      }
      
      // Thread 1
      C o = new C();
      print(o.x);
      
      // Thread 2
      print(g.y);
      ```

      - `g.y` may execute before `y` is initialized, but while `g` is
      - Constructors must not make their object visible before they return

- Scope of variables/names and binding

  - Names (identifiers, symbols) - like `x`, `y`, `z`
    - Low-level issues
      - Are some names reserved?
      - Case-sensitive?
      - What characters are allowed in names?
      - For now, assume usual names
    - Binding - an association between a name and a value
      - Question - which value?
      - When does the binding occur?
  - Addresses of locations
    - `int n = 27;` - top level of a C program
      - `n` stands for `27` or the location containing `27`
      - Value binding - `n` can be changed at runtime, bound to the value
        - Binding time - during execution, can be changed later
      - Address binding - used for expressions like `&n`, can't be changed in this example
        - Binding time - just before execution starts (PIE) or during linking of the program
          - Position Independent Executables - OS can put the program/data anywhere in VM and it'll run
            - Protects against attackers, slows down program start up
          - During linking - linker decides where `n` goes in VM, OS puts it there when the program runs
          - May be done dynamically
      - Size binding for `n` - using in `sizeof n`, must be a constant
        - Binding time - at ABI definition time
          - Depends on the machine and what the system developers expect programmers to want
  - Explicit vs. implicit binding
    - In C -  you must write down the type of each variable
    - In ML - type binding is often implicit, gets inferred
    - Too much implicit - bad for compiler, too much explicit - bad for programmer

- Separate compilation

  - To compile programs quickly, we break them up into pieces and compile separately

    - Link together the result

  - How can we access names defined in other modules without having access to those modules' source code

  - Example in C:

    - ```c
      // a.c
      int x;
      
      // b.c
      extern int x;
      
      //c.c
      int x;
      ```

  - Traditional answer - let it go, coalesce definitions into a single one

  - Current solution - don't allow this, it causes too many problems in practice

- Where bindings live: in namespaces

  - A namespace is a set of compatible bindings - no 2 bindings have the same name

  - A namespace is a partial function from names to values

  - Primitive namespaces

    - Hardwired into the language using specific rules

    - C namespaces:

      - ```c
        int f (void) { // Top-level namespace for this compilation unit, local to f's body
        	struct f { // 1 namespace for stuct tags
                int f; // 1 namespace for members of struct f
            } f; // 1 namespace for local variables
        }
        ```

      - Enumerations have their own namespace

        - ```c
          enum f { zero };
          ```

      - File names have their own namespace

        - ```c
          #include <f>
          ```

      - Preprocessor macros are in a different (global) namespace

        - ```
          #define f f
          ```

      - Labels have their own namespace

        - ```
          f: goto f;
          ```

    - There are features in the language syntax that tell us which namespace is used

  - Namespaces within the language - under user control

    - Labeled namespace:
      - A namespace whose name is in a parent namespace
      - Common usage:
        - `a.b.c.d` - `a`, `a.b`, `a.b.c` are namespaces, each the parent of the next
      - Basic idea - we want short, well-defined names in a well-defined context

  - Information hiding - namespaces that don't tell you all the names in the space

    - Some names are not visible to you

    - 2 ways to do this:

      - In Java, when you declare a name in a namespace, you specify how visible it should be (keywords)

        - ```java
          class C {
          	KEYWORD1 int m() {
                  // Implementation
              }
              
              KEYWORD2 int n() {
                  // Implementation
              }
          }
          ```

        - `public` - visible everywhere that `C` is visible

        - `protected` - visible to class, subclass, and package

        - (nothing) - default visibility, visible to just the class and package

        - `private` - name is only visible to the class

      - Let users compute namespaces from other namespaces

        - Python - namespaces are objects you can fiddle with

## **Lecture 11: Logic Programming**

- 3 main kinds of programming languages

  - Imperative - focused on commands and sequencing (C++, Python, Java, etc.)
  - Functional - focused on functions and call (OCaml, F#, Scala, etc.)
  - Logic - focused on predicates and `and`/`or` (Prolog, etc.)
  - All of these types of languages are coming up with levels of abstraction

- Encourage declarative rather than procedural thinking

  - Declarative - say what you want
  - Procedural - say how to do it
  - Imperative is mostly procedural
  - Functional is a mixture of both
  - Logic is mostly declarative

- Logic programming mantra (we don't always live up to this):

  - Algorithm = Logic + Control
    - Logic tells you whether the algorithm is what you want - you write a specification in logic of what you want
    - Control tells the computer how to go about executing the algorithm efficiently
  - Separation of concerns when solving problems -> split problem into 2 independent, exponentially easier problems

- Example that pushes logic (not worrying about control or efficiency):

  - A Prolog program is a series of clauses, each ends in `.` and is a fact that we're telling the Prolog interpreter

    - In these clauses, logical variables begin with a capital letter and are implicitly universally quantified (the clauses are true for all cases)

  - `sort(L, P) :- permute(L, P), sorted(P).`

  - For every `L` and `P`, `P` is the sorted version of `L` *if* (`:-` means if) `P` is a permutation of `L` *and* `P` is sorted

  - ```prolog
    % Bad version
    sorted([]). % The empty list is sorted
    sorted([_]). % Any singleton list is sorted
    sorted([X, Y]) :- X =< Y. % The list [X, Y] is sorted if X <= Y
    sorted([X, Y|Z]) :- X =< Y, sorted(Z). % List where the first element is X, second is Y, and the rest is Z
    ```

  - ```prolog
    % Corrected version
    sorted([]).
    sorted([_]).
    sorted([X, Y|Z]) :- X =< Y, sorted(Y|Z).
    ```

  - ```prolog
    % Permute
    permute([], []).
    permute([X|L], P) :- permute(L, R), splice(X, R, P).
    ```

  - ```prolog
    % Splice
    splice(X, R, P) :- append(R1, R2, R), append(R1, [X|R2], P).
    ```

  - ```
    % Append
    append([], L, L).
    append([X|L], M, [M|LM]) :- append(L, M, LM).
    ```

  - This works, but it's `O(N!)`

- Prolog syntax - "Edinburgh syntax"

  - A Prolog program is a series of clauses; each is a term followed by `.`
  - A Prolog term is one of the following:
    - Atom - `abcdef`, `ghi`, `'a b c'`, `'o"clock'` (equal only to themselves)
    - Number - `1124`, `2e-29` (equal only to themselves)
    - Variable - `X`, `Tzw`, `_23` (system generates variables starting with `_`)
    - Structure - `f(27)`, `g(19, h(V))` (arity is the number of arguments, functor is the atom at the start of the structure + arity, each argument is a Prolog term)
      - `g/2` is notation that means functor `g` with arity `2`
      - Structures look like function calls, but they're not, they're just data structures that are trees
      - Each internal node in a tree is labeled by an atom, while the leaves are atoms, numbers, or variables
      - There are no function calls in Prolog

- Syntactic sugar

  - Operators: `+`, `-`, `*`, `=`, etc.
    - `X = 5` is syntactic sugar for `'='(X, 5)`
  - List syntax:
    - `[]` -> `'[]'`
    - `[X, Y, Z]` -> `'.'(X, (Y, '.'(Z, '[]')))`
      - Uses `./2`

- Prolog arithmetic

  - `is/2` does arithmetic

    - ```prolog
      ?- is(N, 2+2).
      ?- is(N, '+'(2, 2)).
      ?- N is 2+2.
      N = 4
      ? 3 is 2+2.
      no
      ```

  - Arithmetic is not that popular, try not to use it

- Prolog and lists

  - `member(X, L)` will be true if `X` is a member of the list `L`

    - ```prolog
      member(X, [X|_]).
      member(X, [_|L]) :- member(X, L).
      ```

  - Give the logic for the reverse of a list

    - ```prolog
      reverse([], []).
      reverse([X|L], RX) :- reverse(L, R), append(R, [X], RX).
      ```

      - We can speed this up using an accumulator

        - ```prolog
          revapp([], A, A).
          revapp([X|L], A, R) :- revapp(L, [X|A], R).
          
          reverse(L, R) :- revapp(L, [], R).
          ```

- Prolog interpreter acts as follows:

  - Looks at each clause in the program, looking for one that matches
  - Goal succeeds if a match is found in a clause with no body
  - If a match is found in a clause with a body, that body establishes a replacement goal (we have to prove the body), so we recurse
  - Each time a clause is used in this process, it gets a fresh copy of its logical variables -> the scope of a logical variable is the clause that it appears in

- So far, we've seen 2 kinds of clauses in Prolog, there are 3

  - Facts - clauses without a body
    - `equal(X, X)`
  - Rules - facts with string attached
    - `required(A, B) :- prereq(A, B).`
    - `required(A, B) :- prereq(A, Q), required(Q, B).`
  - Goals (Queries) - questions that you ask the Prolog interpreter
    - `?- required(dance101, dance198)`

- Prolog interpreter starts from a goal and searches for solutions via backwards chaining

  - Backwards chaining - we're goal-oriented, looking for ways to prove that goal, generating subgoals, subgoals of subgoals, etc. until we get to facts
  - This search is always depth-first - it explores the search space in top-down, left-to-right, always expanding the leftmost branch that it has
    - Backtracking on failure

## **Lecture 12: Prolog**

- Unification - taking 2 Prolog terms that are similar and making them identical

  - ```prolog
    ?- f(a, b) = f(a, b).
    yes
    ?- X = f(a).
    X = f(a)
    ?- f(X, a) = f(b, Y).
    X = b
    Y = a
    ```

  - A unifier is a substitution that makes 2 terms equal

  - The Prolog REPL outputs a unifier after every successful computation

  - There can be multiple different unifiers -> some aren't generic enough

    - Prolog picks the most general unifier

  - Every time the Prolog interpreter matches a goal to the head of a clause, it does so by unification, and this unification applies to the body of that clause, for subgoals

    - It's Prolog's only argument-passing convention
    - OCaml allows for pattern matching, but unification can substitute values for variables in the caller as well as in the callee -> OCaml can only do the latter

- A problem with unification -> too powerful

  - ```prolog
    % A very simple predicate
    p(X, X).
    ?- p(Y, f(Y)).
    Y = f(f(f(f(...))))
    ```

    - Results in an infinite term - circular data structure

      - Can be done easily in C/C++
      - Cannot be done in the functional subset of OCaml, you need all of an object's components to create an object

    - This may cause infinite loops in programs

    - Worse than just looping, you can get logically incorrect answers

      - Implement Peano arithmetic -> this is impossible

      - Represent `0` by the atom `'z'` and represent `N + 1` by the structure `succ(N)`

        - `succ(succ(succ(z))) = 3`

      - Specify addition:

        - ```prolog
          add(z, N, N).
          add(succ(M), N, succ(MplusN)) :- add(M, N, MplusN).
          ```

      - Specify subtraction:

        - ```prolog
          sub(A, B, C) :- add(B, C, A).
          ```

      - Specify less than:

        - ```prolog
          lt(X, succ(X)).
          lt(X, succ(Y)) :- lt(X, Y).
          ```

      - Prolog messes up in infinite terms, once they're allowed, Prolog is no longer based on this traditional logic

  - Prolog developers know about this problem

    - They have fixed it -> built-in predicate `unify_with_occurs_check/2`
      - Does unification like `'='` does, but refuses to create cycles
      - `occurs_check` - whenever Prolog binds a value to a variable, it does an extra check to see if that variable occurs in that value
      - This check slows down unification
    - Fixing it is too expensive and Prolog programs typically don't need it
      - Tradeoff between efficiency and correctness -> efficiency wins here

- Another infinite-loop problem that's bigger - you write code that recurses forever

  - Some very simple predicates that have no problem

    - `true.`
    - `fail` - no source code, empty

  - Now, one with a problem

    - ```prolog
      sbtrue :- sbtrue.
      sbtrue.
      ```

      - This kills the stack

  - Another one that's logically equivalent

    - ```prolog
      repeat.
      repeat :- repeat.
      ```

  - Aside on finite domain solving

    - So far we're assumed all passing information around is done by unification
      - Constants compare equal to themselves
      - Variables can be instantiated to terms
      - Structures compared recursively
    - Natural generalization of Prolog unification
      - Ordinarily, the only constraint you can place on a variable is to bind it to a term
      - The finite domain of GNU Prolog lets you put other constraints on a variable
      - These constraints can pile up as you succeed
      - This is a big deal in machine learning

  - How to control Prolog's exploration of a proof tree: the cut (`!`)

    - `?- generate(X, Y, Z), check(Y, Z), write(Y).`

    - Suppose the check always fails unless `Y` is a member of the list `Z`

    - `?- generate(X, Y, Z), member(Y, Z), check(Y, Z), write(Y).`

      - This is a performance improvement
      - Suppose `Y = a` and `Z - [a, a, a, a, a]`
      - `member/2` will succeed 5 times, 4 of those are useless, so we call `check/2` 5 times

    - ```prolog
      ?- generate(X, Y, Z), memberchk(Y, Z), check(Y, Z), write(Y).
      memberchk(X, [X|_]) :- !.
      memberchk(X, [_|L]) :- memberchk(X, L).
      ```

      - `!` is a built-in predicate that does 2 things:

        - Always succeeds (equivalent to `true` logically)
        - When you backtrack into it, the calling predicate immediately fails (`memberchk/2` immediately fails)

      - `once(P) : P, !`

        - ```prolog
          ?- generate(X, Y, Z), once(member(Y, Z)), check(Y, Z), write(Y).
          memberchk(X, [X|_]) :- !.
          memberchk(X, [_|L]) :- memberchk(X, L).
          ```

  - ```prolog
    \+(P) :- P, !, fail.
    \+(_).
    ```

    - This is negation in Prolog, it works, but it has problems
    - You can get answers that are not logical, you've pruned away an important part of your program
    - You can get incomplete answers for the same reasons
    - If you use `\+`, don't use it on arguments that contain logical variables
    - Stands for `P` is not provable
    - Use assumes the Closed World Assumption - everything in the world that is true is given, everything else is false

- Debugging Prolog
  - Standard Prolog debugger uses a 4-port model of debugging
    - Call, fail, succeed, backtrack
    - Stops the Prolog interpreter at each of the ports

## **Reading 7: A First Look at Prolog**

- Prolog is useful for domains that involve searching for solutions to logically-specified problems

- The Building Blocks - Prolog Terms

  - 3 kinds: constants, variables, compound terms
    - Constant - integer, real number, or an atom
      - Names that start with lowercase letter + 0 or more additional letters, digits, or underscores is an atom
      - Atoms treated as constants in Prolog - like a string constant
    - Variable
      - Names beginning with an uppercase letter or an underscore + 0 or more additional letters, digits, or underscores
      - Underscore-led variables have special treatment
    - Compound term
      - An atom followed by a parenthesized, comma-separated list of values
      - Look like function calls in other languages - really just structured data
  - Pattern matching in Prolog terms is called unification
    - 2 terms are said to unify if there is some way of binding their variables that makes them identical
  - Prolog interpreter maintains a collection of facts and rules of inference - internal database that changes as the system runs
    - Prolog program is a set of data for this database
    - Simplest element of the database is a fact - a term followed by a period
      - `parent(kim, holly)`
    - Atom that starts a compound term with `n` parameters is a predicate of arity `n`

- Getting Started with a Prolog Language System

  - `consult` - predicate that can read in facts from a file

  - A query asks if the language is able to prove something

    - All interaction with the Prolog language system takes place through queries

  - Any term can appear in a query

    - ```prolog
      ?- parent(P, jean).
      P = herbert.
      ```

    - Is there a parent of Jean?

  - Prolog predicates are less strict than functions in other languages

    - ```prolog
      ?- parent(esther, Child).
      Child = margaret.
      ?- parent(Parent, Child).
      Parent = kim,
      Child = holly.
      ```

    - Have the choice of stopping or looking for other solutions to the query

      - Can type a semicolon to deny the current query and continue search

    - ```prolog
      ?- parent(Person, Person)
      false.
      ```

      - Checks if anybody is their own parent

  - Queries can be separated by commas - system treats such queries as the logical conjunction of the terms in the list

    - ```prolog
      ?- parent(margaret, X), parent(X, holly).
      X = kim.
      ```

      - `X` must satisfy both predicates

    - ```prolog
      ?- parent(Parent, kim), parent(Grandparent, Parent).
      ...;
      ...;
      false.
      ```

      - System asked for another way to prove the query, but it couldn't -> returns false despite other successes
        - The successes were rejected by the user
      - Asks if Kim has grandparents

- Rules

  - Rule to prove a great-grandparent relation:

    - ```prolog
      greatgrandparent(GGP, GGC) :-
      	parent(GGP, GP), parent(GP, P), parent(P, GGC).
      ```

      - English: to prove `greatgrandparent(GGP, GGC)`, find some `GP` and `P` for which you can prove `parent(GGP, GP)`, then `parent(GP, P)`, and then `parent(P, GGC)`

  - Rule syntax:

    - Term called the head of rule (`greatgrandparent(GGP, GGC)`)
    - Followed by `:-`
    - Followed by comma-separated list of terms called the conditions of the rule
    - Ended by a period

  - Rule tells the language system to prove something -> prove the head, prove the conditions

  - Rules are another type of clause -> rules and facts

  - Steps a Prolog system follows:

    - Start with a goal (term to be proved), which is the query term
      - `greatgrandparent(esther, GreatGrandchild).`
    - To prove this goal, we have to unify it with some fact or the head of some rule in the database
      - Goal unifies with the head of the `greatgrandparent` rule
      - Conditions adopted as new subgoal
      - `parent(esther, GP)`, `parent(GP, P)`, `parent(P, GreatGrandchild)`
    - Prove the first subgoal
      - Unifies with `parent(esther, margaret)`
      - New subgoals: `parent(margaret, P)`, `parent(P, GreatGrandchild)`
    - Prove the next subgoal
      - Unifies with `parent(margaret, kim)`
      - New subgoal: `parent(kim, GreatGrandchild)`
    - Prove the final subgoal
      - Unifies with `parent(kim, holly)`
      - `GreatGrandchild = holly`
    - System outputs variables that occurred in the query (`GreatGrandchild`)

  - The scope of the definition of a variable is the clause that contains it

  - First occurrence within a clause of a name beginning with a capital letter serves as a definition of a variable with that name

    - All other occurrences of the same name in that clause are in the scope of that definition and are bound to the same variable

  - Rules can be recursive, with a condition that unifies with its own head

    - ```prolog
      ancestor(X, Y) :- parent(X, Y).
      ancestor(X, Y) :- parent(Z, Y), ancestor(X, Z).
      ```

    - Predicate defined using 2 rules:

      - First says that `X` is an ancestor of `Y` if `X` is a parent of `Y`
        - This acts as the base case
      - Second says that `X` is an ancestor of `Y` if `X` is an ancestor of a parent of `Y`

    - Prolog language systems search for proofs by trying rules in the order they are given - base case rules and facts should be put first

  - Prolog program is a sequence of clauses, each of which is either a fact or a rule

- The Two Faces of Prolog

  - Instead of thinking of rules as instructions on how to prove something, you can focus on their logical content
  - Think of `greatgrandparent` in this context
    - For all bindings of `GGP`, `GP`, `P`, and `GGC`, if `parent(GGP, GP)`, `parent(GP, P)`, and `parent(P, GGC)` are true, then `greatgrandparent(GGP, GGC)` is true
  - A Prolog program is just a formula in 1st order mathematical logic
    - Declarative way of thinking about the languages
  - Functional languages are called declarative because each piece of the program is a declaration that corresponds to a simple mathematical abstraction
    - People argue that imperative languages are doomed to subtle side-effects and interdependencies
    - Simpler semantics -> easier to develop/maintain programs
  - Prolog has both declarative and procedural aspects

- A Word About Term Interpretation

  - Beginners mistakenly assume that the language system understand atoms
  - Names of atoms suggest obvious interpretations to a human reader -> Prolog interpreters do not have these interpretations
  - Names are chosen to make the program more readable, not because they matter to the language

- Operators

  - Operators are special predicates for which the Prolog language system will accept operator notation
  - `=` is an operator that is provable if and only if its 2 parameters can be unified
    - Can be written `=(1, 1)` or `1 = 1`
  - Predefined operators:
    - Arithmetic: `+`, `-`, `*`, and `/`
      - Does not evaluate the term
    - `:-` operator used to define rules
      - All clauses have the same syntax - a single term followed by a period
      - For rules, that single term is a compound term with `:-` as its predicate
    - Comma operator used to separate the conditions of a rule or the terms in a conjunctive query

- Lists

  - The atom `[]` represents the empty list

  - `.` predicate corresponds to the `::` operator in ML

    - `.` is a list -> Prolog exposes its representation of lists
    - Writing lists with `[ ]` notation is just shorthand

  - Prolog lists can contain a mixture of different types of elements

  - `|` followed by a term represents the tail of a list

    - `[1, 2|X]` unifies with any list that starts with the elements `1` and `2`, `X` is bound to the rest of the list

  - `append` and Other Flexible Predicates

    - `append(X, Y, Z)` is provable if and only if `Z` is the result of appending the list `Y` onto the end of the list `X`

      - Can be used like ML's `@`

        - ```prolog
          ?- append([1, 2], [3, 4], Z).
          Z = [1, 2, 3, 4].
          ```

      - Can also be used in a more flexible way

        - ```prolog
          ?- append(X, [3, 4], [1, 2, 3, 4]).
          X = [1, 2].
          ```

        - ```prolog
          ?- append(X, Y, [1, 2, 3])
          X = [],
          Y = [1, 2, 3] ;
          X = [1],
          Y = [2, 3] ;
          X = [1, 2],
          Y = [3] ;
          X = [1, 2, 3],
          Y = [] ;
          false.
          ```

      - Implementation:

        - ```prolog
          append([], B, B).
          append([Head|TailA], B, [Head|TailC]) :-
          	append(TailA, B, TailC).
          ```

          - First clause states that the result of appending any list `B` to the empty list is the same list `B`
          - Second clause unifies the heads of the first list and the third list, while using the second list
            - Prove `append` using `append` -> eventually comes out to the base case

    - In Prolog, you do not need to specify how the program fails

    - `member(X, Y)` - provable if the list `Y` contains `X`

    - `select(X, Y, Z)` - provable if the list `Y` contains the element `X`, and `Z` is the same as `Y` but with one instance of `X` removed

    - `nth0(X, Y, Z)` - provable if `X` is an integer, `Y` is a list, and `Z` is the `X`th element of `Y`, counting from 0

    - `length(X, Y)` - provable if `X` is a list of length `Y`

      - These predicates are all flexible about their parameters - queries using them, can contain variables anywhere and produce logically correct results

  - `reverse` and Other Inflexible Predicates

    - ```prolog
      reverse([], []).
      reverse([Head|Tail], X) :-
      	reverse(Tail, Y), append(Y, [Head], X).
      ```

      - This is inefficient

    - `reverse` cannot be used as flexibly as `append`

      - Meant to be used where the first parameter is input and the second is output

    - Non-terminating queries are Prolog's version of infinite loops

    - `sort(X, Y)` - sorts a list `X` into a sorted list `Y`

      - `X` cannot be a variable

    - Better for predicates to be fully flexible - more useful and easier to understand

      - Restricted implementations are sometimes choses for efficiency/simplicity

    - The Anonymous Variable

      - `_` is used as a wildcard/anonymous variable
      - All occurrences of `_` are bound independently of one another
      - Use `_` when you need to match a term but do not use the resulting binding

- Negation and Failure

  - Use the `not` predicate for logical negation

  - If Prolog fails to prove the goal within the `not`, the not goal succeeds

  - Watch out for procedural interpretations

    - ```prolog
      sibling(X, Y) :- not(X=Y), parent(P, X), parent(P, Y).
      ```

    - Fails on `sibling(X, Y)` because `X` and `Y` are unbound for the not predicate

    - Fix by reordering:

      - ```prolog
        sibling(X, Y) :- parent(P, X), parent(P, Y), not(X=Y).
        ```

## **Reading 8: A Second Look at Prolog**

- Unification

  - A substitution is a set of bindings for variables

    - When a Prolog system succeeds with a query, it reports the substitution for the variables in the query term that it used to find a proof
      - Prolog uses substitutions frequently while trying to prove queries, the reported ones are only a tiny sample
    - Substitutions written as functions that map variables to terms
    - The result of applying a substitution to a term is an instance of that term
      - When Prolog proves a query, it reports a substitution needed to make a provable instance of the query term
    - 2 Prolog terms are said to unify if there is a some substitution (a unifier) that makes them identical
      - 2 terms that unify might have more than 1 unifier → Prolog binds variables only when necessary, so it chooses unifiers that do just enough substitution to make terms unify
        - These are called most general unifiers
        - A term `x` is more general than another term `y` if `y` is an instance of `x` and `x` is not an instance of `y`
        - All MGUs for a pair of terms are identical except for the way they rename variables

  - Unification is a critical utility for Prolog programs

    - Other languages have parameter-passing mechanisms, but Prolog has unification
    - Other languages have assignment, but Prolog has unification
    - Other languages have data constructors, but Prolog has unification
    - Other languages have data selectors, but Prolog has unification

  - The Occurs Check

    - In general an MGU for a variable `X` and a term `t` is `{X→t}`

    - Exception: if `t` is a compound term in which the same variable `X` occurs, then it cannot be unified with `X` at all

      - Checking whether a particular variable `X` occurs in a term `t` is called the occurs check
      - This is part of any algorithm for finding the MGU of any 2 terms

    - Most Prolog systems implement unification without the occurs check

      - The occurs check rarely shows up in real Prolog programs

      - Programmers tolerate this for the sake of speed

      - Make the system vulnerable to infinite loops/produce faulty unifiers

        - ```prolog
          ?- append([], X, [a|X]).
          X = [a|**]
          ```

          - This is a cyclic term, a circular linked list of `a`'s

      - Result of a unification of 2 terms that should fail the occurs check is undefined

- A Procedural View

  - `p :- q, r`
    - To prove this goal, unify with `p`, then prove `q`, then prove `r`
    - If all 3 steps succeed, the goal is proved
    - If any steps fail, the goal cannot be proved with this procedure
  - Backtracking
    - Prolog uses backtracking to explore all possible targets of a procedure call in the order given, until it finds as many successes as the caller requires or until it exhausts all possibilities
  - Substitution
    - A procedure computes substitutions for variables as it goes
    - Initial substitution is the MGU of the goal term and the head of the clause
      - Additional substitutions are supplied by the proof of each condition in a rule
    - Before the proof of a condition in a rule is attempted, all the substitutions for the rule up to that point are applied
    - Substitution and backtracking work together
      - Backtracking tries different ways of proving a goal, each way makes its own series of substitutions
  - Think not only about the flow of control, but also the flow of substitutions
    - Substitutions carry information from the goal term into the procedure, from each condition in a rule to the next, and back out again

- An Implementational View

  - The Resolution Step
    - Resolution applies 1 clause from a program to make 1 step of progress on a list of goal terms to be proved
    - Removes one term from the list of goals and adds 0 or more terms in its place
    - Applies the MGU that unified the rule head and the goal term to all of the new goal list
      - Only works if the head of the clause and head of the list of goals actually unify
  - The Prolog Interpreter
    - `solve` function implements the Prolog interpreter
    - The `solve` function takes a parameter names goals - a list of goal terms to be proved
      - Each time solve proves the list of goal terms by reducing it to an empty list, it calls `succeed`
  - Collecting the Substitutions
    - `solve` procedure is different from the Prolog language system in that it has no way to report the substitutions it used to succeed
      - It doesn’t collect the substitutions, it just applies them immediately
  - This view of Prolog’s model of execution is implementable
    - Gives a view of Prolog that’s unambiguous
    - Modern Prolog compilers don’t work anything like this

- An Abstract View - Proof Trees

  - Proof-Tree Definition

    - A proof tree is defined as follows:
      - Has 2 kinds of nodes: nothing nodes and solve nodes
      - Each nothing node is a leaf
      - Each solve node contains a list of terms
        - If this list is empty, the solve node is a leaf
        - Otherwise, the solve node has one child for each clause in the program, in order
        - If a given clause doesn’t unify with the head of the list at that solve node, the corresponding child is a nothing node
        - Otherwise, the corresponding child is a solve node containing the list of terms formed from the current list of terms and the clause by applying the resolution step
      - The root of the tree is a solve node containing the list of query terms
    - Given a program and a query, a Prolog language system must act in the order given by a depth-first, left-to-right traversal of the proof tree
    - It doesn’t need to construct the proof tree, but it has to find successes in the proof-tree order

  - Infinite Proof Trees

    - ```prolog
      p :- p.
      p.
      ```

      - This program generates infinite proof trees by the depth-first, left-to-right search behavior

  - Variable Renaming

    - Variables in a clause should be independent of any other variables that happen to have the same names
    - If a variable in a clause happens to have the same name as a variable in the goal terms in the old model, it treats them as if they were the same
    - Eliminate this problem by variable renaming - each time a clause is used, it will be given a fresh set of variable names, different from all the other names that have been used
      - This avoids accidental use of the variable names that already appear in the list of goal terms

- The Lighter Side of Prolog

  - Quoted Atoms as Strings

    - Any string of characters enclosed in single quotes is a term in Prolog
      - `‘abc’` is the same as `abc`
      - Enclosing in single quotes allows you to have spaces in atoms, or atoms that start with capital letters
      - Easiest way to manipulate simple strings in Prolog

  - `write` and `read`

    - The predicate `write(X)` is true for any `X`, but prints out the parameter `X` as a side-effect
      - Can be used for debugging
    - The predicate `read(X)` reads a typed input into `X`
      - This requires the input to be a Prolog term, ended with a period, which will then be unified with `X`

  - `assert` and `retract`

    - The predicate `assert(X)` adds the term `X` as a fact in the database
    - The predicate `retract(X)` removes the term `X` from the database
      - Retracting a term doesn’t necessarily make it unprovable, it just removes 1 clause from the database
      - To retract all things in the database that unify with a given term, you can use the `retractall` predicate
    - Predicates loaded using consult can’t be modified by `assert` or `retract`
    - Use of `assert` and `retract` can make programs self-modifying
      - This makes behavior difficult to reason
      - Isn’t safe, declarative, or efficient

  - The Cut

    - Special predicate that takes no parameters - `!`

      - It always succeeds
      - Used to eliminate backtracking

    - ```prolog
      p :- q1, q2, …, qj, !.
      ```

      - Once Prolog succeeds in solving the first conditions `q_1` through `q_j`, it reaches the cut
      - The cut succeeds, but instructs Prolog to not backtrack and find other solutions to `q_1` through `q_j`

    - The first solution found for a given goal using this rule will be the last solution found for that goal

      - Any subsequent clauses that occur in the program will only be tried if this one fails before the cut

    - Green cuts - placed to improve efficiency by preventing backtracking to places no solutions will be found anyways

    - Red cuts - change the solutions that are found

      - Makes the program non-declarative

## **Reading 9: A Third Look at Prolog**

- Prolog strays away from numerical computation, as it’s built around the manipulation of terms, not numbers

- Prolog programs can be logical specifications of a problem domain, and the query can be a request for a solution to a problem in that domain

- Numeric Computation

  - Terms in Prolog are not evaluated without special effort

  - Numeric Evaluation

    - The predicate `is` can be used to evaluate terms

    - ```prolog
      ?- X is 1+2*3.
      X = 7.
      ```

      - The `is` predicate is an operator
      - When Prolog solves an `is` goal, it evaluates the second parameter and unifies the result with the first
        - For most situations, the first parameter is a variable and is bound to the result of the evaluation of the second parameter
        - The second parameter must be fully instantiated (no unbound variables)
      - The predicates used in the expression being evaluated must be evaluable predicates
        - Binary numeric operators: `+`, `-`, `*`, `/`
        - Unary numeric operator: `-`
        - Arithmetic function: `sqrt(X)`, `abs(X)`, etc.

    - Real numbers and integers do not unify

    - Prolog is dynamically type checked → overloading of operators is resolved at runtime

  - Numeric Comparisons

    - 6 operators for comparing numeric values: `<`,` >`, `=<`, `>=`, `=:=`, `=\=`
      - When Prolog tries to solve one of these goals, it evaluates both parameters and compares the results numerically
      - Both parameters must be fully instantiated
    - Several related operators
      - `X is Y` - evaluates `Y` and unifies the result with `X`
        - Use when you want to evaluate an expression and bind an unbound variable to its value
      - `X=Y` - unifies `X` and `Y`
        - Unification doesn’t evaluate numeric expressions, only pays attention to term structure
      - `X=:=Y` - evaluates both `X` and `Y` and succeeds if and only if they are numerically equal
        - Real and integers can be numerically equal
        - Both operands must be fully instantiated

- Problem Space Search

  - Prolog is particularly well suited for problems that involve searching in a logically defined space of possible solutions

  - The Knapsack Problem

    - Find items to bring to maximize the amount of value you’re carrying

    - ```prolog
      [food (bread, 4, 9200),
      food (pasta, 2 , 4600),
      food (peanutButter, 1, 6700),
      food (babyFood, 3, 6900)]
      ```

    - ```prolog
      % weight(L, N) takes a list L in the form (Name, Weight, Calories) and unifies the total weight of the terms with N
      
      weight([], 0).
      weight([food(_, W, _) | Rest], X) :- weight(Rest, RestW), X is W + RestW.
      ```

    - ```prolog
      % calories(L, N) takes a list L in the form (Name, Weight, Calories) and unifies the total sum of all calories with N
      
      calories([], 0).
      calories([food(_, _, C) | Rest], X) :- calories(Rest, RestC), X is C + RestC.
      ```

    - ```
      % subseq(X, Y) succeeds when list X is the same as list Y, but with 0 or more elements omitted
      
      subseq([], []).
      subseq([Item | RestX], [Item | RestY]) :- subseq(RestX, RestY).
      subseq(X, [_ | RestY]) :- subseq(X, RestY).
      ```

      - This predicate can generate subsequences of a list

    - `findall(X, Goal, L)` unifies `L` with a list of terms, each representing a way to prove `Goal`; each term is an instance of parameter `X`

      - Predefined

    - ```
      % legalKnapsack(Pantry, Capacity, Knapsack) takes a list Pantry of food items and a Capacity; Knapsack is unified with a subsequence of Pantry whose total weight is =< Capacity
      
      legalKnapsack(Pantry, Capacity, Knapsack) :-
      	subseq(Knapsack, Pantry), weight(Knapsack, W), W =< Capacity.
      ```

    - ```
      % maxCalories(List, Result) takes a List of lists of food terms and unifies Result with the element in the list that maximizes total calories
      
      maxC([], Sofar, _ Sofar).
      maxC([First | Rest], _, MC, Result) :-
      	calories(First, FirstC), 
      	MC =< FirstC, 
      	maxC(Rest, First, FirstC, Result).
      maxC([First | Rest], Sofar, MC, Result) :-
      	calories(First, FirstC),
      	MC > FirstC,
      	maxC(Rest, Sofar, MC, Result).
      maxCalories([First | Rest], Result) :- 
      	calories(First, FirstC), maxC(Rest, First, FirstC, Result).
      ```

    - ```
      knapsackOptimization(Pantry, Capacity, Knapsack) :-
      	findall(K, legalKnapsack(Pantry, Capacity, K), L),
      	maxCalories(L, Knapsack).
      ```

- Farewell to Prolog

  - Includes some common control predicates to make common programming patterns easier to express
    - `->` is shorthand for if-then and if-then-else
    - `\+` is shorthand for negation-by-failure
    - `;` is shorthand for disjunction of goals\
  - Includes predefined predicates `catch` and `throw` for exception handling
  - Many public Prolog libraries: basic data structures, network and file I/O, GUIs, interfaces to other languages, object-oriented extensions, etc.

## **Lecture 13: Propositional Logic**

- Prolog is based on logic - what’s logic?
- Propositional logic - reasoning about propositions
  - Proposition - statements about the world
  - Connectives - let you hook together propositions
  - Logical implication doesn’t match what people’s intuitions think it means
    - `p → q` is only false when `p` is true and `q` is observed to be false
      - Tautology
    - Not based on causality
    - Equivalent to `~p || q` or `p <= q` in C
  - Avoid tautologies in Prolog
  - Not good enough for a lot of real-world problems
- Predicate calculus/first-order logic
  - Propositions can have arguments called predicates
  - Proving these statements is harder than in propositional logic
    - PL: run through all possibilities of T/F for every proposition
    - FO: undecidable, no general algorithm
      - We want to check anyways
  - This is what the Prolog interpreter does
    - Checks if all the things you’ve told the interpreter imply something

- Any first-order logic statement can be mechanically translated to a clause
  - Find that the antecedent is true → the consequent is true
  - All logical variables in a clause are implicitly universally qualified
- Prolog interpreter operates via proof by contradiction
  - Takes query as a false statement, then comes up with a counterexample to that false statement
  - Answering via double negation

## **Reading 10: Introduction to Scheme**

- Scheme is a general purpose language
  - Supports operations on structured data (strings, lists, vectors, etc.)
  - Supports operations on traditional data (numbers, chars, etc.)
- Scheme is highly portable across different machines since machine dependencies are almost completely hidden
- Newer builds of Scheme (compiler-based) are fast, capable of writing programs that run on par with lower-level languages
  - Relative inefficiency a result of runtime checks
- Storage for object contents is dynamically allocated when necessary and then automatically deallocated by a garbage collector
  - Smaller values like `int`, `char`, `bool`, and the empty list are immediates and do not incur allocation/deallocation
  - All objects are first-class data values
    - They may be passed freely as arguments to procedures, returned from procedures, and combined into new objects
- Scheme is a call-by-value language
  - For mutable objects, values are actually pointers to the actual storage
    - These are hidden from the programmer
- Scheme is made up of a small core of syntactic forms from which the rest of the forms in the language are built
  - Core forms + derived forms + primitive procedures
  - Compiler can be small, fast, and reliable
- Scheme variables and keywords are lexically scoped and Scheme programs are block-structured
  - Local bindings are only visible lexically (within the program text of that particular code block)
  - Bindings can be shadowed by bindings of the same name in a more local scope
  - The scope of a binding is the block in which the bound identifier is visible, minus sections where that identifier is shadowed
  - Ideal for modularity, readability, maintainability, and reliability
- Procedure definitions can appear within another block/procedure
  - The procedure can be called any time after, even if the enclosing block has finished executing
  - May be unnamed, procedures are first-class data objects like strings or numbers
  - Allows for recursion
- Supports definition of arbitrary control structures with continuations
  - Procedures that embody the remainder of a program at a given point
  - May be obtained at any time during execution
  - When invoked, the program returns to the point where it was obtained
  - Allows for backtracking, multithreading, and coroutines
- Allows definition of syntactic extensions
  - Transformation procedures dictate how existing syntactic forms map to new ones
- Evolved from Lisp and is considered a Lisp dialect
- Scheme Syntax
  - Programs are made up of keywords, variables, structured forms, constant data, whitespace, and comments
    - Keywords, variables, and symbols are called identifiers
      - May be formed from letters, digits, and certain special characters
      - Cannot start with `@`, `+`, `-`, or `.`
        - `+`, `-`, `...`, and `->` are exceptions to this
      - No inherent limit on the length of identifiers
      - Case is significant
    - Structured forms and list constants are enclosed in parentheses
      - Empty list is `()`
      - Brackets can be used in place of parentheses for readability
      - Vectors are lists preceded by `#`
      - Bytevectors are unsigned byte values `(0, ..., 255)` preceded by `#vu8`
    - Strings are enclosed in double quotes
    - Characters are preceded by `#\`
    - Numbers can be written in integers, ratios, floating point, scientific notation, or complex numbers in rectangular or polar notation
    - Boolean for true and false are `#t` and `#f`
      - Anything other than `#f` is true
  - Expressions may span multiple lines and no terminator is required
  - Whitespace between expressions is insignificant
    - Indenting used for readability
  - Comments appear between` ;` and the end of the line
    - Block comments are delimited by `#|` and `|#`
    - `#;` precedes a datum comment
- Scheme Naming Conventions
  - Predicate names end in a `?`
    - Predicates are procedures that return true or false
    - Numeric comparators are exceptions to this
  - Type predicates are created from the name of the type and `?`
  - Names of most character, string, and vector procedures start with` char-`, `string`, and `vector-`
    - Some list procedures start with `list-`, most do not
  - Names of procedures that convert an object of one type into another are `type1->type2`
  - Names of procedures and syntactic forms that cause side effects end with `!`
    - I/O procedures are exceptions to this
- Typographical and Notational Conventions
  - Procedure or syntactic form whose sole purpose is to perform a side-effect should return unspecified
    - Implementation is free to return any number of values
  - Most standard procedures return a single value
    - Language supports procedures that return 0, 1, 1+, or a variable number of values
    - Standard expressions can return the values of their subexpression
  - Syntax violation - program is malformed, detected prior to program execution
    - Exception of type `&syntax` raised, program isn’t executed

## **Reading 11: Getting Started with Scheme**

- Interacting with Scheme

  - Interaction with Scheme follows a REPL

  - Can load files using load procedure

  - Scheme ignores indentation and line breaks - reads program as if it were on 1 line

    - Establish a style and stick to it

  - Constants evaluate to themselves

  - Can define features using the `define` keyword

    - ```scheme
      (define square
      	lambda (n) (* n n)))
      ```

      - All structured forms are enclosed in parentheses and written in prefix notation

- Simple Expressions

  - Simplest Scheme expressions are constant data objects (strings, numbers, symbols, lists, etc.)

    - Numbers
      - Entering a number echoes it back to you
      - Includes exact and inexact integers, rational, real, and complex numbers
        - Exact integers and rational numbers have arbitrary precision
        - Inexact numbers are represented according to IEEE floating-point
      - `+`, `-`, `*`, and `/` provided for arithmetic procedures

  - Procedure applications can be nested, innermost values will be calculated first

  - Basic aggregate data structure is the list

    - Lists can be heterogeneous

    - Lists can be nested

    - Use the syntactic form `quote` to tell Scheme that the following data is a list, not a procedure call

      - `(quote (1 2 3 4 5)) → (1 2 3 4 5)`
      - Abbreviated with `'`
        - `'(1 2 3 4 5) → (1 2 3 4 5)`
      - Called `quote` expressions
        - Objects enclosed in a `quote` expression are quoted
      - Can also be used to prevent Scheme from treating a symbol as a variable

    - `car` - returns the first element of a list

      - `(car ‘(a b c)) → a`

    - `cdr` - returns the tail of the list

      - `(cdr ‘(a b c)) → (b c)`
      - `cdr` of a singleton list is the empty list

    - `car` and `cdr` require non-empty lists as arguments

    - `cons` - constructs list

      - `(cons ‘a ‘()) → (a)`

      - Actually builds pairs, the second argument of `cons` may not be a list

        - The `cdr` of the last pair in a proper list is the empty list, otherwise the list is an improper list (represented by `.`)

          - ```scheme
            (cons ‘a ‘b) → (a . b)
            (cdr ‘(a . b)) → b
            (cons ‘a ‘(b . c)) → (a b . c)
            ```

    - `list` - takes an arbitrary number of arguments and builds a proper list

      - `(list ‘a ‘b ‘c) → (a b c)`

- Variables and Let Expressions

  - Given an expression `expr` containing a variable `var`, we want `var` to have a value `val` when `expr` is evaluated

    - ```scheme
      (let ((x 2))
      	(+ x 3) = 5
      ```

  - The `let` syntactic form includes a list of variable-expression pairs, along with a sequence of expressions (the body of the let)

    - `(let ((var expr) … ) body_1 body_2 ... )`

  - Variables are bound to the values by the `let`

    - Variables bound by `let` are let-bound variables

  - Used to simplify cases of identical subexpressions

  - Brackets often used in place of parentheses for the bindings of a` let` expression

  - let-bound variables are only visible within the body of the `let`

  - `let` expressions can be nested

    - When nested `let` expressions bind the same variable the outer binding is shadowed by the inner binding

- Lambda Expressions

  - `lambda` can be used to create a new procedure

    - `(lambda (var ... ) body_1 body_2 ... )`

      - `var ...` are the formal parameters of the procedure
      - The sequence `body_1 body_2 ...` is its body
      - The argument values that `lambda` is called with are the actual parameters, which are bound to the formal parameters

    - Can be established as the value of a variable

      - ```scheme
        (let ([double (lambda (x) (+ x x))])
        	(list (double (* 3 4))
        		(double (/ 99 11))
        		(double (- 2 7)))) → (24 18 -10)
        ```

  - Procedures may accept 1+ arguments and those arguments may be procedures themselves

  - ```scheme
    (let ([x ‘a])
    	(let ([f (lambda (y) (list x y))])
    		(f ‘b))) → (a b)
    ```

    - `x` is bound outside of the `lambda expression` → `x` occurs free in the lambda expression/`x` is a free variable of the `lambda` expression
      - Variables that occur free should be bound by an enclosing `let` or `lambda`
    - `y` is bound within the lambda expression → `y` doesn’t occur free

  - `let` is a syntactic extension defined in terms of `lambda` and procedure application

  - `lambda` parameter specification can be:

    - A proper list of variables
      - Requires an exact number of parameters
    - A single variable
      - Can take any number of parameters
    - An improper list of variables
      - Takes at least `n` parameters

- Top-Level Definitions

  - Top-level definitions can be established with the syntactic form `define`
  - Top-level definitions are visible in every expression, except those where the binding is shadowed
  - Can be established for any object, not just procedures
    - Usually used for procedures
  - Any definition where the expression is a `lambda` expression can suppress the `lambda` syntactic form

- Conditional Expressions

  - `if` expressions have the form `(if TEST CONSEQUENT ALTERNATIVE)`

    - `CONSEQUENT` is the expression to evaluate if `TEST`is true

    - `ALTERNATIVE` is the expression to evaluate if `TEST` is false

    - ```scheme
      (define abs
      	(lambda (n)
      		(if (< n 0) (- 0 n) n )))
      ```

  - `or` expressions have the form `(or ... )`

    - If there are no subexpressions, this evaluates to false
    - Expressions are evaluated in order until 1 evaluates to true or there are no more expressions to evaluate
      - If a true expression is found, the value of the `or` expression is the value of the last subexpression evaluated

  - `and` expressions work similar to `or`

  - The `null?` predicate returns true if its argument is the empty list

  - The `eqv?` predicate returns true if its 2 arguments are equivalent

  - Scheme has type predicates that return true if the value is of the given type

  - The expression `cond` is like `if`, except it allows for multiple `TEST` and `ALTERNATIVE` expressions

    - ```scheme
      (define sign
      	(lambda (n)
      		(cond
      			[(< n 0) -1]
      			[(> n 0) +1]
      			[else 0])))
      ```

    - Takes the form `(cond (TEST EXPR) ... (else EXPR))`

    - `else` clause may be omitted

- Simple Recursion

  - Recursion - application of a procedure form within that procedure

  - Recursive procedure - a procedure that applies itself

  - Practical use of a recursive procedure necessitates the ability for the procedure to terminate

    - Recursive procedures should have a base case and a recursive step
    - The recursive step should bring the execution closer to the base case in some way

  - ```scheme
    (define length
    	(lambda (ls)
    		(if (null? ls)
    			0
    			(+ (length (cdr ls)) 1))))
    ```

  - Recursion preferred to iterative methods (loops, etc.)

  - ```scheme
    (define abs-all
    	(lambda (ls)
    		(if null? ls)
    			‘()
    			(cons (abs (car ls))
    				(abs-all (cdr ls))))))
    ```

    - This is an example of mapping - `abs-all` maps over all elements of `ls`

    - Can simplify with the map procedure

      - ```scheme
        (define abs-all
        	(lambda (ls)
        		(map abs ls)))
        ```

## **Reading 12: Going Further with Scheme**

- Syntactic Extension

  - Once defined, a syntactic extension has the same status as a core form

    - Compiler needs to make this distinction to focus on the core forms

  - Core syntactic forms include top-level define forms, constants, variables, procedure applications, `quote` expressions, `lambda` expressions, `if` expressions, and `set!` expressions

  - Syntactic extensions extend the syntax of Scheme beyond the core syntax

    - All syntactic extensions must ultimately be derived from the core forms

    - May appear whenever an expression or definition is expected

    - Defined with `define-syntax` - associates a syntactic transformation procedure (transformer) with a keyword

      - ```scheme
        (define-syntax let
        	(syntax-rules ()
        		[(_ ((x e) ...) b_1 b_2 ...)
        			((lambda (x ...) b_1 b_2 ...) e ...)]))
        ```

        - `let` is the name/keyword of the syntactic extension being defined
        - `syntax-rules` is an expression that evaluates to a transformer
        - Items following `syntax-rules` is a list of auxiliary keywords
        - Following the auxiliary keywords is a sequence of 1+ rules or pattern/template pairs
        - Identifiers other than an underscore or ellipsis appearing within a pattern are pattern variables
          - Match any substructure and are bound to that substructure within the corresponding template

- More Recursion

  - `let`-bound procedures are not straightforwardly recursive
    - Can get around this with the `letrec` syntactic form
      - `(letrec ((VAR EXPR) ...) body_1 body_2 ...)`
      - Variables are visible in the expressions as well as the body
      - It must be possible to evaluate all of the expressions without evaluating any of the variables
  - When a procedure call is in tail position, it is a tail call
    - This occurs when the value is returned directly from the `lambda` expression
    - Tail calls are treated as a `goto` or jump
    - When a procedure tail-calls itself, the result is tail recursion
    - Tail recursion can be used for indefinite iteration, without fear of stack overflow

- Continuations

  - During evaluate, the implementation must keep track of what to evaluate and what to do with the value
    - The what to do part is the continuation of a computation
  - At any point during the evaluation of any expression, there is a continuation ready to complete the computation from that point
  - The continuation of any expression can be captured with `call/cc`
    - Must be passed the procedure of 1 argument
    - Continuation is represented by a procedure `k`

- Continuation Passing Style

  - When a procedure is invoked via a nontail call by another, the called procedure receives an implicit continuation that is responsible for completing the calling procedure’s body and returning to the calling procedure’s continuation
    - If the call is a tail call, the called procedure receives the continuation of the calling procedure
  - CPS allows a procedure to pass more than one result to its continuation since the procedure that implements the continuation can take any number of arguments
  - CPS allows a procedure to take separate success and failure continuations
    - Can help to avoid the extra communication necessary to separate successful execution of a procedure from unsuccessful execution

## **Lecture 14: Scheme**

- Naming conventions

  - Predicates end with question marks
    - Equality functions in Scheme
      - `(= 0 0)` - Numeric equality returns `#t` or `#f`
        - `O(N)` for integers
        - `O(1)` for IEEE floating points
      - `(eq? a b)` - Object identity (like pointer comparison)
        - `O(1)`
      - `(eqv? a b)` - like `eq?`, but compares the contents of numbers and strings
        - `O(N)` → worst case for string length/integer width
      - `(equal? a b)` - like `eqv?`, but also compares recursively through pairs, vectors, etc.
        - `O(N)` for finite data structures
        - Infinity if 2 lists are cyclic and recursion goes on forever
    - Lots of type predicates in Scheme, one for each type
      - `(pair? x)` - returns `#t` if `x` is the result of a `cons` operation
      - `(null? x)` - returns `#t` if `x` is the empty list
      - `(boolean? x)`
      - `(procedure? x)`
      - `(symbol? x)` ...

- Difference between function calls and special forms

  - Syntax looks the same, semantics look different
    - `(f a b c)` - call the function `f` with arguments `a`, `b`, and `c`
      - Evaluate the expressions `f`, `a`, `b`, and `c` first, then do the call
    - `(if a b c)` - evaluate `a` and, if the result is not `#f`, evaluate `b` and return its value, otherwise, evaluate `c` and return
      - `if` is a special form
  - Some other special forms:
    - `(lambda (a b) (* b (+ a b)))` - nameless function, like OCaml’s `fun`
    - `(define pi 3.1415926)` - declares an identifier
    - `(cond (E1 F1) (E2 F2) … (En Fn) (else Fdefault))` - like `if`, but with multiple condition-expression pairings
      - Glorified `if-then-else`
    - `(or E1 E2 … En)` - evaluate `E1`, if it’s anything other than `#f`, yield its value, otherwise evaluate `E2` - if nothing is yielded by `En`, evaluate it and yield its value
      - Can return any type of value
      - True is any value other than `#f`
    - `(and E1 E2 … En)` - evaluate `E1`, if it’s `#f`, yield its value, otherwise evaluate `E2` - if nothing is yielded by `En`, evaluate it and yield its value

- Recursion in Scheme

  - Scheme does have loops, we won’t use them

  - Reverse of a list in Scheme

    - ```scheme
      (define (buggy-reverse x)
      	(if (null? x) ‘()
      	(append (reverse (cdr x)) (car x))))
      
      (define (slow-reverse x)
      	(if (null? x) ‘()
      	(append (reverse (cdr x)) (list (car x)))))
      ```

      - Write this more efficiently using an accumulator

        - ```scheme
          (define (revapp x a)
          	(if (null? x) a
          	(revapp (cdr x) (cons (car x) a))))
          (define (reverse x)
          	(revapp x ‘()))
          ```

          - We can write the same thing more compactly/readably using a named `let`

          - ```scheme
            (define (reverse x)
            	(let revapp ((x x) (a ‘())))
            		(if (null? x) a
            		(revapp (cdr x) (cons (car x) a)))))
            ```

            - The scope of `revapp` extends only to its body, its implementation is not exposed
            - Form of a named `let`:
              - `(let FUNCTION_NAME (PARAMETERS_AND_INITIAL_VALUES) BODY)`
              - Defines `FUNCTION_NAME` to be a function with parameters taken from `PARAMETERS_AND_INITIAL_VALUES` and `BODY`, then immediately calls it with arguments specified in parameters and initial values

- Identifiers

  - Can be either 1 of 2 things:

    - Variables that are bound to locations containing values
      - These bindings are determined statically due to static scoping
    - Syntactic keywords are bound to macros that expand into other Scheme expressions

  - Syntactic keywords have their own binding constructs so we can define our own special forms

    - ```scheme
      (define-syntax and
      	(syntax rules ()
      		((and) #t)
      		((and x) x)
      		((and x1 x2 …) (if x1 (and x2 …) #f))))
      ```

    - ```scheme
      (define-syntax and
      	(syntax rules ()
      		((or) #f)
      		((or x) x)
      		((or x1 x2 …) (let ((a x1))(if a a (or x2 …))))))
      ```

  - The problem of capture - not a problem in Scheme

    - Macro expansion is hygienic - scope is determined before you expand the macro, not after
    - C and C++ have non-hygienic macros, so they suffer from capture

- Tail-recursion - required of Scheme implementation

  - Basic idea: if a function `F` must do a function call to `G` next, and then it’ll return whatever `G` returns, then the code must reuse `F`’s stack space instead of consuming more space for `G`
  - Scheme programmers take advantages of this when they write their code

- Continuations

  - Controversial - low-level notions, too much control over how a Scheme interpreter works
  - A very simple low-level control feature that will let us build a lot of other stuff
    - Exception handling, backtracking, etc.
  - Have been called the “essence of Scheme”
  - Basic idea: any interpreter must keep track of 2 things:
    - What expression to evaluate next (the instruction pointer)
    - What to do with this value once the expression has been evaluated (the environment pointer)
  - A continuation is an instruction pointer, environment pointer pair
    - A pair of pointers to the planned future of your program’s execution
    - We can take advantage of this by creating objects that are continuations
  - There’s a built in Scheme function for this
    - `(call-with-current-continuation p)`
    - Creates a continuation, passes it as an argument to `p`, which must be a function that accepts continuations as arguments, and knows what to do with it

## **Lecture 15: More Scheme and Storage Management**

- Scheme continuations

  - A continuation stands for an `(ip, ep)` pair that will tell the interpreter how to execute the rest of your program

  - It’s the head of a “linked list” that tells your program what to do

  - Scheme lets us create and use continuations directly

    - To create a continuation, use `call-with-current-continuation` or `call/cc`

      - `(call/cc (lambda (k) do some stuff))`
        - Creates a continuation `k` pointing here, then calls the function that is `call/cc`’s argument and passes `k` to it
        - Lets that function execute
        - Returns whatever the function returns

    - To use a continuation `k`, you call it (it acts like a procedure with 1 argument)

      - `(k 103)`

        - We know `k = (ip, ep)`
        - The interpreter sets its environment pointer to `ep`
        - The interpreter puts into “return value register” the value of the argument passed to the continuation
        - The interpreter sets its instruction pointer to `ip`
          - This is like a `goto`/jump instruction
          - Extends `goto` by forcing the other 2 events to happen

      - `(call/cc (lambda (k) (k 103)))`

        - Returns `103` after using continuation

      - Multiply all the integers in a list

        - 0 is quite possible, even probable

        - Nonzero elements are likely to be quite large

        - We want to avoid multiplying if there’s a 0 in there anywhere

        - ```scheme
          (define (prod ls)
          	(call/cc (lambda (break) ;; Set up a place to continue from upon finding a 0
          		(let pr ((ls ls))
          			(cond
          				((null? ls) 1)
          				((zero? (car ls)) ((break 0))
          				(else (* (car ls) (pr (cdr ls))))))
          ```

          - This approach performs no multiplication if a 0 is in the list, avoids unnecessary multiplication

  - Performance problems?

    - Overhead of creating/using continuation (very small)
    - Generally not tail recursive, uses up stack space

  - You can do this sort of thing C++/Java by using exceptions, based on a simpler mechanism in C: `setjmp`

    - ```c
      #include <setjmp.h>
      jmp_buf lab; // Label of where to go if something bad happens
      	         // Must be an array type; details depend on implementation
      	         // Think of it as an array of machine register contents
      int f (void) {
      	// Other code
      	if (setjmp(lab)) // Stores ip, ep, etc. into lab, returns 0
      		// Code to be executed if something bad happens
      	} else {
      		// Code to be executed after normal setup
      		g(x);
      	}
      }
      int g (int y) {
      	h (y + 1);
      }
      void h (int z) {
      	// Other code
      	if (bad
      		longjmp(lab, 1); // Restore the ip/ep from lab, cause setjmp 
      				  		       // to return 1
      	// Other code
      }
      ```

  - Here’s something continuations can do, that exception handling/`setjmp` can’t

    - Implement “green threads” - multithreading on a single CPU (no true parallelism - only one thread can run at a given time) with continuations

      - Popular outside of the Scheme world for IoT/embedded apps

      - ```scheme
        ;; List of threads that want to run
        ;; Each thread is a thunk - a parameterless procedure that you
        ;; want to execute, presumably for its side-effects
        ;; This is imperative programming, not functional
        (define thlist ‘())
        ;; Create a thread and add it to our list of threads to run
        (define (newth th)
        	(set! thlist (append thlist (list th))))
        ;; Start the first thread in the list that wants to run=
        (define (start)
        	(let ((th (car thlist)))
        		(set! thlist (cdr thlist))
        		(th)))
        ;; This one is called within threads; a thread calls it if it wants to let
        ;; some other thread run for a while, eventually this thread will get
        ;; control back
        (define (pause)
        	(call/cc
        		(lambda (k)
        			(newth k)
        			(start))))
        ;; Set up a set of cooperating threads that take turns outputting
        ;; something
        ;; Loop forever (outputting h’s, then pause)
        (newth (lambda () (let loop () (display “h”) (pause) (loop))))
        (newth (lambda () (let loop () (display “i”) (pause) (loop))))
        (newth (lambda () (let loop () (newline) (pause) (loop))))
        (start)
        ```

    - Can we do this with `setjmp` or with exceptions? No

      - The loop functions are tail-recursive, so they’re reusing stack frames
      - We can use continuations to resume function that have been suspended
      - We can use continuations to jump into functions (like `pause`) that have already returned
      - With `setjmp`/`longjmp`, the rule is that you can `longjmp` only into a function that hasn’t returned yet; if you violate this rule, behavior is undefined (like a bad pointer)
      - Since you can jump into functions that have already returned, and they can do fancier stuff than pause, including using local variables, etc., the Scheme interpreter must keep their frames around; it can’t reclaim their storage even when the function returns
        - Scheme frames (activation records) are (in general) not on the stack - they’re on the heap
        - Scheme keeps a frame around so long as anything points to it
          - You point at a frame by having a continuation to it
      - Our data structure representing the future of our program is a set of continuations
        - One currently being executed by the Scheme interpreter
          - The others are local variables or within lists of other objects
          - The Scheme interpreter can alter this set of continuations to control what it does
          - So stack frames are no longer on the stack; they’re part of a bigger data structure managed by the garbage collector

  - We don’t need `call/cc` to do continuations, in what is called the continuation passing style or CPS

    - We do this by adding an extra argument to every function, by convention

      - This is what C++ does to support OOP: every method has a `self` argument that points to the object the method is executed on behalf of

      - By convention, to return a value, you call this continuation function with that value as an argument, and then return whatever it returns (this is a tail call)

      - ```scheme
        ;; Rewrite prod to use CPS
        (define prod ls break)
        	(let pr ((ls (k break))
        		(cond
        			((null? ls (k 1))
        			((zero? (car ls)) (break 0)
        			(else (pr (cdr ls) (lambda (r) (k (* r (car 
        			 ls))))))))
        ```

    - In some sense, you don’t need `call/cc` if you don’t want to

      - We have `call/cc` for 2 reasons:
        - Efficiency
        - Clarity

  - Do continuations subsume threads?

    - Can you do multi-CPU threading with continuations?
      - No - they’re a single CPU concept
      - Can be combined with true parallelism
    - Continuations do let you implement:
      - Exception handling (try-catch)
      - Coroutines (yield in Python)
      - It’s possible to think of true multithreading as parallelizing green threads, in the same sense of parallelizing matrix multiplication in traditional C/C++ programs

- Storage management/memory management

  - We need to organize main (addressable) memory to represent our computation to contain:

    - Static variables
      - Variables we declared or library variables
    - Machine code
      - Code we wrote or library code
    - While executing a function (typically put into the frame for that function):
      - Its local variables
      - Temporaries
      - Return address (`ip` of the caller)
      - Pointer to the caller’s frame (`ep` of the caller)
      - Typically in a stack: LIFO
        - Not necessarily true in some languages
    - Other stuff (often the biggest):
      - I/O buffers
      - Objects allocated by `malloc`/`new`
      - List data structures
      - Not LIFO: you deallocate objects in randomish order
      - Put into the heap

  - Storage management for frames

    - Possible to do frames statically (pretty much obsolete)

      - Original Fortran did this for efficiency on long-ago machines
      - You never run out of memory in the middle of your program
      - You typically allocate too much space
      - You can’t do recursion

    - Fixed stack-dynamic allocation

      - Every frame has a size known at compile time
      - When you see a function and all of its local variables, you can figure out how much space it needs at compile time
      - When you enter the function, it’s cheap to reserve space
        - `subq $1028, %rsp`
      - To exit a function, the process can just be reversed
        - `addq $1028, %rsp`
      - You need to know statically how big to make your internal arrays

    - Stack-dynamic allocation

      - Calculate at runtime how much space to allocate for functions
      - Code gets a little slower
      - Unsafe - potential to run out of stack space or mess up the stack pointer

    - Nested functions (functions defined inside other functions)

      - ```java
        inf f(int n) {
        	int g (int m { return m + n; }
        	return g(3);
        }
        ```

        - Code for `g` needs to access `m`’s value (easy: look at calling conventions: either in a register, or near top of stack)
        - How can `g` access `n`’s value? `n` is not a local variable
          - It’s living in ` f`’s frame, but `g` only knows where it’s own frame is
          - `f` needs a way to tell `g` where `f`’s local variables are (where `f`’s frame is)
            - Done via the static chain, an extra argument to each function that specifies where that function’s definer’s frame is
              - Definer - the function that statically encloses the function (`f` is `g`’s definer)
              - Short - always equal to the nesting level of the source code
        - To get this to work, we implement each function as a pair of pointers: the first pointer (`ip`) points to its code, the second pointer (`ep`) points to the definer’s frame
          - Functions are fat pointers → necessary for nested functions
            - Dynamic and static chain

  - Heap management

    - The heap can contain activation records (Scheme, OCaml)
    - The heap can contain objects allocated by the program
    - Managing heap storage can be a pain

## **Lecture 16: Storage Management**

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

              - ```c
                p = malloc(100);
                free(p);
                p->next = NULL; // ERROR
                free(p); // ERROR
                ```

            - Fewer dumb errors that can bloat your program

              - ```c
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

      - ```c++
        struct free {
          void *freeblock;
          size_t blocksize;
          struct free *next;
        };
        struct free *freelist
        ```

      - Create a linked list to represent the free areas
        - Here's how to allocate:

          - ```c++
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

          - ```c++
            void free(void *p) {
                struct free *f = p;
                p->m // Other code
            }
            ```

        - Problem: where do we store the free list? In a separate heap somewhere?
          - No, there's a better place to store the free list
          - Store the free list objects into the free areas themselves:

            - ```c++
              struct free {
                  size_t blocksize;
                  struct free *next;
              };
              struct free *freelist
              ```

            - ```c++
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

            - ```c++
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

        - ```c
          void free(void *p) {
              size_t sp = p;
              size_t object_size = sp[-1];
              size_t previous_object_size = sp[-2];
              // Other code
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

      - ```python
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
    
      - ```python
        p = { "a": 1, "b": 2 } # Reference count of the dict is 1
        p["c"] = p # Reference count of the dict is 2
        p = "def" # Reference count of the dict is 1, not 0 --> dict not freed
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
  
  - ```c
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

## **Lecture 17: Parameter Passing**

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

  - ```c
    static lock_t lock;
    static char *hp, *lp // Global variables, subject to races
        
    void *malloc(size_t n) {
        lock(&lock) // Terrible performance, critical section is a bottleneck
      	if (n <= lp - hp) {
            void *r = hp;
            hp += n;
            unlock(&lock);
            return r;
      	} else expensive(); // This must unlock too
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
        - In Scheme, `(list 3 4 #f)` -> `(3 4 #f)`
          - Defined by `(define list (lambda x x))`
            - `x` is bound to a list of caller arguments
        - In C, `#include <stdarg.h>`
          - Lower-level languages have a harder time with this
        - In Python, `def make_tuple(*x)`
          - Arguments passed as a tuple
      - Keyword correspondence

        - ```python
          def arctan(y, x):
          	# Other code
          return arctan(x=27, y=15)
          ```

- ```python
  def foo(a, *b, **c): # Positional correspondence for a, varargs go into b, keyword args go into c (a dict)
  	# Other code
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

        - ```c++
          int f (int &a, int &b) {
              a = 1;
              b = 2;
              return a + b;     
          }

          int m;
          int n = f(m, m); // Value overwritten, common optimizations not possible
          ```

          - Hurts human readers (misunderstanding code or spend a lot of time reading it)
          - Because of these aliasing problems, there are alternatives that have less aliasing
    - Call by result (Ada)
      - Caller doesn't evaluate its argument; just says where it is
      - Callee must initialize the corresponding parameter
      - When the callee returns, it copies the parameter's value back to the caller
      - Classic example: `read` system call of C (C does this by call by value):

        - ```c++
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
        
        - A thunk is a parameter-less procedure that, when you call it, will return the value you're interested in
      - Whenever the callee needs to know the value of a parameter, it calls the thunk
- This avoids unnecessary work if the callee doesn't use the parameter
      
    - ```c
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

## **Lecture 18: OOP, Exceptions, and Cost Models**

- Parameter passing

  - Call by ___
  - Other calling conventions
    - Prolog's call by unification
      - Caller and callee can both instantiate variables
        - Caller: `p(X, a)`
        - Callee: `p(b, Y) :- ...`
          - Binds both `X` in caller and `Y` in callee
    - Macro calls (done at compile-time)
      - Binding names to expressions (or other parts of your program)
      - Scheme, C, C++, etc.
      - Can go to far - controversial
      - Templates and generics replace a lot of the need for them

- Object-oriented languages

  - C++, Java, etc.

  - OOP is not the same as programming in an object-oriented language

    - You can write an object-oriented program in C

      - Ex) Linux kernel (in C) uses an object-oriented style for file systems

        - ```c
          struct s {
            int i, j; // Instance variables
            int (*open) (struct s*, int, char); // Method
            int (*close) (void); // Method
          }
          ```

    - You can write a non-object-oriented program in OCaml

      - Ex) Homework 1

    - Object-oriented languages fimplify the job of using an object-oriented style

  - There's no single style of object-oriented langauges (or OOP)

    - i.e. there isn't a complete consense on the definition of object-oriented

      - Ex) static checking vs. dynamic checking

    - Class-based (Java, OCaml, etc.) vs. prototype-based languages (Self, JavaScript, etc.)

      - Classes: 
        - Bundle together fields and methods
        - Namespace control
        - Instantiable (you can call a constructor)
        - Inheritable (you can have subclasses)
        - Classes are types
      - Prototypes (typically use dynamic checking):
        - No classes per se
        - A "prototype" is an object that has been initialized to be the way you like
          - You've given it instance variables and methods
        - If you want more objects like the prototype `p`, use `p.clone()`
          - Like calling a constructor, but isn't a constructor
      - Class-based approach more common due to:
        - Inertia: class-based approach started first
        - Performance: dynamic checking of prototype-based languages slow you down
        - Reliability: static checking guarantees freedom from certain bug classes

    - Single (Java, etc.) vs. multiple (C++, Python, etc.) inheritance

    - Can a subclass omit a parent method?

      - Ordinarily, no
      - But even in Java, a subclass can override with a method that always fails at runtime; wouldn't it be better to say this at compile-time
        - Argument for allowing this behavior

    - What can a class inherit?

      - Instance variables
      - Methods
      - Invariants (Eiffel) - a logical constraint on what a method can do

    - Delegation

      - Can a class delegate the implementation of a method to some other method of some other object

      - ```c++
        class C { // Delegation by hand
          D o;
          int m(int i) {
            return o.m(i);
            // Other code
          }
        }
        ```

  - Object-oriented programming - automate common programming patterns

    - Inheritance is a common pattern, there are others

- Exception handling - ways to address faults in your programs

  - Terminology:

    - Error - problem in the programmer's head
    - Fault - latent bug in the program (read the source code to find it)
    - Failure - program behavior is busted, and this is visible to the user

  - Focus on faults and failures here

    - Some techniques:

      - Static checking - checking at compile-time

        - Most reliable, program cannot have the failures you're worried about

        - E.g., OCaml's `option` types

          - `list option` is either `None` or `Some of list`
          - You must use a match expression to look inside a `list option` and get at the underlying list
          - This is checked at compile time

        - Vs. Java's `null` references

          - ```java
            List l = null;
            l.get(); // Runtime error
            ```

        - Not as flexible - when in doubt, static checkers will complain, can give false alarms

          - ```java
            List l = null;
            if (l != null)
            	l.get(); // No runtime error
            ```

        - Sometimes impractical

          - Often hard to prove subscript checking

      - Preconditions

        - Associated with each method or function is a logical expression (side-effect free, may be complex) that it's the caller's responsibility to make true, and the callee can assume hold

          - ```c
            double sqrt(double x) precondition(0 <= x);
            
            int close(int fd) precondition(isopen(fd));
            ```

        - How to enforce preconditions?

          - Simple model: when debugging, compiler generates code checking that each precondition holds
            - In production: this code is not generated
          - More complicated: check it statically, put in runtime checks only if static checking cannot determine

      - Total definition - everything normally considered to be a failure is instead turned into a non-failure, by defining the  behavior in this case

        - C/C++: using a variable that's not initialized is a failure
        - Java: every variable is initialized to 0-ish
          - Eliminated a class of failure
          - A bit less efficiency
          - Can mask programming errors
        - C/C++ have total definitions for `sqrt(x)` - you get a `NaN` 
          - Relies on the special values of IEEE floating point

      - Fatal handling of failures

        - A failure causes your program to reliably crash
        - C/C++: `abort();`

      - Exception handling

        - ```java
          try {
          	// Do stuff that might cause failures
          } catch (IOException e) {
            // Deal with IOException failures
          } finally {
            // This code is always executed, no matter how we exited
          }
          ```

        - How is this implemented?

          - When an exception is hit, you walk through the dynamic chain, looking for an appopriate `catch` clause
            - Along the way, you pop stack frames and execute  any `finally` blocks

        - Argument for exception handling

          - Write ordinary code in the `try` section and exceptional code in the `catch` case
            - Makes it easy to see the common case

        - Argument against exception handling

          - Human reader has to constantly be aware of control flow

          - Stops certain optimizations by the compiler

          - Java lets you reason about exception handling code by using checked exceptions

            - ```java
              Object
              	Throwable
              		Exception
              		Error
              ```

              - `Throwable` is simple: all it has is a string for debugging and another associated `Throwable`, representing the cause of the exception
              - `Error` is used for serious problems that typically aren't recoverable
                - Out of memory
              - `Exception` is for recoverable conditions
                - `EOF` on input

            - With checked exceptions, each method that can throw any kind of exception must state in its API, that it can throw that exception type

              - ```java
                int m(int) throws IOException
                ```

                - This puts the caller on notice, and the Java compiler checks your code
                - If your method uses `throw new IOException ()` or call some other method whose API says `throws IOException`, this must be part of the API unless the method itself catches `IOException`
                - This let `javac` check that every `Exception` is caught by somebody

              - This checking is not done for `Error`s

- Cost models

  - Mental model of the resources required to develop or execute a program

    - Distinguish between `O(...)` and absolute cost
      - `O(N^2)` algorithm will be worse than `O(N log N)` algorithm no matter what language you use
      - Absolute costs are still a significant deal
    - Important for choosing a language
    - Important for writing your code, assuming a particular language
    - What costs?
      - Time (wall-clock time vs. CPU time, latency vs. throughput)
      - Space (RAM, cache, flash/disk, etc.)
      - Power or energy (IoT/server farms)
      - Communications overhead (DNS accesses)
      - Etc.

  - To develop a cost model, draw pictures

    - e.g., Lisp lists vs. Python lists

    - Python-> Scheme is bad performance - they don't have compatible cost models

    - Prolog unification

      - `O(min(|X|, |Y|))`
      - `unify_with_occurs_check`: `O(max(|X|, |Y|))`

    - Low-level cost models

      - C/C++ have a `register` keyword

        - ```c
          int abs(int n) {
            register int r = n; // Advises the compiler to store r in a machine register
            return r < 0 ? -r : r;
          }
          ```

          - This is put in in the 1970s to help the compiler optimize better
          - Nowadays, many compilers either ignore `register` or pay not that much attention to it, because they know better

      - C/C++ have an `inline` keyword

        - ```c
          inline int abs(int n) { return n < 0 ? -n : n }
          
          int f(int x) {
          	printf("%d\n", abs(n))
          }
          ```

          - Compiles as if the subroutine were inside the function already
          - Optimizes the callee's code in the context of the caller
          - Omits the `call` and `ret` instructions
          - Modern compilers automatically do this - `inline` sort of obsolete

  - Our cost models are changing with time

## **Lecture 19: Semantics and History**

- 























