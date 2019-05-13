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
           switch (contents, boardOwner) {
           | (Ship, Human) => {js| 🚢 |js}
           | (Ship, AI) => ""
           | (Miss, _) => {js| 💨 |js}
           | (Hit, _) => {js| 🔥 |js}
           | (Sunk, _) => {js| ☠ |js}
           | (Empty, _) => ""
           }
         )
         |> ReasonReact.string 
     )}
     </div>
  </div>;
};
