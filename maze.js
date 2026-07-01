const canvas = document.getElementById("mazeCanvas");
const ctx = canvas.getContext("2d");

let ROWS = 21;
let COLS = 21;
const CELL_SIZE = 20;

const WALL = 1;
const PATH = 0;
const START = "S";
const END = "E";

let maze = [];

// ================= BUTTON =================
document.getElementById("generateBtn")
.addEventListener("click", generateMaze);

// ================= INIT =================
function initializeMaze() {
    maze = [];

    for (let r = 0; r < ROWS; r++) {
        maze[r] = [];
        for (let c = 0; c < COLS; c++) {
            maze[r][c] = WALL;
        }
    }
}

// ================= SHUFFLE =================
function shuffle(arr) {
    for (let i = arr.length - 1; i > 0; i--) {
        let j = Math.floor(Math.random() * (i + 1));
        [arr[i], arr[j]] = [arr[j], arr[i]];
    }
}

// ================= VALID =================
function isValid(r, c) {
    return r > 0 && c > 0 && r < ROWS - 1 && c < COLS - 1;
}

// ================= CARVE MAZE =================
function carve(r, c) {

    maze[r][c] = PATH;

    let dirs = [
        [-2, 0],
        [2, 0],
        [0, -2],
        [0, 2]
    ];

    shuffle(dirs);

    for (let d of dirs) {

        let nr = r + d[0];
        let nc = c + d[1];

        if (isValid(nr, nc) && maze[nr][nc] === WALL) {

            maze[r + d[0] / 2][c + d[1] / 2] = PATH;

            carve(nr, nc);
        }
    }
}

// ================= 🔥 ADD MULTIPLE PATHS =================
function addLoops(density = 0.25) {

    for (let r = 1; r < ROWS - 1; r++) {
        for (let c = 1; c < COLS - 1; c++) {

            if (maze[r][c] === WALL && Math.random() < density) {
                maze[r][c] = PATH;
            }
        }
    }
}

// ================= START/END =================
function placeStartEnd() {

    maze[1][1] = START;

    for (let r = ROWS - 2; r >= 1; r--) {
        for (let c = COLS - 2; c >= 1; c--) {

            if (maze[r][c] === PATH) {
                maze[r][c] = END;
                return;
            }
        }
    }
}

// ================= DRAW =================
function drawMaze() {

    canvas.width = COLS * CELL_SIZE;
    canvas.height = ROWS * CELL_SIZE;

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    for (let r = 0; r < ROWS; r++) {
        for (let c = 0; c < COLS; c++) {

            if (maze[r][c] === WALL) ctx.fillStyle = "#111";
            else if (maze[r][c] === PATH) ctx.fillStyle = "white";
            else if (maze[r][c] === START) ctx.fillStyle = "#3b82f6";
            else if (maze[r][c] === END) ctx.fillStyle = "#ef4444";

            ctx.fillRect(c * CELL_SIZE, r * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
    }
}

// ================= HELPERS =================
function getMaze(){ return maze; }
function getRows(){ return ROWS; }
function getCols(){ return COLS; }

function getStartPosition(){ return { row: 1, col: 1 }; }

function getEndPosition(){
    for (let r = 0; r < ROWS; r++) {
        for (let c = 0; c < COLS; c++) {
            if (maze[r][c] === END) return { row: r, col: c };
        }
    }
}

function isWalkable(r, c){
    return maze[r][c] !== WALL;
}

function drawCell(r, c, color){
    ctx.fillStyle = color;
    ctx.fillRect(c * CELL_SIZE, r * CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

// ================= RESET =================
function redrawMazeOnly(){
    drawMaze();
}

// ================= GENERATE =================
function generateMaze(){

    let r = parseInt(document.getElementById("rowsInput")?.value);
    let c = parseInt(document.getElementById("colsInput")?.value);

    ROWS = r > 5 ? r : 21;
    COLS = c > 5 ? c : 21;

    initializeMaze();
    carve(1, 1);

    // 🔥 THIS CREATES MULTIPLE PATHS
    addLoops(0.25);

    placeStartEnd();
    drawMaze();
}

// auto start
generateMaze();