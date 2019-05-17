// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Board$ReactHooksTemplate = require("./components/Board.bs.js");
var AppContext$ReactHooksTemplate = require("./components/AppContext.bs.js");

((require('./game.css')));

function handleShipHit(board, fleet, x, y) {
  var hitShip = List.find((function (ship) {
          var coordinateList = $$Array.to_list(ship[/* coordinates */4]);
          return List.exists((function (coordinateTuple) {
                        if (x === coordinateTuple[0]) {
                          return y === coordinateTuple[1];
                        } else {
                          return false;
                        }
                      }), coordinateList);
        }), fleet);
  hitShip[/* damage */0] = hitShip[/* damage */0] + 1 | 0;
  Caml_array.caml_array_set(Caml_array.caml_array_get(board, x), y, /* Hit */3);
  if (hitShip[/* damage */0] === hitShip[/* shipLength */3]) {
    hitShip[/* isSunk */2] = true;
    for(var index = 0 ,index_finish = hitShip[/* coordinates */4].length - 1 | 0; index <= index_finish; ++index){
      var match = Caml_array.caml_array_get(hitShip[/* coordinates */4], index);
      Caml_array.caml_array_set(Caml_array.caml_array_get(board, match[0]), match[1], /* Sunk */4);
    }
  }
  List.for_all((function (ship) {
          return ship[/* isSunk */2] === true;
        }), fleet);
  return /* () */0;
}

function isGameOver(fleet) {
  return List.for_all((function (ship) {
                return ship[/* isSunk */2];
              }), fleet);
}

function takeTurn(gameState, x, y, boardOwner, setGameState) {
  var match = boardOwner ? /* tuple */[
      gameState[/* aiBoard */2],
      gameState[/* aiFleet */3]
    ] : /* tuple */[
      gameState[/* humanBoard */0],
      gameState[/* humanFleet */1]
    ];
  var fleet = match[1];
  var board = match[0];
  var match$1 = Caml_array.caml_array_get(Caml_array.caml_array_get(board, x), y);
  if (match$1 !== 1) {
    if (match$1 !== 0) {
      
    } else {
      Caml_array.caml_array_set(Caml_array.caml_array_get(board, x), y, /* Miss */2);
    }
  } else {
    handleShipHit(board, fleet, x, y);
  }
  return Curry._1(setGameState, (function (param) {
                var match = List.for_all((function (ship) {
                        return ship[/* isSunk */2];
                      }), fleet);
                if (boardOwner) {
                  if (match) {
                    return /* record */[
                            /* humanBoard */gameState[/* humanBoard */0],
                            /* humanFleet */gameState[/* humanFleet */1],
                            /* aiBoard */gameState[/* aiBoard */2],
                            /* aiFleet */gameState[/* aiFleet */3],
                            /* turnState : Winner */Block.__(1, [/* Human */0])
                          ];
                  } else {
                    return /* record */[
                            /* humanBoard */gameState[/* humanBoard */0],
                            /* humanFleet */gameState[/* humanFleet */1],
                            /* aiBoard */$$Array.map((function (elem) {
                                    return elem;
                                  }), gameState[/* aiBoard */2]),
                            /* aiFleet */List.map((function (elem) {
                                    return elem;
                                  }), gameState[/* aiFleet */3]),
                            /* turnState : Playing */Block.__(0, [/* Human */0])
                          ];
                  }
                } else if (match) {
                  return /* record */[
                          /* humanBoard */gameState[/* humanBoard */0],
                          /* humanFleet */gameState[/* humanFleet */1],
                          /* aiBoard */gameState[/* aiBoard */2],
                          /* aiFleet */gameState[/* aiFleet */3],
                          /* turnState : Winner */Block.__(1, [/* AI */1])
                        ];
                } else {
                  return /* record */[
                          /* humanBoard */$$Array.map((function (elem) {
                                  return elem;
                                }), gameState[/* humanBoard */0]),
                          /* humanFleet */List.map((function (elem) {
                                  return elem;
                                }), gameState[/* humanFleet */1]),
                          /* aiBoard */gameState[/* aiBoard */2],
                          /* aiFleet */gameState[/* aiFleet */3],
                          /* turnState : Playing */Block.__(0, [/* AI */1])
                        ];
                }
              }));
}

function aiTakeTurn(gameState, x, y, boardOwner, setGameState) {
  return /* () */0;
}

function Game(Props) {
  var match = React.useState((function () {
          return AppContext$ReactHooksTemplate.initialState(/* () */0);
        }));
  var setGameState = match[1];
  var gameState = match[0];
  var partialAiTakeTurn = function (param) {
    return (function (param) {
        var func = function (param$1, param$2, param$3) {
          return /* () */0;
        };
        return (function (param) {
            var func$1 = Curry._1(func, param);
            return (function (param) {
                return Curry._2(func$1, param, setGameState);
              });
          });
      });
  };
  var partialTakeTurn = function (param) {
    return (function (param$1) {
        var func = function (param$2, param$3, param$4) {
          var param$5 = param$1;
          var param$6 = param$2;
          var param$7 = param$3;
          var param$8 = param$4;
          return takeTurn(param, param$5, param$6, param$7, param$8);
        };
        return (function (param) {
            var func$1 = Curry._1(func, param);
            return (function (param) {
                return Curry._2(func$1, param, setGameState);
              });
          });
      });
  };
  var match$1 = gameState[/* turnState */4];
  var tmp;
  tmp = match$1.tag ? (
      match$1[0] ? React.createElement("h1", undefined, "YOU LOST!") : React.createElement("h1", undefined, "YOU WON!")
    ) : React.createElement("div", undefined, React.createElement("h2", {
              className: "board-title"
            }, "Warship"), React.createElement(AppContext$ReactHooksTemplate.BoardProvider[/* make */1], AppContext$ReactHooksTemplate.BoardProvider[/* makeProps */0](gameState, null, /* () */0), React.createElement(Board$ReactHooksTemplate.make, {
                  boardOwner: /* Human */0,
                  onTileClick: partialAiTakeTurn
                }), React.createElement(Board$ReactHooksTemplate.make, {
                  boardOwner: /* AI */1,
                  onTileClick: partialTakeTurn
                })));
  return React.createElement("div", {
              className: "game-container"
            }, tmp);
}

var make = Game;

exports.handleShipHit = handleShipHit;
exports.isGameOver = isGameOver;
exports.takeTurn = takeTurn;
exports.aiTakeTurn = aiTakeTurn;
exports.make = make;
/*  Not a pure module */
