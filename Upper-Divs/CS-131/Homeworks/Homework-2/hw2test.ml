let accept_all string = Some string
let accept_empty_suffix = function
   | _::_ -> None
   | x -> Some x

type my_nonterminals =
  | Sentence | Noun | Verb | Person | Place | Object | Past 
  | Present | Future | Punctuation | Unreachable;;

let my_grammar =
  (Sentence, function
    | Sentence -> [[N Noun; N Verb; N Noun; N Punctuation];
                   [N Noun; N Verb; N Punctuation];
                   [N Noun; N Verb]]
    | Noun -> [[N Person];
               [N Place];
               [N Object]]
    | Verb -> [[N Past];
               [N Present];
               [N Future]]
    | Person -> [[T "Bob"];
                 [T "Joe"];
                 [T "Dan"]]
    | Place -> [[T "Los Angeles"];
                [T "Las Vegas"];
                [T "New York"]]
    | Object -> [[T "apple"];
                 [T "car"];
                 [T "table"]]
    | Past -> [[T "went to"];
               [T "ate"];
               [T "met"]]
    | Present -> [[T "is going to"];
                  [T "is eating"];
                  [T "meet"]]
    | Future -> [[T "will go to"];
                 [T "will eat"];
                 [T "will meet"]]
    | Punctuation -> [[T "."];
                      [T "!"];
                      [T "?"]]
    | Unreachable -> [[T "x"]]);;

let make_matcher_test0 = make_matcher my_grammar accept_all ["meet"] = None;;
let make_matcher_test1 = make_matcher my_grammar accept_all ["Bob"; "ate"] = Some [];;
let make_matcher_test2 = make_matcher my_grammar accept_empty_suffix ["Bob"; "ate"; "apple"; "Bob"] = None;;
let make_matcher_test3 = make_matcher my_grammar accept_all ["Bob"; "ate"; "apple"; "Bob"] = Some ["apple"; "Bob"];;
let make_matcher_test4 = make_matcher my_grammar accept_empty_suffix ["Joe"; "is going to"; "Las Vegas"; "!"] = Some [];;
let make_matcher_test5 = make_matcher my_grammar accept_empty_suffix ["Dan"; "ate"; "?"] = Some [];;
let make_matcher_test6 = make_matcher my_grammar accept_empty_suffix ["x"] = None;;
let make_matcher_test = make_matcher_test0 && make_matcher_test1 && make_matcher_test2 && make_matcher_test3 && make_matcher_test4 &&
                        make_matcher_test5 && make_matcher_test6;;

let make_parser_test0 = make_parser my_grammar ["meet"] = None;;
let make_parser_test1 = make_parser my_grammar ["Bob"; "ate"; "apple"; "Bob"] = None;;
let make_parser_test2 = make_parser my_grammar ["x"] = None;;
let make_parser_test3 = make_parser my_grammar ["Bob"; "ate"] = Some (Node (Sentence,
                                                                                [Node (Noun, 
                                                                                        [Node (Person, [Leaf "Bob"])]);
                                                                                 Node (Verb, 
                                                                                        [Node (Past, [Leaf "ate"])])]));;
let make_parser_test4 = make_parser my_grammar ["Joe"; "is going to"; "Las Vegas"; "!"] = Some (Node (Sentence,
                                                                                                [Node (Noun, 
                                                                                                        [Node (Person, [Leaf "Joe"])]);
                                                                                                 Node (Verb, 
                                                                                                        [Node (Present, [Leaf "is going to"])]);
                                                                                                 Node (Noun, 
                                                                                                        [Node (Place, [Leaf "Las Vegas"])]);
                                                                                                 Node (Punctuation, [Leaf "!"])]));;
let make_parser_test5 = make_parser my_grammar ["Dan"; "ate"; "?"] = Some (Node (Sentence,
                                                                                [Node (Noun, 
                                                                                        [Node (Person, [Leaf "Dan"])]);
                                                                                 Node (Verb, 
                                                                                        [Node (Past, [Leaf "ate"])]);
                                                                                 Node (Punctuation, [Leaf "?"])]));;
let make_parser_test6 = match make_parser my_grammar ["Dan"; "ate"; "?"] with | Some x -> parse_tree_leaves x = ["Dan"; "ate"; "?"] | _ -> false;;
let make_parser_test = make_parser_test0 && make_parser_test1 && make_parser_test2 && make_parser_test3 && make_parser_test4 &&
                       make_parser_test5 && make_parser_test6;;