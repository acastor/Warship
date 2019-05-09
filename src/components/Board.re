open SharedTypes;

[@react.component]
let make = (~state, ~boardOwner: player, ~boardArray: board) => {
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
    <div className="board-grid">
      {boardArray
       |> Array.mapi((index: int, row: row) =>
            <BoardRow key={string_of_int(index)} row index />
          )
       |> ReasonReact.array}
    </div>
  </div>;
};
