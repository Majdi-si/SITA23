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


let rec simplifie expr =
  match expr with
  | Somme (Num 0., e) -> simplifie e
  | Somme (e, Num 0.) -> simplifie e
  | Produit (Num 1., e) -> simplifie e
  | Produit (e, Num 1.) -> simplifie e
  | Produit (Num 0., e) -> Num 0.
  | Produit (e, Num 0.) -> Num 0.
  | Oppose (Num 0.) -> Num 0.
  | _ -> expr

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
  Printf.printf "simplifie e = %f\n" (eval2 subst (simplifie e)); (* Correction ici *)
  affiche e;;
  Printf.printf "\n";;
  affiche (derive e "x");;
  Printf.printf "\n";;
  affiche (simplifie e);; (* Correction ici *)
  Printf.printf "\n";;
  affiche (derive (simplifie e) "x");; (* Correction ici *)
  Printf.printf "\n";;
  affiche (simplifie (Somme (Num 0., e)));;
  
