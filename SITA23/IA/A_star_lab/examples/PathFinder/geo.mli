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

(** Modules describing geometric types and functions *)

module P2D :
  sig
    type t = { x : float; y : float; }
    val fprint : out_channel -> t -> unit
    val to_string : t -> string
    val distance : t -> t -> float
  end

module Rectangle :
  sig
    type t = { ll : P2D.t; ur : P2D.t; }
    val inside : t -> P2D.t -> bool
  end

module Circle :
  sig
    type t = { center : P2D.t; radius : float; }
    val inside : t -> P2D.t -> bool
  end
