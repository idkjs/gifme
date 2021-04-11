let ipcSendBuffer = Electron.IpcRenderer.sendBuffer;

let ipcSend = Electron.IpcRenderer.send;

let storeFile = (data) => {
  let filename = StoreFile.filename();
  let reader = FileReader.create();
  FileReader.onload(
    reader,
    () => {
      let result = FileReader.resultAsString(reader);
      Node_fs.writeFileSync(filename, result, `binary);
      ();
    }
  );
  FileReader.readAsBinaryString(reader, data);
  filename;
};

let sendCapture = (data) => {
  ipcSend("capture-taken", storeFile(data));
  ();
};

let onClose = (_e) => ipcSend("close-capture", "");


let closeButton = (~onClick) =>
  <button onClick className="capture__close"> {React.string ({js|✖|js})} </button>;
[@react.component]
let make =() => {
 <div> {closeButton(~onClick=onClose)} <CaptureScreen onComplete=sendCapture /> </div>
};
