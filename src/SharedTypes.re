type shipType =
  | Carrier
  | Battleship
  | Destroyer
  | Submarine
  | PatrolBoat;

type boardTileState =
  | Empty
  | Ship
  | Miss
  | Hit
  | Sunk;

type row = array(boardTileState);

type board = array(row);

type player =
  | Human
  | AI;

type turnState =
  | Playing(player)
  | Winner(player);

type ship = {
  mutable damage: int,
  shipType,
  mutable isSunk: bool,
  shipLength: int,
  // these shouldn't be mutable.. is there a way to not define them right away?
  mutable coordinates: array((int, int)),
};

type fleet = list(ship);

type state = {
  humanBoard: board,
  humanFleet: fleet,
  aiBoard: board,
  aiFleet: fleet,
  turnState,
};

let boardSize = 10;
