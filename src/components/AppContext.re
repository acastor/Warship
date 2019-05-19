open SharedTypes;
open Util;

// TODO clean this up; mapping of shiptype to ship length
let buildFleet = () => {
  let carrier = {
    damage: 0,
    shipType: Carrier,
    isSunk: false,
    shipLength: 5,
    coordinates: Array.make(5, ((-1), (-1))),
  };
  let battleship = {
    damage: 0,
    shipType: Battleship,
    isSunk: false,
    shipLength: 4,
    coordinates: Array.make(4, ((-1), (-1))),
  };
  let submarine = {
    damage: 0,
    shipType: Submarine,
    isSunk: false,
    shipLength: 3,
    coordinates: Array.make(3, ((-1), (-1))),
  };
  let destroyer = {
    damage: 0,
    shipType: Destroyer,
    isSunk: false,
    shipLength: 3,
    coordinates: Array.make(3, ((-1), (-1))),
  };
  let patrolBoat = {
    damage: 0,
    shipType: PatrolBoat,
    isSunk: false,
    shipLength: 2,
    coordinates: Array.make(2, ((-1), (-1))),
  };
  [carrier, battleship, submarine, destroyer, patrolBoat];
};

let updateBoardWithShipCoordinates = (board: board, ship: ship) => {
  Array.map(((x, y)) => board[x][y] = Ship, ship.coordinates);
};

let randomlyPlaceShips = (board: board, fleet: fleet) => {
  // iterate through every ship
  List.map(
    ship => {
      let randomX =
        ref(Js.Math.floor(float_of_int(boardSize) *. Js.Math.random()));
      let randomY =
        ref(Js.Math.floor(float_of_int(boardSize) *. Js.Math.random()));
      // 2 for the two directions (north/south and east/west)
      let randomDirection =
        ref(Js.Math.floor(float_of_int(2) *. Js.Math.random()));
      while (!
               isLegalPlacement(
                 board,
                 randomX^,
                 randomY^,
                 randomDirection^,
                 ship.shipLength,
               )) {
        randomX := Js.Math.floor(float_of_int(boardSize) *. Js.Math.random());
        randomY := Js.Math.floor(float_of_int(boardSize) *. Js.Math.random());
        randomDirection := Js.Math.floor(float_of_int(2) *. Js.Math.random());
      };
      let x = randomX^;
      let y = randomY^;
      let direction = randomDirection^;

      // get the ship coordinates starting at this position
      // save the coordinates on the ship and update the board
      ship.coordinates = getCoordinatesForShip(ship, x, y, direction);
      updateBoardWithShipCoordinates(board, ship);
    },
    fleet,
  );
};

let initialState = () => {
  let humanFleet = buildFleet();
  let aiFleet = buildFleet();
  let humanBoard = Array.make_matrix(boardSize, boardSize, Empty);
  let aiBoard = Array.make_matrix(boardSize, boardSize, Empty);
  ignore(randomlyPlaceShips(humanBoard, humanFleet));
  ignore(randomlyPlaceShips(aiBoard, aiFleet));
  {humanBoard, humanFleet, aiBoard, aiFleet, turnState: Playing(Human)};
};

let boardContext = React.createContext(initialState());

module BoardProvider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = React.Context.provider(boardContext);
};
