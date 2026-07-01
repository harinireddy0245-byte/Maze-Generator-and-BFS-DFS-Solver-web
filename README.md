# Maze Generator and Solver Using BFS and DFS

## Project Overview

The **Maze Generator and Solver** is a C++ application developed to demonstrate the concepts of maze generation and pathfinding algorithms. The project combines recursive maze generation with two widely used graph traversal algorithms, **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**, to create and solve random mazes. It also evaluates the generated maze by assigning a difficulty level based on several performance metrics.

The primary objective of this project is to help users understand how search algorithms operate in different scenarios while providing a simple and interactive console-based interface. The application allows users to generate random mazes of custom dimensions, visualize them, solve them using BFS or DFS, and compare the results based on the number of visited cells and path length.

---

## Features

The project offers the following features:

- Random maze generation using recursive backtracking.
- User-defined maze dimensions.
- Automatic placement of the start (`S`) and end (`E`) points.
- Maze solving using **Breadth-First Search (BFS)**.
- Maze solving using **Depth-First Search (DFS)**.
- Visualization of the discovered solution path.
- Display of the total number of visited cells.
- Calculation of the discovered path length.
- Automatic maze difficulty rating as **Easy**, **Medium**, or **Hard**.
- Interactive menu-driven console application.

---

## Technologies Used

- **Programming Language:** C++
- **Compiler:** GNU G++ Compiler
- **Integrated Development Environment (IDE):** Visual Studio Code
- **Version Control:** Git and GitHub

### Standard Libraries Used

- `<iostream>`
- `<vector>`
- `<queue>`
- `<algorithm>`
- `<random>`
- `<ctime>`
- `<string>`

---

## Project Description

The project begins by prompting the user to enter the desired number of rows and columns for the maze. Based on the provided dimensions, the program generates a random maze consisting of walls and open pathways. The recursive backtracking algorithm is used to ensure that every generated maze contains a valid route from the starting point to the destination.

Once the maze is created, the application displays an interactive menu through which the user can perform different operations. The generated maze can be displayed at any time, or the user can choose either the Breadth-First Search (BFS) or Depth-First Search (DFS) algorithm to solve it.

The **Breadth-First Search (BFS)** algorithm explores neighboring cells level by level. It guarantees the shortest possible path from the source to the destination whenever a path exists. During execution, the algorithm records every visited cell and reconstructs the shortest route after reaching the destination.

The **Depth-First Search (DFS)** algorithm follows a recursive strategy by exploring one path as deeply as possible before backtracking whenever a dead end is encountered. Although DFS does not always produce the shortest path, it provides an efficient recursive traversal mechanism and effectively demonstrates graph exploration techniques.

After solving the maze, the application displays the solution path by marking the visited route. It also reports the total number of visited cells and the overall path length. These values are then passed to the **Difficulty Rater**, which estimates the complexity of the generated maze based on its size, explored nodes, and solution length.

---

## Project Structure

The project is divided into multiple modules to improve readability, maintainability, and modularity.

| Module | Description |
|---------|-------------|
| **MazeGenerator** | Generates random mazes using recursive backtracking. |
| **BFSSolver** | Solves the maze using Breadth-First Search. |
| **DFSSolver** | Solves the maze using Depth-First Search. |
| **DifficultyRater** | Evaluates maze complexity based on predefined metrics. |
| **Main Program** | Provides the user interface and integrates all project modules. |

---

## Algorithm Workflow

1. Accept the maze dimensions from the user.
2. Generate a random maze using recursive backtracking.
3. Place the starting (`S`) and ending (`E`) points.
4. Display the generated maze.
5. Solve the maze using either BFS or DFS.
6. Highlight the discovered solution path.
7. Display the number of visited cells.
8. Display the path length.
9. Calculate and display the maze difficulty.
10. Allow the user to generate another maze or exit.

---

## How to Compile and Run

### Compile

```bash
g++ main.cpp MazeGenerator.cpp BFSSolver.cpp DFSSolver.cpp DifficultyRater.cpp -o MazeGenerator
```

### Run

**Windows**

```bash
MazeGenerator.exe
```

**Linux / macOS**

```bash
./MazeGenerator
```

---

## Sample Menu

```text
========== MAZE SOLVER ==========

1. Show Maze
2. BFS Solve
3. DFS Solve
4. Generate New Maze
5. Exit
```

---

## Difficulty Rating

The maze difficulty is determined using three parameters:

- Maze dimensions
- Number of visited cells
- Solution path length

Based on these values, the maze is classified as:

- **Easy**
- **Medium**
- **Hard**

---

## Applications

This project can be applied in several domains, including:

- Artificial Intelligence
- Robotics Navigation
- Graph Theory
- Data Structures and Algorithms
- Educational Demonstrations
- Game Development
- Pathfinding Simulations

---

## Future Enhancements

The project can be further improved by incorporating additional features such as:

- Graphical User Interface (GUI)
- A* Search Algorithm
- Dijkstra's Algorithm
- Maze Saving and Loading
- Adjustable Difficulty Levels
- Performance Comparison Graphs
- Animated Maze Solving
- Multiple Maze Generation Techniques

---

## Conclusion

The **Maze Generator and Solver Using BFS and DFS** successfully demonstrates the practical implementation of maze generation and graph traversal algorithms using C++. The project integrates recursive maze generation, two fundamental pathfinding algorithms, and a difficulty evaluation mechanism into a single interactive application. Its modular architecture, simple user interface, and algorithm visualization make it an effective educational tool for understanding graph traversal techniques and maze-solving strategies. Furthermore, the project provides a strong foundation for future enhancements such as graphical visualization, advanced search algorithms, and real-time performance analysis.
  
