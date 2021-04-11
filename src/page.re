

type action =
  | SetImage(string)
  | UploadImage(string)
  | SetVideos(array(string))
  | RemoveImage
  | ToggleExpand; /* The component's state type. It can be anything, including, commonly, being a record type */

type state = {
  image: option(string),
  existingVideos: array(string),
  isExpanded: bool
};


let uploadImage = (img, _self) => UploadImage(img);

let ipcSend = Electron.IpcRenderer.send;

let ipcOn = Electron.IpcRenderer.on;


let sendCommand = (command, _e) => ipcSend(command, "foo");

[@bs.module "path"] external extname : string => string = "extname";

let getVideos = () =>
  Node_fs.readdirSync(StoreFile.storeDir)
  |> Array.to_list
  |> List.filter((f) => extname(f) == ".webm")
  |> List.map((x) => Node_path.join([|StoreFile.storeDir, x|]))
  |> Array.of_list;
let initialState = {image: None, isExpanded: false, existingVideos: [||]};

let reducer = (state, action) =>
    switch action {
    | SetVideos( existingVideos )=>
      {
        ...state,
       existingVideos
      }
    | UploadImage( str )=>
      {
        ...state,
        image: Some (str),
        existingVideos: Array.append([|str|], state.existingVideos)
      }
    | SetImage(str) => {...state, image: Some (str)}
    | RemoveImage => {...state, image: None}
    | ToggleExpand =>{
      sendCommand( "expand-window")|>ignore;
        {...state, isExpanded: !state.isExpanded}}
    };
 [@react.component]
let make =() => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

 React.useEffect0(()=>{
    let existingVideos = getVideos();
  dispatch(SetVideos(existingVideos))|>ignore;
    let image = ipcOn("capture-taken");

    let _ = dispatch(UploadImage(image));
    None
 });

    let stop = ()=>dispatch(RemoveImage);
    let className=( a) => a ++ " " ++ (state.isExpanded ? a ++ "--open" : a ++ "-closed");
    <div className="app">
      (
        switch state.image {
        | Some (img) => <DelayUploadButton filename=img onCompleted=stop onCancelled=stop />
        | None =>
          <div className="start">
            <button className="start__button" onClick={_=>sendCommand("open-capture")|>ignore}>
              {React.string ({js|＋|js})}
            </button>
            <div className="channelSelect">
              <button
                className="channelSelect__button" onClick={_=>dispatch(ToggleExpand)}>
                {React.string ("#general")}
                <span className="channelSelect__chevron">
                {React.string ({js|▾|js})}
                </span>
              </button>
            </div>
          </div>
        }
      )
      <div className="addModule__channelList" />
      <ListVideos
        onVideoSelect={img=>dispatch(SetImage(img))}
        videos=state.existingVideos
      />
    </div>
};
