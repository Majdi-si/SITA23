type expression =
  | Entier of int
  | Variable of string
  | Division of expression * expression

let expr = Division (Entier 360, Variable "ne")

type instruction = 
  | Right of expression
  | Forward of expression
  | Repeat of expression * instruction list
  | Bloc of instruction list  

(* exemple : repeat ne [right (360 / ne);
repeat ne [right (360 / ne); forward sz]]*)
let exemple = Repeat (Variable "ne", [Right (Division (Entier 360, Variable "ne")); 
                                     Repeat (Variable "ne", [Right (Division (Entier 360, Variable "ne")); 
                                                            Forward (Variable "sz")])])

let rec eval env = function
  | Entier n -> n
  | Variable v -> List.assoc v env
  | Division (e1, e2) -> 
      let v1 = eval env e1 in
      let v2 = eval env e2 in
      if v2 = 0 then failwith "Division by zero"
      else v1 / v2