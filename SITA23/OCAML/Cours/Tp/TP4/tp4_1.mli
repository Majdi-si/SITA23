type 'a t = 'a list * 'a list

exception FileVide

val empty : 'a t

val is_empty : 'a t -> bool

val add : 'a -> 'a t -> 'a t

val take : 'a t -> 'a * 'a t

val print_tuple : int t -> unit
