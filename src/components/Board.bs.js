// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var BoardRow$ReactHooksTemplate = require("./BoardRow.bs.js");
var AppContext$ReactHooksTemplate = require("./AppContext.bs.js");

function getBoardNameClass(boardOwner) {
  var owner = boardOwner ? "ai" : "player";
  return "board-grid board-" + owner;
}

function Board(Props) {
  var boardOwner = Props.boardOwner;
  var onTileClick = Props.onTileClick;
  var gameState = React.useContext(AppContext$ReactHooksTemplate.boardContext);
  var board = boardOwner ? gameState[/* aiBoard */2] : gameState[/* humanBoard */0];
  return React.createElement("div", {
              className: "board-container"
            }, React.createElement("h2", {
                  className: "title-color"
                }, boardOwner ? "Enemy" : "You"), React.createElement("div", {
                  className: getBoardNameClass(boardOwner)
                }, $$Array.mapi((function (index, param) {
                        return React.createElement(BoardRow$ReactHooksTemplate.make, {
                                    index: index,
                                    boardOwner: boardOwner,
                                    onTileClick: onTileClick,
                                    key: String(index)
                                  });
                      }), board)));
}

var make = Board;

exports.getBoardNameClass = getBoardNameClass;
exports.make = make;
/* react Not a pure module */
