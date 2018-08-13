let str_i = string_of_int;
let str = ReasonReact.string;

/*
 `mapC` is a helper function which can help you convert a simple array of items
 to a reactElement. Using this function is like using the original JS `map`
 function to iterate over your items.
 */
type mapCType('a) =
  ('a => ReasonReact.reactElement, array('a)) => ReasonReact.reactElement;
let mapC = (f, la) => ReasonReact.array(Array.map(f, la));

type mapIType('a) =
  ('a, int, ReasonReact.reactElement, array('a)) => ReasonReact.reactElement;
let mapI = (f, la) => ReasonReact.array(Belt.Array.mapWithIndex(la, f));

/* Generate the `px` value from an int */
let px = (value: int) => str_i(value) ++ "px";

/** Filter an array */
let filter = (~f, arr: array('a)) =>
  arr |> ArrayLabels.to_list |> ListLabels.filter(~f) |> ArrayLabels.of_list;