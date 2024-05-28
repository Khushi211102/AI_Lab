#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 3

struct Node {
    int puzzle[N][N];
    struct Node *parent;
    int x, y;
};

struct Node *newNode(int puzzle[N][N], int x, int y, struct Node *parent) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    memcpy(node->puzzle, puzzle, sizeof(node->puzzle));
    node->x = x;
    node->y = y;
    node->parent = parent;
    return node;
}

bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

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

// maxDepth: The maximum depth or level to search to (a depth limit for the search).
// currentDepth: The current depth or level in the search.
bool dfs(struct Node *node, int goal[N][N], int maxDepth, int currentDepth) {
    // ensures that the search doesn't go deeper than the specified maximum depth.
    if (currentDepth > maxDepth) {
        return false; // Reached maximum depth without finding the goal.
    }
    if (isGoal(node->puzzle, goal)) {
        printf("Solution Path:\n");
        printPath(node);
        return true;
    }
    // dx contains horizontal changes (left and right), and dy contains vertical changes (up and down).
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int newX = node->x + dx[i];
        int newY = node->y + dy[i];
        if (isSafe(newX, newY)) {
            struct Node *child = newNode(node->puzzle, newX, newY, node);
            child->puzzle[node->x][node->y] = child->puzzle[newX][newY];
            child->puzzle[newX][newY] = 0;
            child->x = newX;
            child->y = newY;
            // the dfs function is then called recursively with the child node as the new
            // current state(node), and currentDepth + 1 to increase the depth by one.
            if (dfs(child, goal, maxDepth, currentDepth + 1)) {
                return true; // solution has been found, so the function immediately returns true
            }
        }
    }
    return false;
}

int main() {
    int puzzle[N][N] = {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };
    int goal[N][N] = {
        {1, 2, 3},
        {5, 8, 6},
        {0, 7, 4}
    };
    int x = 1, y = 2;  // Position of the blank tile (0)
    int maxDepth = 25; // Maximum depth to limit DFS search
    if (!dfs(newNode(puzzle, x, y, NULL), goal, maxDepth, 0)) {
        printf("No solution exists within the specified depth.\n");
    }
    return 0;
}
