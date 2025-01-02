#include <stdio.h>

void BFS_solve(int grid[9][9], int size);
void DFS_solve(int grid[9][9], int size);
//void H_Solve(int grid[9][9], int size);

void print_grid(int grid[9][9], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    printf("\n\nTesting on easy 6x6 grid...\n");
    int grid_6x6_easy[6][6] = {
        {6, 0, 0, 0, 0, 0},
        {0, 0, 1, 3, 0, 6},
        {0, 0, 4, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 4},
        {3, 0, 5, 0, 0, 0}
    };
    printf("Problem:\n");
    print_grid(grid_6x6_easy, 6);
    BFS_solve(grid_6x6_easy, 6);
    DFS_solve(grid_6x6_easy, 6);
    //H_Solve(grid_6x6_easy, 6);

    printf("\n\nTesting on hard 6x6 grid...\n");
    int grid_6x6_hard[6][6] = {
        {0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 5, 0},
        {0, 0, 3, 0, 0, 0},
        {0, 5, 0, 0, 0, 0},
        {6, 0, 0, 5, 4, 0},
        {0, 0, 2, 0, 6, 0}
    };
    printf("Problem:\n");
    print_grid(grid_6x6_hard, 6);
    BFS_solve(grid_6x6_hard, 6);
    DFS_solve(grid_6x6_hard, 6);
    //H_Solve(grid_6x6_hard, 6);

    
    return 0;
}
