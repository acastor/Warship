open SharedTypes;

[@react.component]
let make = (~x: string, ~y: string, ~tile: boardTileState) => {
  <div className="board-tile" x y>
    {tile
     |> (
       contents =>
         (
           switch (contents) {
           | Ship => {js| 🚢 |js}
           | Miss => {js| 💨 |js}
           | Hit => {js| 🔥 |js}
           | Sunk => {js| ☠ |js}
           | Empty => ""
           }
         )
         |> ReasonReact.string
     )}
  </div>;
};
