#include <stdio.h>
#include "BFS_Sudoku.h"
#include "DFS_Sudoku.h"


void print_grid(int grid[9][9]) {
    int size = 9;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    printf("\n\nTesting on invalid 9x9 grid\n");
    int invalid_grid[9][9] = {
        {0, 0, 9, 0, 7, 0, 0, 0, 5},
        {0, 0, 2, 1, 0, 0, 9, 0, 0},
        {1, 0, 0, 0, 2, 8, 0, 0, 0},
        {0, 7, 0, 0, 0, 5, 0, 0, 1},
        {0, 0, 8, 5, 1, 0, 0, 0, 0},
        {0, 5, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 6},
        {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 1, 0, 0, 0, 0, 0, 8, 7}
    };
    print_grid(invalid_grid);
    BFS_solve(invalid_grid);
    DFS_solve(invalid_grid);
    //H_Solve(invalid_grid,9);

    printf("\n\nTesting on easy 9x9 grid\n");
    int easy_grid[9][9] = {
        {0, 0, 7, 2, 8, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 5, 0, 6},
        {4, 1, 3, 0, 0, 6, 0, 8, 0},
        {7, 2, 0, 3, 9, 0, 0, 0, 0},
        {3, 4, 0, 0, 0, 0, 8, 1, 0},
        {6, 8, 0, 1, 0, 7, 0, 0, 2},
        {0, 0, 0, 6, 7, 4, 0, 2, 3},
        {0, 0, 0, 0, 0, 5, 7, 0, 0},
        {1, 0, 6, 0, 2, 3, 0, 4, 0}
    };
    print_grid(easy_grid);
    BFS_solve(easy_grid);
    DFS_solve(easy_grid);
    //H_Solve(easy_grid,9);
    
    printf("\n\nTesting on medium 9x9 grid\n");
    int medium_grid[9][9] = {
        {0, 0, 0, 0, 5, 0, 9, 7, 6},
        {8, 0, 5, 1, 9, 0, 0, 3, 0},
        {3, 7, 0, 0, 4, 0, 0, 8, 0},
        {0, 8, 0, 0, 0, 0, 0, 0, 9},
        {0, 2, 0, 0, 0, 0, 4, 0, 7},
        {0, 9, 0, 0, 2, 6, 0, 1, 5},
        {0, 0, 0, 0, 8, 1, 6, 0, 0},
        {9, 0, 0, 3, 0, 0, 0, 0, 0},
        {2, 0, 0, 4, 0, 9, 0, 0, 0}
    };
    print_grid(medium_grid);
    BFS_solve(medium_grid);
    DFS_solve(medium_grid);
    //H_Solve(medium_grid, 9);

    printf("\n\nTesting on hard 9x9 grid\n");
    int hard_grid[9][9] = {
        {0, 3, 0, 0, 0, 1, 5, 0, 0},
        {0, 0, 0, 5, 0, 0, 0, 8, 4},
        {0, 0, 5, 0, 0, 7, 0, 6, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 0, 2, 0, 0, 0, 7, 0},
        {0, 0, 0, 8, 5, 0, 0, 0, 9},
        {0, 0, 3, 0, 9, 4, 0, 0, 7},
        {0, 0, 4, 0, 0, 0, 0, 0, 8},
        {5, 0, 6, 0, 1, 0, 0, 0, 0}
    };
    print_grid(hard_grid);
    BFS_solve(hard_grid);
    DFS_solve(hard_grid);
    //H_Solve(hard_grid, 9);

    
    return 0;
}
