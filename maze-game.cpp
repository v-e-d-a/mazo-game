#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include<bits/stdc++.h>

using namespace std;

struct Cell {
    int row;
    int col;
};

bool isValidMove(const vector<vector<char>>& maze, int row, int col) {
    int numRows = maze.size();
    int numCols = maze[0].size();
    return (row >= 0 && row < numRows && col >= 0 && col < numCols && maze[row][col] != '#');
}

vector<Cell> findPath(const vector<vector<char>>& maze, const Cell& start, const Cell& end) {
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
    vector<vector<Cell>> parent(maze.size(), vector<Cell>(maze[0].size(), {-1, -1}));

    int numRows = maze.size();
    int numCols = maze[0].size();

    queue<Cell> q;
    q.push(start);
    visited[start.row][start.col] = true;

    while (!q.empty()) {
        Cell curr = q.front();
        q.pop();

        int currRow = curr.row;
        int currCol = curr.col;

        if (currRow == end.row && currCol == end.col) {
            vector<Cell> path;
            while (currRow != -1 && currCol != -1) {
                path.push_back({currRow, currCol});
                Cell prev = parent[currRow][currCol];
                currRow = prev.row;
                currCol = prev.col;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Check all four possible neighbors
        vector<int> dr = {-1, 0, 1, 0};
        vector<int> dc = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int newRow = currRow + dr[i];
            int newCol = currCol + dc[i];

            if (isValidMove(maze, newRow, newCol) && !visited[newRow][newCol]) {
                q.push({newRow, newCol});
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = {currRow, currCol};
            }
        }
    }

    return {}; // Return an empty path if no path is found
}

void printMaze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() {
    // Read the maze from file
    vector<vector<char>> maze;
    ifstream in("maze1.txt");
    string line;
    while (getline(in, line)) {
        vector<char> row(line.begin(), line.end());
        maze.push_back(row);
    }
    in.close();

    // Start and end cells
    Cell start = {0, 0};
   Cell end = {static_cast<int>(maze.size()) - 1, static_cast<int>(maze[0].size()) - 1};


    // Find and print the path
    vector<Cell> path = findPath(maze, start, end);
    if (!path.empty()) {
        cout << "Path found!" << endl;
        for (const auto& cell : path) {
            maze[cell.row][cell.col] = '*';
        }
        printMaze(maze);
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}
