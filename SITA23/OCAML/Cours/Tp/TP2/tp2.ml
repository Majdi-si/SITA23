let rec sigma_direct f a b =
  if a > b then 0
  else f a + sigma_direct f (a + 1) b

let sigma_terminal f a b =
  let rec aux a acc =
    if a > b then acc
    else aux (a + 1) (acc + f a)
  in
  aux a 0

let sigma_terminal_inc f a b i =
  let rec aux a acc i =
    if a > b then acc
    else aux (a + i) (acc + f a) i
  in
  aux a 0 i

let sigma_terminal_fonc f a b s =
  let rec aux a acc s =
    if a > b then acc
    else aux (s a) (acc + f a) s
  in
  aux a 0 s
  
let sigma_terminal_predicat f a b s cont =
  let rec aux a acc =
    if cont a then acc
    else aux (s a) (acc + (f a))
  in
  aux a 0

let rec 


let () =
  Printf.printf "sigma_direct (fun x -> x) 1 10 = %d\n" (sigma_direct (fun x -> x) 1 10);
  Printf.printf "sigma_direct (fun x -> x * x) 1 10 = %d\n" (sigma_direct (fun x -> x * x) 1 10);
  Printf.printf "sigma_direct (fun x -> x * x * x) 1 10 = %d\n" (sigma_direct (fun x -> x * x * x) 1 10);
  Printf.printf "sigma_terminal (fun x -> x) 1 10 = %d\n" (sigma_terminal (fun x -> x) 1 10);
  Printf.printf "sigma_terminal (fun x -> x * x) 1 10 = %d\n" (sigma_terminal (fun x -> x * x) 1 10);
  Printf.printf "sigma_terminal (fun x -> x * x * x) 1 10 = %d\n" (sigma_terminal (fun x -> x * x * x) 1 10);
  Printf.printf "sigma_terminal_inc (fun x -> x) 1 10 2 = %d\n" (sigma_terminal_inc (fun x -> x) 1 10 2);
  Printf.printf "sigma_terminal_inc (fun x -> x * x) 1 10 2 = %d\n" (sigma_terminal_inc (fun x -> x * x) 1 10 2);
  Printf.printf "sigma_terminal_inc (fun x -> x * x * x) 1 10 2 = %d\n" (sigma_terminal_inc (fun x -> x * x * x) 1 10 2);
  Printf.printf "sigma_terminal_fonc (fun x -> x) 1 10 (fun x -> x + 1) = %d\n" (sigma_terminal_fonc (fun x -> x) 1 10 (fun x -> x + 1));
  Printf.printf "sigma_terminal_fonc (fun x -> x * x) 1 10 (fun x -> x + 1) = %d\n" (sigma_terminal_fonc (fun x -> x * x) 1 10 (fun x -> x + 1));
  Printf.printf "sigma_terminal_fonc (fun x -> x * x * x) 1 10 (fun x -> x + 1) = %d\n" (sigma_terminal_fonc (fun x -> x * x * x) 1 10 (fun x -> x + 1));
  Printf.printf "sigma_terminal_predicat (fun x -> x) 1 10 (fun x -> x + 1) (fun x -> x > 10) = %d\n" (sigma_terminal_predicat (fun x -> x) 1 10 (fun x -> x + 1) (fun x -> x > 10));