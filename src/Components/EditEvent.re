open Models;
open Helpers;

let d = Belt.Option.getWithDefault;
let getValueFromEvent = evt : string => (
                                          evt
                                          |> ReactEventRe.Form.target
                                          |> ReactDOMRe.domElementToObj
                                        )##value;
let getIntValueFromEvent = evt : int =>
  int_of_string(
    (evt |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj)##value,
  );
module EditEventContent = {
  let component = ReasonReact.statelessComponent("EditEventContent");

  let make =
      (
        ~event: event,
        ~updateTitle,
        ~updatePercentageComplete,
        ~updateFrom,
        ~updateTo,
        ~updateLane,
        ~lanes,
        _children,
      ) => {
    ...component,
    render: _self => {
      let laneOptions =
        ReasonReact.array(
          Array.map(
            lane =>
              <option key=lane.id value=lane.id> (str(lane.title)) </option>,
            lanes,
          ),
        );
      <div className="form">
        <div className="field">
          <label> (str("Lane")) </label>
          <select
            value=event.laneId
            onChange=(e => updateLane(getValueFromEvent(e)))>
            laneOptions
          </select>
        </div>
        <div className="field">
          <label> (str("Title")) </label>
          <input
            value=event.title
            onChange=(e => updateTitle(getValueFromEvent(e)))
          />
        </div>
        <div className="field">
          <label> (str("From")) </label>
          <input
            _type="number"
            value=(str_i(event.from))
            onChange=(e => updateFrom(getIntValueFromEvent(e)))
          />
        </div>
        <div className="field">
          <label> (str("To")) </label>
          <input
            _type="number"
            min=1
            value=(str_i(event.to_))
            onChange=(e => updateTo(getIntValueFromEvent(e)))
          />
        </div>
        <div className="field">
          <label> (str("(%) Complete")) </label>
          <input
            _type="number"
            step=10.0
            value=(str_i(event.percentageComplete))
            onChange=(e => updatePercentageComplete(getIntValueFromEvent(e)))
          />
        </div>
      </div>;
    },
  };
};

type action =
  | UpdateTitle(string)
  | UpdatePercentageComplete(int)
  | UpdateFrom(int)
  | UpdateTo(int)
  | UpdateLane(string)
  | Nothing;
type state = event;
let reducer = (action, state: state) =>
  switch (action) {
  | UpdateTitle(s) => ReasonReact.Update({...state, title: s})
  | UpdatePercentageComplete(i) =>
    ReasonReact.Update({...state, percentageComplete: i})
  | UpdateFrom(i) => ReasonReact.Update({...state, from: i})
  | UpdateTo(i) => ReasonReact.Update({...state, to_: i > 0 ? i : 1})
  | UpdateLane(laneId) => ReasonReact.Update({...state, laneId})
  | _ => ReasonReact.Update(state)
  };
let defaultEvent = {
  id: "-1",
  laneId: "-1",
  title: "",
  from: 0,
  to_: 1,
  percentageComplete: 0,
  color: None,
  fontColor: None,
};

Random.init(int_of_float(Js.Date.now()));
let getDefaultEvent = laneId => {
  ...defaultEvent,
  id: string_of_int(Random.int(1000000)),
  laneId,
};

let component = ReasonReact.reducerComponent("EditEvent");
let make =
    (~shown, ~cancel, ~event: option(event), ~lanes, ~submit, _children) => {
  ...component,
  initialState: _ =>
    switch (event) {
    | None => getDefaultEvent(lanes[0].id)
    | Some(event) =>
      event.laneId == "-1" ? {...event, laneId: lanes[0].id} : event
    },
  willReceiveProps: _ =>
    switch (event) {
    | None => getDefaultEvent(lanes[0].id)
    | Some(event) =>
      event.laneId == "-1" ? {...event, laneId: lanes[0].id} : event
    },
  reducer,
  render: _self =>
    <Dialog
      title="Edit Event"
      shown
      cancel=(_ => cancel())
      submit=(
        t =>
          if (String.length(_self.state.title) > 0) {
            submit(_self.state);
          }
      )>
      ...<EditEventContent
           event=_self.state
           updateTitle=(v => _self.send(UpdateTitle(v)))
           updateFrom=(v => _self.send(UpdateFrom(v)))
           updateTo=(v => _self.send(UpdateTo(v)))
           updatePercentageComplete=(
             v => _self.send(UpdatePercentageComplete(v))
           )
           updateLane=(v => _self.send(UpdateLane(v)))
           lanes
         />
    </Dialog>,
};