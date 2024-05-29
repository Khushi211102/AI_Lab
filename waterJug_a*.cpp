#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

struct State {
    int jug1;
    int jug2;
    int depth;
    State* parent;

    State(int j1, int j2, int d, State* p) : jug1(j1), jug2(j2), depth(d), parent(p) {}

    bool operator==(const State& other) const {
        return (jug1 == other.jug1) && (jug2 == other.jug2);
    }

    struct Hash {
        size_t operator()(const State& s) const {
            return hash<int>()(s.jug1) ^ hash<int>()(s.jug2);
        }
    };
};

struct CompareStates {
    bool operator()(const State* s1, const State* s2) const {
        return (s1->depth) > (s2->depth);
    }
};

bool isGoalState(const State& state, int target) {
    return (state.jug1 == target) || (state.jug2 == target);
}

int heuristic(const State& state, int target) {
    return abs(state.jug1 - target) + abs(state.jug2 - target);
}

void aStarSearch(int jug1_capacity, int jug2_capacity, int target) {
    priority_queue<State*, vector<State*>, CompareStates> pq;
    unordered_set<State, State::Hash> visited;

    State* initialState = new State(0, 0, 0, nullptr);
    pq.push(initialState);

    while (!pq.empty()) {
        State* currentState = pq.top();
        pq.pop();

        visited.insert(*currentState);

        if (isGoalState(*currentState, target)) {
            while (currentState != nullptr) {
                cout << "(" << currentState->jug1 << ", " << currentState->jug2 << ")" << endl;
                currentState = currentState->parent;
            }
            return;
        }

        for (int i = 0; i <= jug1_capacity; ++i) {
            for (int j = 0; j <= jug2_capacity; ++j) {
                if (i == 0 && j == 0) continue;
                if (i == currentState->jug1 && j == currentState->jug2) continue;

                State nextState(
                    (i == jug1_capacity) ? jug1_capacity : i,
                    (j == jug2_capacity) ? jug2_capacity : j,
                    currentState->depth + 1,
                    currentState
                );

                if (visited.find(nextState) == visited.end()) {
                    pq.push(new State(nextState));
                }
            }
        }
    }

    cout << "No solution found!" << endl;
}

int main() {
    int jug1_capacity = 5;
    int jug2_capacity = 3;
    int target = 4;

    cout << "A* Search Path:" << endl;
    aStarSearch(jug1_capacity, jug2_capacity, target);

    return 0;
}
