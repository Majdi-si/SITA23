type expr =
  | Nombre of float
  | Var of string
  | Somme of expr * expr
  | Produit of expr * expr
  | Oppose of expr
  | Inverse of expr

let expr1 = Oppose(Produit (Inverse (Nombre(2.0)), Somme(Nombre(1.0), Produit(Nombre(3.0), Var("x")))));;

let rec eval expr =
  match expr with
  | Nombre x -> x
  | Var x -> failwith "Contient une variable"
  | Somme (e1, e2) -> eval e1 +. eval e2
  | Produit (e1, e2) -> eval e1 *. eval e2
  | Oppose e1 -> -. eval e1
  | Inverse e1 -> 1. /. eval e1 ;;

let rec eval2 expr sub =
  match expr with
  | Nombre x -> x
  | Var x -> sub x
  | Somme (e1, e2) -> eval2 e1 sub +. eval2 e2 sub
  | Produit (e1, e2) -> eval2 e1 sub *. eval2 e2 sub
  | Oppose e1 -> -. eval2 e1 sub
  | Inverse e1 -> 1. /. eval2 e1 sub ;;

let subst = fun v ->
  match v with
  "x" -> 1.
  | _ -> failwith "subst: variable inconnue";;

eval2 expr1 subst ;;


let rec derive expr var =
  match expr with
  | Nombre _ -> Nombre 0.
  | Var x -> if x = var then Nombre 1. else Nombre 0.
  | Somme (e1, e2) -> Somme (derive e1 var, derive e2 var)
  | Produit (e1, e2) -> Somme (Produit (derive e1 var, e2), Produit (e1, derive e2 var))
  | Oppose e1 -> Oppose (derive e1 var)
  | Inverse e1 -> Oppose (Produit (derive e1 var, Inverse (Produit (e1, e1))));;


let rec iter f expr =
  match expr with
  | Nombre x -> f (Nombre x)
  | Var x -> f (Var x)
  | Somme (e1, e2) -> f (Somme (iter f e1, iter f e2)) 
  | Produit (e1, e2) -> f (Produit (iter f e1, iter f e2))
  | Oppose e1 -> f (Oppose (iter f e1))
  | Inverse e1 -> f (Inverse (iter f e1));;


let eval_2_iter expr sub = iter