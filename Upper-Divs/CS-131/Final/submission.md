## CS 131 Final



## Question 1 (12 points)

Consider the following part of the grammar for C, which was discussed in class:



```
STMT -> LSTMT
STMT -> if ( EXPR ) STMT

LSTMT -> ;
LSTMT -> EXPR ;
LSTMT -> return ;
LSTMT -> return EXPR ;
LSTMT -> break ;
LSTMT -> continue ;
LSTMT -> while ( EXPR ) STMT
LSTMT -> do STMT while ( EXPR );
LSTMT -> if ( EXPR ) LSTMT else STMT
LSTMT -> for ( EXPROPT ; EXPROPT ; EXPROPT ) STMT
LSTMT -> switch ( EXPR ) STMT
LSTMT -> { STMTS }
```



In class I mentioned that we could remove the ')' token from the `LSMT -> do STMT while ( EXPR ) ;` rule without making the resulting C-like language ambiguous. What other tokens could we remove from these grammar rules without introducing ambiguity to the resulting C-like language? Remove as many tokens as you can, and briefly justify why the remaining tokens cannot be removed. Assume no changes to the grammar rules for `EXPR`, `EXPROPT`, and `STMTS` (these rules are not listed above).



------



### Answer

```
STMT -> LSTMT
STMT -> if EXPR ) STMT (*)

LSTMT -> ;
LSTMT -> EXPR ;
LSTMT -> return ;
LSTMT -> return EXPR ;
LSTMT -> break (*)
LSTMT -> continue (*)
LSTMT -> while EXPR ) STMT (*)
LSTMT -> do STMT while EXPR ; (*)
LSTMT -> if EXPR ) LSTMT else STMT (*)
LSTMT -> for EXPROPT ; EXPROPT ; EXPROPT ) STMT (*)
LSTMT -> switch EXPR ) STMT (*)
LSTMT -> { STMTS }

The '(' character can be removed from the expressions 'STMT -> if (EXPR) STMT',
'LSTMT -> while ( EXPR ) STMT', LSTMT -> do STMT while ( EXPR );',
'LSTMT -> if ( EXPR ) LSTMT else STMT', and 'LSTMT -> switch ( EXPR ) STMT'.
This is because the keyword in front of each of these statements is enough to
make the statement unambiguous; the open parentheses is unnecessary.

In addition, either the 'for' or the '(' may be removed from the rule
'LSTMT -> for ( EXPROPT ; EXPROPT ; EXPROPT ) STMT', but not both. Only one of
these is necessary for the statement to be unambiguous. If both were removed,
then the structure would be ambiguous, as it could possibly represent 3
consecutive EXPRs. In the above grammar, '(' was removed, keeping the 'for'
token intact.

The semicolons following "break" and "continue" can be removed, as both of these 
tokens are unique and don't need the semicolon to denote the end of their
respective rules. All other semicolons must be preserved, otherwise structures
like "return ; EXPR ;" may become ambiguous, as there would be no token
describing where a rule ends.

Keywords such as "return", "break", "continue", "while", "else", and "switch"
are required to remain in their respective rules in order to identify the type
of statement being represented, as they all become ambiguous without them.

The keyword "do" must remain in the rule since "STMT while ( EXPR )" is
ambiguous otherwise.

The curly braces in the final rule must remain there in order to prevent the if-
statement from becoming ambiguous in terms of what expressions fall within the
"if" block and which don't.
```



## Question 2 (6 points)

In lecture, we discussed the following Prolog predicate:



```prolog
sorted([]).
sorted([_]).
sorted([X, Y|Z]) :- X =< Y, sorted([Y|Z]).
```



Consider the following Prolog predicate `sortie/1`, which is similar:



```prolog
sortie([]).
sortie([X]).
sortie([X|L]) :- allge(L, X).
allge([], Y).
allge([X], Y) :- X >= Y.
allge([X|L], Y) :- X >= Y, allge(L, X).
```



Are `sorted/1` and `sortie/1` logically equivalent? If so, briefly explain why; if not, give a counterexample.



------



### Answer

```
sorted/1 and sortie/1 are logically equivalent. sorted/1 simply compares the
first 2 elements of the list to check if the first is less than or equal to the
second, before moving on to the tail. sortie/1 takes a more inefficient route by 
calling on the predicate allge/2, which checks if each element in the list is
greater than or equal to the head before moving on. Despite the inefficiency,
these predicates are still logically equivalent, as any list that would cause
sorted/1 to succeed would cause sortie/1 to succeed, and vice versa. Both check
that the head of a list is less than or equal to all elements in the tail of the
list; sorted/1 does so implicitly while sorted/2 does so explicitly.
```



