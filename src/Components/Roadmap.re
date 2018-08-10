open Models;

let component = ReasonReact.statelessComponent("Roadmap");

let createHeaderWithColSpan = (colspan: int, message) =>
  ReasonReact.createDomElement(
    "th",
    ~props={"colspan": string_of_int(colspan)},
    [|ReasonReact.string(message)|],
  );

let months = [|"Augustus", "September", "October", "November", "December"|];
let numberOfMonths = Array.length(months);
let monthDevider = 4;

let generateMonthHeaders = () =>
  ReasonReact.array(
    Array.map(
      (month: string) => createHeaderWithColSpan(monthDevider, month),
      months,
    ),
  );

let make = (~rows: rows, _children) => {
  ...component,
  render: _self =>
    <table className="roadmap">
      <thead className="year">
        <tr> <th /> (createHeaderWithColSpan(5, string_of_int(2018))) </tr>
      </thead>
      <thead> <tr> <th /> (generateMonthHeaders()) </tr> </thead>
      <tbody>
        (
          ReasonReact.array(
            Array.map(
              (row: row) =>
                <tr key=(string_of_int(row.id)) className="row">
                  <td> (ReasonReact.string(row.title)) </td>
                </tr>,
              rows,
            ),
          )
        )
      </tbody>
    </table>,
};