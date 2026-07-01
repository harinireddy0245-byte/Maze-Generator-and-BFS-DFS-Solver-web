// =====================================================
//  Maze Generator Project
// =====================================================



#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;



// ===== MazeGenerator.h =====


#include <vector>

class MazeGenerator
{
private:
    int rows, cols;
    std::vector<std::vector<char>> maze;

    void carvePath(int r, int c);

public:
    MazeGenerator(int r, int c);

    void generateMaze();
    void displayMaze();

    std::vector<std::vector<char>>& getMaze();
};




// ===== BFSSolver.h =====


#include <vector>

class BFSSolver
{
public:
    static int visitedCount;
    static int pathLength;

    static bool solve(std::vector<std::vector<char>>& maze);
};




// ===== DFSSolver.h =====


#include <vector>

class DFSSolver
{
public:
    static int visitedCount;
    static int pathLength;

    static bool solve(std::vector<std::vector<char>>& maze);
};




// ===== DifficultyRater.h =====


#include <string>

class DifficultyRater
{
public:
    static std::string rateDifficulty(
        int pathLength,
        int visitedCells,
        int rows,
        int cols
    );
};




// ===== MazeGenerator.cpp =====

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

static mt19937 rng(time(0));

MazeGenerator::MazeGenerator(int r,int c)
{
    rows=r;
    cols=c;

    maze.resize(rows,vector<char>(cols,'#'));
}

void MazeGenerator::carvePath(int r,int c)
{
    maze[r][c]='.';

    vector<pair<int,int>> dirs =
    {
        {-2,0},
        {2,0},
        {0,-2},
        {0,2}
    };

    shuffle(dirs.begin(), dirs.end(), rng);

    for(auto dir : dirs)
    {
        int nr = r + dir.first;
        int nc = c + dir.second;

        if(nr>0 && nr<rows-1 &&
           nc>0 && nc<cols-1 &&
           maze[nr][nc]=='#')
        {
            maze[r + dir.first/2][c + dir.second/2]='.';

            carvePath(nr,nc);
        }
    }
}



    void MazeGenerator::generateMaze()
{
    maze.assign(rows, vector<char>(cols,'#'));

    carvePath(1,1);
    for(int i=1;i<rows-1;i++)
{
    for(int j=1;j<cols-1;j++)
    {
        if(maze[i][j]=='#')
        {
            if(rand()%100 < 15)
            {
                maze[i][j]='.';
            }
        }
    }
}

    maze[1][1]='S';

    // find reachable place for E
    for(int i=rows-2;i>=1;i--)
    {
        for(int j=cols-2;j>=1;j--)
        {
            if(maze[i][j]=='.')
            {
                maze[i][j]='E';
                return;
            }
        }
    }
}


void MazeGenerator::displayMaze()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cout<<maze[i][j]<<" ";
        }

        cout<<endl;
    }
}

vector<vector<char>>& MazeGenerator::getMaze()
{
    return maze;
}



// ===== BFSSolver.cpp =====

#include <queue>
#include <iostream>

using namespace std;
int BFSSolver::visitedCount=0;
int BFSSolver::pathLength=0;
bool BFSSolver::solve(vector<vector<char>>& maze)
{
    visitedCount=0;
pathLength=0;
    int rows=maze.size();
    int cols=maze[0].size();

    queue<pair<int,int>> q;

    vector<vector<bool>> visited(
        rows,
        vector<bool>(cols,false)
    );

    vector<vector<pair<int,int>>> parent(
        rows,
        vector<pair<int,int>>(cols,{-1,-1})
    );

    int sr=-1,sc=-1;
    int er=-1,ec=-1;

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(maze[i][j]=='S')
            {
                sr=i;
                sc=j;
            }

            if(maze[i][j]=='E')
            {
                er=i;
                ec=j;
            }
        }
    }

    q.push({sr,sc});
    visited[sr][sc]=true;
    visitedCount=1;

    int dr[4]={-1,1,0,0};
    int dc[4]={0,0,-1,1};

    while(!q.empty())
    {
        auto current=q.front();
        q.pop();

        int r=current.first;
        int c=current.second;

        if(r==er && c==ec)
        {
            break;
        }

        for(int i=0;i<4;i++)
        {
            int nr=r+dr[i];
            int nc=c+dc[i];

            if(nr>=0 && nr<rows &&
               nc>=0 && nc<cols &&
               !visited[nr][nc] &&
               maze[nr][nc]!='#')
            {
                visited[nr][nc]=true;
                visitedCount++;
                parent[nr][nc]={r,c};

                q.push({nr,nc});
            }
        }
    }

    if(!visited[er][ec])
        return false;

    int r=er;
    int c=ec;

    while(!(r==sr && c==sc))
    {
        pathLength++;
        if(maze[r][c]!='E')
            maze[r][c]='*';

        auto p=parent[r][c];

        r=p.first;
        c=p.second;
    }

    return true;
}