## Question 3 (8 points)

Simplify `sortie/1` and `allge/2` as best you can, by using only the following simplification methods:



- Replace a term with `_`.
- Remove a clause.
- Remove a subgoal from a clause



Your simplified `sortie/1` should be logically equivalent to the original `sortie/1`. Your simplified `allge/2` can behave any way you like. For each simplification you use, briefly explain why it doesn't change the logic of `sortie/1`.



------



### Answer

```prolog
sortie([]).
sortie([_]).
sortie([X|L]) :- allge(L, X).
allge([], Y).
allge([X|L], Y) :- X >= Y, allge(L, X).
```

```
The X in sortie([X]) can be replaced by _ because X is used to identify the
singleton list, but isn't used in the body of the clause, therefore it's better
to use _, which still identifies the singleton list, but doesn't cause any
unnecessary unification.

The clause allge([X], Y) :- X >= Y. can be removed, as the last clause can
implicitly handle the case of the singleton list.
```



## Question 4 (3 points)

Russell's paradox centers on the set of all sets that are not members of themselves. Suppose we attempt to investigate the paradox in GNU Prolog, by asking the question "Is there a list `L` that is a member of itself?"



Construct a Prolog query that is a natural translation of this English-language question. Your query should invoke at least one predicate that is builtin to GNU Prolog



------



### Answer

```prolog
f(L) :- member(L, L).
```



## Question 5 (12 points)

Try the query out in GNU Prolog, and explain the resulting misbehavior.



------



### Answer

```
If the predicate f(L) is used as a query, the error "cannot display cyclic term
for L ?" appears. This is because Prolog is attempting to unify L with a list
that contains L, which means it needs to unify L with a list that contains
itself. Therefore, L will be continuously unified with a list that contains a
list, that contains a list, etc., resulting in an infinite-loop/cyclic
definition which prompts this error from Prolog.
```



## Question 6 (10 points)

Can you fix the misbehavior by defining and using your own predicate instead of the standard one? If so, show how; if not, briefly explain why not.



------



### Answer

```
There doesn't seem to be any fix to the misbehavior in terms of actually finding
any lists that are members of themselves. The cyclic behavior error that occurs
when using Prolog's builtin predicate can be avoided by using the
unify_with_occurs_check predicate, however, this will simply lead to the
predicate f/1 succeeding, outputting true.
```

```prolog
my_mem(X, L) :- unify_with_occurs_check(X, L).
my_mem(X, [X|_]).
my_mem(X, [_|T]) :- my_mem(X, T).

f(L) :- my_mem(L, L).
```



## Question 7 (8 points)

If `!` makes Prolog code run faster and helps it avoid infinite or near-infinite loops, why not use `!` all the time? Briefly explain by giving an example where `!` breaks things.



------



### Answer

```
The cut predicate has 2 potential uses discussed in class: green cuts and red
cuts. Green cuts are cuts that are used for the sole purpose of making a program
more efficient, and should be used whenever possible. On the other hand, red
cuts may affect a program's performance, which is why ! is not used as often as
possible. For instance, take the following predicate:
```

```prolog
p :- should_succeed.

should_succeed :- !, fail.
should_succeed.
```

```
The query to should_succeed should succeed. However, Prolog will first look at
the rule defining should_succeed that uses a cut. This cut will get backtracked
into due to the fail, and p will be told to immediately fail. This behavior
occurs even though there is a fact that says should_succeed should succeed.
Therefore, the use of the cut has broken this program.
```



## Question 8 (10 points)

Define a Scheme function `c2` such that `(c2 f)` returns a curried version of the two-argument function `f`. For example, `(((c2 cons) 'a) 'b)` should return the pair `(a . b)` just as `(cons 'a 'b)` does.



------



### Answer

```scheme
(define (c2 f)
  (lambda (x)
    (lambda (y)
      (f x y))))
```



## Question 9 (10 points)

Assuming you've defined `c2`, what does `(c2 apply)` return? Illustrate with an example of using the returned value. Hint: `apply` is a builtin function that applies a function to a list of arguments; for example, `(apply + '(3 2 9))` is equivalent to `(+ 3 2 9)` and returns `14`.



------



### Answer

```
(c2 apply) returns a curried function that takes in 2 parameters: a function and 
a list. It will then apply the function to the list and return the expected
value.

