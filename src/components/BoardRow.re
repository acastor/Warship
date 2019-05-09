open SharedTypes;

[@react.component]
let make = (~row: row, ~index: int) => {
  <div className="board-row">
    {row
     |> Array.mapi((ind: int, tile: boardTileState) => {
          let id = string_of_int(index) ++ string_of_int(ind);

          <BoardTile
            key=id
            x={string_of_int(index)}
            y={string_of_int(ind)}
            tile
          />;
        })
     |> ReasonReact.array}
  </div>;
};
