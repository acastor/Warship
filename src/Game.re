[%bs.raw {|require('./game.css')|}];

open SharedTypes;

let handleShipHit = (~board: board, ~fleet: fleet, ~x: int, ~y: int) => {
  // which ship did we hit
  let hitShip =
    List.find(
      (ship: ship) => {
        let coordinateList = Array.to_list(ship.coordinates);
        List.exists(
          coordinateTuple => {
            let (x2, y2) = coordinateTuple;
            x == x2 && y == y2;
          },
          coordinateList,
        );
      },
      fleet,
    );

  // update the ship
  hitShip.damage = hitShip.damage + 1;
  board[x][y] = Hit;

  // is the ship sunk?
  if (hitShip.damage == hitShip.shipLength) {
    hitShip.isSunk = true;

    for (index in 0 to Array.length(hitShip.coordinates) - 1) {
      let (x2, y2) = hitShip.coordinates[index];
      board[x2][y2] = Sunk;
    };
  };

  // are all the ships sunk?
  let hasSunkAllShips =
    List.for_all((ship: ship) => ship.isSunk == true, fleet);
  ();
  // if(hasSunkAllShips) {
  //   // end game
  // }
  //  else {
  //   // switch turn
  // }
};

let takeTurn =
    (~gameState: state, ~x: int, ~y: int, ~boardOwner: player, ~setGameState) => {
  let (board, fleet) =
    switch (boardOwner) {
    | Human => (gameState.humanBoard, gameState.humanFleet)
    | AI => (gameState.aiBoard, gameState.aiFleet)
    };

  switch (board[x][y]) {
  | Ship => handleShipHit(board, fleet, x, y)
  | Empty => board[x][y] = Miss;
  | _ => ()
  };

  setGameState(_ =>
    switch (boardOwner) {
    | Human => {
        ...gameState,
        humanBoard: Array.map(elem => elem, gameState.humanBoard),
        humanFleet: List.map(elem => elem, gameState.humanFleet),
      }
    | AI => {
        ...gameState,
        aiBoard: Array.map(elem => elem, gameState.aiBoard),
        aiFleet: List.map(elem => elem, gameState.aiFleet),
      }
    }
  );

  // switch turn
};

let aiTakeTurn =
    (~gameState: state, ~x: int, ~y: int, ~boardOwner: player, ~setGameState) => {
  ()// determine ai guess
    ;
    // call takeTurn with coordinates
};

[@react.component]
let make = () => {
  let (gameState, setGameState) = React.useState(AppContext.initialState);
  let partialAiTakeTurn = aiTakeTurn(~setGameState);
  let partialTakeTurn = takeTurn(~setGameState);

  <div className="game-container">
    <h2 className="board-title"> {ReasonReact.string("Warship")} </h2>
    <AppContext.BoardProvider value=gameState>
      <Board boardOwner=Human onTileClick=partialAiTakeTurn />
      <Board boardOwner=AI onTileClick=partialTakeTurn />
    </AppContext.BoardProvider>
  </div>;
};
