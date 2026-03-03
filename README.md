# Sudoku Solver — DFS & BFS

## Overview

This project implements a Sudoku solver using two fundamental search algorithms:

- Depth-First Search (DFS)
- Breadth-First Search (BFS)

The goal of this project is to explore state-space search strategies and compare their performance in solving constraint satisfaction problems like Sudoku.

---
### Depth-First Search (DFS)

DFS explores one branch of the search tree as deep as possible before backtracking.

**Advantages:**
- Lower memory usage
- Faster solution discovery in many Sudoku cases

**Disadvantages:**
- May explore deep invalid branches before backtracking

---

### Breadth-First Search (BFS)

BFS explores all nodes at the current depth before moving deeper.

**Advantages:**
- Guaranteed to find the shallowest solution
- Systematic exploration

**Disadvantages:**
- Very high memory consumption
- Not practical for complex Sudoku puzzles

---

## Implementation Details
####  Board Representation
- Standard 9×9 Sudoku grid.
- Empty cells are represented by `0`.
- Each cell stores an integer (1–9 for numbers, 0 for empty).

---

#### BFS (Breadth-First Search) Implementation
- Uses a **queue** to explore states level by level.
- Each node stores:
  - Current board state (`state[9][9]`)
  - The last action performed (`action = [value, row, column]`)
  - Pointer to next node in the queue.
- Algorithm steps:
  1. Initialize the queue with the root node (initial board).
  2. While the queue is not empty:
     - Dequeue a node.
     - Check if the board is complete → return solution if yes.
     - Find the first empty cell.
     - Generate child nodes for each valid value in that cell.
     - Enqueue each valid child node.
  3. Continue until a solution is found or the queue is empty.
- Pros: Finds the shallowest solution, systematic search.
- Cons: High memory consumption due to storing all frontier nodes.

---

#### DFS (Depth-First Search) Implementation
- Uses a **stack** to explore states by diving deep first.
- Each node stores:
  - Current board state (`state[9][9]`)
  - Pointer to the next node in the stack.
- Algorithm steps:
  1. Initialize the stack with the root node (initial board).
  2. While the stack is not empty:
     - Pop a node from the stack.
     - Check if the board is valid and complete → print solution if yes.
     - Expand the first empty cell with all legal numbers.
     - Push all valid child nodes onto the stack.
  3. Repeat until a solution is found or the stack is empty.
- Pros: Low memory usage, efficient backtracking.
- Cons: May explore deep invalid branches unnecessarily.

---

#### Validity Checks
- For both BFS and DFS:
  - Row check: No repeated numbers in a row.
  - Column check: No repeated numbers in a column.
  - Subgrid check: No repeated numbers in the 3×3 subgrid.

---

#### Node Expansion
- BFS: Creates a new node for each valid number in the first empty cell, enqueues it.
- DFS: Creates a new node for each valid number, pushes onto the stack for deeper exploration.

---

## Performance Comparison

| Algorithm | Time Efficiency | Memory Usage | Practicality |
|------------|-----------------|--------------|--------------|
| DFS        | High            | Low          | Recommended  |
| BFS        | Low             | Very High    | Not practical for full Sudoku |
