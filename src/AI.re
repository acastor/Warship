open SharedTypes;
open Util;

type startingMove = {
  x: int,
  y: int,
  weight: float,
};

let probability_weight = 1000;

// starting book's high probability weight
let start_high_min = 20;
let start_high_max = 30;

// starting book's medium probability weight
let start_med_min = 15;
let start_med_max = 25;

// starting book's low probability weight
let start_low_min = 10;
let start_low_max = 20;

// Randomness control when selecting between cells of equal probability
let randomness = 0.1;

let getRandom = (min, max) => {
  Js.Math.random() *. float_of_int(max - min) +. float_of_int(min);
};

let aiVirtualBoard = Array.make_matrix(boardSize, boardSize, Empty);

let startingMovesArr = [
  {x: 7, y: 3, weight: getRandom(start_low_min, start_low_max)},
  {x: 6, y: 2, weight: getRandom(start_low_min, start_low_max)},
  {x: 3, y: 7, weight: getRandom(start_low_min, start_low_max)},
  {x: 2, y: 6, weight: getRandom(start_low_min, start_low_max)},
  {x: 6, y: 6, weight: getRandom(start_low_min, start_low_max)},
  {x: 3, y: 3, weight: getRandom(start_low_min, start_low_max)},
  {x: 5, y: 5, weight: getRandom(start_low_min, start_low_max)},
  {x: 4, y: 4, weight: getRandom(start_low_min, start_low_max)},
  {x: 0, y: 8, weight: getRandom(start_med_min, start_med_max)},
  {x: 1, y: 9, weight: getRandom(start_high_min, start_high_max)},
  {x: 8, y: 0, weight: getRandom(start_med_min, start_med_max)},
  {x: 9, y: 1, weight: getRandom(start_high_min, start_high_max)},
  {x: 9, y: 9, weight: getRandom(start_high_min, start_high_max)},
  {x: 0, y: 0, weight: getRandom(start_high_min, start_high_max)},
];

let getNumberOfHitCells = (shipCoordinates: array((int, int)), board: board) => {
  List.length(
    List.filter(
      ((x, y)) => board[x][y] == Hit,
      Array.to_list(shipCoordinates),
    ),
  );
};

let updateAIVirtualBoard = (humanBoard: board, ~x: int, ~y: int) => {
  switch (humanBoard[x][y]) {
  | Ship => aiVirtualBoard[x][y] = Hit
  | Empty => aiVirtualBoard[x][y] = Miss
  | _ => ()
  };
};

let getProbabilityGrid = (~humanFleet: fleet, ~humanBoard: board) => {
  let probabilityGrid = Array.make_matrix(boardSize, boardSize, 0);
  // let's get all the ship s that aren't sunk yet
  let shipsToHit = List.filter(ship => !ship.isSunk, humanFleet);

  // TODO direction should prob just be a type
  let checkCoordinateInDirection =
      (
        humanBoard: board,
        x: int,
        y: int,
        direction: int,
        ship: ship,
        ~probabilityGrid,
      ) =>
    if (Util.isLegalPlacement(aiVirtualBoard, x, y, direction, ship.shipLength)) {
      let shipCoordinates = getCoordinatesForShip(ship.shipLength, x, y, direction);
      let tileWeight = ref(1);
      let numberOfHitCells = getNumberOfHitCells(shipCoordinates, humanBoard);

      if (numberOfHitCells > 0) {
        tileWeight := probability_weight * numberOfHitCells;
      };

      ignore(Array.map(
        ((x, y)) =>
          probabilityGrid[x][y] = probabilityGrid[x][y] + tileWeight^,
        shipCoordinates,
      ));
    };

  // evaluate the probability of a ship populating each tile
  ignore(List.map(
    ship =>
      Array.mapi(
        (y, columnArr) =>
          Array.mapi(
            (x, _) => {
              checkCoordinateInDirection(
                humanBoard,
                x,
                y,
                directionHorizontal,
                ship,
                ~probabilityGrid,
              );
              checkCoordinateInDirection(
                humanBoard,
                x,
                y,
                directionVertical,
                ship,
                ~probabilityGrid,
              );

              if (aiVirtualBoard[x][y] != Empty) {
                probabilityGrid[x][y] = 0;
              };
            },
            columnArr,
          ),
        humanBoard,
      ),
    shipsToHit,
  ));
  probabilityGrid;
};

let aiShoot = (humanFleet: fleet, humanBoard: board) => {
  let probabilityGrid = getProbabilityGrid(~humanFleet, ~humanBoard);

  // add our list of high probability targets
  ignore(List.map(
    (startingMove: startingMove) => {
      let x = startingMove.x;
      let y = startingMove.y;
      if (probabilityGrid[x][y] != 0) {
        probabilityGrid[x][y] =
          probabilityGrid[x][y] + int_of_float(startingMove.weight);
      };
    },
    startingMovesArr,
  ));

  // get the tile with the highest probability of having a ship
  let maxProbability = ref(0);
  let target = ref(((-1), (-1)));
  ignore(Array.mapi(
    (x, columnArr) =>
      Array.mapi(
        (y, _) =>
          if (probabilityGrid[x][y] > maxProbability^) {
            target := (x, y);
            maxProbability := probabilityGrid[x][y];
          },
        columnArr,
      ),
    probabilityGrid,
  ));
  let (x, y) = target^;
  Js.log(
    "The guess is (" ++ string_of_int(x) ++ ", " ++ string_of_int(y) ++ ")",
  );

  updateAIVirtualBoard(humanBoard, ~x, ~y);
  target^;
};
