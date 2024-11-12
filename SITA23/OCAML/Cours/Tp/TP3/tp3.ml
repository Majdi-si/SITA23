type expr = 
  | Num of float
  | Var of string
  | Somme of expr * expr
  | Produit of expr * expr
  | Oppose of expr
  | Inverse of expr

let trois_x = Produit(Num 3., Var "x");;
let un_plus_trois_x = Somme(Num 1., trois_x);;
let e = Produit(Inverse(Oppose(Num 2.)), un_plus_trois_x);;

let rec eval expr =
  match expr with
  | Num x -> x
  | Var x -> failwith "Contient une variable"
  | Somme (e1, e2) -> eval e1 +. eval e2
  | Produit (e1, e2) -> eval e1 *. eval e2
  | Oppose e1 -> -. eval e1
  | Inverse e1 -> 1. /. eval e1;;


let rec eval2 subst expr =
  match expr with
  | Num x -> x
  | Var x -> subst x
  | Somme (e1, e2) -> eval2 subst e1 +. eval2 subst e2
  | Produit (e1, e2) -> eval2 subst e1 *. eval2 subst e2
  | Oppose e1 -> -. eval2 subst e1
  | Inverse e1 -> 1. /. eval2 subst e1;;

let subst = fun v ->
  match v with
  | "x" -> 1.
  | _ -> failwith "subst: variable inconnue";;

let rec derive expr var =
  match expr with
  | Num _ -> Num 0.
  | Var x -> if x = var then Num 1. else Num 0.
  | Somme (e1, e2) -> Somme (derive e1 var, derive e2 var)
  | Produit (e1, e2) -> Somme (Produit (derive e1 var, e2), Produit (e1, derive e2 var))
  | Oppose e1 -> Oppose (derive e1 var)
  | Inverse e1 -> Oppose (Produit (derive e1 var, Inverse (Produit (e1, e1))))

let rec iter f expr =
  match expr with
  | Num x -> f (Num x)
  | Var x -> f (Var x)
  | Somme (e1, e2) -> f (Somme (iter f e1, iter f e2)) 
  | Produit (e1, e2) -> f (Produit (iter f e1, iter f e2))
  | Oppose e1 -> f (Oppose (iter f e1))
  | Inverse e1 -> f (Inverse (iter f e1));;



(* let eval2 subst expr = eval2 subst (iter subst expr);; *)

let simplifie_somme = fun e1 e2 ->
  match e1, e2 with
  | Num 0., e -> e
  | e, Num 0. -> e
  | Num e1, Num e2 -> Num (e1 +. e2)
  | _, _ -> Somme (e1, e2)

let simplifie_produit = fun e1 e2 ->
  match e1, e2 with
  | Num 0., _ -> Num 0.
  | _, Num 0. -> Num 0.
  | Num 1., e -> e
  | e, Num 1. -> e
  | Num e1, Num e2 -> Num (e1 *. e2)
  | _, _ -> Produit (e1, e2)


let simplifie expr = iter (fun e -> 
  match e with
  | Somme (e1, e2) -> simplifie_somme e1 e2
  | Produit (e1, e2) -> simplifie_produit e1 e2
  | _ -> e) expr;;

let rec affiche expr =
  match expr with
  | Num x -> Printf.printf "%f" x
  | Var x -> Printf.printf "%s" x
  | Somme (e1, e2) -> Printf.printf "("; affiche e1; Printf.printf " + "; affiche e2; Printf.printf ")"
  | Produit (e1, e2) -> Printf.printf "("; affiche e1; Printf.printf " * "; affiche e2; Printf.printf ")"
  | Oppose e1 -> Printf.printf "-"; affiche e1
  | Inverse e1 -> Printf.printf "1/"; affiche e1;;


let () = 
  (*Printf.printf "eval trois_x = %f\n" (eval trois_x);*)
  (*Printf.printf "eval un_plus_trois_x = %f\n" (eval un_plus_trois_x);
  Printf.printf "eval e = %f\n" (eval e);*)
  Printf.printf "eval (Produit(Num 2., Num 3.)) = %f\n" (eval (Produit(Num 2., Num 3.)));
  Printf.printf "eval2 subst e = %f\n" (eval2 subst e);;
  Printf.printf "derive e x = %f\n" (eval2 subst (derive e "x"));
  Printf.printf "iter (fun x -> x) e = %f\n" (eval2 subst (iter (fun x -> x) e));
  Printf.printf "simplifie e = %f\n" (eval2 subst (simplifie e));
  Printf.printf "\n";;
  affiche (simplifie (derive e "x"));;
  affiche (derive e "x");;

