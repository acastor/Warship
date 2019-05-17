open SharedTypes;

[@react.component]
let make = (~index: int, ~boardOwner: player, ~onTileClick) => {
  let gameState = React.useContext(AppContext.boardContext);
  let board =
    switch (boardOwner) {
    | Human => gameState.humanBoard
    | AI => gameState.aiBoard
    };

  <div className="board-row">
    {board[index]
     |> Array.mapi((ind: int, tile: boardTileState) =>
          <BoardTile
            key={string_of_int(index) ++ string_of_int(ind)}
            x={string_of_int(index)}
            y={string_of_int(ind)}
            boardOwner
            onTileClick
          />
        )
     |> ReasonReact.array}
  </div>;
};
