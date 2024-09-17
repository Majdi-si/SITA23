open OUnit2
open Cours

let test_eval _ =
  let expr1 = Or (And (Var "x", Var "y"), Or (Var "z", False)) in
  let env1 = [("x", true); ("y", false); ("z", true)] in
  let env2 = [("x", true); ("y", false); ("z", false)] in
  assert_equal (eval expr1 env1) true;
  assert_equal (eval expr1 env2) false

let suite =
  "TestSuite" >::: [
    "test_eval" >:: test_eval;
  ]

let () =
  run_test_tt_main suite