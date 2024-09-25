type expr =
  | False
  | True
  | Var of string
  | Or of expr * expr
  | And of expr * expr

let rec nb_nodes = fun e ->
  match e with
  | False -> 1
  | True -> 1
  | Var _ -> 1
  | Or (e1, e2) -> 1 + nb_nodes e1 + nb_nodes e2
  | And (e1, e2) -> 1 + nb_nodes e1 + nb_nodes e2

let rec depth = fun e -> 
    match e with 
    | False -> 0
    | True -> 0
    | Var _ -> 0
    | Or (e1, e2) -> 1 + max (depth e1) (depth e2)
    | And (e1, e2) -> 1 + max (depth e1) (depth e2)

let rec nb_var = fun e ->
    match e with
    | False -> 0
    | True -> 0
    | Var _ -> 1
    | Or (e1, e2) -> nb_var(e1) + nb_var(e2)
    | And (e1, e2) -> nb_var(e1) + nb_var(e2)

let rec eval = fun e env ->
    match e with
    | False -> false
    | True -> true
    | Var x -> (try List.assoc x env with Not_found -> failwith ("Variable " ^ x ^ " not found"))
    | Or (e1, e2) -> eval e1 env || eval e2 env
    | And (e1, e2) -> eval e1 env && eval e2 env




let () =
    let expr1 = Or (And (Var "x", Var "y"), Or (Var "z", False)) in
    Printf.printf "nb_nodes(expr1) = %d\n" (nb_nodes expr1);
    Printf.printf "depth(expr1) = %d\n" (depth expr1);
    Printf.printf "nb_var(expr1) = %d\n" (nb_var expr1);
    Printf.printf "eval(expr1, {x=true, y=false, z=true}) = %b\n" (eval expr1 [("x", true); ("y", false); ("z", true)]);
    Printf.printf "eval(expr1, {x=true, y=false, z=false}) = %b\n" (eval expr1 [("x", true); ("y", false); ("z", false)]);
    