// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var React = require("react");
var Js_math = require("bs-platform/lib/js/js_math.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Board$ReactHooksTemplate = require("./components/Board.bs.js");

((require('./game.css')));

function initialGameState(param) {
  return /* record */[
          /* humanBoard */$$Array.make_matrix(10, 10, /* Empty */0),
          /* aiBoard */$$Array.make_matrix(10, 10, /* Empty */0),
          /* gameState : Playing */Block.__(0, [/* Human */0])
        ];
}

function buildFleet(param) {
  var carrier = /* record */[
    /* damage */0,
    /* shipType : Carrier */0,
    /* isSunk */false,
    /* shipLength */5,
    /* coordinates */Caml_array.caml_make_vect(5, /* tuple */[
          -1,
          -1
        ])
  ];
  var battleship = /* record */[
    /* damage */0,
    /* shipType : Battleship */1,
    /* isSunk */false,
    /* shipLength */4,
    /* coordinates */Caml_array.caml_make_vect(4, /* tuple */[
          -1,
          -1
        ])
  ];
  var submarine = /* record */[
    /* damage */0,
    /* shipType : Submarine */3,
    /* isSunk */false,
    /* shipLength */3,
    /* coordinates */Caml_array.caml_make_vect(3, /* tuple */[
          -1,
          -1
        ])
  ];
  var destroyer = /* record */[
    /* damage */0,
    /* shipType : Destroyer */2,
    /* isSunk */false,
    /* shipLength */3,
    /* coordinates */Caml_array.caml_make_vect(3, /* tuple */[
          -1,
          -1
        ])
  ];
  var patrolBoat = /* record */[
    /* damage */0,
    /* shipType : PatrolBoat */4,
    /* isSunk */false,
    /* shipLength */2,
    /* coordinates */Caml_array.caml_make_vect(2, /* tuple */[
          -1,
          -1
        ])
  ];
  return /* array */[
          carrier,
          battleship,
          submarine,
          destroyer,
          patrolBoat
        ];
}

function isLegalPlacement(board, x, y, direction, shipLength) {
  var validPlacement = /* record */[/* contents */false];
  if (direction === 0) {
    validPlacement[0] = (x + shipLength | 0) <= 10;
  } else {
    validPlacement[0] = (y + shipLength | 0) <= 10;
  }
  if (validPlacement[0]) {
    for(var index = 0 ,index_finish = shipLength - 1 | 0; index <= index_finish; ++index){
      if (validPlacement[0]) {
        if (direction === 0) {
          validPlacement[0] = Caml_array.caml_array_get(Caml_array.caml_array_get(board, x + index | 0), y) !== /* Ship */1;
        } else {
          validPlacement[0] = Caml_array.caml_array_get(Caml_array.caml_array_get(board, x), y + index | 0) !== /* Ship */1;
        }
      }
      
    }
  }
  return validPlacement;
}

function randomlyPlaceShips(board, fleet) {
  return $$Array.map((function (ship) {
                var randomX = Js_math.floor(10 * Math.random());
                var randomY = Js_math.floor(10 * Math.random());
                var randomDirection = Js_math.floor(2 * Math.random());
                while(!isLegalPlacement(board, randomX, randomY, randomDirection, ship[/* shipLength */3])[0]) {
                  randomX = Js_math.floor(10 * Math.random());
                  randomY = Js_math.floor(10 * Math.random());
                  randomDirection = Js_math.floor(2 * Math.random());
                };
                var x = randomX;
                var y = randomY;
                var direction = randomDirection;
                for(var index = 0 ,index_finish = ship[/* shipLength */3] - 1 | 0; index <= index_finish; ++index){
                  if (direction === 0) {
                    Caml_array.caml_array_set(Caml_array.caml_array_get(board, x + index | 0), y, /* Ship */1);
                    Caml_array.caml_array_set(ship[/* coordinates */4], index, /* tuple */[
                          x + index | 0,
                          y
                        ]);
                  } else {
                    Caml_array.caml_array_set(Caml_array.caml_array_get(board, x), y + index | 0, /* Ship */1);
                    Caml_array.caml_array_set(ship[/* coordinates */4], index, /* tuple */[
                          x,
                          y + index | 0
                        ]);
                  }
                }
                return /* () */0;
              }), fleet);
}

function Game(Props) {
  var match = React.useState((function () {
          return initialGameState(/* () */0);
        }));
  var gameState = match[0];
  var match$1 = React.useState((function () {
          return buildFleet(/* () */0);
        }));
  var match$2 = React.useState((function () {
          return buildFleet(/* () */0);
        }));
  randomlyPlaceShips(gameState[/* humanBoard */0], match$1[0]);
  randomlyPlaceShips(gameState[/* aiBoard */1], match$2[0]);
  return React.createElement("div", {
              className: "game-container"
            }, React.createElement("h2", {
                  className: "board-title"
                }, "Warship"), React.createElement(Board$ReactHooksTemplate.make, {
                  gameState: gameState,
                  boardOwner: /* Human */0,
                  boardArray: gameState[/* humanBoard */0]
                }), React.createElement(Board$ReactHooksTemplate.make, {
                  gameState: gameState,
                  boardOwner: /* AI */1,
                  boardArray: gameState[/* aiBoard */1]
                }));
}

var boardSize = 10;

var directionVertical = 0;

var directionHorizontal = 1;

var make = Game;

exports.boardSize = boardSize;
exports.directionVertical = directionVertical;
exports.directionHorizontal = directionHorizontal;
exports.initialGameState = initialGameState;
exports.buildFleet = buildFleet;
exports.isLegalPlacement = isLegalPlacement;
exports.randomlyPlaceShips = randomlyPlaceShips;
exports.make = make;
/*  Not a pure module */
