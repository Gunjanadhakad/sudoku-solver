#include <iostream>
#include <cstdlib>
#include <ctime>

#define N 9
#define EMPTY 0

bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if num is already present in the current row
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // Check if num is already present in the current column
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // Check if num is already present in the current 3x3 subgrid
    int subgridStartRow = row - row % 3;
    int subgridStartCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[subgridStartRow + i][subgridStartCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool findEmptyCell(int grid[N][N], int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;
    if (!findEmptyCell(grid, row, col)) {
        return true;  // Sudoku solved
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;  // Subgrid solved
            }

            // Undo the current assignment and try the next value
            grid[row][col] = EMPTY;
        }
    }

    return false;  // No solution found
}

void generateSudoku(int grid[N][N]) {
    // Clear the grid
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            grid[row][col] = EMPTY;
        }
    }

    solveSudoku(grid);  // Generate a solved Sudoku grid

    // Remove random cells to create a puzzle
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    int cellsToRemove = 40;  // Adjust the number of cells to remove for the desired difficulty level

    while (cellsToRemove > 0) {
        int row = rand() % N;
        int col = rand() % N;

        if (grid[row][col] != EMPTY) {
            grid[row][col] = EMPTY;
            cellsToRemove--;
        }
    }
}

void displaySudoku(int grid[N][N]) {
    std::cout << "Sudoku Grid:" << std::endl;
    std::cout << "-------------" << std::endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == EMPTY) {
                std::cout << "- ";
            } else {
                std::cout << grid[row][col] << " ";
            }
            if ((col + 1) % 3 == 0) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
        if ((row + 1) % 3 == 0) {
            std::cout << "-------------" << std::endl;
        }
    }
}

bool compareSudoku(int grid1[N][N], int grid2[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid1[row][col] != grid2[row][col]) {
                return false;
            }
        }
    }
    return true;
}

void playSudokuGame() {
    int puzzleGrid[N][N];     // Sudoku puzzle grid
    int solutionGrid[N][N];   // Solution grid entered by the user

    generateSudoku(puzzleGrid);  // Generate a new Sudoku puzzle

    std::cout << "Welcome to Sudoku!" << std::endl;
    std::cout << "Enter your solution (0 for empty cells):" << std::endl;

    // Display the generated Sudoku puzzle
    displaySudoku(puzzleGrid);

    // Take input from the user for the solution grid
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            std::cout << "Enter value for row " << row + 1 << ", column " << col + 1 << ": ";
            std::cin >> solutionGrid[row][col];
        }
    }

    // Check if the solution matches the correct solution
    bool isCorrect = compareSudoku(puzzleGrid, solutionGrid);

    if (isCorrect) {
        std::cout << "Congratulations! You solved the Sudoku puzzle correctly!" << std::endl;
    } else {
        std::cout << "Your solution is incorrect. Keep trying!" << std::endl;
    }
}

int main() {
    playSudokuGame();

    return 0;
}
