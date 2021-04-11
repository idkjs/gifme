// open Webapi;
let window: Dom.element = [%bs.raw "window"];

[@bs.val] external createElement : string => Dom.element = "document.createElement";

[@bs.val] external appendChild : Dom.element => Dom.element = "document.body.appendChild";

[@bs.send]
external addEventListener : (Dom.element, string, unit => unit) => unit = "addEventListener";

[@bs.send]
external removeEventListener : (Dom.element, string, unit => unit) => unit = "removeEventListener";

[@bs.get] external getWidth : Dom.element => int = "innerWidth";

[@bs.get] external getHeight : Dom.element => int = "innerHeight";

[@bs.set] external setWidth : (Dom.element, int) => unit = "width";

[@bs.set] external setHeight : (Dom.element, int) => unit = "height";

[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";
