type expr = 
  | Const of int
  | Var of string
  | Tab of string * expr
  | Somme of expr * expr
  | Produit of expr * expr

let expr = 
  Somme (
    Produit (Const 5, Somme (Var "x", Const (-3))),
    Tab ("t", Somme (Var "y", Const 1))
  );;

let expr = Tab ("t", Tab ("t", Const 2));;

