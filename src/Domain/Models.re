type column = {title: string};
type columns = array(column);

type row = {
  title: string,
  id: int,
};
type rows = array(row);

type entry = {
  entryType: string,
  from: int,
  to_: int,
};