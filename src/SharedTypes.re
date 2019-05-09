type ship =
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