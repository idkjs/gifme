type t;

type data = {. "data": Blob.t};

[@bs.new] external create : Navigator.mediaStream => t = "MediaRecorder";

[@bs.send] external start : t => unit = "start";

[@bs.send] external stop : t => unit = "stop";

[@bs.set] external ondataavailable : (t, data => unit) => unit = "ondataavailable";

[@bs.set] external onstop : (t, data => unit) => unit = "onstop";
