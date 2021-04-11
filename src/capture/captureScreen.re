type recordStatus =
  | BeforeRecord
  | CountdownRecord
  | IsRecording
  | DoneRecording;

type state = {
  stream: option(Navigator.mediaStream),
  recordStream: option(MediaRecorder.t),
  status: recordStatus,
  chunk: option(Blob.t)
};

type action =
  | RecordingFinished
  | SetStream(Navigator.mediaStream, MediaRecorder.t)
  | SetStatus(recordStatus)
  | Reset
  | UpdateChunks(Blob.t);
let reducer = (state, action) =>
  switch action {
  | Reset => {...state, chunk: None, status: BeforeRecord}
  | RecordingFinished =>
    ReasonReact.SideEffects(
      (
        (self) =>
          switch state.recordStream {
          | Some((s)) => MediaRecorder.stop(s)
          | _ => ()
          }
      )
    )
  | UpdateChunks(chunk) => {...state, chunk: Some(chunk)}
  | SetStream(stream, m) =>
    {...state, recordStream: Some(m), stream: Some(stream)}
  | SetStatus(status) =>
    WithSideEffects(
      {...state, status},
      (
        (self) =>
          switch (status, state.recordStream) {
          | (IsRecording, Some((s))) => MediaRecorder.start(s)
          | _ => ()
          }
      )
    )
  };


let capturedButton = onClick =>
  <button onClick className="capture__record"> {React.string ({js|◉|js})} </button>;

let id = (i)  => i;
let initialState ={status: BeforeRecord, recordStream: None, stream: None, chunk: None};
[@react.component]
let make = (~onComplete)  => {
let (state, dispatch ) = React.useReducer(reducer,initialState);
    let r = (a) => id (a);
    let reset = r (Reset);
    let onData = d => r(UpdateChunks(d));
    let onStop = r (SetStatus (DoneRecording));
    let stopRecording = r (RecordingFinished);
    let onCountDownDone = r (SetStatus (IsRecording));
    let startRecording = r (SetStatus (CountdownRecord));
    let onStreamReady = (stream ,m) => r(SetStream(stream(m)));
    switch state.status {
    | DoneRecording =>
      switch state.chunk {
      | Some (chunk) => <PreviewConfirm chunk onComplete onCancel=reset />
      | _ => <h1>{React.string( "Nope")} </h1>
      }
    | status =>
      <div>
        <VideoStream onData onStop onStreamReady />
        (
          switch status {
          | BeforeRecord => capturedButton(startRecording)
          | CountdownRecord =>
            <div className="capture__countdown"> <Countdown onCompleted=onCountDownDone /> </div>
          | IsRecording =>
            <div className="capture__isRecording">
              <button className="capture__stopButton" onClick=stopRecording>
                {React.string ({js|▣|js})}
              </button>
            </div>
          | _ => <div />
          }
        )
      </div>
    }
};
