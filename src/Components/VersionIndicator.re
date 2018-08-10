[@bs.module] external package : Js.t({..}) = "./../../package.json";

let contentStaticComponent =
  ReasonReact.statelessComponent("VersionIndicator");

let make = _children => {
  ...contentStaticComponent,
  render: _self =>
    <div className="version-indicator">
      (ReasonReact.string("version: " ++ package##version))
    </div>,
};