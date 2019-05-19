open SharedTypes;

let isLegalPlacement =
    (board: board, x: int, y: int, direction: int, shipLength: int) => {
  let validPlacement = ref(false);
  if (direction == directionVertical) {
    validPlacement := x + shipLength <= boardSize;
  } else {
    validPlacement := y + shipLength <= boardSize;
  };

  if (validPlacement^) {
    for (index in 0 to shipLength - 1) {
      if (validPlacement^) {
        if (direction == directionVertical) {
          validPlacement := board[x + index][y] != Ship;
        } else {
          validPlacement := board[x][y + index] != Ship;
        };
      };
    };
  };

  validPlacement^;
};

let getCoordinatesForShip = (shipLength: int, x: int, y: int, direction: int) => {
  let shipCoordinatesArr = Array.make(shipLength, ((-1), (-1)));
  for (index in 0 to shipLength - 1) {
    if (direction == directionVertical) {
      shipCoordinatesArr[index] = (x + index, y);
    } else {
      shipCoordinatesArr[index] = (x, y + index);
    };
  };
  shipCoordinatesArr;
};
