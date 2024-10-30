#include <iostream>
#include <ctime>
using namespace std;

/*
    Copyright (c) 2024 VladSamarov
    Mail for contacts webchrgm@gmail.com
*/

int input_int (string text, int min_int, int max_int) {
    string ssize;
    int isize = 0;
    do {
        cout << text;
        cin >> ssize;
        try {
            isize = stoul(ssize);
        } catch (exception) {
            isize = min_int;
        }
    } while (isize < min_int || isize > max_int);
    return isize;
}

int main () {
    srand(time(0));
    int x = 0, y = 0, temp = 0, i = 0, j = 0, k = 0;
    cout << "Map size X by Y" << endl;
    x = input_int("X [5...99]: ", 5, 99);
    y = input_int("Y [5...99]: ", 5, 99);
    cout << endl;
    
    int dx[8] { 1, 1, 1,  0, 0, -1, -1, -1};
    int dy[8] {-1, 0, 1, -1, 1, -1,  0,  1};
    int mines[x + 1][y + 1];
    int ans[x + 1][y + 1];
    char map[x + 1][y + 1];
    
    for (i = 0; i <= x + 1; i++) {
        for (j = 0; j <= y + 1; j++) {
            mines[i][j] = 0;
            ans[i][j] = 0;
            map[i][j] = 35; // 63 = ?, 35 = #
        }
    }
    int count_iter = x * y * .15;
    int max_iter = x * y;
    int count_mines = 0;
    
    while (count_iter > 0) {
        --max_iter;
        if (max_iter < 0)
           break;
        i = (rand() % x) + 1;
        j = (rand() % y) + 1;
        if (mines[i][j] == 0) { 
            temp = 0;
            for (k = 1; k < x; k++)
                temp += mines[k][j];
            if (temp + 1 >= x / 2)
                continue;
            temp = 0;
            for (k = 1; k < y; k++)
                temp += mines[i][k];
            if (temp + 1 >= y / 2)
                continue;
            mines[i][j] = 1;
            count_iter -= 1;
            count_mines += 1;
        }
    }
    int check_count = count_mines;
    cout << "Number of mines - " << count_mines << endl;
    cout << "s - exit the game, f - check the box (P) in place of the mine, o - open the cell" << endl;
    for (i = 1; i <= x; i++) {
        for (j = 1; j <= y; j++) {
            if (mines[i][j] == 1) {
                ans[i][j] = 9;
            } else {
                temp = 0;
                for (k = 0; k < 8; k++)
                    temp += mines[i + dx[k]][j + dy[k]];
                ans[i][j] = temp;
            }
        }
    }
    for (i = 1; i <= x; i++) {
        for (j = 1; j <= y; j++) {
            if (ans[i][j] == 0) {
                map[i][j] = 48; // 48 = 0
                for (k = 0; k < 8; k++) {
                    temp = ans[i + dx[k]][j + dy[k]];
                    map[i + dx[k]][j + dy[k]] = temp + 48;
                }
            }
        }
    }
    int max_step = 0;
    for (i = 1; i <= x; i++) {
        for (j = 1; j <= y; j++) {
            if (map[i][j] == 35) {
                ++max_step;
            }
        }
    }
    cout << endl;
    
    int sx {}, sy {}, step {};
    for (step = 0; step <= max_step + 1; step++) {
        
        if (step >= max_step) {
            count_mines = 0;
        }
        
        for (i = -2; i <= x; i++) {
            for (j = -1; j <= y; j++) {
                cout.width(2);
                if ((i == -1 || i == -2) && j == -1) {
                    cout << ' ';
                } else if (i == -2 && j == 0) {
                    cout << ' ';
                } else if (i == -1 && j == 0) {
                    cout << 'Y';
                } else if (i == -2 && y > 9) {
                    temp = j / 10;
                    if (temp == 0)
                        cout << ' ';
                    else
                        cout << temp;
                } else if (i == -2 && y < 10) {
                    cout << ' ';
                } else if (i == -1) {
                    cout << j % 10;
                } else if (j == -1 && i == 0) {
                    cout << 'X';
                } else if (j == -1) {
                    cout << i;
                } else if (i == 0) {
                    cout << '-';
                } else if (j == 0) {
                    cout << '|';
                } else {
                    if (count_mines == 0) {
                        if (map[i][j] == 80 && mines[i][j] == 1) {
                            --check_count;
                        }
                        if (mines[i][j] == 1) {
                            cout << '*';
                        } else {
                            cout << ans[i][j];
                        }
                    } else {
                        cout << map[i][j];
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
        
        if (count_mines == 0) {
            if (check_count == 0) {
                cout << "All mines were found correctly!";
            } else {
                cout << "The number of mines not found - " << check_count;
            }
            cout << endl;
            break;
        } else {
            if (step == 0)
                cout << "Maximum number of steps - " << max_step << endl;
            else if (step > 0)
                cout << "Steps left - " << max_step - step << endl;
        }
        
        if (step > 0)
            cout << "It remains to find the mines - " << count_mines << endl;
        
        char action {80};
        string saction;
        cout << "s - exit, f - check box, o - open: ";
        cin >> saction;
        if (saction == "f") {
            action = 102;
        } else if (saction == "o") {
            action = 111;
        } else {
            action = 115;
        }
        
        if (action == 102 || action == 111) {
            if (action == 102)
                cout << "Check the box: ";
            if (action == 111)
                cout << "Open a cell: ";
            cout << endl;
            
            sx = input_int("X-coordinate [1..." + to_string(x) + "]: ", 1, x);
            sy = input_int("Y-coordinate [1..." + to_string(y) + "]: ", 1, y);
            
            if (action == 111) {
                if (map[sx][sy] == 80) {
                    ++count_mines;
                }
                if (mines[sx][sy] == 1) {
                    cout << "There's a mine in the cell!" << endl;
                    count_mines = 0;
                } else {
                    map[sx][sy] = ans[sx][sy] + 48;
                }
            } else if (action == 102) {
                if (map[sx][sy] != 80) {
                    map[sx][sy] = 80; // 77 = M, 70 = F, 88 = X, 80 = P
                    --count_mines;
                }
            }
        } else {
            cout << "Exiting the game" << endl;
            break;
        }
        cout << endl;
    }
}
