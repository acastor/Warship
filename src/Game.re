[%bs.raw {|require('./game.css')|}];

open SharedTypes;

let initialGameState = () => {
  humanBoard: Array.make_matrix(10, 10, Empty),
  aiBoard: Array.make_matrix(10, 10, Empty),
  gameState: Playing(Human),
};

[@react.component]
let make = () => {
  let (state, updateState) = React.useState(initialGameState);

  <div className="game-container">
    <h2 className="board-title"> {ReasonReact.string("Warship")} </h2>
    <Board state boardOwner=Human boardArray={state.humanBoard} />
    <Board state boardOwner=AI boardArray={state.aiBoard} />
  </div>;
};
