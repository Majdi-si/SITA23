(* Type task (sans abstraction) *)
type task = {
    id : int;
    start: int;
    endt : int;
}

(* Type t abstrait *)
type t

(* Fonction read *)
val read : string -> t

(* Fonction fprint *)
val fprint : out_channel -> t -> unit

(* Fonction fold *)
val fold : (task -> 'a -> 'a) -> t -> 'a -> 'a

(* Fonction make *)