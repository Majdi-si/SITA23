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

  let is_goal (_,pb) u = 
    Geo.P2D.(u.x = pb.Problem.dest.x && u.y = pb.Problem.dest.y)

  let k _ u v =
    let open Geo.P2D in
    let dx = u.x -. v.x in
    let dy = u.y -. v.y in
    sqrt (dx *. dx +. dy *. dy)

  let h (_,pb) u =
    let open Geo.P2D in
    let dx = u.x -. pb.Problem.dest.x in
    let dy = u.y -. pb.Problem.dest.y in
    2. *. sqrt (dx *. dx +. dy *. dy)

  let check_constraints pb v =
    Problem.inside_domain pb v && Problem.outside_obstacles pb v

  let next (_,pb) {Geo.P2D.x=x; y} = 
    let l = ref [] in
    let add (dx, dy) =
      let v = { Geo.P2D.x = x +. dx; y = y +. dy } in
      if check_constraints pb v then l := v :: !l
    in
    List.iter add [(1., 0.); (0., 1.); (-1., 0.); (0., -1.); (1., 1.); (1., -1.); (-1., 1.); (-1., -1.)];
    !l

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
