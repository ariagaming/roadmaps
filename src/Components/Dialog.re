open Helpers;

let dialogComponent = ReasonReact.statelessComponent("DialogComponent");

let make = (~shown=false, ~title="No title", ~cancel, ~submit, _children) => {
  let cancelHandler = t => cancel(t);
  let submitHandler = t => submit(t);
  {
    ...dialogComponent,
    render: _self =>
      ReasonReact.createDomElement(
        "div",
        ~props={"className": "dialog", "data-shown": shown},
        [|
          <div className="dialog--inner">
            <div className="title"> (ReasonReact.string(title)) </div>
            <div className="dialog-content"> _children </div>
            <div className="footer">
              <button className="btn-submit" onClick=submitHandler>
                (str("Submit"))
              </button>
              <button className="btn-cancel" onClick=cancelHandler>
                (str("Cancel"))
              </button>
            </div>
          </div>,
        |],
      ),
  };
};