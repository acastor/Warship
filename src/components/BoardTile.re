open SharedTypes;

[@react.component]
let make =
    (~x: string, ~y: string, ~tile: boardTileState, ~boardOwner: player) => {
  <div className="board-tile" x y>
  <div className="tile-emoji">
    {tile
     |> (
       contents =>
         (
           switch (contents) {
             // todo hide the ship if this is in the ai board
           | Ship => {js| 🚢 |js}
           | Miss => {js| 💨 |js}
           | Hit => {js| 🔥 |js}
           | Sunk => {js| ☠ |js}
           | Empty => ""
           }
         )
         |> ReasonReact.string
     )}
     </div>
  </div>;
};