For instance, the call (((c2 apply) +) '(3 2 1)) gets such a curried function,
takes in the + operator, then takes in the list '(3 2 1), then adds each element
in the list as apply would, then returns the final sum of 6. A call 
(((c2 apply) *) '(3 2 1)) would do the same thing, except multiplying each
element and returning the product.
```



## Question 10 (12 points)

```scheme
(define (g x)
  (let f ((y x))
    f))
```



Show what the function `g` does, by giving example calls to `g` and explaining the returned value. Is `g` curried? Briefly explain.



------



### Answer

```
g seems to take any parameter x, and return the result of calling the function y
on it. From there, it evaluates the function y with the parameter x, assigning
the result to a local variable f, which is then returned.

(g 2) will return #<procedure:f>, indicating the return value is a procedure,
which is essentially (y 2), where y is some yet-to-be-defined function.

g is not curried, as currying involves the use of single-parameter functions,
which are used to create intermediate functions that allow for more parameters
to be accepted. In the case of g, intermediate functions are created, but they
do not accept any extra parameters, instead only taking in x. g and f seem to
act more like aliases for the function y.
```



## Question 11 (12 points)

Translate the definition of `g` to OCaml as best you can, or, if such a translation is impossible, explain why not.



------



### Answer

```
This definition is not possible to translate into OCaml, as let-expressions in
OCaml must be made up of expressions that are able to be evaluated beforehand.
This is due to OCaml's nature of being a strongly-typed language, which is
strict on static type checking. Since (y x) cannot be evaluated beforehand,
assuming y doesn't yet exist in the program, this procedure cannot be replicated 
in OCaml.
```



## Question 12 (18 points)

Dybvig gives the following example of the continuation-passing style:



```scheme
(define product
  (lambda (ls k)
    (let ([break k])
      (let f ([ls ls] [k k])
        (cond
         [(null? ls) (k 1)]
         [(= (car ls) 0) (break 0)]
         [else (f (cdr ls)
                  (lambda (x)
                    (k (* (car ls) x))))])))))

(product '(1 2 3 4 5) (lambda (x) x)) => 120
```



Translate this function definition and example call into OCaml as clearly and concisely as you can, except use a curried continuation-passing style (CPS) instead of the style that Dybvig uses. In curried CPS, a function is passed a continuation as its only argument and returns another function that accepts the function's actual argument and does the real work. So, instead of the continuation being an additional argument at the end, as with Dybvig's example, it's an additional curried argument at the beginning.



------



### Answer

```ocaml
let product k =
    let rec f k ls =
        match ls with
        | [] -> k 1
        | hd::tl -> f (fun x -> k (hd * x)) tl 
    in 
    f (fun r -> r) ls;;

(product (fun x -> x)) [1; 2; 3; 4; 5];;
```



## Question 13 (9 points)

The Homework 2 hint code uses something like CPS, but it isn't curried CPS because the continuations (which are called "acceptors") are passed *after* the actual arguments, whereas curried CPS wants them passed *before*.



Rewrite the following three functions of the Homework 2 hint code so that they use curried CPS. Your rewritten versions should be as simple and elegant as you can make them.



```ocaml
let match_nucleotide nt frag accept =
    match frag with
    | [] -> None
    | n::tail -> if n == nt then accept tail else None

let append_matchers matcher1 matcher2 frag accept =
    matcher1 frag (fun frag1 -> matcher2 frag1 accept)

let make_appended_matchers make_a_matcher ls = 
	let rec mams = function
        | [] -> match_empty
        | head::tail -> append_matchers (make_a_matcher head) (mams tail)
	in mams ls
```



------



### Answer

```ocaml
let match_nucleotide accept nt = function
    | [] -> None
    | n::tail -> if n == nt then accept tail else None;;

let append_matchers accept matcher1 matcher2 =
    (accept matcher1) matcher2;;

let make_appended_matchers accept make_a_matcher ls = 
	let rec mams = function
        | [] -> match_empty
        | head::tail -> append_matchers accept (make_a_matcher head) (mams tail)
	in mams ls
```



## Question 14 (10 points)

Give a Java code example of synchronization that uses only `volatile` (not `synchronized` or any atomic data type). In your example, show how `volatile` prevents a race condition that could occur if some or all of the `volatile` keywords in your example were removed.



------



### Answer

```java
public class Example {
  private volatile int count = 0;
  
  public int getCount() {
    return count;
  }
  
  public void inc() {
    count++;
  }
}
```

```
If the volatile keyword were removed from the above class, then a race condition
could occur. Say 2 threads were executing the functions in the class above.
Without volatile, Java allows these threads to access the value of count that
they have cached for themselves for greater efficiency. As a result, they would
be able to increment and return different values of count throughout their
execution. By declaring count as volatile, we're forcing these threads to avoid
this optimization, instead reading and writing the value of count from main
memory, preventing possible race conditions that may arise from varying orders
of execution.
```



## Question 15 (12 points)

The formal definition of the Java Memory Model contains this statement in section 17.4.4 "Synchronization Order":



"The final action in a thread `T1` synchronizes with any action in another thread `T2` that detects that `T1` has terminated. `T2` may accomplish this by calling `T1.isAlive()` or `T1.join()`."



Suppose we relax the Java Memory Model by removing this statement. Show that this removal would cause a race condition to occur in the Java skeleton code for Homework 3, provided by the file [`jmm.jar`](https://web.cs.ucla.edu/classes/winter21/cs131/hw/jmm.jar), and explain the effects this race condition would have on the skeleton code's behavior.



------



### Answer

```
Without the use of the T1.join() in the dowork method, race conditions form in
the timing of execution performed by each thread. Each thread is started and
then joined to track CPU time variables, however, by ignoring the JMM, the data
collected by each thread is unaware of each other. As a result, when the main
thread accumulates the CPU time taken by each thread, it will improperly count
due to the lack of joining, resulting in a compromised CPU time.
```



## Question 16 (10 points)

Explain why copying garbage collectors typically can make more effective use of hardware caches than conservative garbage collectors can.



------



### Answer

```
Copying garbage collectors make use of a structure called the nursery. They
organize the heap such that older data, which is less likely to be deallocated
soon, is in one location, while newer data, which is more likely to be
deallocated soon is in another. Since all the data that is likely to be
deallocated is in similar locations in memory, the garbage collector can focus
on that area. This makes better use of caching, as the system knows where a high
percentage of the data it will need to access will be: in the nursery. Relevant
roots can then be cached and accessed when they need to be garbage collected,
whereas in a traditional MARK + SWEEP garbage collector, no such correlation
between likelihood of garbage collection and location on the heap exists.
```



## Question 17 (18 points)

The basic idea of the Python `asyncio` library can be used in other programming languages as well. Evaluate the following three languages as potential candidates for supporting applications that are built much like these apps are built in Python with `asyncio`:



- Java
- OCaml
- D, Odin, Zig (whichever of these languages you studied for Homework 6)



For example, you might indicate which parts of the `asyncio` idea would work well, which parts would cause problems, and why.



------



### Answer

```
The biggest difference in Java's approach to these sort of applications is its
capability to use multithreading for parallelism. Since asyncio is held down by
Python's GIL, this wasn't possible in asyncio. Immediately, this tells us that
it may be possible to scale Java applications better through the use of
parallelism. In addition, Java's builtin multithreading and JMM provides a lot
of support for synchronization, making it possible for a large number of clients 
to access a given server. Java handles asynchronous operations using FutureTask
and CompletableFuture, which each provide methods that introduce callbacks into
the code. Since these are supported by the language, this makes it very possible 
to develop similar applications in Java.

OCaml can also deal with asynchronous programming using the Async package. This
package provides much of the functionality that asyncio does, including
abstractions for callbacks and I/O interfaces. At its core, OCaml also executes
in a single-threaded manner, so, while multithreading can be used to take
advantage of the time waiting for callbacks to return, true parallelism is not
possible. The biggest difference between OCaml and Python is likely that OCaml
has strong static type checking, as opposed to Python's dynamic checking. Due to 
the increased reliability and lack of runtime checking, it's possible that the
application designed using OCaml will be more efficient as a result.

DLang also seems to provide support for concurrent programming. The asynchronous 
library implements the majority of the asyncio library from Python, resulting in
a very similar comparison. Once again, major differences seem to come down to
the languages themselves. Python's dynamic checking and single-threaded nature
may make D a more viable candidate for such an application. However, D has a
distinct lack of resources when it comes to writing asynchronous code due to its
relative lack of use. As a result, from a development standpoint, it may be
easier to decipher the complexities of concurrent programming through the
asyncio route.
```

