type arith_op = Add | Sub | Mul | Div | Mod

type stack_op = Dup | Swap | Print

type instruction =
    | Int of int
    | Arith of arith_op
    | Stack of stack_op
    | If of prog * prog * prog
    | While of prog

and prog = instruction list

(*Représenter le programme <4 3 2 * + dup * print> avec les types précédents.*)

let prog1 = [Int 4; Int 3; Int 2; Arith Mul; Arith Add; Stack Dup; Arith Mul; Stack Print]

(*Définir la fonction syracuse: int -> prog qui prend le terme initial entier u0 en para-
mètre et qui renvoie le programme Forth suivant, permettant de calculer et afficher les termes de
la suite de Syracuse de terme initial u0 jusqu’à obtenir 1 :
<u0 while(<dup 1 swap ->, <print if(<dup 2 swap %>, <3 * 1 +>, <2 swap />)>)>
    
    if(prog_cond, prog_then, prog_else) : conditionnelle
1. on commence par exécuter le programme prog_cond qui doit placer un entier en sommet
de pile : on interprète la condition comme fausse si cet entier est zéro et comme vraie s’il
est différent de zéro ;
2. on doit ensuite supprimer cet entier du sommet de pile puis exécuter le programme
prog_then si la condition est vraie, sinon le programme prog_else.
1IENAC Majeure SITA
2
— while(prog_cond, prog_body) : boucle non-bornée
1. le programme prog_cond est utilisé de la même manière que pour la conditionnelle ;
2. si la condition est vraie, le programme prog_body est exécuté, puis on retourne à l’étape 1.*)

let syracuse u0 = [Int u0; While ([Stack Dup; Int 1; Stack Swap; Arith Sub], [Stack Print; If ([Stack Dup; Int 2; Stack Swap; Arith Mod], [Int 3; Arith Mul; Int 1; Arith Add], [Int 2; Stack Swap; Arith Div])])]

(*Error: This expression has type 'a * 'b
       but an expression was expected of type prog = instruction list*)

let syracuse u0 = [Int u0; While ([Stack Dup; Int 1; Stack Swap; Arith Sub], [Stack Print; If ([Stack Dup; Int 2; Stack Swap; Arith Mod], [Int 3; Arith Mul; Int 1; Arith Add], [Int 2; Stack Swap; Arith Div])])]
(*Définir la fonction exec_arith: int list -> arith_op -> int list qui prend une pile d’entiers

(*Définir la fonction top: ’a list -> ’a * ’a list qui prend une liste en paramètre et renvoie

(*Définir les deux fonctions :
top: ’a list -> ’a * ’a list
top2: ’a list -> ’a * ’a * ’a list
qui prennent une liste en paramètre et renvoient le couple (resp. le triplet) du premier élément
(resp. des deux premiers éléments) et du reste de la liste. Si la liste ne comporte pas assez
d’éléments, ces fonctions doivent lever l’exception StackError que vous aurez préalablement
définie.*)


exception StackError

let top l = match l with
    | [] -> raise StackError
    | x::q -> (x, q)

let top2 l = match l with
    | [] -> raise StackError
    | x::y::q -> (x, y, q)
    | _ -> raise StackError

(*En considérant que la pile est une liste d’entiers, et en utilisant la fonction top2 définie à
la question 5, définir la fonction :
exec_arith: int list -> arith_op -> int list
qui dépile les deux nombres en sommet de pile, exécute sur ces deux nombres l’opération arith-
métique passée en paramètre, empile leur résultat, puis renvoie la nouvelle pile correspondante.*)

let exec_arith l op = match top2 l with
    | (x, y, q) -> match op with
        | Add -> (x + y)::q
        | Sub -> (x - y)::q
        | Mul -> (x * y)::q
        | Div -> (x / y)::q
        | Mod -> (x mod y)::q
    | _ -> raise StackError

(*Définir la fonction print_stack: int list -> unit qui prend une pile d’entiers en
paramètre et l’imprime sur la sortie standard en utilisant l’itérateur approprié du module List,
e.g. après les trois premières instructions de l’exemple de la question 3 : [2|3|4|].*)

let print_stack l = Printf.printf "[%s]\n" (String.concat ";" (List.map string_of_int l))

print_stack [2;3;4]

(*En utilisant les deux fonctions définies à la question 5, définir la fonction :
exec_stack: int list -> stack_op -> int listIENAC Majeure SITA
3
de manière similaire à la fonction exec_arith de la question 6, pour exécuter les opérations de
manipulation de la pile.
les opérateurs de pile manipulent le contenu du sommet de pile :
— dup : duplication du sommet de pile (e.g. [2|3|4] devient [2|2|3|4]) ;
— swap : échange des deux nombres en sommet de pile (e.g. [2|3|4] devient [3|2|4]) ;
— print : affichage du sommet de pile sur la sortie standard sans modifier la pile.*)

let exec_stack l op = match op with
    | Dup -> match top l with
        | (x, q) -> x::x::q
    | Swap -> match top2 l with
        | (x, y, q) -> y::x::q
    | Print -> match top l with
        | (x, q) -> Printf.printf "%d\n" x; l

(*À l’aide des fonctions précédentes, définir la fonction exec: prog -> int list qui prend
un programme Forth en paramètre, exécute ses instructions l’une après l’autre avec une pile
initialement vide puis renvoie la pile obtenue quand il n’y a plus d’instruction à exécuter.
Indication : pour les boucles, quand la condition est vraie, on exécute le corps la boucle, puis
il suffit de réexécuter le programme entier (à partir de la boucle elle-même) jusqu’à ce que la
condition devienne fausse, et on exécute alors la suite du programme comme pour les autres
instructions.*)

let exec p =
  let rec exec' p l = match p with
    | [] -> l
    | Const x :: q -> exec' q (x :: l)
    | Arith op :: q -> exec' q (exec_arith l op)
    | Stack op :: q -> exec' q (exec_stack l op)
    | If (cond, then_prog, else_prog) :: q ->
        let l' = exec' cond l in
        (match l' with
         | 0 :: l'' -> exec' (else_prog @ q) l''
         | _ :: l'' -> exec' (then_prog @ q) l'')
    | While (cond, body) :: q ->
        let rec boucle l =
          let l' = exec' cond l in
          match l' with
          | 0 :: l'' -> exec' q l''
          | _ :: l'' -> boucle (exec' body l'')
        in
        boucle l
  in
  exec' p []
(*Tester la fonction exec avec le programme de la question 3.*)

let _ = exec (syracuse 5) |> print_stack

(*Définir la fonction syracuse2: int -> prog qui prend le terme initial entier u0 en para-