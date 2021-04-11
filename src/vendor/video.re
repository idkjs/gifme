// open WebApi;
[@bs.set] external setSrcObject : (Dom.element, Navigator.mediaStream) => unit = "srcObject";

[@bs.set] external setSrcObjectString : (Dom.element, string) => unit = "srcObject";

[@bs.set] external onLoaded : (Dom.element, unit => unit) => unit = "onloadedmetadata";

[@bs.send] external play : Dom.element => unit = "play";

[@bs.send] external pause : Dom.element => unit = "pause";
