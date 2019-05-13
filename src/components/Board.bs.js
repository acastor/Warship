// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var BoardRow$ReactHooksTemplate = require("./BoardRow.bs.js");

function getBoardNameClass(boardOwner) {
  var owner = boardOwner ? "ai" : "player";
  return "board-grid board-" + owner;
}

function Board(Props) {
  Props.gameState;
  var boardOwner = Props.boardOwner;
  var boardArray = Props.boardArray;
  return React.createElement("div", {
              className: "board-container"
            }, React.createElement("h2", {
                  className: "board-title"
                }, boardOwner ? "Enemy" : "You"), React.createElement("div", {
                  className: getBoardNameClass(boardOwner)
                }, $$Array.mapi((function (index, row) {
                        return React.createElement(BoardRow$ReactHooksTemplate.make, {
                                    row: row,
                                    index: index,
                                    boardOwner: boardOwner,
                                    key: String(index)
                                  });
                      }), boardArray)));
}

var make = Board;

exports.getBoardNameClass = getBoardNameClass;
exports.make = make;
/* react Not a pure module */
