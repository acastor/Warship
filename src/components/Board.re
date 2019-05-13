open SharedTypes;

let getBoardNameClass = (~boardOwner: player) => {
  let owner = switch(boardOwner) {
    | Human => "player"
    | AI => "ai"
  };
  "board-grid" ++ " board-" ++ owner
};

[@react.component]
let make = (~gameState, ~boardOwner: player, ~boardArray: board) => {
  <div className="board-container">
    <h2 className="board-title">
      {boardOwner
       |> (
         owner =>
           (
             switch (owner) {
             | Human => "You"
             | AI => "Enemy"
             }
           )
           |> ReasonReact.string
       )}
    </h2>
    <div className={getBoardNameClass(boardOwner)}>
      {boardArray
       |> Array.mapi((index: int, row: row) =>
            <BoardRow key={string_of_int(index)} row index boardOwner />
          )
       |> ReasonReact.array}
    </div>
  </div>;
};
