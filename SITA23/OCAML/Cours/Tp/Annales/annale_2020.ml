type expr = 
  |Const of int
  |Var of string
  |Tab of string * expr
  |Somme of expr * expr
  |Produit of expr * expr;;

let expr1 = Somme(
  Produit(
    Const (5),
    Somme(
      Var("x"), Const(-3)
    )
  ),
  Tab(
    "t",
    Somme(
      Var("y"), Const(1)
    )
  )
);;

let expr2 = Tab(
  "t",
  Tab(
    "t",Const(2)
  )
);;

type env = {id : string; adresse : int};;

let env1 = [|("x", 0); ("y", 1); ("t", 2)|] ;;


let adresse env id =
  let taille = Array.length env in
  let rec aux ind =
    if ind < taille then
      match env.(ind) with
      |(x,y) when x = id -> y
      |_ -> aux (ind + 1) 
    else raise Not_found in
  aux 0;;


adresse env1 "x";;
adresse env1 "t";;
adresse env1 "i";;

let rec eval exp env tab=
  match exp with
  | Const(x) -> x
  | Var(x) -> tab.(adresse env x)
  | Tab (x,y) -> tab. ((adresse env x) + eval y env tab)
  | Somme (x,y) -> (eval x env tab) + (eval y env tab)
  | Produit (x,y) -> (eval x env tab) * (eval y env tab);;

let tab1 = [|11; 2; 5; 4; 3; 2; 1|];;

eval expr1 env1 tab1;;
eval expr2 env1 tab1;;

let rec iter exp f = 
  match exp with
  |Const _-> ()
  |Var _ -> ()
  |Tab (_,y) -> f y ; iter y f
  |Somme (x, y) -> f x; f y; iter x f; iter y f
  |Produit (e1, e2) -> f e1; f e2; iter e1 f; iter e2 f ;;



(*Const et Var : Pour les constantes et les variables, il n'y a pas de sous-expression, donc nous n'avons rien à faire.
Tab : Pour les tableaux, nous appliquons la fonction f à l'index (qui est une expression) et nous appelons récursivement iter sur cette sous-expression.
Somme et Produit : Pour les sommes et les produits, nous appliquons la fonction f aux deux sous-expressions et nous appelons récursivement iter sur chacune des sous-expressions.*)