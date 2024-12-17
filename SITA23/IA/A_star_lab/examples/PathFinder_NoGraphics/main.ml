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

let main () =
  (* Parse command line *)
  Arg.parse Options.options Options.anonymous_fun Options.usage_msg;
  (* Init path-finding problem *)
  let pb= Problem.init () in
  Problem.print pb [];
  flush stdout;
(*
  (* Open graph *)
  let graph=
    if !Options.display then Draw.open_graph pb
    else {Draw.height=0;width=0} in
 *)
  (* Search shortest path, and display while searching *)
  (*
  try
    let _path = Pathfinder.MyAstar.search (graph,pb) in
    if !Options.display then (
      Draw.events := [Graphics.Button_down;Graphics.Key_pressed];
      Draw.wait !Draw.events;
      Graphics.close_graph () )
  with Exit ->
    if !Options.display then Graphics.close_graph ();;
 *)
  let path = Pathfinder.MyAstar.search pb in
  Printf.printf "\n\n";
  Problem.print pb path
;;

(*---------------------------------*)
(* Appel de la fonction principale *)

main ()
