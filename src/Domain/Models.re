type column = {title: string};
type columns = array(column);

type row = {
  title: string,
  id: int,
  from: int,
  lng: int,
};
type rows = array(row);

type event = {
  id: string,
  laneId: string,
  title: string,
  from: int,
  to_: int,
  percentageComplete: int,
  color: option(string),
  fontColor: option(string),
};

type lane = {
  id: string,
  title: string,
  order: int,
  color: string,
  fontColor: string,
};

type roadmap = {
  months: array(string),
  lanes: array(lane),
  events: array(event),
};