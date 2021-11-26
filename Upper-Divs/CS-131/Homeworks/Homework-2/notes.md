# Naïve Parsing of Context Free Grammars

## Goal

**Use OCaml to build a matcher and parser for a given grammar**

## Requirements

- Part 1: Write the function `convert_grammar <gram1>` that takes in a HW1 grammar and returns a HW2 grammar
- Part 2: Write the function `parse_tree_leaves <tree>` that takes in a parse tree and returns a list of the leaf nodes in order
- Part 3: Write the function `make_matcher <gram>` that returns a matcher for the given grammar
- Part 4: Write the function `make_parser <gram>` that returns a parser for the given grammar
- Part 5: Write a test case `make_matcher_test` for `make_matcher`
- Part 6: Write a test case `make_parser_test` for `make_parser`
  - Check that `parse_tree_leaves` is the inverse of `make_parser`
- Part 7: Write a report
  - Explain why you wrote `make_parser` in terms of `make_matcher` or vice versa
  - Explain any vulnerabilities in the solution, using test cases
  - 80 columns/line, 50-100 lines ~4000-8000B

## High-level Structure

- Create a function `make_parser` that takes in a grammar and returns a parse tree
- Create a function `make_matcher` that takes in a grammar and returns unnecessary terminals (???)
  - Parse from left to right in terms of grammar rules
  - Should be a curried function that takes in parameters of an acceptor and a fragment
    - Acceptor - uses the `Some` structure to either accept or reject a fragment
      - Accept - returns the tail of the input suffix
      - Reject - return `None`
- Create a function `convert_grammar` that takes in a grammar and converts it from HW1 format to HW2 format
  - HW1 format - List of `<Start Symbol, Symbol List>` pairs
  - HW2 format - `<Start Symbol, F: NT -> Symbol List>` pair
- Create a function `parse_tree_leaves` that takes in a tree and returns a list that lists the leaf nodes in-order
  - Breadth-first search (?)
- Function currying goes matcher -> apply matcher to acceptor -> apply matcher + acceptor to fragment

## Part 1 Notes

- Not a static function -> just need to model the function
- ~~Use `List.assoc`~~
- Return a tuple with a start symbol and function
  - ~~Function should use `List.assoc` to model pattern matching~~
- Use `List.filter` instead to handle duplicate keys
- Build final list recursively with a locally defined function
- Introduce another parameter for currying purposes
- Return a tuple of the starting symbol and the function

## Part 2 Notes

- Type: `('a, 'b) parse_tree -> 'b list = <fun>`
- In-order traversal of `<tree>` --> BFS
- `parse_tree` is a node
  - Tuple of node's value and list of its children
- Use simple pattern matching to find `Node` vs. `Leaf`
  - On nodes, concatenate recursive call of left subtree and right subtree
  - On leaves, initialize a list containing the leaf's value
- ~~Assume each node only has 2 subtrees~~
  - Fixed

## Part 3 Notes

- Type: `'a * ('a -> ('a, 'b) symbol list list) -> ('b list -> 'c option) ->'b list -> 'c option = <fun>`
- The matcher is the result of `make_matcher <gram>`
  - `matcher <accept> <frag>`
- ~~Key is gluing multiple matchers together~~
- Take a nonterminal, expand it to match possibilities, glue with rest of pattern
- ~~Use old code - append and or~~
  - Append - parts of a rule together
  - Or - handle duplicate LHSs
- `make_matcher` cannot handle terminals
  - `make_matcher` begins recursive calls, is not recursive on its own

## Part 4 Notes

- Type: `'a * ('a -> ('a, 'b) symbol list list) -> 'b list -> ('a, 'b) parse_tree option = <fun>`
- Use `make_matcher` logic
- Suffix must be empty
- Construct tree from bottom up
- Build path first, build actual tree structure next

## Relevant Links

- **[`List` Documentation](http://caml.inria.fr/pub/docs/manual-ocaml/libref/List.html)**
- **[Old Homework 2](https://web.cs.ucla.edu/classes/winter21/cs131/hw/hw2-2006-4.html)**
- **[`Stdlib` Documentation](http://caml.inria.fr/pub/docs/manual-ocaml/libref/Stdlib.html)**

