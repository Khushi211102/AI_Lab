#include <bits/stdc++.h>
using namespace std;

vector<int> a(10);

int make2() {
    if (a[5] == 2) {
        return 5;
    }
    for (int i = 2; i <= 8; i += 2) {
        if (a[i] == 2) {
            return i;
        }
    }
    return 0;
}

int posswin(int p) {
    if (p == 1) {
        int mul = 1;
        int ch = -1;
        for (int j = 1; j <= 3; j++) {
            mul = 1;
            for (int i = 3 * (j - 1) + 1; i <= 3 * j; i++) {
                mul *= a[i];
                if (a[i] == 2) {
                    ch = i;
                }
            }
            if (mul == 18) {
                return ch;
            }
        }

        for (int j = 1; j <= 3; j++) {
            mul = 1;
            for (int i = j; i <= 9; i += 3) {
                mul *= a[i];
                if (a[i] == 2) {
                    ch = i;
                }
            }
            if (mul == 18) {
                return ch;
            }
        }

        mul = 1;
        for (int i = 1; i <= 9; i += 4) {
            mul *= a[i];
            if (a[i] == 2) {
                ch = i;
            }
        }
        if (mul == 18) {
            return ch;
        }

        mul = 1;
        for (int i = 3; i <= 7; i += 3) {
            mul *= a[i];
            if (a[i] == 2) {
                ch = i;
            }
        }
        if (mul == 18) {
            return ch;
        }
        return 0;
    } else {
        int mul = 1;
        int ch = -1;
        for (int j = 1; j <= 3; j++) {
            mul = 1;
            for (int i = 3 * (j - 1) + 1; i <= 3 * j; i++) {
                mul *= a[i];
                if (a[i] == 2) {
                    ch = i;
                }
            }
            if (mul == 50) {
                return ch;
            }
        }

        for (int j = 1; j <= 3; j++) {
            mul = 1;
            for (int i = j; i <= 9; i += 3) {
                mul *= a[i];
                if (a[i] == 2) {
                    ch = i;
                }
            }
            if (mul == 50) {
                return ch;
            }
        }

        mul = 1;
        for (int i = 1; i <= 9; i += 4) {
            mul *= a[i];
            if (a[i] == 2) {
                ch = i;
            }
        }
        if (mul == 50) {
            return ch;
        }

        mul = 1;
        for (int i = 3; i <= 7; i += 2) {
            mul *= a[i];
            if (a[i] == 2) {
                ch = i;
            }
        }
        if (mul == 50) {
            return ch;
        }
        return 0;
    }
}

