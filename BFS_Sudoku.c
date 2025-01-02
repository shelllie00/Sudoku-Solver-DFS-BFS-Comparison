#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 9
#define HEIGHT 3
#define QUEUE_CAPACITY 100000 // if 10000, example 3 will result in queue overflow

typedef struct Node {
    int state[SIZE][SIZE];
    int action[3]; // {number, row, column}
} Node;

typedef struct Queue {
    Node* data[QUEUE_CAPACITY];
    int front;
    int rear;
} Queue;

// Queue functions
Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = 0;
    return q;
}

int is_empty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    if ((q->rear + 1) % QUEUE_CAPACITY == q->front) {
        printf("Queue overflow\n");
        exit(1);
    }
    q->data[q->rear] = node;
    q->rear = (q->rear + 1) % QUEUE_CAPACITY;
}

Node* dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    Node* node = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    return node;
}

// Utility functions
void copy_state(int dest[SIZE][SIZE], int src[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int is_valid(int grid[SIZE][SIZE], int row, int col, int num) {
    int row_start = (row / HEIGHT) * HEIGHT;
    int col_start = (col / 3) * 3;

    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return 0;
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[row_start + i][col_start + j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

int get_empty_spot(int grid[SIZE][SIZE], int* row, int* col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

int is_solution_valid(int grid[SIZE][SIZE]) {
    int total = 45; // 1 + 2 + ... + 9

    for (int i = 0; i < SIZE; i++) {
        int row_sum = 0, col_sum = 0;
        for (int j = 0; j < SIZE; j++) {
            row_sum += grid[i][j];
            col_sum += grid[j][i];
        }
        if (row_sum != total || col_sum != total) {
            return 0;
        }
    }

    for (int row = 0; row < SIZE; row += HEIGHT) {
        for (int col = 0; col < SIZE; col += 3) {
            int block_sum = 0;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < 3; j++) {
                    block_sum += grid[row + i][col + j];
                }
            }
            if (block_sum != total) {
                return 0;
            }
        }
    }

    return 1;
}

void BFS_solve(int board[SIZE][SIZE]) {
    printf("\nSolving with BFS...\n");
    clock_t start_time = clock();

    Node* root = (Node*)malloc(sizeof(Node));
    copy_state(root->state, board);

    Queue* frontier = create_queue();
    enqueue(frontier, root);

    while (!is_empty(frontier)) {
        Node* node = dequeue(frontier);

        int row, col;
        if (!get_empty_spot(node->state, &row, &col)) {
            if (is_solution_valid(node->state)) {
                printf("Found solution:\n");
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        printf("%d ", node->state[i][j]);
                    }
                    printf("\n");
                }
                clock_t end_time = clock();
                printf("Elapsed time: %.2f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
                free(frontier);
                return;
            }
        }

        for (int num = 1; num <= SIZE; num++) {
            if (is_valid(node->state, row, col, num)) {
                Node* child = (Node*)malloc(sizeof(Node));
                copy_state(child->state, node->state);
                child->state[row][col] = num;
                enqueue(frontier, child);
            }
        }
        free(node);
    }

    printf("No possible solutions\n");
    clock_t end_time = clock();
    printf("Elapsed time: %.2f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    free(frontier);
}
