#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define SIZE 9
#define HEIGHT 3

typedef struct Node {
    int state[SIZE][SIZE];
    struct Node* next;
} Node;


typedef struct Problem {
    int initial[SIZE][SIZE];
} Problem;

// Check if the current state is legal
bool check_legal(int state[SIZE][SIZE]) {
    int total = 45; 

    // Check each row and column
    for (int i = 0; i < SIZE; i++) {
        int row_sum = 0, col_sum = 0;
        for (int j = 0; j < SIZE; j++) {
            row_sum += state[i][j];
            col_sum += state[j][i];
        }
        if (row_sum != total || col_sum != total) {
            return false;
        }
    }

    // Check each block
    for (int row = 0; row < SIZE; row += HEIGHT) {
        for (int col = 0; col < SIZE; col += HEIGHT) {
            int block_sum = 0;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < HEIGHT; j++) {
                    block_sum += state[row + i][col + j];
                }
            }
            if (block_sum != total) {
                return false;
            }
        }
    }

    return true;
}

// Find the first empty spot (represented by 0)
bool get_spot(int state[SIZE][SIZE], int* row, int* col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (state[i][j] == 0) {
                *row = i;
                *col = j;
                return true;
            }
        }
    }
    return false;
}

// Filter out invalid values in the row
void filter_row(int state[SIZE][SIZE], int row, bool used[SIZE + 1]) {
    for (int col = 0; col < SIZE; col++) {
        if (state[row][col] != 0) {
            used[state[row][col]] = true;
        }
    }
}

// Filter out invalid values in the column
void filter_col(int state[SIZE][SIZE], int col, bool used[SIZE + 1]) {
    for (int row = 0; row < SIZE; row++) {
        if (state[row][col] != 0) {
            used[state[row][col]] = true;
        }
    }
}

// Filter out invalid values in the block
void filter_quad(int state[SIZE][SIZE], int row, int col, bool used[SIZE + 1]) {
    int start_row = (row / HEIGHT) * HEIGHT;
    int start_col = (col / HEIGHT) * HEIGHT;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (state[start_row + i][start_col + j] != 0) {
                used[state[start_row + i][start_col + j]] = true;
            }
        }
    }
}

// Action generator
Node* actions(int state[SIZE][SIZE]) {
    int row, col;
    if (!get_spot(state, &row, &col)) {
        return NULL; 
    }

    bool used[SIZE + 1] = {false};
    filter_row(state, row, used);
    filter_col(state, col, used);
    filter_quad(state, row, col, used);

    Node* head = NULL;
    for (int num = 1; num <= SIZE; num++) {
        if (!used[num]) {
            Node* new_node = (Node*)malloc(sizeof(Node));
            memcpy(new_node->state, state, sizeof(new_node->state));
            new_node->state[row][col] = num;
            new_node->next = head;
            head = new_node;
        }
    }
    return head;
}

// DFS
int** DFS(Problem* problem) {
    Node* stack = (Node*)malloc(sizeof(Node));
    memcpy(stack->state, problem->initial, sizeof(stack->state));
    stack->next = NULL;

    while (stack) {
        Node* node = stack;
        stack = stack->next;

        if (check_legal(node->state)) {
            int** solution = (int**)malloc(SIZE * sizeof(int*));
            for (int i = 0; i < SIZE; i++) {
                solution[i] = (int*)malloc(SIZE * sizeof(int));
                memcpy(solution[i], node->state[i], SIZE * sizeof(int));
            }
            free(node);
            return solution;
        }

        Node* children = actions(node->state);
        while (children) {
            Node* child = children;
            children = children->next;
            child->next = stack;
            stack = child;
        }
        free(node);
    }

    return NULL;
}

// dfs solver
void DFS_solve(int board[SIZE][SIZE]) {
    printf("\nSolving with DFS...\n");

    clock_t start_time = clock();
    Problem problem;
    memcpy(problem.initial, board, sizeof(problem.initial));

    int** solution = DFS(&problem);
    clock_t end_time = clock();

    if (solution) {
        printf("Found solution:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", solution[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("No possible solutions\n");
    }

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.2f seconds\n", elapsed_time);
}