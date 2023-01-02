const figlet = require("figlet");
const readline = require("readline");

const rl = readline.createInterface({
  input : process.stdin,
  output: process.stdout,
});

const X = "X";
const O = "O";
const BOARD_SIZE = 3;

let playerX;
let playerO;
let currentPlayer = X;

/*
 * [
 *   [null, null, null],
 *   [null, null, null],
 *   [null, null, null]
 * ]
 * Arrays within array, filled with null
 */

let board = Array(BOARD_SIZE)
  .fill(null)
  .map(() => Array(BOARD_SIZE).fill(null));

function print(out) { process.stdout.write(out); }

function printBoard() {
  /* Top of the board */
  console.log("\n                        1   2   3");
  console.log("                      -------------");

  for (let i = 0; i < BOARD_SIZE; i++) {
    /* Each row be like 1 | ... */
    let row = `                    ${i + 1} |`;
    
    /* The rest of the row */
    for (let j = 0; j < BOARD_SIZE; j++) {
      let cell = board[i][j] || " ";
      row += ` ${cell} `;
      if (j < BOARD_SIZE - 1) {
        row += "|";
      }
    }
    
    /* We would need a closing | */
    row += "|";
    row += ` ${i + 1}`;

    /* Divider */
    console.log(row);
    console.log("                      -------------");
  }
  console.log("                        1   2   3\n");
}

/* 
  * The question method's callback function is defined as an arrow 
  * function that takes an input argument. 
  * The input argument is the user's response to the question, 
  * which is a string containing the row and column coordinates of their move.
*/

function getPlayerMove() {
  rl.question(
    `\n
      It's ${currentPlayer}'s turn.
      Enter the row (x's coordinate) 
      and column (y's coordinate)) 
      of your move (e.g. 2 3): `,
    (input) => {
      /* parse to Int, base 10 */
      const [row, col] = input.split(" ").map((x) => parseInt(x, 10) - 1);
      
      if (
        /* Within the board */
        row >= 0 &&
        row < BOARD_SIZE &&
        
        /* Within the board */
        col >= 0 &&
        col < BOARD_SIZE &&
        
        /* Ain't shit be there */
        !board[row][col]
      )
      {
        /* A valid move, ye */
        board[row][col] = currentPlayer;
        
        /* If that move conclude the game */
        if (checkForWin()) {
          printBoard();
          console.log(`\n${currentPlayer} wins!`);
          print(clr(`${currentPlayer} wins!\n`, "green"));
          rl.close();
        } else if (checkForDraw()) {
          printBoard();
          console.log("\nIt's a draw!");
          print(clr(`Nobody wins\n`, "yellow"));
          rl.close();
        } else {
          /* If not, switch player */
          currentPlayer = currentPlayer === X ? O : X;
          printBoard();
          getPlayerMove();
        }
      } else {
        console.log("\nInvalid move! Please try again.");
        print(clr("Invalid move! Somebody has already marked it down or you entered something stupid\n", "red"));
        getPlayerMove();
      }
    }
  );
}

/* Fk straight forward init */
function checkForWin() 
{
  return checkRows() || checkCols() || checkDiagonals();
}

function clr(text, color) {
  var code = { red: 91, green: 92, blue: 34, cian: 96, yellow: 93 } [color];
  if (code) return "\x1b[" + code + "m" + text + "\x1b[0m";
}

function checkRows() 
{
  for (let i = 0; i < BOARD_SIZE; i++) 
  {
    /* rows having the same symbol, vertical */
    if (board[i].every((x) => x === currentPlayer)) 
    return true;
  }
  return false;
}

function checkCols() 
{
  /* columns having the same symbol, horizontal */
  for (let i = 0; i < BOARD_SIZE; i++) 
  {
    if (board.every((y) => y[i] === currentPlayer)) 
      return true;
  }
  return false;
}

function checkDiagonals() {
  
  /* every row, i decrement from the last     index */
  /* every row, i increment from the starting index */
  return (
    board.every((row, i) => row[i] === currentPlayer) ||
    board.every((row, i) => row[BOARD_SIZE - i - 1] === currentPlayer)
  );
}

function checkForDraw() 
{
  /* "X" and "O" are both truthy value */
  /* "null" is a falsy value */
  return board.every((array) => array.every((cell) => cell));
}

function main() {
  console.log(figlet.textSync("Tic Tac Toe"));
  console.log("\nWelcome to Tic Tac Toe!\n");

  rl.question("Enter Player X name: ", (input) => {
    playerX = input;
    rl.question("Enter Player O name: ", (input) => {
      playerO = input;
  
      console.log(`\n${playerX} is X and ${playerO} is O`);
      printBoard();
      getPlayerMove();
    });
  });
}

main();