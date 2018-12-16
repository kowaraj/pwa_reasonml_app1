let str = ReasonReact.string;

type item = {
  id: int,
  title: string,
  completed: bool
};

module ToDoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, ~onToggle, children) => {
    ...component,
    render: (self) =>
      <div className="item" onClick=( (_evt) => onToggle() )>
          
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
  | AddItem
  | ToggleItem(int);

let component = ReasonReact.reducerComponent("ToDoApp2");

let lastId = ref(0);
let newItem = () => {
  lastId := lastId^ + 1;
  {id: lastId^, title: "A new item", completed: false}
};

let make = (children) => {
  ...component,
  initialState: () => {
    items: [
        {id: 0, title: "Write some things to do", completed: false}
    ]
  },
  reducer: ( action, {items} ) => {
    switch (action) {
      | AddItem =>  ReasonReact.Update({items: [newItem(), ...items]})
      | ToggleItem(id) =>
          let items = List.map( (item) => item.id === id ? 
                                            {...item, completed: ! item.completed} :
                                            item,
                                 items);
          ReasonReact.Update({items: items});
    }
  },
  
  render: (self) => {
    let numItems = List.length(self.state.items);
    let onToggle = () => ();
    <div className="app">
      <div className="title">  (str("What to do 2")) </div>

      <button
          onClick=((e) => self.send(AddItem)) >
          (str("Add something"))
      </button>

      <div className="items">
          
          (ReasonReact.array(
            Array.of_list(
              List.map(
              (item) => <ToDoItem
                key=(string_of_int(item.id))
                item
                onToggle=( () => self.send(ToggleItem(item.id)))
                />,   self.state.items))))

      </div>
      
      <div className="footer"> (str(string_of_int(numItems) ++ " items"))      </div>
    </div>
  }
};