void go(int n, int p) {
    if (p == 1) {
        a[n] = 3;
    } else {
        a[n] = 5;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cout << "Choose 1 for First and 2 for Second" << endl;
    int n;
    cin >> n;

    // 1 2 3
    // 4 5 6
    // 7 8 9
    for (int i = 0; i < 10; i++) {
        a[i] = 2;
    }

    int cnt = 1;
    if (n == 1) {
        while (cnt < 10) {
            if (cnt % 2 == 1) {
                for (int i = 1; i <= 9; i++) {
                    cout << a[i] << " ";
                    if (i % 3 == 0) {
                        cout << endl;
                    }
                }
                cout << "Choose a Position" << endl;
                int x;
                cin >> x;
                while (a[x] != 2) {
                    cout << "Wrong Position" << endl;
                    cin >> x;
                }
                // go(x,1);
                a[x] = 3;
            } 
            else {
                if (cnt == 2) {
                    if (a[5] == 2) {
                        a[5] = 5;
                    } else {
                        a[1] = 5;
                    }
                }
                if (cnt == 4) {
                    int ch = posswin(1);
                    if (ch != 0) {
                        a[ch] = 5;
                    } else {
                        int d = make2();
                        a[d] = 5;
                    }
                }
                if (cnt == 6) {
                    int ch = posswin(2);
                    // cout << ch << " posswin" << endl;
                    if (ch > 0) {
                        a[ch] = 5;
                        for (int i = 1; i <= 9; i++) {
                            cout << a[i] << " ";
                            if (i % 3 == 0) {
                                cout << endl;
                            }
                        }
                        cout << "Computer Wins" << endl;
                        return 0;
                    } else if (posswin(1)) {
                        a[posswin(1)] = 5;
                    } else {
                        a[make2()] = 5;
                    }
                }
                if (cnt == 8) {
                    int ch = posswin(2);
                    // cout << ch << " posswin" << endl;
                    if (ch > 0) {
                        a[ch] = 5;
                        for (int i = 1; i <= 9; i++) {
                            cout << a[i] << " ";
                            if (i % 3 == 0) {
                                cout << endl;
                            }
                        }
                        cout << "Computer Wins" << endl;
                        return 0;
                    } else if (posswin(1)) {
                        a[posswin(1)] = 5;
                    } else {
                        for (int i = 1; i <= 9; i++) {
                            if (a[i] == 2) {
                                a[i] = 5;
                                break;
                            }
                        }
                    }
                }
            }
            cnt++;
            // cout << cnt << endl;
        }
        cout << "Draw" << endl;
        for (int i = 1; i <= 9; i++) {
            cout << a[i] << " ";
            if (i % 3 == 0) {
                cout << endl;
            }
        }
    } else {
        while (cnt < 10) {
            if (cnt % 2 == 0) {
                for (int i = 1; i <= 9; i++) {
                    cout << a[i] << " ";
                    if (i % 3 == 0) {
                        cout << endl;
                    }
                }
                cout << "Choose a Position" << endl;
                int x;
                cin >> x;
                while (a[x] != 2) {
                    cout << "Wrong Position" << endl;
                    cin >> x;
                }
                go(x, 2);
            } else {
                if (cnt == 1) {
                    a[1] = 3;
                }
                if (cnt == 3) {
                    if (a[9] == 2) {
                        a[9] = 3;
                    } else {
                        a[3] = 3;
                    }
                }
                if (cnt == 5) {
                    int ch = posswin(1);
                    if (ch > 0) {
                        a[ch] = 3;
                        for (int i = 1; i <= 9; i++) {
                            cout << a[i] << " ";
                            if (i % 3 == 0) {
                                cout << endl;
                            }
                        }
                        cout << "Computer Wins" << endl;
                        return 0;
                    } else if (posswin(2)) {
                        a[posswin(2)] = 3;
                    } else if (a[7] == 2) {
                        a[7] = 3;
                    } else {
                        a[3] = 3;
                    }
                }
                if (cnt == 7) {
                    int ch = posswin(1);
                    if (ch > 0) {
                        a[ch] = 3;
                        for (int i = 1; i <= 9; i++) {
                            cout << a[i] << " ";
                            if (i % 3 == 0) {
                                cout << endl;
                            }
                        }
                        cout << "Computer Wins" << endl;
                        return 0;
                    } else if (posswin(2)) {
                        a[posswin(2)] = 3;
                    } else {
                        for (int i = 1; i <= 9; i++) {
                            if (a[i] == 2) {
                                a[i] = 5;
                                break;
                            }
                        }
                    }
                }
                if (cnt == 9) {
                    int ch = posswin(1);
                    if (ch > 0) {
                        a[ch] = 3;
                        for (int i = 1; i <= 9; i++) {
                            cout << a[i] << " ";
                            if (i % 3 == 0) {
                                cout << endl;
                            }
                        }
                        cout << "Computer Wins" << endl;
                        return 0;
                    } else if (posswin(2)) {
                        a[posswin(2)] = 3;
                    } else {
                        for (int i = 1; i <= 9; i++) {
                            if (a[i] == 2) {
                                a[i] = 5;
                                break;
                            }
                        }
                    }
                }
            }
            cnt++;
        }
        cout << "Draw" << endl;
        for (int i = 1; i <= 9; i++) {
            cout << a[i] << " ";
            if (i % 3 == 0) {
                cout << endl;
            }
        }
    }

    return 0;
}
