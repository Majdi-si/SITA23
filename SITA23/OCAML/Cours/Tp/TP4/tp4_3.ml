type 'a tree = 
  | Empty 
  | Node of 'a tree * 'a * 'a tree

module Set = Tp4_1


let iter f tree =
  let rec aux container =
    if Set.is_empty container then ()
    else
      let (node, container) = Set.take container in
      match node with
      | Empty -> aux container
      | Node (l, x, r) -> 
        f x;
        aux (Set.add l (Set.add r container))
  in
  aux (Set.add tree Set.empty)


let () =
  let tree = Node (Node (Empty, 1, Empty), 2, Node (Empty, 3, Empty)) in
  iter (fun x -> Printf.printf "%d\n" x) tree
  

