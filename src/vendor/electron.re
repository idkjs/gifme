module IpcRenderer = {
  type t;
  [@bs.scope "ipcRenderer"] [@bs.module "electron"] external ipcRenderer : t = "";
  [@bs.scope "ipcRenderer"] [@bs.module "electron"] [@bs.val]
  external send : (string, string) => unit = "";
  [@bs.scope "ipcRenderer"] [@bs.module "electron"] [@bs.val]
  external sendBuffer : (string, Js.Typed_array.array_buffer) => unit = "send";
  [@bs.scope "ipcRenderer"] [@bs.module "electron"] [@bs.val]
  external on : (string, (unit, string) => unit) => unit = "";
};
