type kind = 
  | Start
  | End

type t = {
  id: int;
  date: int;
  kind: kind;
}

let fprint oc event =
  let kind_str = match event.kind with
    | Start -> "Start"
    | End -> "End"
  in
  Printf.fprintf oc "Task ID: %d, Date: %d, Kind: %s\n" event.id event.date kind_str