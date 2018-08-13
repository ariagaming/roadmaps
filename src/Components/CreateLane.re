open Models;
open Helpers;

let d = Belt.Option.getWithDefault;
let getValueFromEvent = evt : string => (
                                          evt
                                          |> ReactEventRe.Form.target
                                          |> ReactDOMRe.domElementToObj
                                        )##value;
module CreateLaneContent = {
  let component = ReasonReact.statelessComponent("CreateLaneContent");

  let make =
      (
        ~lane: lane,
        ~updateTitle,
        ~updateOrder,
        ~updateBackground,
        ~updateColor,
        _children,
      ) => {
    ...component,
    render: _self =>
      <div className="form">
        <div className="field">
          <label> (str("Title")) </label>
          <input
            value=lane.title
            onChange=(e => updateTitle(getValueFromEvent(e)))
          />
        </div>
        <div className="field">
          <label> (str("Order")) </label>
          <input
            _type="number"
            value=(str_i(lane.order))
            onChange=(e => updateOrder(int_of_string(getValueFromEvent(e))))
          />
        </div>
        <div className="field">
          <label> (str("Background Color")) </label>
          <input
            _type="color"
            value=lane.color
            onChange=(e => updateBackground(getValueFromEvent(e)))
          />
        </div>
        <div className="field">
          <label> (str("Font Color")) </label>
          <input
            _type="color"
            value=lane.fontColor
            onChange=(e => updateColor(getValueFromEvent(e)))
          />
        </div>
      </div>,
  };
};

type action =
  | UpdateTitle(string)
  | UpdateOrder(int)
  | UpdateBackground(string)
  | UpdateColor(string)
  | Nothing;
type state = lane;
let reducer = (action, state) =>
  switch (action) {
  | UpdateTitle(s) => ReasonReact.Update({...state, title: s})
  | UpdateOrder(i) => ReasonReact.Update({...state, order: i})
  | UpdateBackground(i) => ReasonReact.Update({...state, color: i})
  | UpdateColor(i) => ReasonReact.Update({...state, fontColor: i})
  | _ => ReasonReact.Update(state)
  };

Random.init(int_of_float(Js.Date.now()));
let defaultLane = {
  id: "-1",
  title: "",
  order: (-1),
  color: "maroon",
  fontColor: "white",
};

let component = ReasonReact.reducerComponent("CreateLane");
let make = (~shown, ~cancel, ~submit, _children) => {
  ...component,
  initialState: () => {
    ...defaultLane,
    id: string_of_int(Random.int(1000000)),
  },
  reducer,
  render: _self =>
    <Dialog
      title="Create Lane"
      shown
      cancel=(t => cancel())
      submit=(
        t =>
          if (_self.state.title != "") {
            submit(_self.state);
          }
      )>
      ...<CreateLaneContent
           lane=_self.state
           updateTitle=(v => _self.send(UpdateTitle(v)))
           updateOrder=(v => _self.send(UpdateOrder(v)))
           updateBackground=(v => _self.send(UpdateBackground(v)))
           updateColor=(v => _self.send(UpdateColor(v)))
         />
    </Dialog>,
};