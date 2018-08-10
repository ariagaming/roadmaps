open Models;

type action =
  | Nothing;

type appState = {
  rows,
  version: string,
};

let initialState = () : appState => {
  rows: [|{id: 1, title: "Something"}, {id: 2, title: "Other"}|],
  version: "0.0.0",
};

let component = ReasonReact.reducerComponent("App");
let make = _children => {
  ...component,
  initialState,
  reducer: (action: action, state: appState) => ReasonReact.Update(state),
  render: self =>
    <div className="app">
      <Roadmap rows=self.state.rows />
      <VersionIndicator />
    </div>,
};