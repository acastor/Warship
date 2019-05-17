open SharedTypes;

let getBoardNameClass = (~boardOwner: player) => {
  let owner =
    switch (boardOwner) {
    | Human => "player"
    | AI => "ai"
    };
  "board-grid" ++ " board-" ++ owner;
};

[@react.component]
let make = (~boardOwner: player, ~onTileClick) => {
  let gameState = React.useContext(AppContext.boardContext);
  let board =
    switch (boardOwner) {
    | Human => gameState.humanBoard
    | AI => gameState.aiBoard
    };
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
      {board
       |> Array.mapi((index: int, row: row) =>
            <BoardRow
              key={string_of_int(index)}
              index
              boardOwner
              onTileClick
            />
          )
       |> ReasonReact.array}
    </div>
  </div>;
};
