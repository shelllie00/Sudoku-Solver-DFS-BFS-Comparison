#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 9 // Change this value if grid size changes
#define HEIGHT (SIZE / 3)

typedef struct Node {
    int state[SIZE][SIZE];
    struct Node *next;
} Node;

// Function prototypes
bool check_legal(int state[SIZE][SIZE]);
Node* expand(Node* node, int size);
Node* create_node(int state[SIZE][SIZE]);
void push(Node** stack, Node* node);
Node* pop(Node** stack);
bool is_empty(Node* stack);
void print_solution(int state[SIZE][SIZE]);

bool check_legal(int state[SIZE][SIZE]) {
    int total = SIZE * (SIZE + 1) / 2;

    // Check rows and columns
    for (int row = 0; row < SIZE; row++) {
        int row_sum = 0, col_sum = 0;
        for (int col = 0; col < SIZE; col++) {
            row_sum += state[row][col];
            col_sum += state[col][row];
        }
        if (row_sum != total || col_sum != total) {
            return false;
        }
    }

    // Check quadrants
    for (int row = 0; row < SIZE; row += HEIGHT) {
        for (int col = 0; col < SIZE; col += HEIGHT) {
            int block_sum = 0;
            for (int r = 0; r < HEIGHT; r++) {
                for (int c = 0; c < HEIGHT; c++) {
                    block_sum += state[row + r][col + c];
                }
            }
            if (block_sum != total) {
                return false;
            }
        }
    }

    return true;
}

Node* expand(Node* node, int size) {
    // Create a list of valid states
    Node* head = NULL;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (node->state[row][col] == 0) {
                for (int num = 1; num <= size; num++) {
                    int new_state[SIZE][SIZE];
                    memcpy(new_state, node->state, sizeof(new_state));
                    new_state[row][col] = num;

                    if (check_legal(new_state)) {
                        Node* new_node = create_node(new_state);
                        new_node->next = head;
                        head = new_node;
                    }
                }
                return head;
            }
        }
    }
    return head;
}

Node* create_node(int state[SIZE][SIZE]) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    memcpy(new_node->state, state, sizeof(new_node->state));
    new_node->next = NULL;
    return new_node;
}

void push(Node** stack, Node* node) {
    node->next = *stack;
    *stack = node;
}

Node* pop(Node** stack) {
    if (*stack == NULL) {
        return NULL;
    }
    Node* top = *stack;
    *stack = (*stack)->next;
    return top;
}

bool is_empty(Node* stack) {
    return stack == NULL;
}

void print_solution(int state[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", state[i][j]);
        }
        printf("\n");
    }
}

void DFS_solve(int board[SIZE][SIZE]) {
    printf("\nSolving with DFS...\n");

    clock_t start_time = clock();

    Node* start = create_node(board);
    Node* stack = NULL;
    push(&stack, start);

    while (!is_empty(stack)) {
        Node* node = pop(&stack);
        if (check_legal(node->state)) {
            printf("Found solution:\n");
            print_solution(node->state);
            free(node);
            break;
        }

        Node* children = expand(node, SIZE);
        while (children) {
            Node* child = children;
            children = children->next;
            push(&stack, child);
        }

        free(node);
    }

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.2f seconds\n", elapsed_time);
}

