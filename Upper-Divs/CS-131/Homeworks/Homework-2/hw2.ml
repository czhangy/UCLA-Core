(* Parse tree definition *)
type ('nonterminal, 'terminal) parse_tree =
  | Node of 'nonterminal * ('nonterminal, 'terminal) parse_tree list
  | Leaf of 'terminal

(* Symbol definition *)
type ('nonterminal, 'terminal) symbol = 
  | N of 'nonterminal 
  | T of 'terminal

(* Convert grammar *)
let convert_grammar gram1 = 
  let get_list gram1 nt = 
    let rec build_assoc l = 
      match l with
      | [] -> []
      | head::tail -> (snd head)::build_assoc tail
    and rhs = List.filter (fun p -> fst p = nt) (snd gram1)
    in
      build_assoc rhs
  in
  (fst gram1), get_list gram1;;

(* Parse tree leaves *)
let rec parse_tree_leaves tree = 
    let rec get_nodes l =
      match l with
      | [] -> []
      | head::tail -> parse_tree_leaves head @ get_nodes tail
    in
    match tree with
    | Node (_, head::tail) -> (parse_tree_leaves head) @ (get_nodes tail)
    | Leaf x -> [x]
    | _ -> [];;

(* Make matcher *)
let make_matcher gram = 
  (* Match nonterminals *)
  let rec match_nonterminals rhss rule_map accept frag =
    (* Process each RHS *)
    let rec process_rhs rhs rule_map accept frag =
      (* Lowest level, match a terminal *)
      let match_terminals t accept frag =
        match frag with
        | [] -> None
        | prefix::suffix -> if prefix = t then accept suffix
                            else None
      in
      match rhs with
      | [] -> accept frag
      | cur_node::other_nodes -> 
          match cur_node with
          | T x -> match_terminals x (process_rhs other_nodes rule_map accept) frag
          | N x -> match frag with
                  | [] -> if rhs = [] then accept []
                          else None
                  | l -> match_nonterminals (rule_map x) rule_map (process_rhs other_nodes rule_map accept) l
    in
    match rhss with
    | [] -> None
    | cur_rhs::other_rhss -> match (process_rhs cur_rhs rule_map accept frag) with
                             | None -> match_nonterminals other_rhss rule_map accept frag
                             | Some x -> Some x
  in
  fun accept frag -> match_nonterminals ((snd gram) (fst gram)) (snd gram) accept frag;;

(* Path -> parse tree *)
let rec build_tree path =
  let rec build_level current path =
    match current with
    | [] -> path, []
    | head::tail -> match head with
                    | T x -> (match build_level tail path with
                              | (remainder, level_node) -> remainder, (Leaf x)::level_node)
                    | N x -> match build_tree path with
                              | (level, cur_node) -> match build_level tail level with
                                                     | (remainder, child_nodes) -> remainder, cur_node::child_nodes
  in
  match build_level (snd (List.hd path)) (List.tl path) with
   | (remainder, level_nodes) -> remainder, Node((fst (List.hd path)), level_nodes);;

(* Make parser *)
let make_parser gram frag =
  (* Get path, tuples of LHS and RHS that build the parse tree *)
  let generate_path gram = 
    (* Parse nonterminals *)
    let rec parse_nonterminals lhs rhss rule_map accept path frag =
      (* Parse individual RHSs *)
      let rec parse_rhs rhs rule_map accept path frag =
        (* Parse terminals *)
        let parse_terminals t accept frag =
          match frag with
          | [] -> None
          | prefix::suffix -> if prefix = t then accept suffix
                              else None
        in
        match rhs with
        | [] -> accept path frag
        | cur_node::other_nodes -> 
            match cur_node with
            | T x -> parse_terminals x (parse_rhs other_nodes rule_map accept path) frag
            | N x -> match frag with
                    | [] -> if rhs = [] then (accept path [])
                            else None
                    | l -> parse_nonterminals x (rule_map x) rule_map (parse_rhs other_nodes rule_map accept) path l
      in
      match rhss with
      | [] -> None
      | cur_rhs::other_rhss -> match (parse_rhs cur_rhs rule_map accept ((lhs, cur_rhs)::path) frag) with
                                | None -> parse_nonterminals lhs other_rhss rule_map accept path frag
                                | Some x -> Some x
    (* Enforce complete matching only *)
    and accept_empty_suffix path = function
        | [] -> Some path
        | _ -> None
    in
    fun frag -> parse_nonterminals (fst gram) ((snd gram) (fst gram)) (snd gram) accept_empty_suffix [] frag
  in
  match generate_path gram frag with
  | Some path -> Some (snd (build_tree (List.rev path)))
  | None -> None;;