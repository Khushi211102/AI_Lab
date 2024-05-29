#include <iostream>
#include <unordered_set>
#include <stack>
#include <vector>
#include <tuple>

using namespace std;

// State structure representing the state of the jugs
struct State {
    int jug1;      // Amount of water in the first jug
    int jug2;      // Amount of water in the second jug
    int depth;     // Depth in the search tree (number of moves)
    State* parent; // Pointer to the parent state (for path reconstruction)

    // Constructor for the State
    State(int j1, int j2, int d, State* p) : jug1(j1), jug2(j2), depth(d), parent(p) {}

    // Equality operator to compare two states
    bool operator==(const State& other) const {
        return (jug1 == other.jug1) && (jug2 == other.jug2);
    }

    // Hash function for the State structure to use it in unordered_set
    struct Hash {
        size_t operator()(const State& s) const {
            return hash<int>()(s.jug1) ^ hash<int>()(s.jug2);
        }
    };
};

// Function to check if the current state is the goal state
bool isGoalState(const State& state, int target) {
    return (state.jug1 == target) || (state.jug2 == target);
}

// Heuristic function to estimate the cost from the current state to the goal
int heuristic(const State& state, int target) {
    return abs(state.jug1 - target) + abs(state.jug2 - target);
}

// Depth-limited search function used in IDA*
bool depthLimitedSearch(State* currentState, int jug1_capacity, int jug2_capacity, int target, int limit, unordered_set<State, State::Hash>& visited) {
    stack<State*> stack;
    stack.push(currentState);

    while (!stack.empty()) {
        State* current = stack.top();
        stack.pop();

        // If the goal state is found, print the path and return true
        if (isGoalState(*current, target)) {
            while (current != nullptr) {
                cout << "(" << current->jug1 << ", " << current->jug2 << ")" << endl;
                current = current->parent;
            }
            return true;
        }

        visited.insert(*current);

        // Generate all possible next states
        vector<State*> nextStates = {
            new State(jug1_capacity, current->jug2, current->depth + 1, current), // Fill jug1
            new State(current->jug1, jug2_capacity, current->depth + 1, current), // Fill jug2
            new State(0, current->jug2, current->depth + 1, current),             // Empty jug1
            new State(current->jug1, 0, current->depth + 1, current),             // Empty jug2
            new State(max(0, current->jug1 - (jug2_capacity - current->jug2)), min(jug2_capacity, current->jug2 + current->jug1), current->depth + 1, current), // Pour jug1 -> jug2
            new State(min(jug1_capacity, current->jug1 + current->jug2), max(0, current->jug2 - (jug1_capacity - current->jug1)), current->depth + 1, current)  // Pour jug2 -> jug1
        };

        // For each next state, if it hasn't been visited and is within the depth limit, push it onto the stack
        for (State* nextState : nextStates) {
            if (visited.find(*nextState) == visited.end() && (nextState->depth + heuristic(*nextState, target)) <= limit) {
                stack.push(nextState);
            }
        }
    }

    return false; // No solution found within the current depth limit
}

// Iterative Deepening A* Search function
void iterativeDeepeningAStarSearch(int jug1_capacity, int jug2_capacity, int target) {
    for (int limit = 0; limit < 100; ++limit) { // Arbitrarily chosen depth limit
        unordered_set<State, State::Hash> visited; // Set to keep track of visited states
        State* initialState = new State(0, 0, 0, nullptr); // Initial state with empty jugs
        if (depthLimitedSearch(initialState, jug1_capacity, jug2_capacity, target, limit, visited)) {
            return; // Solution found and printed by depthLimitedSearch
        }
    }

    cout << "No solution found!" << endl; // If no solution is found within the depth limit
}

int main() {
    int jug1_capacity = 5; // Capacity of the first jug
    int jug2_capacity = 3; // Capacity of the second jug
    int target = 4;        // Target amount of water to measure

    cout << "Iterative Deepening A* Search Path:" << endl;
    iterativeDeepeningAStarSearch(jug1_capacity, jug2_capacity, target);

    return 0;
}
