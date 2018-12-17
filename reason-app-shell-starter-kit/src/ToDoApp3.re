let str = ReasonReact.string;

type state = {
  text: string,
  color: string
};

type action =
  | ClickButton1
  | ClickButton2;

let component = ReasonReact.reducerComponent("ToDoApp3");

let make = (children) => {
  ...component,
  initialState: () => {text: "init string", color: "blue"},
  
  reducer: ( action, {text, color}) => switch action {
   | ClickButton1 => ReasonReact.Update({text: "new text 1", color: "red"})
   | ClickButton2 => ReasonReact.Update({text: "new text 2", color: "green"})

  },
  
  render: (self) =>
    <div className="app">

      <div className="title">
        (str("----- test -----"))

      <button
        onClick=((e) => self.send(ClickButton1))>
        (str("THE BUTTON #1"))
      </button>


      <button
        onClick=((e) => self.send(ClickButton2))>
        (str("THE BUTTON #2"))
      </button>

    </div>
          

      <div id="bla" style=(
        ReactDOMRe.Style.make(~backgroundColor=self.state.color, ~fontSize="48px", ()))>
          (str(self.state.text))
      </div>
      
  
    </div>

};
