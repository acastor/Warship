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

type gameState =
  | Setup
  | Playing(player)
  | Winner(player);

type state = {
  humanBoard: board,
  aiBoard: board,
  gameState: gameState
};

type ship = {
  mutable damage: int,
  shipType: shipType,
  mutable isSunk: bool,
  shipLength: int,
  // these shouldn't be mutable.. is there a way to not define them right away?
  mutable coordinates: array((int, int))
};

type fleet = array(ship);