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
  let rec aux a acc =
    if a > b then acc
    else aux (s a) (acc + f a) 
  in
  aux a 0
  
let sigma_terminal_predicat f a b s cont  =
  let rec aux a acc =
    if cont a then acc
    else aux (s a) (acc + (f a))
  in
  aux a 0

let sigma_terminal_binaire f a b s cont binaire neutre =
  let rec aux a acc =
    if cont a then acc
    else aux (s a) (binaire acc  (f a))
  in
  aux a neutre

let integrale f a b dx = 
  sigma_terminal_binaire f a b (fun x -> x +. dx) (fun x -> x >= b) (fun x y -> x +. y) 0.

let pi epsilon =
  let f n = if n mod 2 = 0 then 1.0 /. (2.0 *. float_of_int n +. 1.0) else -.1.0 /. (2.0 *. float_of_int n +. 1.0) in
  let s n = n + 1 in
  let cont n = abs_float (f n) < epsilon in
  let binaire (acc, n) term = (acc +. term, n + 1) in
  let (approx, _) = sigma_terminal_binaire (fun n -> f n) 0 max_int s cont (fun (acc, n) term -> (acc +. term, n + 1)) (0.0, 0) in
  4.0 *. approx

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
  Printf.printf "sigma_terminal_binaire (fun x -> x) 1 10 (fun x -> x + 1) (fun x -> x > 10) (fun x y  -> x+y) = %d\n" (sigma_terminal_binaire (fun x -> x) 1 10 (fun x -> x + 1) (fun x -> x > 10) (fun x y -> x+y) 0);
  Printf.printf "Factoriel 5 = %d\n" (sigma_terminal_binaire (fun x -> x) 1 5 (fun x -> x+1) (fun x -> x > 5) (fun x y  -> x*y) 1);
  Printf.printf "Intégrale de 1 à 100 de x² = %f\n" (integrale (fun x -> x *. x) 1. 100. 0.1);
  let epsilon = 1e-6 in
  Printf.printf "Approximation de π avec epsilon = %f : %f\n" epsilon (pi epsilon)