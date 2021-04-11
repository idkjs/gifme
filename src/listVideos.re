module VideoItem = {
  type state = {
    videoRef: ref(option(Dom.element)),
    isPlaying: bool
  };
  type actions =
    | Play
    | Stop;
 let playVideo = (video, _) =>
    switch video^ {
    | None => ()
    | Some((r)) => Video.play(r)
    };
  let stopVideo = (video, _) =>
    switch video^ {
    | None => ()
    | Some((r)) => Video.pause(r)
    };

    let initialState = {videoRef: ref(None), isPlaying: false};
    [@react.component]
  let make = (~video, ~onVideoSelect) => {
let (state,dispatch)= React.useReducer((state, action) =>
      switch action {
      | Play =>
      playVideo(state.videoRef)|>ignore;
        {...state, isPlaying: true}
      | Stop =>
       stopVideo(state.videoRef)|>ignore;
     {...state, isPlaying: false}
      },initialState) ;

  let setSectionRef = ref(Js.Nullable.null);

    React.useEffect0(()=>{
       switch state.videoRef^ {
      | None => ()
      | Some((r)) =>
        Document.addEventListener(r, "mouseover", dispatch(Play))|>ignore;
        Document.addEventListener(r, "mouseout", dispatch(Stop))|>ignore;
      };
   None
    });

      let onClick = (_) => onVideoSelect(video);
      <div className="videoItem" onClick>
        <video
          ref={setSectionRef}
          loop=true
          className="videoItem__video"
          src=video
        />
      </div>;
    }
};

[@react.component]
let make = (~videos, ~onVideoSelect) => {

    <div className="videoList">
{videos
        |> Array.map((video) => <VideoItem onVideoSelect video key=video />)
        |> React.array}
    </div>
};
