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

type obstacle=
    R of Geo.Rectangle.t
  | C of Geo.Circle.t
      
type problem = {
    xmin:float;xmax:float;ymin:float;ymax:float;
(*    xmin:int;xmax:int;ymin:int;ymax:int; *)
    orig : Geo.P2D.t;
    dest: Geo.P2D.t;
    obstacles : obstacle list }

let obstacle1= 
  let oxmin=4. and oymin=20. and oxmax=40. and oymax=30. in
  let ll= {Geo.P2D.x=oxmin;y=oymin}
  and ur= {Geo.P2D.x=oxmax;y=oymax} in
  R {Geo.Rectangle.ll= ll; ur= ur}

let obstacle2= 
  let oxmin=20. and oymin=5. and oxmax=25. and oymax=30. in
  let ll= {Geo.P2D.x=oxmin;y=oymin}
  and ur= {Geo.P2D.x=oxmax;y=oymax} in
  R {Geo.Rectangle.ll= ll; ur= ur}

let obstacle3=
  let c= {Geo.P2D.x= 40.; y= 35.}
  and r= 3. in
  C {Geo.Circle.center= c; radius= r}

(*------------------------------*)
(* Checking problem constraints *)
  
let inside_domain pb =
  let ll= {Geo.P2D.x= pb.xmin;y=pb.ymin}
  and ur= {Geo.P2D.x= pb.xmax;y=pb.ymax} in
  let dom= {Geo.Rectangle.ll= ll;ur=ur} in
  fun p -> Geo.Rectangle.inside dom p

let outside_obstacles pb p =
  let rec check obstacles =
    match obstacles with
      o::os ->
       (match o with
        | C c -> not (Geo.Circle.inside c p) && check os
        | R r -> not (Geo.Rectangle.inside r p) && check os)
    | [] -> true  in
  check pb.obstacles
  
let check_constraints pb l =
    (* Filtre une liste [l] de points et renvoie la liste des points 
       satisfaisant les contraintes d'appartenance au domaine et
       d'évitement des obstacles définis dans [pb] *)
  let inside_domain = inside_domain pb in
  List.filter (fun p -> inside_domain p && outside_obstacles pb p ) l
  
(*----------*)
(* Printing *)
  
let matrix_of pb path =
  try
    let n= truncate (pb.ymax-.pb.ymin) in
    let p= truncate (pb.xmax-.pb.xmin) in
    let is_location p i j =
      i= truncate p.Geo.P2D.y && j= truncate p.Geo.P2D.x in
    let mat=
      Array.init n
        (fun i ->
          Array.init p
            (fun j ->
              if is_location pb.orig i j then 'O'
              else if is_location pb.dest i j then 'D'
              else
                let p= {Geo.P2D.x= float j +. pb.xmin;y= float i +. pb.ymin} in
                if outside_obstacles pb p then '.' else 'X') ) in
    List.iter
      (fun p ->
        let i= truncate (p.Geo.P2D.y-.pb.ymin)
        and j= truncate (p.Geo.P2D.x-. pb.xmin) in
        if not (is_location pb.orig i j) && not (is_location pb.dest i j) then
          mat.(i).(j)<- 'o' )
      path;
    mat
  with _-> failwith "matrix_of"
  
let print pb path =
  try
    let mat= matrix_of pb path in
    let n= Array.length mat in
    for i= n-1 downto 0 do
      let p= Array.length mat.(i) in
      for j=0 to p-1 do
        Printf.printf "%c" mat.(i).(j)
      done;
      Printf.printf "\n"
    done;
    flush stdout
  with _-> failwith "Problem.print"
  
(*------------------------*)
(* Problem initialization *)

let init () =
  (* grid size *)
  let xmin=0. and ymin=0. and xmax=50. and ymax=50. in
  (* origin and destination coordinates *)
  let xo=8. and yo=10. and xd=40. and yd=40. in
  let orig = {Geo.P2D.x=xo;y=yo} and dest = {Geo.P2D.x=xd;y=yd} in
  (* initialize grid *)
  let obstacles= [obstacle1;obstacle2;obstacle3] in
(*  let obstacles= [] in *)
  { xmin=xmin;ymin=ymin;xmax=xmax;ymax=ymax;
    orig=orig;dest=dest;
    obstacles= obstacles }

