let rec pgcd a b =
  match b with
  |0-> a
  |_-> pgcd b (a mod b);;

type int_seq =
  |Vide
  |Node of int * int_seq

let rec length seq =
  match seq with
  |Vide -> 0
  |Node(a,reste) -> 1 + (length reste) ;;

let seq = Node(1, (Node(2 ,Node(3 ,Vide))));;

let rec sum seq = 
  match seq with
  |Vide -> 0
  |Node(a,reste) -> a + (sum reste)

let rec map f seq =
  match seq with
  |Vide -> Vide
  |Node (a, reste) -> Node (f(a), (map f reste))

let rec affichage seq = 
  match seq with
  |Vide -> ()
  |Node(a, next) -> 
      Printf.printf "%d " a; 
      affichage next

let rec filter pred seq = 
  match seq with
  |Vide -> Vide
  |Node (a, reste) -> 
    if pred a then
      Node (a, filter pred reste)
    else
      filter pred reste

let pred_impair x = 
  x mod 2 = 1

let comprehension f pred seq =
  map f (filter pred seq)

let rec map2 f seq1 seq2 =
  match seq1, seq2 with
  |_, Vide | Vide, _ -> Vide
  |Node(a,reste1), Node(b,reste2) -> Node(f(a), Node(f(b), map2 f reste1 reste2))
 
  
let () =
  (* Calcul et affichage du PGCD de 3822 et 2310 *)
  Printf.printf "PGCD de 3822 et 2310 = %d\n" (pgcd 3822 2310);

  (*Définition de la séquence : <1,2,3>*)
  (*Printf.printf "Séquence <1,2,3> : %d\n" Node(1, (Node(2 ,Node(3 ,Vide))))*)

  (* Calcul de la taille de la sequence *)
  Printf.printf "Taille de seq = %d\n" (length seq);

  (* Calcul de la taille de la sequence *)
  Printf.printf "Somme de seq = %d\n" (sum seq);

  (* Application de la fonction map à la séquence *)
  let seq2 = map (fun x -> x * x) seq in
  Printf.printf "Affichage de la séquence après application de la fonction : ";
  affichage seq2;
  Printf.printf "\n";

  (* Application de la fonction filter à la séquence *)
  let seq3 = filter pred_impair seq in
  Printf.printf "Affichage de la séquence après application de la fonction filter : ";
  affichage seq3;
  Printf.printf "\n";

  (* Application de la fonction comprehension à la séquence *)
  let seq4 = comprehension (fun x -> x * x) pred_impair seq in
  Printf.printf "Affichage de la séquence après application de la fonction comprehension : ";
  affichage seq4;
  Printf.printf "\n";

  (* Application de la fonction map2 à la séquence *)
  let seq5 = map2 (fun x -> x * x) seq seq in
  Printf.printf "Affichage de la séquence après application de la fonction map2 : ";
  affichage seq5;
  Printf.printf "\n";

  ()

