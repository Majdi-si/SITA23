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

(** Program options (slow motion, display, etc) *)

val slowmotion : bool ref
val sleeptime : float ref
val display : bool ref
val options : (string * Arg.spec * string) list
val anonymous_fun : string -> 'a
val usage_msg : string
