let rec sigma_direct f a b =
  if a > b then 0
  else f a + sigma_direct f (a + 1) b

let sigma_terminal f a b =
  let rec aux a acc =
    if a > b then acc
    else aux (a + 1) (acc + f a)
  in
  aux a 0

let sigma_terminal_2 f a b i =
  let rec aux a acc i
    if a > b then acc
    else aux (a + i) (acc + f a) i
  in
  aux a 0 i

let sigma_terminal_fonc f a b s =
  let rec aux a acc s 
    if a > b then acc
    else aux (s(a)) (acc + f a) s
  in
  aux a 0 s

let sigma_terminal_predicat f a b s cont =
  let rec aux a acc s 
    if cont b then acc
    else aux (s(a)) (acc + f a) s 
  in
  aux a 0 s


let sigma_terminal_generale f a b s cont g neutre =
  let rec aux a acc 
     if cont b then neutre
     else aux (s(a)) g(acc f a)
  aux a neutre


let factorielle n = sigma_terminal_generale (fun x -> x) 1 n (fun x -> x + 1) (fun x -> x > n) (fun x y-> x*y) 1

let integrale f a b dx = sigma_terminal_generale f a b (fun x -> x +. dx) (fun x -> x >= b) (fun x y -> x +. y) 0.