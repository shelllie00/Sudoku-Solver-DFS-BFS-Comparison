#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 9

typedef struct {
    int state[MAX_SIZE][MAX_SIZE];
} Node;

typedef struct {
    int size;
    int height;
    int initial[MAX_SIZE][MAX_SIZE];
} Problem;

void copy_state(int dest[MAX_SIZE][MAX_SIZE], int src[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

bool check_legal(Problem *problem, int state[MAX_SIZE][MAX_SIZE]) {
    int exp_sum = (problem->size * (problem->size + 1)) / 2;

    for (int row = 0; row < problem->size; row++) {
        int row_sum = 0, col_sum = 0;

        for (int col = 0; col < problem->size; col++) {
            row_sum += state[row][col];
            col_sum += state[col][row];
        }

        if (row_sum != exp_sum || col_sum != exp_sum) {
            return false;
        }
    }

    for (int row_start = 0; row_start < problem->size; row_start += problem->height) {
        for (int col_start = 0; col_start < problem->size; col_start += 3) {
            int block_sum = 0;

            for (int i = 0; i < problem->height; i++) {
                for (int j = 0; j < 3; j++) {
                    block_sum += state[row_start + i][col_start + j];
                }
            }

            if (block_sum != exp_sum) {
                return false;
            }
        }
    }

    return true;
}

int *filter_values(int *values, int values_len, int *used, int used_len, int *filtered_len) {
    int *filtered = (int *)malloc(values_len * sizeof(int));
    int count = 0;

    for (int i = 0; i < values_len; i++) {
        bool is_used = false;
        for (int j = 0; j < used_len; j++) {
            if (values[i] == used[j]) {
                is_used = true;
                break;
            }
        }
        if (!is_used) {
            filtered[count++] = values[i];
        }
    }

    *filtered_len = count;
    return filtered;
}

void get_spot(Problem *problem, int state[MAX_SIZE][MAX_SIZE], int *row, int *col) {
    int min_options = problem->size + 1;
    int options[MAX_SIZE];
    int options_len;

    for (int i = 0; i < problem->size; i++) {
        for (int j = 0; j < problem->size; j++) {
            if (state[i][j] == 0) {
                options_len = problem->size;
                for (int k = 0; k < problem->size; k++) {
                    options[k] = k + 1;
                }

                for (int k = 0; k < problem->size; k++) {
                    if (state[i][k] != 0) {
                        options[state[i][k] - 1] = 0;
                    }
                    if (state[k][j] != 0) {
                        options[state[k][j] - 1] = 0;
                    }
                }

                int row_start = (i / problem->height) * problem->height;
                int col_start = (j / 3) * 3;

                for (int r = row_start; r < row_start + problem->height; r++) {
                    for (int c = col_start; c < col_start + 3; c++) {
                        if (state[r][c] != 0) {
                            options[state[r][c] - 1] = 0;
                        }
                    }
                }

                int count = 0;
                for (int k = 0; k < problem->size; k++) {
                    if (options[k] != 0) {
                        count++;
                    }
                }

                if (count < min_options) {
                    min_options = count;
                    *row = i;
                    *col = j;
                }
            }
        }
    }
}

void actions(Problem *problem, int state[MAX_SIZE][MAX_SIZE], Node **nodes, int *num_nodes) {
    int row, col;
    get_spot(problem, state, &row, &col);

    int values[MAX_SIZE];
    for (int i = 0; i < problem->size; i++) {
        values[i] = i + 1;
    }

    int used[MAX_SIZE];
    int used_len = 0;

    for (int i = 0; i < problem->size; i++) {
        if (state[row][i] != 0) {
            used[used_len++] = state[row][i];
        }
        if (state[i][col] != 0) {
            used[used_len++] = state[i][col];
        }
    }

    int row_start = (row / problem->height) * problem->height;
    int col_start = (col / 3) * 3;

    for (int r = row_start; r < row_start + problem->height; r++) {
        for (int c = col_start; c < col_start + 3; c++) {
            if (state[r][c] != 0) {
                used[used_len++] = state[r][c];
            }
        }
    }

    int filtered_len;
    int *filtered_values = filter_values(values, problem->size, used, used_len, &filtered_len);

    for (int i = 0; i < filtered_len; i++) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        copy_state(new_node->state, state, problem->size);
        new_node->state[row][col] = filtered_values[i];
        nodes[*num_nodes] = new_node;
        (*num_nodes)++;
    }

    free(filtered_values);
}

Node *DFS(Problem *problem) {
    Node *start = (Node *)malloc(sizeof(Node));
    copy_state(start->state, problem->initial, problem->size);

    if (check_legal(problem, start->state)) {
        return start;
    }

    Node *stack[1000];
    int stack_size = 0;

    stack[stack_size++] = start;

    while (stack_size > 0) {
        Node *node = stack[--stack_size];

        if (check_legal(problem, node->state)) {
            return node;
        }

        Node *children[100];
        int num_children = 0;

        actions(problem, node->state, children, &num_children);

        for (int i = 0; i < num_children; i++) {
            stack[stack_size++] = children[i];
        }

        free(node);
    }

    return NULL;
}
