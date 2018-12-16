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

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

module Input = {
  type state = string;
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    reducer: (newText, _text) => ReasonReact.Update(newText),
    render: ({state: text, send}) =>
      <input
        value=text
        type_="text"
        placeholder="Write something to do"
        onChange=((evt) => send(valueFromEvent(evt)))
        onKeyDown=((evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            send("")
          }
        )
      />
  }
};
  
type state = {
  items: list(item)
};

type action =
  | AddItem(string)
  | ToggleItem(int);

let component = ReasonReact.reducerComponent("ToDoApp2");

let lastId = ref(0);
let newItem = (text) => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, completed: false}
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
      | AddItem(text) =>  ReasonReact.Update({items: [newItem(text), ...items]})
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
      <div className="title">
          (str("What to do 2"))
          <Input onSubmit=((text) => self.send(AddItem(text))) />            
      </div>

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
      
      <div className="footer"> (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};
