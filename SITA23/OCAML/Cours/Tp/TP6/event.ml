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

let is_start event =
  match event.kind with
  | Start -> true
  | End -> false

let id event = event.id

let compare_kind k1 k2 =
  match (k1, k2) with
  | Start, End -> 1
  | End, Start -> -1
  | _ -> 0

let compare e1 e2 =
  let date_cmp = compare e1.date e2.date in
  if date_cmp <> 0 then date_cmp
  else compare_kind e1.kind e2.kind

  module Task = struct
    type t = {
      id: int;
      start_date: int;
      end_date: int;
    }

    let fold f init tasks =
      List.fold_left (fun acc task -> f task acc) init tasks
  end

  let tasks2events tasks =
    let add_task_events task events =
      let start_event = { id = task.id; date = task.start_date; kind = Start } in
      let end_event = { id = task.id; date = task.end_date; kind = End } in
      start_event :: end_event :: events
    in
    let events = Task.fold add_task_events [] tasks in
    List.sort compare events

let () =
  let tasks = [
    { Task.id = 1; start_date = 1; end_date = 3 };
    { Task.id = 2; start_date = 2; end_date = 4 };
    { Task.id = 3; start_date = 3; end_date = 5 };
  ] in
  let events = tasks2events tasks in
  List.iter (fprint stdout) events
