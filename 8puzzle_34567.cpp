#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <queue>
#include <vector>

#define N 3
#define MAX_DEPTH 25

// Node structure to represent a state of the puzzle
struct Node {
    int puzzle[N][N];
    struct Node *parent;
    int x, y;
    int depth;  // Depth for DFS and other depth-based searches
    int cost;   // Cost for Best-First Search
};

// Function to create a new node
struct Node *newNode(int puzzle[N][N], int x, int y, int newX, int newY, int depth, struct Node *parent) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    memcpy(node->puzzle, puzzle, sizeof(node->puzzle));
    node->puzzle[x][y] = node->puzzle[newX][newY];
    node->puzzle[newX][newY] = 0;
    node->x = newX;
    node->y = newY;
    node->parent = parent;
    node->depth = depth;
    node->cost = 0;
    return node;
}

// Function to check if a position is within the puzzle boundaries
bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Function to check if the current puzzle configuration matches the goal
bool isGoal(int puzzle[N][N], int goal[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != goal[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to print the solution path
void printPath(struct Node *node) {
    if (node == NULL) {
        return;
    }
    printPath(node->parent);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", node->puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to calculate the Manhattan distance heuristic
int manhattanDistance(int puzzle[N][N], int goal[N][N]) {
    int distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != 0) {
                for (int k = 0; k < N; k++) {
                    for (int l = 0; l < N; l++) {
                        if (puzzle[i][j] == goal[k][l]) {
                            distance += abs(i - k) + abs(j - l);
                        }
                    }
                }
            }
        }
    }
    return distance;
}

// BFS (Breadth-First Search) implementation
void bfs(int puzzle[N][N], int x, int y, int goal[N][N]) {
    std::queue<struct Node*> q;
    struct Node *root = newNode(puzzle, x, y, x, y, 0, NULL);
    q.push(root);

    while (!q.empty()) {
        struct Node *node = q.front();
        q.pop();

        if (isGoal(node->puzzle, goal)) {
            printf("Solution Path:\n");
            printPath(node);
            return;
        }

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int newX = node->x + dx[i];
            int newY = node->y + dy[i];

            if (isSafe(newX, newY)) {
                struct Node *child = newNode(node->puzzle, node->x, node->y, newX, newY, node->depth + 1, node);
                q.push(child);
            }
        }
    }

    printf("No solution found.\n");
}

// DFS (Depth-First Search) implementation
bool dfs(struct Node *node, int goal[N][N]) {
    if (isGoal(node->puzzle, goal)) {
        printf("Solution Path:\n");
        printPath(node);
        return true;
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newX = node->x + dx[i];
        int newY = node->y + dy[i];

        if (isSafe(newX, newY)) {
            struct Node *child = newNode(node->puzzle, node->x, node->y, newX, newY, node->depth + 1, node);
            if (dfs(child, goal)) {
                return true;
            }
        }
    }
    return false;
}

// Helper function to run DFS
void runDFS(int puzzle[N][N], int x, int y, int goal[N][N]) {
    struct Node *root = newNode(puzzle, x, y, x, y, 0, NULL);
    if (!dfs(root, goal)) {
        printf("No solution found.\n");
    }
}

// Depth-Limited DFS implementation
bool depthLimitedDFS(struct Node *node, int goal[N][N], int limit) {
    if (isGoal(node->puzzle, goal)) {
        printf("Solution Path:\n");
        printPath(node);
        return true;
    }

    if (node->depth >= limit) {
        return false;
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newX = node->x + dx[i];
        int newY = node->y + dy[i];

        if (isSafe(newX, newY)) {
            struct Node *child = newNode(node->puzzle, node->x, node->y, newX, newY, node->depth + 1, node);
            if (depthLimitedDFS(child, goal, limit)) {
                return true;
            }
        }
    }
    return false;
}

// Helper function to run Depth-Limited DFS
void runDepthLimitedDFS(int puzzle[N][N], int x, int y, int goal[N][N], int limit) {
    struct Node *root = newNode(puzzle, x, y, x, y, 0, NULL);
    if (!depthLimitedDFS(root, goal, limit)) {
        printf("No solution found within the depth limit.\n");
    }
}

// Iterative Deepening DFS implementation
bool iterativeDeepeningDFS(int puzzle[N][N], int x, int y, int goal[N][N], int maxDepth) {
    for (int limit = 0; limit <= maxDepth; limit++) {
        struct Node *root = newNode(puzzle, x, y, x, y, 0, NULL);
        if (depthLimitedDFS(root, goal, limit)) {
            return true;
        }
    }
    return false;
}

// Comparator for Best-First Search priority queue
struct compare {
    bool operator()(struct Node* a, struct Node* b) {
        return a->cost > b->cost;
    }
};

// Best-First Search implementation using Manhattan Distance heuristic
void bestFirstSearch(int puzzle[N][N], int x, int y, int goal[N][N]) {
    std::priority_queue<struct Node*, std::vector<struct Node*>, compare> pq;
    struct Node *root = newNode(puzzle, x, y, x, y, 0, NULL);
    root->cost = manhattanDistance(root->puzzle, goal);
    pq.push(root);

    while (!pq.empty()) {
        struct Node *node = pq.top();
        pq.pop();

        if (isGoal(node->puzzle, goal)) {
            printf("Solution Path:\n");
            printPath(node);
            return;
        }

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int newX = node->x + dx[i];
            int newY = node->y + dy[i];

            if (isSafe(newX, newY)) {
                struct Node *child = newNode(node->puzzle, node->x, node->y, newX, newY, node->depth + 1, node);
                child->cost = manhattanDistance(child->puzzle, goal);
                pq.push(child);
            }
        }
    }

    printf("No solution found.\n");
}

// Main function to run all the search algorithms
int main() {
    int puzzle[N][N] = {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };
    int goal[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    int x = 1, y = 2;  // Position of the blank tile (0)
    
    printf("BFS:\n");
    bfs(puzzle, x, y, goal);
    
    printf("DFS:\n");
    runDFS(puzzle, x, y, goal);
    
    printf("Depth-Limited DFS:\n");
    runDepthLimitedDFS(puzzle, x, y, goal, MAX_DEPTH);
    
    printf("Iterative Deepening DFS:\n");
    if (!iterativeDeepeningDFS(puzzle, x, y, goal, MAX_DEPTH)) {
        printf("No solution found within the depth limit.\n");
    }

    printf("Best-First Search:\n");
    bestFirstSearch(puzzle, x, y, goal);
    
    return 0;
}
