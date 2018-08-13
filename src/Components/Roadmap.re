open Models;
open Helpers;

module MonthHeaders = {
  let c = ReasonReact.statelessComponent("MonthHeaderds");
  let make = (~months: array(string), _children) => {
    ...c,
    render: _self =>
      <thead className="roadmap--months">
        <tr> <th /> (mapC(m => <th key=m> (str(m)) </th>, months)) </tr>
      </thead>,
  };
};

module Events = {
  let c = ReasonReact.statelessComponent("Event");
  let make =
      (
        ~events: array(event),
        ~color: string="grey",
        ~fontColor="black",
        ~selectEvent,
        _children,
      ) => {
    let generateGradient = (color: string, percentage: int) =>
      "linear-gradient(
      to right,
      green, green "
      ++ str_i(percentage)
      ++ "%, "
      ++ color
      ++ " "
      ++ str_i(percentage)
      ++ "%, "
      ++ color
      ++ ")";

    let generateStyle = (e: event, index: int) =>
      ReactDOMRe.Style.make(
        ~left=px(217 + e.from * 50),
        ~width=px(e.to_ * 50 - 1),
        ~marginTop=px(7 + index * 37),
        ~height=px(30),
        ~backgroundColor=Belt.Option.getWithDefault(e.color, color),
        ~backgroundImage=
          generateGradient(
            Belt.Option.getWithDefault(e.color, color),
            e.percentageComplete,
          ),
        ~color=Belt.Option.getWithDefault(e.fontColor, fontColor),
        (),
      );

    {
      ...c,
      render: _self =>
        mapI(
          (i, e) =>
            <div
              key=(str_i(i))
              className="event"
              style=(generateStyle(e, i))
              onClick=(_ => selectEvent(e))>
              <span className="title"> (str(e.title)) </span>
            </div>,
          events,
        ),
    };
  };
};

module Lanes = {
  let c = ReasonReact.statelessComponent("Lanes");
  let make =
      (
        ~lanes: array(lane),
        ~events: array(event),
        ~months: array(string),
        ~selectEvent,
        _children,
      ) => {
    let getSubEvents = lane =>
      filter((e: event) => e.laneId == lane.id, events);
    {
      ...c,
      render: _self =>
        mapC(
          lane => {
            let subEvents = getSubEvents(lane);

            <tr key=lane.title>
              <td>
                <div
                  className="title"
                  style=(
                    ReactDOMRe.Style.make(
                      ~height=px(Array.length(subEvents) * 35),
                      (),
                    )
                  )>
                  <span> (str(lane.title)) </span>
                </div>
              </td>
              (mapC(m => <td key=m />, months))
              <Events
                events=subEvents
                color=lane.color
                fontColor=lane.fontColor
                selectEvent=(event => selectEvent(event))
              />
            </tr>;
          },
          lanes,
        ),
    };
  };
};

let component = ReasonReact.statelessComponent("Roadmap");
let make = (~roadmap: roadmap, ~selectEvent, _children) => {
  ...component,
  render: _self =>
    <table className="roadmap" onScroll=(e => Js.log(e))>
      <MonthHeaders months=roadmap.months />
      <tbody>
        <Lanes
          lanes=roadmap.lanes
          events=roadmap.events
          months=roadmap.months
          selectEvent
        />
      </tbody>
    </table>,
};