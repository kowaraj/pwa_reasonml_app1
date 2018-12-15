let str = ReasonReact.string;

type item = {
  title: string,
  completed: bool
};

module ToDoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, children) => {
    ...component,
    render: (self) =>
      <div className="item">
        <input
          type_="checkbox"
          checked=(item.completed)
          /* TODO make interactive */
        />
        (str(item.title))
      </div>
  };
};

type state = {
  items: list(item)
};

type action =
  | AddItem;

let component = ReasonReact.reducerComponent("ToDoApp2");

let newItem = () => {title: "just a new item", completed: false};

let make = (children) => {
  ...component,
  initialState: () => {
    items: [
        {title: "Write some things to do", completed: false}
    ]
  },
  reducer: ( action, state ) => {
    switch (action) {
      | AddItem =>  ReasonReact.Update({items: [newItem(), ...state.items]})
    }
  },
  
  render: (self) => {
    let numItems = List.length(self.state.items);
    <div className="app">
      <div className="title">  (str("What to do 2")) </div>

      <button
          onClick=((e) => self.send(AddItem)) >
          (str("Add something"))
      </button>

      <div className="items">
          (ReasonReact.array(
            Array.of_list(
              List.map( (item) => <ToDoItem item />,   self.state.items))))

      </div>
      
      
      <div className="footer"> (str(string_of_int(numItems) ++ " items"))      </div>
    </div>
  }
};
