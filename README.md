在 VS Code Terminal 中輸入以下指令：
gcc -fPIC -c DFS_Sudoku.c -o DFS_Sudoku.o
gcc -fPIC -c BFS_Sudoku.c -o BFS_Sudoku.o
gcc -shared -o libBFSSudoku.dll BFS_Sudoku.o
gcc -shared -o libDFSSudoku.dll DFS_Sudoku.o
gcc sudoku_solver.c -L. -lDFSSudoku -lBFSSudoku -o main
./main
我是用動態連結 lib（應該啦）
==================================================================
google doc：

https://docs.google.com/document/d/19iCwdcd6wHNWvhRv4cU1-kgGNNH2vjvHofuyhSclACU/edit?usp=sharing
