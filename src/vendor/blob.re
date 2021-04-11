type t = {
  .
  "size": int,
  "type_": string
};

type inputType =
  | Array(Js.Array.t(string))
  | Blob(t);

type data = {. "data": string};

[@bs.new] external blob : inputType => t = "Blob";
