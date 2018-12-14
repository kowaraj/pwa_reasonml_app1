let str = ReasonReact.string;

type item = {
  title: string,
  completed: bool
};

type state = {
  items: list(item)
};

let component = ReasonReact.reducerComponent("ToDoApp2");
  
let make = (children) => {
  ...component,
  initialState: () => {
    items: [
        {title: "Write some things to do", completed: false}
      ]
    },
  reducer: ( (), _ ) => ReasonReact.NoUpdate,
  
  render: ({state: {items}}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">  (str("What to do 2")) </div>
      <div className="items">  (str("Nothing"))      </div>
      <div className="footer"> (str(string_of_int(numItems) ++ " items"))      </div>
    </div>
  }
};
