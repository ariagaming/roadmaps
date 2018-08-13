open Models;
open Helpers;

type action =
  | CreateLane(lane)
  | ToggleCreateLaneDialog
  | ToggleEditEvent(option(event))
  | UpdateEvent(event)
  | Nothing;

type appState = {
  roadmap,
  version: string,
  lane: option(lane),
  event: option(event),
  showLaneDialog: bool,
  showEventDialog: bool,
};

let initialState = () : appState => {
  roadmap: Defaults.roadmap,
  version: "0.0.0",
  lane: None,
  event: None,
  showLaneDialog: false,
  showEventDialog: false,
};

let insertOrUpdate = (as_: array(event), a: event) => {
  let index = ref(-1);
  let r =
    Belt.Array.mapWithIndex(as_, (i, _a) =>
      if (a.id == _a.id) {
        index := i;
        a;
      } else {
        _a;
      }
    );

  if (index > ref(-1)) {
    r;
  } else {
    Array.append(r, [|a|]);
  };
};

let reducer = (action: action, state: appState) =>
  switch (action) {
  | CreateLane(lane) =>
    ReasonReact.Update({
      ...state,
      showLaneDialog: false,
      roadmap: {
        ...state.roadmap,
        lanes: Array.append(state.roadmap.lanes, [|lane|]),
      },
    })

  | ToggleCreateLaneDialog =>
    ReasonReact.Update({...state, showLaneDialog: ! state.showLaneDialog})
  | ToggleEditEvent(optionEvent) =>
    switch (optionEvent) {
    | None =>
      ReasonReact.Update({...state, showEventDialog: false, event: None})
    | Some(_) =>
      ReasonReact.Update({
        ...state,
        showEventDialog: true,
        event: optionEvent,
      })
    }
  | UpdateEvent(event) =>
    let newEvents = insertOrUpdate(state.roadmap.events, event);
    Js.log(newEvents);
    ReasonReact.Update({
      ...state,
      showEventDialog: false,
      roadmap: {
        ...state.roadmap,
        events: newEvents,
      },
    });
  | _ => ReasonReact.Update(state)
  };

let component = ReasonReact.reducerComponent("App");
let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <div className="app" onTouchMove=(e => Js.log(e))>
      <div className="menu">
        <div
          className="menu--item"
          onClick=(_ => self.send(ToggleCreateLaneDialog))>
          (str("Create Lane"))
        </div>
        <div
          className="menu--item"
          onClick=(
            _ => self.send(ToggleEditEvent(Some(EditEvent.defaultEvent)))
          )>
          (str("Create Event"))
        </div>
      </div>
      <Roadmap
        roadmap=self.state.roadmap
        selectEvent=(p => self.send(ToggleEditEvent(Some(p))))
      />
      <VersionIndicator />
      <CreateLane
        shown=self.state.showLaneDialog
        cancel=(t => self.send(ToggleCreateLaneDialog))
        submit=(lane => self.send(CreateLane(lane)))
      />
      <EditEvent
        shown=self.state.showEventDialog
        event=self.state.event
        lanes=self.state.roadmap.lanes
        cancel=(t => self.send(ToggleEditEvent(None)))
        submit=(event => self.send(UpdateEvent(event)))
      />
    </div>,
};