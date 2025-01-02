#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Board dimensions (standard Sudoku is 9x9)
#define SIZE 9
#define HEIGHT 3

// Define the Node structure
typedef struct Node {
    int state[SIZE][SIZE];  // Board state
    int action[3];          // [value, row, column]
    struct Node* next;      // Used for the queue
} Node;

// Define the Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

// Initialize the queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// Check if the queue is empty
bool isEmpty(Queue* q) {
    return q->size == 0;
}

// Enqueue operation
void enqueue(Queue* q, Node* newNode) {
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// Dequeue operation
Node* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;
    Node* temp = q->front;
    q->front = q->front->next;
    q->size--;
    if (q->front == NULL) q->rear = NULL;
    return temp;
}

// Create a new node
Node* createNode(int state[SIZE][SIZE], int value, int row, int col) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->state, state, SIZE * SIZE * sizeof(int));
    newNode->action[0] = value;
    newNode->action[1] = row;
    newNode->action[2] = col;
    newNode->next = NULL;
    return newNode;
}

// Check if a number is valid in the given position
bool isValid(int state[SIZE][SIZE], int row, int col, int value) {
    // Check the row
    for (int i = 0; i < SIZE; i++) {
        if (state[row][i] == value) return false;
    }
    // Check the column
    for (int i = 0; i < SIZE; i++) {
        if (state[i][col] == value) return false;
    }
    // Check the subgrid
    int startRow = (row / HEIGHT) * HEIGHT;
    int startCol = (col / HEIGHT) * HEIGHT;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (state[startRow + i][startCol + j] == value) return false;
        }
    }
    return true;
}

// Check if the board is complete (no empty cells)
bool isComplete(int state[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (state[i][j] == 0) return false;
        }
    }
    return true;
}

// BFS algorithm to solve Sudoku
Node* BFS(int initial[SIZE][SIZE]) {
    Queue queue;
    initQueue(&queue);
    clock_t start_time = clock();

    Node* root = createNode(initial, 0, 0, 0);
    enqueue(&queue, root);

    while (!isEmpty(&queue)) {
        Node* current = dequeue(&queue);

        if (isComplete(current->state)) {
            return current;  // Solution found
        }

        // Find the first empty cell
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (current->state[row][col] == 0) {
                    // Try all possible values in the empty cell
                    for (int value = 1; value <= SIZE; value++) {
                        if (isValid(current->state, row, col, value)) {
                            Node* child = createNode(current->state, value, row, col);
                            child->state[row][col] = value;
                            enqueue(&queue, child);
                        }
                    }
                    return NULL;  // Stop further exploration of this branch
                }
            }
        }
    }
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.2f seconds\n", elapsed_time);
    return NULL;  // No solution found
}

// Print the board
void printBoard(int state[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%2d ", state[i][j]);
        }
        printf("\n");
    }
}


