let sum_m list = 
  let max_i = ref 0 in
  let max_j = ref 0 in
  let max_sum = ref 0 in
  for i = 0 to (List.length list) - 1 do
    let sum = ref 0 in
    for j = i to (List.length list) - 1 do
      sum := !sum + (List.nth list j);
      if !sum > !max_sum then begin
        max_sum := !sum;
        max_i := i;
        max_j := j
      end
    done;
  done;
  !max_sum, !max_i, !max_j
  
  let () =
    let list = [1; -2; 1; 2; -1; 3; -2; 1] in
    let max_sum, max_i, max_j = sum_m list in
    Printf.printf "Max sum: %d, from index %d to %d\n" max_sum max_i max_j