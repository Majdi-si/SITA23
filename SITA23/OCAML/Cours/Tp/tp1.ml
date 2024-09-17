let rec pgcd a b =
  match b with 
  | 0 -> a
  | _ -> pgcd b (a mod b)


type int_seq =
  |Vide
  |Node of int * int_seq

let seq = Node (1, Node (2, Node (3, Vide)))
let seq5 = Node (4, Node (5, Node (6, Vide)))

let rec length seq = 
  match seq with
  |Vide -> 0
  |Node (_, next) -> 1 + length next

let rec sum seq =
  match seq with
  |Vide -> 0
  |Node (a, next) -> a + sum next

let rec map f seq =
  match seq with
  |Vide -> Vide
  |Node(a, next) -> Node(f a, map f next)

let rec affichage seq = 
  match seq with
  |Vide -> ()
  |Node(a, next) -> 
      Printf.printf "%d " a; 
      affichage next

let rec filter pred seq =
  match seq with
  |Vide -> Vide
  |Node(a, next) -> if pred a then
    Node(a, filter pred next)
    else
        filter pred next

let impair x = x mod 2 = 1

let comprehension f pred seq =
  map f (filter pred seq )

  let rec map2 f seq1 seq2 =
    match seq1, seq2 with
    | Vide, _ | _, Vide -> Vide
    | Node(a, next1), Node(b, next2) -> Node(f a, Node(f b, map2 f next1 next2))

let rec iter f seq z =
  match seq with
  | Vide -> z
  | Node(a, next) -> f a (iter f next z)

let iter_sum seq = iter (fun x acc -> x + acc) seq 0
let iter_length seq = iter (fun _ acc -> acc + 1) seq 0
let iter_map f seq = iter (fun x acc -> Node(f x, acc)) seq Vide

let prod seq1 seq2 =
  iter (fun x acc -> 
    iter (fun y acc2 -> Node(x*y, acc2)) seq2 acc
    ) seq1 Vide

let () =
  (* Calcul et affichage du PGCD de 3822 et 2310 *)
  Printf.printf "PGCD de 3822 et 2310 = %d\n" (pgcd 3822 2310);
  (* Calcul et affichage de la longueur de la séquence *)
  Printf.printf "Longueur de la séquence = %d\n" (length seq);
  (* Calcul et affichage de la somme de la séquence *)
  Printf.printf "Somme de la séquence = %d\n" (sum seq);
  (* Affichage de la séquence *)
  Printf.printf "Affichage de la séquence : ";
  affichage seq;
  Printf.printf "\n";
  (* Application d'une fonction sur la séquence *)
  let seq2 = map (fun x -> x * x) seq in
  Printf.printf "Affichage de la séquence après application de la fonction : ";
  affichage seq2;
  Printf.printf "\n";
  (* Filtrage de la séquence *)
  let seq3 = filter impair seq in
  Printf.printf "Affichage de la séquence après filtrage des impairs : ";
  affichage seq3;
  Printf.printf "\n";
  (* Application de la compréhension de liste *)
  let seq4 = comprehension (fun x -> x * x) impair seq in
  Printf.printf "Affichage de la séquence après compréhension de liste : ";
  affichage seq4;
  Printf.printf "\n";
  (* Affichage de la séquence seq5 *)
  Printf.printf "Affichage de la séquence seq5 : ";
  affichage seq5;
  Printf.printf "\n";
  (* Application de la fonction map2 sur seq et seq5 *)
  let seq6 = map2 (fun x -> x * x) seq seq5 in
  Printf.printf "Affichage de la séquence après application de la fonction map2 : ";
  affichage seq6;
  Printf.printf "\n";
  (* Application de la fonction iter sur seq *)
  let seq7 = iter (fun x acc -> x + acc) seq 0 in
  Printf.printf "Application de la fonction iter sur seq : %d\n" seq7;
  (* Application de la fonction iter_sum sur seq *)
  Printf.printf "Somme de la séquence avec iter_sum : %d\n" (iter_sum seq);
  (* Application de la fonction iter_length sur seq *)
  Printf.printf "Longueur de la séquence avec iter_length : %d\n" (iter_length seq);
  (* Application de la fonction iter_map sur seq *)
  Printf.printf "Affichage de la séquence après application de iter_map : ";
  affichage (iter_map (fun x -> x * x) seq);
  Printf.printf "\n";
  Printf.printf "Affichage de la séquence après application de iter_map : ";
  affichage (prod seq seq5);
  Printf.printf "\n";



