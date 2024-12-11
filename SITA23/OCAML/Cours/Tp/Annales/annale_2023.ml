type t = 
  | Var of string
  | Neg of t
  | Dis of t * t
  | Conj of t * t ;;

let formule_1 = Conj (
  Conj (
    Dis (Var "u1", Dis (Neg (Var "u2"), Var "u3")),
    Dis (Var "u2", Neg (Var "u4"))
  ),
  Neg (Var "u1")
);;

let formule_2 = Dis (
  Neg (
    Dis (
      Var "u1", Conj (Var "u2", Neg (Var "u3"))
    )
  ),
  Conj (
    Var "u1", Neg (Conj (Var "u2", Neg (Var "u4")))
  )
);;

type assignment = {
  id_variable : string;
  valeur : bool;
};;

exception Not_found ;;

let rec get id env =
  match env with
  | [] -> raise Not_found
  | x :: h when x.id_variable = id -> x.valeur
  | x :: h -> get id h;;

let rec eval env f =
  match f with
  |Var (x) -> get x env
  |Neg (t) -> not(eval env t)
  |Dis (t1, t2) -> eval env t1 || eval env t2
  |Conj (t1, t2) -> eval env t1 && eval env t2;;


let list_env = [
  { id_variable = "u1"; valeur = true };
  { id_variable = "u2"; valeur = false };
  { id_variable = "u3"; valeur = true };
  { id_variable = "u4"; valeur = false };
];;

eval list_env formule_1;;
eval list_env formule_2;;

let rec nnf t = 
  match t with
  |Neg(Neg (r)) -> nnf r
  |Neg(Dis(p, q)) -> Conj(nnf (Neg(p)), nnf (Neg(q)))
  |Neg(Conj(p, q)) -> Dis(nnf (Neg(p)), nnf (Neg(q)))
  |Dis (p, q) -> Dis (nnf p, nnf q)
  |Conj (p, q) -> Conj (nnf p, nnf q)
  |_ -> t;;

nnf formule_2;;


let prod h p q =
  List.fold_right
    (fun pi pr -> List.fold_right (fun qj qr -> h pi qj :: qr) q pr) 
    p [] ;;

let rec n2cnf t =
  match t with
  | Var x -> [[(x, true)]]
  | Neg (Var x) -> [[(x, false)]]
  | Conj (p, q) -> n2cnf p @ n2cnf q
  | Dis (p, q) ->
    let cp = n2cnf p in
    let cq = n2cnf q in
    prod (@) cp cq
  | _ -> failwith "Formule non en NNF" ;;

let rec unique = function
  | [] -> []
  | [x] -> [x]
  | x :: (y :: _ as t) -> if x = y then unique t else x :: unique t

let rec check_opposite = function
  | [] -> false
  | [x] -> false
  | (x, b1) :: (y, b2) :: t -> if x = y && b1 <> b2 then true else check_opposite ((y, b2) :: t) ;;

let simplify clause =
  let sorted_clause = List.sort compare clause in
  let unique_clause = unique sorted_clause in
  if check_opposite unique_clause then [] else unique_clause ;;

let rec scnf t =
  match t with
  | Var x -> [[(x, true)]]
  | Neg (Var x) -> [[(x, false)]]
  | Conj (p, q) -> scnf p @ scnf q
  | Dis (p, q) ->
    let cp = scnf p in
    let cq = scnf q in
    List.filter (fun clause -> clause <> []) (prod (fun p q -> simplify (p @ q)) cp cq)
  | _ -> failwith "Formule non en NNF" ;;

(* Exemple d'utilisation *)
let formule_2 = Dis (
  Neg (
    Dis (
      Var "u1", Conj (Var "u2", Neg (Var "u3"))
    )
  ),
  Conj (
    Var "u1",
    Neg (
      Conj (Var "u2", Neg (Var "u4"))
    )
  )
);;