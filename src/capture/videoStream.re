type state = {videoRef: ref(Js.Nullable.t(Dom.element))};

let refreshStream = (stream, videoRef) =>
  switch (stream) {
  | None => ()
  | Some(s) =>
    switch (videoRef^) {
    | None => ()
    | Some(r) =>
      Video.setSrcObject(r, s);
      Video.onLoaded(r, _ => Video.play(r));
    }
  };

[@react.component]
let make = (~onData, ~onStop, ~onStreamReady) => {
  let (state, dispatch) = React.useReducer(_, {videoRef: ref(None)});
  let setSectionRef = ref(Js.Nullable.null);

  let startUserMedia = (onData, onStop, onStreamReady) => {
    let _f =
      Navigator.getUserMedia({"audio": false, "video": Navigator.Bool(true)})
      |> Js.Promise.then_(stream => {
           let m = MediaRecorder.create(stream);
           MediaRecorder.ondataavailable(m, d => onData(d##data));
           MediaRecorder.onstop(m, onStop);
           onStreamReady(stream, m);
           refreshStream(Some(stream), state.videoRef);
           Js.Promise.resolve();
         });
    ();
  };
  React.useEffect0(() => {
    startUserMedia(onData, onStop, onStreamReady) |> ignore;
    None;
  });
  <video ref={dispatch(setSectionRef.current)} />;
};
