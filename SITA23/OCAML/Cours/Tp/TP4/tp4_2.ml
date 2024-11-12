type 'a t = {stack : 'a list; size : int}

exception Empty

let empty = {stack = []; size = 0}

let take = fun s ->
match s.stack with
[] -> raise Empty
| h :: t -> (h, {stack = t; size = s.size - 1})

let add = fun e s ->
  match s.stack with
  |[] -> {stack = e :: []; size = 1}
  |l -> {stack = e :: l; size = s.size + 1}

let is_empty = fun s ->
  match s.stack with
  |[] -> true
  |_ -> false

let size = fun s -> s.size

let print_tuple = fun s ->
  Printf.printf "stack = %s\nsize = %d\n" (String.concat " " (List.map string_of_int s.stack)) s.size;;

let () = 
  let s = add 1 empty in
  let s = add 2 s in
  let s = add 3 s in
  let s = add 4 s in
  let s = add 5 s in
  print_tuple s;
  Printf.printf "\n";
  let (e, s) = take s in
  Printf.printf "e = %d\n" e;
  Printf.printf "size = %d\n" s.size;;