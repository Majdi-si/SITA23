type 'a t = 'a list * 'a list;;


exception FileVide;;

let empty = ([],[]);;

let is_empty = function
  | ([], []) -> true
  | _ -> false;;

let add = fun x t ->
  match t with
  | (l1, l2) -> (x::l1, l2);;


let take = fun t ->
  match t with
  | ([],_) -> raise FileVide
  | (l1,[]) -> let l2 = List.rev l1 in (List.hd l2, ([],List.tl l2))
  | (l1,l2) -> (List.hd l2, (l1,(List.tl l2)));;

let print_tuple = fun t ->
  match t with
  | (l1,l2) -> Printf.printf "l1 = %s\nl2 = %s\n" (String.concat " " (List.map string_of_int l1)) (String.concat " " (List.map string_of_int l2));;


let () = 
  let t = add 1 empty in
  let t = add 2 t in
  let t = add 3 t in
  let t = add 4 t in
  let t = add 5 t in
  let (e, t) = take t in
  Printf.printf "e = %d\n" e;
  print_tuple t;;