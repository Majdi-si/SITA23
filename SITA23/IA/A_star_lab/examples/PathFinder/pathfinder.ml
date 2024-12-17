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

module MyModel = struct
  type state= Geo.P2D.t
  type user_param = Draw.graph * Problem.problem

  let initial_state (_,pb) = pb.Problem.orig
                           
  (* !!!!!!   PARTIE A MODIFIER !!!!!! *)
  (* Note: vous pouvez rajouter des fonctions intermédiaires, si besoin,
     par exemple pour vérifier si un point est dans un obstacle ou à
     l'extérieur du domaine. *)
     
  let is_goal (_,pb) u = true

  let k _ u v= 0.

  let h (_,pb) u=  0.

  let next (_,pb) {Geo.P2D.x=x;y}= []
  (* !!!!!!   FIN DE LA PARTIE A MODIFIER !!!!!! *)
      
  let do_at_insertion _pb _ _ = ()
  let do_at_extraction (graph,pb) q memory u =
    let scale= Draw.scale graph pb in
    let p = u in
    let path= Memory.get_path memory p in
    let frontier= Pqueue.elements q in
    if !Options.display then (
      let closed= Memory.closed_list memory in
      Draw.display scale p path frontier closed pb;
      Draw.wait !Draw.events);
    if !Options.slowmotion then Draw.sleep !Options.sleeptime
end

module MyAstar = A_star.Make(MyModel)
