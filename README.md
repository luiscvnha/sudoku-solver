# Sudoku Solver

A simple terminal application that solves Sudoku puzzles.

## Installation

```
$ make
```

## How to use

In to order to represent empty squares, you can use either a space or a 0.

### Interactive mode
#### 1. Execute

```
$ ./sudokusolver -i
```

#### 2. Input the grid

```
   123456789
  +---------
1 | 624 573
2 | 8 7 32 9
3 | 7 92 65
4 |  16  8 4
5 |  9 315 7
6 |        3
7 |4    7  2
8 |21    4
9 |7 32 49 6
```

#### 3. Get the solution

```
+-----------------------+
| 9 6 2 | 4 1 5 | 7 3 8 |
| 1 8 5 | 7 6 3 | 2 4 9 |
| 3 7 4 | 9 2 8 | 6 5 1 |
|-------+-------+-------|
| 5 3 1 | 6 7 2 | 8 9 4 |
| 6 4 9 | 8 3 1 | 5 2 7 |
| 8 2 7 | 5 4 9 | 1 6 3 |
|-------+-------+-------|
| 4 9 6 | 1 5 7 | 3 8 2 |
| 2 1 8 | 3 9 6 | 4 7 5 |
| 7 5 3 | 2 8 4 | 9 1 6 |
+-----------------------+
```

### Non-interactive mode
#### 1. Execute

```
$ ./sudokusolver < inputs/level6/1.txt
```

#### 2. Get the solution

```
+-----------------------+
| 7 9 8 | 5 1 4 | 6 2 3 |
| 6 3 4 | 7 9 2 | 8 1 5 |
| 1 5 2 | 3 6 8 | 4 9 7 |
|-------+-------+-------|
| 4 8 6 | 2 3 7 | 9 5 1 |
| 9 2 1 | 6 4 5 | 7 3 8 |
| 5 7 3 | 9 8 1 | 2 4 6 |
|-------+-------+-------|
| 3 4 7 | 8 5 9 | 1 6 2 |
| 2 1 5 | 4 7 6 | 3 8 9 |
| 8 6 9 | 1 2 3 | 5 7 4 |
+-----------------------+
```
