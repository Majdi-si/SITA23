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

open Problem

type graph= {
  width: int;
  height: int }

let width= 500
let height= 500
      
let open_graph pb =
  Graphics.open_graph (Printf.sprintf " %dx%d+50-0" width height);
  Graphics.auto_synchronize false;
  Graphics.display_mode false;
  Graphics.remember_mode true;
  {width=width;height=height};;

(*----------------------------------------------*)
(* Scale problem data to fit the graphic window *)

let scale graph pb =
  fun {Geo.P2D.x=x;y=y} ->
    let dx= pb.xmax-.pb.xmin in
    let dy= pb.ymax-.pb.ymin in
    let x_graph= truncate (float graph.width *.(x-.pb.xmin)/.dx)
    and y_graph= truncate (float graph.height *.(y-.pb.ymin)/.dy) in
    (x_graph,y_graph)
      
(*-------------------*)
(* Drawing functions *)
      
let fill_obstacle scale color a =
  match a with
    R {Geo.Rectangle.ll= p1; ur= p2} ->
      let (xmin,ymin)= scale p1 and (xmax,ymax)= scale p2 in
      Graphics.set_color color;
      Graphics.fill_rect xmin ymin (xmax-xmin) (ymax-ymin);
  | C {Geo.Circle.center= c; radius= r} ->
      let xc,yc= scale c in
      let rx,ry= scale {Geo.P2D.x=r;y=r} in
      Graphics.set_color color;
      Graphics.fill_ellipse xc yc rx ry


let fill_node scale color p =
  let r= 3 in
  Graphics.set_color color;
  let (x,y)= scale p in
  Graphics.fill_circle x y r;;

let draw_node scale color p =
  let (x,y)= scale p in
  let r= 3 in
  Graphics.set_color color;
  Graphics.draw_circle x y r;;

let draw_path scale color l =
  Graphics.set_color color;
  let rec loop l =
    match l with
      p::ls ->
	let (x,y)= scale p in
	Graphics.lineto x y;
	loop ls
    | [] -> () in
  match l with
    p0::ls ->
      let (x0,y0)= scale p0 in
      Graphics.moveto x0 y0;
      loop l
  | [] -> ();;

let draw_problem scale color pb =
  List.iter (fill_obstacle scale color) pb.obstacles;
  fill_node scale Graphics.black pb.orig;
  fill_node scale Graphics.black pb.dest

(*---------*)

let sleep n =
  (* Unix.sleep is interupted by Graphics signals *)
  (* Use this function instead: *)
  let start = Unix.gettimeofday() in
  let rec delay t =
    try
      ignore (Unix.select [] [] [] t)
    with Unix.Unix_error(Unix.EINTR, _, _) ->
      let now = Unix.gettimeofday() in
      let remaining = start +. n -. now in
      if remaining > 0.0 then delay remaining in
  delay n
    
(*---------*)

let display scale u path frontier closed problem =
  Graphics.clear_graph ();
  List.iter (draw_node scale Graphics.red) frontier;
  List.iter (draw_node scale Graphics.green) closed;
  draw_path scale Graphics.blue path;
  draw_node scale Graphics.blue u;
  draw_problem scale Graphics.black problem;
  Graphics.synchronize ();;

(*-----------------*)
(* Events handling *)

let events = ref [Graphics.Button_down;Graphics.Key_pressed;Graphics.Poll]

exception Exit

let wait events =
  let status= Graphics.wait_next_event events in
  if status.Graphics.keypressed &&  status.Graphics.key= 'q' then
    raise Exit



