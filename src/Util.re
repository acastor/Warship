open SharedTypes;

let isLegalPlacement =
    (~board, x: int, y: int, direction: int, shipLength: int) => {
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
          validPlacement := board[x + index][y] == Empty;
        } else {
          validPlacement := board[x][y + index] == Empty;
        };
      };
    };
  };

  validPlacement;
};
