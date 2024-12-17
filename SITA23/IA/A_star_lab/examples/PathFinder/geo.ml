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

module P2D =
  struct
    type t= { x:float; y:float }  

    let fprint outchan pt = Printf.fprintf outchan "%f %f\n" pt.x pt.y
    let to_string p = Printf.sprintf "%.2f %.2f" p.x p.y

(*    let make x y = {x=x;y=y} *)
      
    let distance a b =
      let dx= b.x-.a.x and dy= b.y-.a.y in
      sqrt (dx*.dx+.dy*.dy)
  end

module Rectangle =
  struct
    type t= { ll: P2D.t;  (* Lower left point *)
              ur: P2D.t } (* Upper right point *)

    let inside r p =
      p.P2D.x >= r.ll.P2D.x
    && p.P2D.x <= r.ur.P2D.x
    && p.P2D.y >= r.ll.P2D.y
    && p.P2D.y <= r.ur.P2D.y
  end

module Circle =
  struct
    type t = {center : P2D.t ; radius : float}

    let inside c p = P2D.distance c.center p <= c.radius
  end    
