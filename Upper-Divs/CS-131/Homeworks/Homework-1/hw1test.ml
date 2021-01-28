(* subset tests *)
let subset_test0 = subset [] [];;
let subset_test1 = subset [1;2;3;4] [1;2;3;4;5];;
let subset_test2 = not (subset [1;2;3;4;5] [1;2;3;4]);;
let subset_test3 = subset [1;2;3;4;5] [1;2;3;4;5];;
let subset_test4 = subset ["hello"] ["hello";"world"];;
let subset_test4 = not(subset ["hello";"world"] ["hello"]);;

(* equal sets tests *)
let equal_sets_test0 = equal_sets [] [];;
let equal_sets_test1 = equal_sets [1;2;3] [1;2;3];;
let equal_sets_test2 = equal_sets [1;1;2;2;3;3] [1;2;3];;
let equal_sets_test3 = not(equal_sets [1;2;3] [1;2;4]);;
let equal_sets_test4 = equal_sets ["hello";"hello"] ["hello"];;
let equal_sets_test5 = not(equal_sets ["hello"] ["world"]);;

(* set union tests *)
let set_union_test0 = equal_sets (set_union [1;2;3] []) [1;2;3];;
let set_union_test1 = equal_sets (set_union [1;2;3] [3;2;1]) [1;2;3];;
let set_union_test2 = not (equal_sets (set_union [1;2;3] [4;5;6]) [1;2;3]);;
let set_union_test3 = equal_sets (set_union [] []) [];;
let set_union_test2 = equal_sets (set_union ["hello"] ["world"]) ["hello";"world"];;

(* symmetric difference tests *)
let set_symdiff_test0 = equal_sets (set_symdiff [1;2;3] [1;2;3]) [];;
let set_symdiff_test1 = equal_sets (set_symdiff [1;2;3] [3;4;5]) [1;2;4;5];;
let set_symdiff_test2 = equal_sets (set_symdiff [1;2;3] []) [1;2;3];;
let set_symdiff_test2 = equal_sets (set_symdiff [] []) [];;
let set_symdiff_test2 = equal_sets (set_symdiff ["hi";"hello"] ["hello";"world"]) ["hi";"world"];;

(*compute fixed point tests *)
let computed_fixed_point_test0 = computed_fixed_point (>) (fun x -> -x) 2 = -2;;
let computed_fixed_point_test1 = computed_fixed_point (=) (fun x -> x * x) 1 = 1;;

type tennis_nonterminals =
  | Tournament | Match | Set | Game | Point

let tennis_rules =
    [Tournament, [N Match];
     Tournament, [N Set; N Set];
     Match, [N Set];
     Match, [N Tournament];
     Set, [N Game; N Game; N Game];
     Game, [N Point; N Point];
     Point, [T"15"; T"30"; T"40"; T"Love"]
    ]

let filter_reachable_test0 = filter_reachable (Tournament, tennis_rules) = (Tournament, tennis_rules);;
let filter_reachable_test1 = filter_reachable (Match, tennis_rules) = (Match, tennis_rules);;
let filter_reachable_test2 = filter_reachable (Set, tennis_rules) = 
  (Set, [Set, [N Game; N Game; N Game];
        Game, [N Point; N Point];
        Point, [T"15"; T"30"; T"40"; T"Love"]
        ]);;
let filter_reachable_test3 = filter_reachable (Point, tennis_rules) = (Point, [Point, [T"15"; T"30"; T"40"; T"Love"]]);;