type size = {
  .
  "width": int,
  "height": int
};

type sizeOrBool =
  | Size(size)
  | Bool(bool);

type userMediaOptions = {
  .
  "audio": bool,
  "video": sizeOrBool
};

type mediaStream;

[@bs.scope "navigator.mediaDevices"] [@bs.val "getUserMedia"]
external getUserMedia : userMediaOptions => Js.Promise.t(mediaStream) = "";
