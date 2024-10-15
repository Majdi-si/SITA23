open Graphics

type expression =
  | Entier of int
  | Variable of string
  | Division of expression * expression

let expr = Division (Entier 360, Variable "ne")


type instruction = 
  | Right of expression
  | Forward of expression
  | Repeat of expression * instruction
  | Bloc of instruction list  

(* exemple : repeat ne [right (360 / ne);
repeat ne [right (360 / ne); forward sz]]*)

let exemple = Repeat (Variable "ne", Bloc [Right (Division (Entier 360, Variable "ne"));
                                        Repeat (Variable "ne", Bloc [Right (Division (Entier 360, Variable "ne"));
                                                                  Forward (Variable "sz")])])

let rec eval env = function
  | Entier n -> n
  | Variable v -> List.assoc v env
  | Division (e1, e2) -> 
      let v1 = eval env e1 in
      let v2 = eval env e2 in
      if v2 = 0 then failwith "Division by zero"
      else v1 / v2


let play env prog =
  let heading = ref 0 in
  let rec play_rec = function
    | Right e ->
        let angle = eval env e in
        heading := (!heading + angle) mod 360
    | Forward e ->
        let distance = eval env e in
        let rad = float_of_int !heading *. (Float.pi /. 180.0) in
        let dx = int_of_float (float_of_int distance *. cos rad) in
        let dy = int_of_float (float_of_int distance *. sin rad) in
        Graphics.rlineto dx dy
    | Repeat (e, instr) ->
        let count = eval env e in
        for _ = 1 to count do
          play_rec instr
        done
    | Bloc instrs ->
        List.iter play_rec instrs
  in
  play_rec prog
  
let () =
  Graphics.open_graph ""; (* open graphic window *)
  Graphics.moveto 300 225; (* current point initialization *)
  let env = [("ne", 36); ("sz", 20)] in
  play env exemple;
  ignore (Graphics.read_key ()) (* wait for a key to be pressed *)