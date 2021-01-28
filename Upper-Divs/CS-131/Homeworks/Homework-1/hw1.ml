(* subset *)
let rec subset a b = 
  match a, b with
  | [], _ -> true (* base cases *)
  | _, [] -> false
  | a::at, b -> List.mem a b && subset at b;;

(* equal sets *)
let equal_sets a b =
    subset a b && subset b a;;

(* set union *)
let rec set_union a b = 
    a @ b;;

(* symmetric difference *)
let set_symdiff a b =
  let rec set_intersection a b =
    match a, b with
    | [], _ -> [] (* base case *)
    | a::at, b -> if List.mem a b then a::set_intersection at b
                  else set_intersection at b
  in
    List.filter (fun x -> not (List.mem x (set_intersection a b))) (set_union a b);;

(* It is not possible to check if a set is a member of itself in OCaml using our current structure. Our sets are of type 'a list. This means they contain
  members of type 'a. If a set were to be a member of itself, then it would need to be of type 'a list list. However, we can keep applying this logic to 
  say our set will be of type 'a list list list list... For this reason, it is impossible to implement a check to see if a set is a member of itself*)

(* computed fixed point *)
let rec computed_fixed_point eq f x =
  if eq (f x) x then x
  else computed_fixed_point eq f (f x);;

(* filter unreachable rules *)
type ('nonterminal, 'terminal) symbol = 
  | N of 'nonterminal
  | T of 'terminal;;

let rec filter_reachable g =
  let rec build_reachables r ls = (* r is the subset of rules left to search, ls is a list of nonterminals to search *)
    match r, ls with
    | [], _ -> [] (* base cases *)
    | _, [] -> []
    | a, (T b)::bt -> []
    | a, (N b)::bt -> (* b is the next nonterminal to check for*)
      let 
        rules = List.filter (fun x -> fst x = b) (a) (* get all rules reachable from b *)
        and get_symbol x = match x with | N x -> Some (N x) | _ -> None (* filter all terminals out *)
      in
        (rules @ (build_reachables (set_symdiff r rules) (bt @ (List.filter_map get_symbol (List.concat (snd (List.split rules))))))) (* get a list of all nonterminals on the RHSs *)
    in
      let reachables = build_reachables (snd g) [N(fst g)]
      in
        (fst g, List.filter (fun x -> List.mem x reachables) (snd g));;
