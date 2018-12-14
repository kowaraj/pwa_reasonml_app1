let component = ReasonReact.statelessComponent("ToDoApp");
let str = ReasonReact.string;

type item = {
  title: string,
  completed: bool
};

type state = {
  items: list(item)
};
  
let make = _children => {
  ...component,
  render: _self =>
    <div className="app">
      <div className="title">
        (str("What to do"))
      </div>
      <div className="items">
        (str("Nothing"))
      </div>
    </div>

};
