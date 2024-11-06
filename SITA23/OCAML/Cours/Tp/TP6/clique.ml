
(* begin provided *)
let fprint = fun c cl ->
  Printf.fprintf c "{";
  let maxi = IS.max_elt cl in
  let cl = IS.remove maxi cl in
  IS.iter (Printf.fprintf c "%d,") cl;
  Printf.fprintf c "%d}" maxi
(* end provided *)