// ===== DFSSolver.cpp =====

#include <iostream>
using namespace std;

int DFSSolver::visitedCount = 0;
int DFSSolver::pathLength = 0;

bool dfs(
    vector<vector<char>>& maze,
    vector<vector<bool>>& visited,
    int r,
    int c
)
{
    int rows = maze.size();
    int cols = maze[0].size();

    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return false;

    if (maze[r][c] == '#')
        return false;

    if (visited[r][c])
        return false;

    visited[r][c] = true;
    DFSSolver::visitedCount++;

    if (maze[r][c] == 'E')
        return true;

    // mark tentative path (only for visualization)
    if (maze[r][c] != 'S' && maze[r][c] != 'E')
        maze[r][c] = '*';

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (dfs(maze, visited, nr, nc))
        {
            DFSSolver::pathLength++;
            return true;
        }
    }

    // BACKTRACK (remove wrong path)
    if (maze[r][c] != 'S' && maze[r][c] != 'E')
        maze[r][c] = '.';

    return false;
}

bool DFSSolver::solve(vector<vector<char>>& maze)
{
    visitedCount = 0;
    pathLength = 0;

    int rows = maze.size();
    int cols = maze[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    int sr = -1, sc = -1;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 'S')
            {
                sr = i;
                sc = j;
            }
        }
    }

    return dfs(maze, visited, sr, sc);
}



// ===== DifficultyRater.cpp =====


using namespace std;

string DifficultyRater::rateDifficulty(
    int pathLength,
    int visitedCells,
    int rows,
    int cols
)
{
    int score = 0;

    if(rows * cols > 400)
        score += 2;
    else if(rows * cols > 150)
        score += 1;

    if(pathLength > 50)
        score += 2;
    else if(pathLength > 20)
        score += 1;

    if(visitedCells > 100)
        score += 2;
    else if(visitedCells > 50)
        score += 1;

    if(score >= 5)
        return "HARD";
    else if(score >= 3)
        return "MEDIUM";
    else
        return "EASY";
}



// ===== main.cpp =====

#include <iostream>

using namespace std;

int main()
{
    int rows, cols;

    cout << "Enter rows: ";
    cin >> rows;

    cout << "Enter cols: ";
    cin >> cols;

    MazeGenerator maze(rows, cols);
    maze.generateMaze();

    int choice;

    do
    {
        cout << "\n========== MAZE SOLVER ==========\n";
        cout << "1. Show Maze\n";
        cout << "2. BFS Solve\n";
        cout << "3. DFS Solve\n";
        cout << "4. Generate New Maze\n";
        cout << "5. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                maze.displayMaze();
                break;
            }

            case 2:
            {
                auto bfsMaze = maze.getMaze();

                bool found = BFSSolver::solve(bfsMaze);

                if(found)
                    cout << "\nBFS PATH FOUND!\n";
                else
                    cout << "\nNO PATH FOUND!\n";

                for(auto row : bfsMaze)
                {
                    for(auto cell : row)
                        cout << cell << " ";

                    cout << endl;
                }

                cout << "\nVisited Cells: "
                     << BFSSolver::visitedCount;

                cout << "\nPath Length: "
                     << BFSSolver::pathLength;

                cout << "\nMaze Difficulty: "
                     << DifficultyRater::rateDifficulty(
                            BFSSolver::pathLength,
                            BFSSolver::visitedCount,
                            rows,
                            cols
                        ) << endl;

                break;
            }

            case 3:
            {
                auto dfsMaze = maze.getMaze();

                bool found = DFSSolver::solve(dfsMaze);

                if(found)
                    cout << "\nDFS PATH FOUND!\n";
                else
                    cout << "\nNO PATH FOUND!\n";

                for(auto row : dfsMaze)
                {
                    for(auto cell : row)
                        cout << cell << " ";

                    cout << endl;
                }

                cout << "\nVisited Cells: "
                     << DFSSolver::visitedCount;

                cout << "\nPath Length: "
                     << DFSSolver::pathLength;

                cout << "\nMaze Difficulty: "
                     << DifficultyRater::rateDifficulty(
                            DFSSolver::pathLength,
                            DFSSolver::visitedCount,
                            rows,
                            cols
                        ) << endl;

                break;
            }

            case 4:
            {
                cout << "Enter new rows: ";
                cin >> rows;

                cout << "Enter new cols: ";
                cin >> cols;

                maze = MazeGenerator(rows, cols);
                maze.generateMaze();

                cout << "\nNEW MAZE GENERATED!\n";
                break;
            }

            case 5:
            {
                cout << "\nExiting Program...\n";
                break;
            }

            default:
            {
                cout << "\nInvalid Choice!\n";
            }
        }

    } while(choice != 5);

    return 0;
}

