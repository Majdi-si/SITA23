type 'a t = 'a list * 'a list

exception Empty

let empty = ([], [])

let is_empty = fun q ->
  q = empty

let add = fun x (front, back) ->
  (x::front, back)

let take = fun (front, back) ->
  match back with
    [] ->
      begin
        match List.rev front with
          [] -> raise Empty
        | x :: xs -> (x, ([], xs))
      end
  | x :: back -> (x, (front, back))

(* "recursive" version (one recursive call at most)
   to shorten the code - probably less efficient *)
(* let rec take = fun q -> *)
(*   match q with *)
(*     ([], []) -> raise Empty *)
(*   | (front, []) -> take ([], List.rev front) *)
(*   | (front, x :: back) -> (x, (front, back)) *)
