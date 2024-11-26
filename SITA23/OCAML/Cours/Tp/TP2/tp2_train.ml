let rec sigma_direct f a b =
  if a > b then 0
  else f a + sigma_direct f (a + 1) b

let sigma_terminal f a b =
  let rec aux a acc =
    if a > b then acc
    else aux (a + 1) (acc + f a)
  in
  aux a 0

