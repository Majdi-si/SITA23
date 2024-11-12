type 'a t
(** The type of stacks containing elements of type ['a]. *)
exception Empty
val empty : 'a t
(** Empty stack. *)
val take : 'a t -> 'a * 'a t
(** [take s] returns the top element and the rest of stack [s].
Raises exception [Empty] if [s] is empty. *)

val add : 'a -> 'a t -> 'a t
(** [add e s] returns a stack containing element [e] on top of stack [s]. *)

val print_tuple : int t -> unit
(** [print_tuple s] prints the stack [s]. *)