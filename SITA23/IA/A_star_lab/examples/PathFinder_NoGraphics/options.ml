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

(*-----------------*)
(* Program options *)

let slowmotion= ref false
let sleeptime= ref 0.05
let display= ref true

let options= [
  ("-s",Arg.Set slowmotion, "slow motion");
  ("-t",Arg.Set_float sleeptime, "time between slow motion steps");
  ("-nd",Arg.Clear display, "no graphic display")
(*  ("-m",Arg.Set manhattan, "use Manhattan distance. Horizontal and vertical moves only") *)
]

let anonymous_fun= fun s -> failwith (Printf.sprintf "There should be no anonymous arguments: %s" s)

let usage_msg= "./test [options]"

