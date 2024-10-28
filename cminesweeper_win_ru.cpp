#include <iostream>
#include <ctime>
#include <string>
using namespace std;

/*
    Copyright (c) 2024 VladSamarov
    Mail for contacts webchrgm@gmail.com
*/

int input_int(string text, int min_int, int max_int) {
    string ssize;
    int isize = 0;
    do {
        cout << text;
        cin >> ssize;
        try {
            isize = stoul(ssize);
        }
        catch (exception) {
            isize = min_int;
        }
    } while (isize < min_int || isize > max_int);
    return isize;
}

int main() {
    system("chcp 1251");
    srand(time(0));
    int x = 0, y = 0, temp = 0, i = 0, j = 0, k = 0;
    cout << "Размер карты X на Y" << endl;
    x = input_int("X [5...99]: ", 5, 99);
    y = input_int("Y [5...99]: ", 5, 99);
    cout << endl;

    int dx[8]{ 1, 1, 1,  0, 0, -1, -1, -1 };
    int dy[8]{ -1, 0, 1, -1, 1, -1,  0,  1 };
    int mines[100][100];
    int ans[100][100];
    char map[100][100];

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
        //int i = rand() % (end - start + 1) + start;
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
    cout << "Количество мин - " << count_mines << endl;
    cout << "s - выйти из игры, f - поставить флажок (P) на место мины, o - открыть ячейку" << endl;
    for (i = 1; i <= x; i++) {
        for (j = 1; j <= y; j++) {
            if (mines[i][j] == 1) {
                ans[i][j] = 9;
            }
            else {
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

    int sx{}, sy{}, step{};
    for (step = 0; step <= max_step + 1; step++) {

        if (step >= max_step) {
            count_mines = 0;
        }

        for (i = -2; i <= x; i++) {
            for (j = -1; j <= y; j++) {
                cout.width(2);
                if ((i == -1 || i == -2) && j == -1) {
                    cout << ' ';
                }
                else if (i == -2 && j == 0) {
                    cout << ' ';
                }
                else if (i == -1 && j == 0) {
                    cout << 'Y';
                }
                else if (i == -2 && y > 9) {
                    temp = j / 10;
                    if (temp == 0)
                        cout << ' ';
                    else
                        cout << temp;
                }
                else if (i == -2 && y < 10) {
                    cout << ' ';
                }
                else if (i == -1) {
                    cout << j % 10;
                }
                else if (j == -1 && i == 0) {
                    cout << 'X';
                }
                else if (j == -1) {
                    cout << i;
                }
                else if (i == 0) {
                    cout << '-';
                }
                else if (j == 0) {
                    cout << '|';
                }
                else {
                    if (count_mines == 0) {
                        if (map[i][j] == 80 && mines[i][j] == 1) {
                            --check_count;
                        }
                        if (mines[i][j] == 1) {
                            cout << '*';
                        }
                        else {
                            cout << ans[i][j];
                        }
                    }
                    else {
                        cout << map[i][j];
                    }
                }
            }
            cout << endl;
        }
        cout << endl;

        if (count_mines == 0) {
            if (check_count == 0) {
                cout << "Все мины найдены верно!";
            }
            else {
                cout << "Количество ненайденных мин - " << check_count;
            }
            cout << endl;
            break;
        }
        else {
            if (step == 0)
                cout << "Максимальное количество шагов - " << max_step << endl;
            else if (step > 0)
                cout << "Осталось шагов - " << max_step - step << endl;
        }

        if (step > 0)
            cout << "Осталось найти мин - " << count_mines << endl;

        char action{ 80 };
        string saction;
        cout << "s - выйти, f - флажок, o - открыть: ";
        cin >> saction;
        if (saction == "f") {
            action = 102;
        }
        else if (saction == "o") {
            action = 111;
        }
        else {
            action = 115;
        }

        if (action == 102 || action == 111) {
            if (action == 102)
                cout << "Поставить флажок: ";
            if (action == 111)
                cout << "Открыть ячейку: ";
            cout << endl;

            sx = input_int("координата X [1..." + to_string(x) + "]: ", 1, x);
            sy = input_int("координата Y [1..." + to_string(y) + "]: ", 1, y);

            if (action == 111) {
                // открыть
                if (map[sx][sy] == 80) {
                    ++count_mines;
                }
                if (mines[sx][sy] == 1) {
                    cout << "В ячейке мина!" << endl;
                    count_mines = 0;
                }
                else {
                    map[sx][sy] = ans[sx][sy] + 48;
                }
            }
            else if (action == 102) {
                // флажок
                if (map[sx][sy] != 80) {
                    map[sx][sy] = 80; // 77 = M, 70 = F, 88 = X, 80 = P
                    --count_mines;
                }
            }
        }
        else {
            cout << "Выход из игры" << endl;
            system("pause");
            break;
        }
        cout << endl;
    }
}
