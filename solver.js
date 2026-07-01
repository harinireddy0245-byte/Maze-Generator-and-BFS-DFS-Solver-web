const VISITED_BFS = "#87CEEB";
const VISITED_DFS = "#f59e0b";
const SOLUTION = "#22c55e";

function sleep(ms){
    return new Promise(r=>setTimeout(r,ms));
}

const directions=[[-1,0],[1,0],[0,-1],[0,1]];

// BFS
document.getElementById("bfsBtn").addEventListener("click",solveBFS);

async function solveBFS(){

    const rows=getRows();
    const cols=getCols();
    const start=getStartPosition();
    const end=getEndPosition();

    let visited=Array.from({length:rows},()=>Array(cols).fill(false));
    let parent=Array.from({length:rows},()=>Array(cols).fill(null));

    let q=[start];
    visited[start.row][start.col]=true;

    while(q.length){

        let cur=q.shift();

        drawCell(cur.row,cur.col,VISITED_BFS);
        await sleep(10);

        if(cur.row===end.row && cur.col===end.col) break;

        for(let d of directions){
            let nr=cur.row+d[0];
            let nc=cur.col+d[1];

            if(nr>=0&&nc>=0&&nr<rows&&nc<cols&&
               !visited[nr][nc]&&isWalkable(nr,nc)){

                visited[nr][nc]=true;
                parent[nr][nc]=cur;
                q.push({row:nr,col:nc});
            }
        }
    }

    drawPath(parent,end,start);
}

// DFS FIXED
document.getElementById("dfsBtn").addEventListener("click",solveDFS);

async function solveDFS(){

    redrawMazeOnly(); // IMPORTANT FIX

    const rows=getRows();
    const cols=getCols();
    const start=getStartPosition();
    const end=getEndPosition();

    let visited=Array.from({length:rows},()=>Array(cols).fill(false));
    let parent=Array.from({length:rows},()=>Array(cols).fill(null));

    let stack=[start];

    while(stack.length){

        let cur=stack.pop();

        if(visited[cur.row][cur.col]) continue;

        visited[cur.row][cur.col]=true;

        drawCell(cur.row,cur.col,VISITED_DFS);
        await sleep(10);

        if(cur.row===end.row && cur.col===end.col) break;

        for(let d of directions){

            let nr=cur.row+d[0];
            let nc=cur.col+d[1];

            if(nr>=0&&nc>=0&&nr<rows&&nc<cols&&
               !visited[nr][nc]&&isWalkable(nr,nc)){

                parent[nr][nc]=cur;
                stack.push({row:nr,col:nc});
            }
        }
    }

    drawPath(parent,end,start);
}

// PATH DRAW
async function drawPath(parent,end,start){

    let cur=end;

    while(cur && !(cur.row===start.row&&cur.col===start.col)){

        drawCell(cur.row,cur.col,SOLUTION);
        cur=parent[cur.row][cur.col];
        await sleep(20);
    }
}