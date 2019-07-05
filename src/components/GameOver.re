open SharedTypes;

[@react.component]
let make = (~turnState, ~setGameState) => {
  let click = _ => {
    // Reinit the gameState
    setGameState(_ => AppContext.initialState());
  };

  <div className="gameover-container">
    {switch (turnState) {
     //  Playing state should never be valid here.
     | Playing(_) => <div />
     | Winner(Human) =>
       <h1 className="title-color game-title">
         {ReasonReact.string("YOU WON!")}
       </h1>
     | Winner(AI) =>
       <h1 className="title-color game-title">
         {ReasonReact.string("YOU LOST!")}
       </h1>
     }}
    <button id="replay-btn" className="button-xlarge" onClick=click>
      <span className="title-color">
        {ReasonReact.string("Play Again")}
      </span>
    </button>
  </div>;
};
