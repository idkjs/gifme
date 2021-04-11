[@bs.val] external createObjectURL : 'a => string = "URL.createObjectURL";

[@react.component]
let make =(~chunk, ~onComplete, ~onCancel) => {
    let url = createObjectURL(chunk);

    <div className="capture__doneRecording">
      <video autoPlay=true loop=true src=url />
      <div className="confirmBox">
        <button onClick={ _ => onCancel ()}> {React.string({js|⟲|js})} </button>
        <button onClick={_ => onComplete (chunk)}>
          {React.string ({js|✔|js})}
        </button>
      </div>
    </div>

};
