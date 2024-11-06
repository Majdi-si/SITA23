type task = {
    id : int;
    start: int;
    endt : int;
}

let fprint_task out_channel task =
  Printf.fprintf out_channel "%d %d %d" task.id task.start task.endt

let make = fun id start endt -> {id; start; endt}

module TS = Set.Make(struct
  type t = task
  let compare task1 task2 = compare task1.id task2.id
end)

type t = TS.t
let fold = TS.fold


(* begin provided *)
let input_line_option = fun chin ->
  try Some (input_line chin) with End_of_file -> None

let read = fun file ->
  let chin = open_in file in
  let rec loop = fun tasks ->
    match input_line_option chin with
      None -> tasks
    | Some line ->
        let task = Scanf.sscanf line "%d %d %d" make in
        loop (TS.add task tasks) in
  let triplets = loop TS.empty in
  close_in chin;
  triplets

let fprint = fun chout tasks ->
  TS.iter (fun task -> Printf.fprintf chout "%a\n" fprint_task task) tasks
(* end provided *)

let () = 
  let tasks = read "tasks.txt" in
  fprint stdout tasks