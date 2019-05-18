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

let isGameOver = (~fleet: fleet) => List.for_all(ship => ship.isSunk, fleet);

let aiTakeTurn = (~gameState: state, ~boardOwner: player, ~setGameState) => {
  ()// takeTurn(
    //   ~gameState,
    //   ~x=0,
    //   ~y=0,
    //   ~boardOwner,
    //   ~setGameState,
    ; // call takeTurn with coordinates
 // determine ai guess
    // );
};

/*
  Method to shoot at a tile. 
  Returns whether the shot was valid. Invalid shots are at Sunk and Miss tiles.
 */
let shoot = (~board: board, ~x: int, ~y: int, ~fleet: fleet) => {
  switch (board[x][y]) {
  | Ship =>
    handleShipHit(board, fleet, x, y);
    true;
  | Empty =>
    board[x][y] = Miss;
    true;
  | _ => false
  };
};

let takeTurn =
    (~gameState: state, ~x: int, ~y: int, ~boardOwner: player, ~setGameState) => {
  let (board, fleet) =
    switch (boardOwner) {
    | Human => (gameState.humanBoard, gameState.humanFleet)
    | AI => (gameState.aiBoard, gameState.aiFleet)
    };

  // only update the state for valid moves (clicking an Empty or Ship tile)
  if (shoot(board, x, y, fleet)) {
    // check for winner and switch turn & update board or end game
    setGameState(_ =>
      switch (boardOwner, isGameOver(fleet)) {
      | (Human, false) => {
          ...gameState,
          humanBoard: Array.map(tile => tile, gameState.humanBoard),
          humanFleet: List.map(ship => ship, gameState.humanFleet),
          turnState: Playing(Human),
        }
      | (AI, false) => {
          ...gameState,
          aiBoard: Array.map(tile => tile, gameState.aiBoard),
          aiFleet: List.map(ship => ship, gameState.aiFleet),
          turnState: Playing(AI),
        }
      | (Human, true) => {...gameState, turnState: Winner(AI)}
      | (AI, true) => {...gameState, turnState: Winner(Human)}
      }
    );

    if (gameState.turnState == Playing(AI)) {
      aiTakeTurn(~gameState, ~boardOwner=Human, ~setGameState);
    };
  };
};

let onTileClickHandler =
    (~gameState: state, ~x: int, ~y: int, ~boardOwner: player, ~setGameState) => {
  switch (boardOwner) {
  | Human => ()
  | AI => takeTurn(~gameState, ~x, ~y, ~boardOwner, ~setGameState)
  };
};

[@react.component]
let make = () => {
  let (gameState, setGameState) = React.useState(AppContext.initialState);
  let partialOnTileClickHandler = onTileClickHandler(~setGameState);

  <div className="game-container">
    {switch (gameState.turnState) {
     | Playing(_) =>
       <div>
         <h2 className="board-title"> {ReasonReact.string("Warship")} </h2>
         <AppContext.BoardProvider value=gameState>
           <Board boardOwner=Human onTileClick=partialOnTileClickHandler />
           <Board boardOwner=AI onTileClick=partialOnTileClickHandler />
         </AppContext.BoardProvider>
       </div>
     | Winner(Human) => <h1> {ReasonReact.string("YOU WON!")} </h1>
     | Winner(AI) => <h1> {ReasonReact.string("YOU LOST!")} </h1>
     }}
  </div>;
};
