## CS 131 Final



## Question 1 (12 points)

Consider the following part of the grammar for C, which was discussed in class:



```
STMT -> LSTMT
STMT -> if (EXPR) STMT

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



In class I mentioned that we could remove the ')' token from the `LSMT -> do STMT while ( EXPR ) ;` rule wihtout making the resulting C-like language ambiguous. What other tokens could we remove from these grammar rules without introducing ambiguity to the resulting C-like language? Remove as many tokens as you can, and briefly justify why the remaining tokens cannot be removed. Assume no changes to the grammar rules for `EXPR`, `EXPROPT`, and `STMTS` (these rules are not listed above).



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



## Question 3 (8 points)

Simplify `sortie/1` and `allge/2` as best you can, by using only the following simplification methods:



- Replace a term with `_`.
- Remove a clause.
- Remove a subgoal from a clause



Your simplified `sortie/1` should be logically equivalent to the original `sortie/1`. Your simplified `allge/2` can behave any way you like. For each simplification you use, briefly explain why it doesn't change the logic of `sortie/1`.



## Question 4 (3 points)

Russell's paradox centers on the set of all sets that are not members of themselves. Suppose we attempt to investigate the paradox in GNU Prolog, by asking the question "Is there a list `L` that is a member of itself?"



Construct a Prolog query that is a natural translation of this English-language question. Your query should invoke at least one predicate that is builtin to GNU Prolog



## Question 5 (12 points)

Try the query out in GNU Prolog, and explain the resulting misbehavior.



## Question 6 (10 points)

Can you fix the misbehavior by defining and using your own predicate instead of the standard one? If so, show how; if not, briefly explain why not.



## Question 7 (8 points)

If `!` makes Prolog code run faster and helps it avoid infinite or near-infinite loops, why not use `!` all the time? Briefly explain by giving an example where `!` breaks things.



## Question 8 (10 points)

Define a Scheme function `c2` such that `(c2 f)` returns a curried version of the two-argument function `f`. For example, `(((c2 cons) 'a) 'b)` should return the pair `(a . b)` just as `(cons 'a 'b)` does.



## Question 9 (10 points)

Assuming you've defined `c2`, what does `(c2 apply)` return? Illustrate with an example of using the returned value. Hint: `apply` is a builtin function that applies a function to a list of arguments; for example, `(apply + '(3 2 9))` is equivalent to `(+ 3 2 9)` and returns `14`



## Question 10 (12 points)

```scheme
(define (g x)
  (let f ((y x))
    f))
```



Show what the function `g` does, by giving example calls to `g` and explaining the returned value. Is `g` curried? Briefly explain.



## Question 11 (12 points)

Translate the definition of `g` to OCaml as best you can, or, if such a translation is impossible, explain why not.



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



## Question 14 (10 points)

Give a Java code example of synchronization that uses only `volatile` (not `synchronized` or any atomic data type). In your example, show how `volatile` prevents a race condition that could occur if some or all of the `volatile` keywords in your example were removed.



## Question 15 (12 points)

The formal definition of the Java Memory Model contains this statement in section 17.4.4 "Synchronization Order":



"The final action in a thread `T1` synchronizes-with any action in another thread `T2` that detects that `T1` has terminated. `T2` may accomplish this by calling `T1.isAlive()` or `T1.join()`."



Suppose we relax the Java Memory Model by removing this statement. Show that this removal would cause a race condition to occur in the Java skeleton code for Homework 3, provided by the file [`jmm.jar`](https://web.cs.ucla.edu/classes/winter21/cs131/hw/jmm.jar), and explain the effects this race condition would have on the skeleton code's behavior.



## Question 16 (10 points)

Explain why copying garbage collectors typically can make more effective use of hardware caches than conservative garbage collectors can.



## Question 17 (18 points)

The basic idea of the Python `asyncio` library can be used in other programming languages as well. Evaluate the following three languages as potential candidates for supporting applications that are built much like these apps are build in Python with `asyncio`:



- Java
- OCaml
- D, Odin, Zig (whichever of these languages you studied for Homework 6)



For example, you might indicate which parts of the `asyncio` idea would work well, which parts would cause problems, and why.

