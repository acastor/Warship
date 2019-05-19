open SharedTypes;
open Util;

let createShip =
    (shipLength: int, coordinates: array((int, int)), shipType: shipType) => {
  damage: 0,
  shipType,
  isSunk: false,
  shipLength,
  coordinates,
};

let shipsAndLengths = [
  (Carrier, 5),
  (Battleship, 4),
  (Submarine, 3),
  (Destroyer, 3),
  (PatrolBoat, 2),
];

let updateBoardWithShipCoordinates = (board: board, ship: ship) => {
  ignore(Array.map(((x, y)) => board[x][y] = Ship, ship.coordinates));
};

let randomlyPlaceShips = (board: board) => {
  // iterate through every ship
  List.map(
    ((shipType: shipType, shipLength: int)) => {
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
                 shipLength,
               )) {
        randomX := Js.Math.floor(float_of_int(boardSize) *. Js.Math.random());
        randomY := Js.Math.floor(float_of_int(boardSize) *. Js.Math.random());
        randomDirection := Js.Math.floor(float_of_int(2) *. Js.Math.random());
      };
      let x = randomX^;
      let y = randomY^;
      let direction = randomDirection^;

      // get the ship coordinates starting at this position
      let shipCoordinates =
        getCoordinatesForShip(shipLength, x, y, direction);

      // create the ship and update the board with it's position
      let ship = createShip(shipLength, shipCoordinates, shipType);
      updateBoardWithShipCoordinates(board, ship);
      ship;
    },
    shipsAndLengths,
  );
};

let initialState = () => {
  let humanBoard = Array.make_matrix(boardSize, boardSize, Empty);
  let aiBoard = Array.make_matrix(boardSize, boardSize, Empty);
  let humanFleet = randomlyPlaceShips(humanBoard);
  let aiFleet = randomlyPlaceShips(aiBoard);
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
