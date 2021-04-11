let tickTimeInMs = 10;

let msInSec = 1000;

let seconds = 3;

let rest = msInSec / tickTimeInMs;

type action =
  | Tick; /* The component's state type. It can be anything, including, commonly, being a record type */

type state = {
  total: int,
  timerId: ref(option(Js.Global.intervalId))
};

let component = ReasonReact.reducerComponent("CountDown");

let make = (~onCompleted, ~seconds=seconds, _children) => {
  ...component,
  initialState: () => {total: seconds * rest * tickTimeInMs, timerId: ref(None)},
  reducer: (action, state) =>
    switch action {
    | Tick =>
      if (state.total <= 0) {
        switch state.timerId^ {
        | Some((id)) => Js.Global.clearInterval(id)
        | _ => ()
        };
        onCompleted();
        ReasonReact.NoUpdate;
      } else {
        ReasonReact.Update({...state, total: state.total - tickTimeInMs});
      }
    },
  didMount: (self) => {
    :=(self.state.timerId, Some(Js.Global.setInterval(self.reduce((_) => Tick), tickTimeInMs)));
    ReasonReact.NoUpdate;
  },
  willUnmount: (self) =>
    switch self.state.timerId^ {
    | Some((id)) => Js.Global.clearInterval(id)
    | _ => ()
    },
  render: ({state: {total}}) => {
    let seconds = total / 1000; /* let percentage = float_of_int (total / 100) /. 100.0; */
    let timesMessage = seconds == 1 ? "second" : "seconds";
    let text = {j|$seconds $timesMessage|j};
    <div className="countdown">
      <p className="countdown__tagline"> (React.string("Starting in...")) </p>
      <h1 className="countdown__text"> (React.string(text)) </h1>
    </div>;
  }
};
