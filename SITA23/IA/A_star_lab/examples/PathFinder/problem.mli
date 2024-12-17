(***********************************************************************)
(*                                                                     *)
(*         Pathfinder (A* algorithm for path-finding problems)         *)
(*                                                                     *)
(*         David Gianazza, Ecole Nationale de l'Aviation Civile        *)
(*                                                                     *)
(*  Copyright 2017 Ecole Nationale de l'Aviation Civile.               *)
(*  All rights reserved.  This file is distributed under the terms of  *)
(*  the GNU Library General Public License.                            *)
(*                                                                     *)
(***********************************************************************)

(** A path-finding problem, with obstacles between origin and destination. *)

type obstacle=
    R of Geo.Rectangle.t
  | C of Geo.Circle.t
        
type problem = {
    xmin:float;xmax:float;ymin:float;ymax:float; (* Boundaries of the domain *)
  (*xmin:int;xmax:int;ymin:int;ymax:int;*) (* Boundaries of the domain *)
    orig : Geo.P2D.t; (** Point of departure *)
    dest: Geo.P2D.t; (** Destination *)
    obstacles: obstacle list }

val print: problem -> Geo.P2D.t list -> unit

val inside_domain: problem -> Geo.P2D.t -> bool
(** [inside_domain pb p] returns [true] if point [p] is inside
    the domain defined in problem [pb], and [false] otherwise *)

val outside_obstacles: problem -> Geo.P2D.t -> bool
(** [outsided_obstacles pb p] returns [true] if point [p] is outside
    the obstacles defined in problem [pb], and [false] otherwise *)
  
val check_constraints: problem -> Geo.P2D.t list -> Geo.P2D.t list
(** [check_constraints pb points] filters the list [points] and returns
    only the points inside the domain and outside the obstacles defined
    in problem [pb]. *)

val init : unit -> problem
(** [init_problem ()] returns a path-finding problem. *)

