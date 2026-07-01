document.getElementById("difficultyBtn")
.addEventListener("click", runComparison);

function sleep(ms){
    return new Promise(r => setTimeout(r, ms));
}

// ================= MAIN =================
async function runComparison() {

    const bfs = await runBFS();
    await sleep(300);
    const dfs = await runDFS();

    document.getElementById("difficultyResult").innerHTML = `
        <b>BFS</b><br>
        Visited: ${bfs.visited}<br>
        Path: ${bfs.path}<br><br>

        <b>DFS</b><br>
        Visited: ${dfs.visited}<br>
        Path: ${dfs.path}
    `;
}

// ================= BFS =================
async function runBFS() {

    redrawMazeOnly();

    const rows = getRows();
    const cols = getCols();
    const start = getStartPosition();
    const end = getEndPosition();

    let visited = Array.from({ length: rows }, () =>
        Array(cols).fill(false)
    );

    let parent = Array.from({ length: rows }, () =>
        Array(cols).fill(null)
    );

    let q = [start];
    visited[start.row][start.col] = true;

    let count = 0;

    while (q.length) {

        let cur = q.shift();
        count++;

        drawCell(cur.row, cur.col, "#87CEEB");
        await sleep(5);

        if (cur.row === end.row && cur.col === end.col) break;

        for (let d of directions) {

            let nr = cur.row + d[0];
            let nc = cur.col + d[1];

            if (
                nr >= 0 && nc >= 0 &&
                nr < rows && nc < cols &&
                !visited[nr][nc] &&
                isWalkable(nr, nc)
            ) {
                visited[nr][nc] = true;
                parent[nr][nc] = cur;
                q.push({ row: nr, col: nc });
            }
        }
    }

    return {
        visited: count,
        path: countPath(parent, end, start)
    };
}

// ================= DFS =================
async function runDFS() {

    redrawMazeOnly();

    const rows = getRows();
    const cols = getCols();
    const start = getStartPosition();
    const end = getEndPosition();

    let visited = Array.from({ length: rows }, () =>
        Array(cols).fill(false)
    );

    let parent = Array.from({ length: rows }, () =>
        Array(cols).fill(null)
    );

    let stack = [start];
    let count = 0;

    while (stack.length) {

        let cur = stack.pop();

        if (visited[cur.row][cur.col]) continue;

        visited[cur.row][cur.col] = true;
        count++;

        drawCell(cur.row, cur.col, "orange");
        await sleep(5);

        if (cur.row === end.row && cur.col === end.col) break;

        for (let d of directions) {

            let nr = cur.row + d[0];
            let nc = cur.col + d[1];

            if (
                nr >= 0 && nc >= 0 &&
                nr < rows && nc < cols &&
                !visited[nr][nc] &&
                isWalkable(nr, nc)
            ) {
                parent[nr][nc] = cur;
                stack.push({ row: nr, col: nc });
            }
        }
    }

    return {
        visited: count,
        path: countPath(parent, end, start)
    };
}

// ================= PATH LENGTH =================
function countPath(parent, end, start) {

    let cur = end;
    let count = 0;

    while (cur && !(cur.row === start.row && cur.col === start.col)) {
        count++;
        cur = parent[cur.row][cur.col];
    }

    return count;
}