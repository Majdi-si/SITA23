type 'a t

exception Empty

val empty : 'a t

val is_empty : 'a t -> bool

val add : 'a -> 'a t -> 'a t

val take : 'a t -> 'a * 'a t
