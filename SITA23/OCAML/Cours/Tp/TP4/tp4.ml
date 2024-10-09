type 'a t = 
  | Entree of 'a list
  | Sortie of 'a list;;


exception FileVide;;

let empty = Entree [];;

let is_empty = function
  | Entree [] -> true
  | _ -> false;;


let add e = function
  | Entree l -> Entree (e :: l)
  | Sortie l -> Entree (e :: l);;

let take = function
  | Entree [] -> raise FileVide
  | Entree (e :: l) -> (e, Entree l)
  | Sortie (e :: l) -> (e, Sortie l);;

let () = 
  let t = empty in
  Printf.printf "%b\n" (is_empty t);
  let t = add 1 t in
  Printf.printf "%b\n" (is_empty t);
  let t = add 2 t in
  let t = add 3 t in
  let (e, t) = take t in
  Printf.printf "%d\n" e;