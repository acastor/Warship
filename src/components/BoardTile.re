open SharedTypes;

let getTileContents = (tile: boardTileState, ~boardOwner: player) =>
  switch (tile, boardOwner) {
  | (Ship, Human) => {js| 🚢 |js}
  | (Ship, AI) => ""
  | (Miss, _) => {js| 💨 |js}
  | (Hit, _) => {js| 🔥 |js}
  | (Sunk, _) => {js| ☠ |js}
  | (Empty, _) => ""
  };

[@react.component]
let make = (~x: string, ~y: string, ~boardOwner: player, ~onTileClick) => {
  let gameState = React.useContext(AppContext.boardContext);
  let partialGetEmojiForTile = getTileContents(~boardOwner);
  let click = event => {
    onTileClick(
      ~gameState,
      ~x=int_of_string(x),
      ~y=int_of_string(y),
      ~boardOwner,
    );
  };
  let board =
    switch (boardOwner) {
    | Human => gameState.humanBoard
    | AI => gameState.aiBoard
    };

  <div className="board-tile" x y onClick=click>
    <div className="tile-emoji">
      {board[int_of_string(x)][int_of_string(y)]
       |> partialGetEmojiForTile
       |> ReasonReact.string}
    </div>
  </div>;
};
