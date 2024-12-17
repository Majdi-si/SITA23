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

(** Implementation of A* algorithm for path-finding problems *)

module MyModel :
  sig
    type state = Geo.P2D.t
    type user_param = Draw.graph * Problem.problem
    val initial_state : user_param -> Geo.P2D.t
    val is_goal : user_param -> Geo.P2D.t -> bool
    val k : user_param -> Geo.P2D.t -> Geo.P2D.t -> float
    val h : user_param -> Geo.P2D.t -> float
    val next : user_param -> Geo.P2D.t -> Geo.P2D.t list
    val do_at_insertion : user_param -> 'b -> 'c -> unit
    val do_at_extraction : user_param -> (float, Geo.P2D.t) Pqueue.t -> Geo.P2D.t Memory.t -> Geo.P2D.t -> unit
  end


module MyAstar : (A_star.Astar with type state= MyModel.state and type user_param= MyModel.user_param)

