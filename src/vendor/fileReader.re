type t;

[@bs.send] external readAsArrayBuffer : (t, Blob.t) => unit = "readAsArrayBuffer";

[@bs.send] external readAsBinaryString : (t, Blob.t) => unit = "readAsBinaryString";

[@bs.set] external onload : (t, unit => unit) => unit = "onload";

[@bs.get] external result : t => Js.Typed_array.array_buffer = "result";

[@bs.get] external resultAsString : t => string = "result";

[@bs.new] external create : unit => t = "FileReader";
