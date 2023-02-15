#include <stdio.h>

int check_top_wall(int x);  // Проверка на соприкосновение мяча с верхней позицией
int check_bot_wall(int x);           // Проверка на сопр с нижней позицией
int check_left_wall(int x);          // Проверка с левой
int check_right_wall(int x);         // Проверка с правой
void score_print(int pl1, int pl2);  // Печать счета
int check_drow_pad(int x, int y, int padx, int pady);  // рисуем ракетки
int check_left_pad(int ball_x, int ball_y, int pad_x, int pad_y);  //функция столкновения с левой ракеткой
int check_right_pad(int ball_x, int ball_y, int pad_x, int pad_y);  //функция столкновения с правой ракеткой

int main() {
    char c;             // вводим символы
    int width = 25;     // длина
    int length = 80;    // ширина
    int ball_x = 40;    //начальная позиция мяча по х
    int ball_y = 12;    // начальная позиция мяча по у
    int speed_x = 1;    // скорость по х
    int speed_y = 1;    // скорость по у
    int pad1_x = 2;     // расположение первой ракетки по х
    int pad1_y = 13;    // расположение первой ракетки по у
    int pad2_x = 77;    //расположение второй ракетки по х
    int pad2_y = 13;    // расположение второй ракетки по у
    int score_pl1 = 0;  //счет первого игрока
    int score_pl2 = 0;  //счет второго игрока

    while (scanf("%c", &c)) {                      // бесконечный ввод до break
        if (score_pl1 == 21 || score_pl2 == 21) {  // счет доходит до 21 и останавливает цикл while
            break;
        }

        if (c != '\n' && c != 'a' && c != 'z' && c != 'k' && c != 'm') {  // обработка недопустимых символов
            if (c == 'q') {  // если мы введем q, то остановим цикл wile
                break;
            }
        }

        if (check_left_wall(ball_x) ==
            1) {  // если равно 1, возвращаем ракетки на начальную позицию и передаем мяч сопернику.
            score_pl2++;  //счет растет на 1
            ball_x = 75;  //передача мяча сопернику
            ball_y = 13;  //
            pad1_x = 2;   //начальные координаты левого игрока
            pad1_y = 13;  //
            pad2_x = 77;  // начальные координаты правого игрока
            pad2_y = 13;  //
        }

        if (check_right_wall(ball_x) ==
            1) {  // аналогично с верзней функцией, только мяч уходит к левому игроку
            score_pl1++;
            ball_x = 4;
            ball_y = 13;
            pad1_x = 2;
            pad1_y = 13;
            pad2_x = 77;
            pad2_y = 13;
        }

        score_print(score_pl1, score_pl2);  // простая функция печати на поле счета
        if (c == 'a') {  // четыре условия для обработки вводимых клавиш одну объясню, остальные на примере
            if (pad1_y > 2) {
                pad1_y -= 1;
            }
        }
        if (c == 'z') {
            if (pad1_y < 22) {
                pad1_y += 1;
            }
        }
        if (c == 'k') {  // к отвечает за перемещение правой ракетки на одну клетку вверх
            if (pad2_y > 2) {  // если координата y второй ракетки больше двух (не дает уйти за границы), то
                               // поднимаем на единицу выше координаты идут снизу вверх
                pad2_y -= 1;
            }
            // printf("\n");
        }
        if (c == 'm') {
            if (pad2_y < 22) {
                pad2_y += 1;
            }
        }

        for (int y = 0; y < width; y++) {       //цикл по игрику по всей ширине
            for (int x = 0; x < length; x++) {  // цикл по иксу по всей ширине
                if (y == 0 || y == width - 1) {  // выставляем знаки равно на нулевой высоте и вконце
                    printf("=");
                } else if (y == ball_y && x == ball_x) {  // совпадение текущей клетки и х и у мяча
                    if (check_top_wall(ball_y) == 1 ||
                        check_bot_wall(ball_y) == 1) {  //проверка на удар об верхнюю и нижнюю клетку
                        speed_y *= -1;  // изменяет движение по игреку, то есть меняет диагональ
                    }
                    if (check_right_pad(ball_x, ball_y, pad2_x, pad2_y) == 1) {
                        speed_x *= -1;  //меняем диагональ
                    }
                    if (check_left_pad(ball_x, ball_y, pad1_x, pad1_y) == 1) {
                        speed_x *= -1;  // меняем диагональ
                    }
                    printf("*");       // в остальных случаях ресуем мяч
                } else if (x == 40) {  //посередине ресуем сетку
                    printf("|");
                } else if ((check_drow_pad(x, y, pad1_x, pad1_y) ==
                                1  // отресовка первой и второй ракетки (проверяется текущая координата и
                                   // координата ракеток)
                            || check_drow_pad(x, y, pad2_x, pad2_y) == 1)) {
                    printf("#");
                } else {  //если условия не выполнены, то просто ставим пробел
                    printf(" ");
                }
            }
            printf("\n");  //после проверки строки, мы переходим на следующую
        }

        ball_x += speed_x;  //простшее движение
        ball_y += speed_y;  // просто прибаляем к координатам 1, знак которой вычесляется ранее таким образом
                            // мяч и двигается по определенным диагоналям
    }
}

int check_top_wall(int y) {
    if (y == 1) {  // если игрек мяча равен 1, то он каснулся верха
        return 1;
    }
    return 0;
}

int check_bot_wall(int y) {
    if (y == 23) {  //если y мяча равен 23 --> Произошло столкновение с низом
        return 1;
    }
    return 0;
}

int check_right_pad(int ball_x, int ball_y, int pad_x, int pad_y) {  //функция столкновения с ракеткой
    if (ball_x == pad_x - 1 && ball_y > pad_y - 2 &&
        pad_y + 2 > ball_y) {  // так как ракетка состоит из 3 клеток, а основной является центральная
        return 1;  // то мы добавляетм еще 2 условия на ниже от центральной и выше от центральной
    }
    return 0;
}

int check_left_pad(int ball_x, int ball_y, int pad_x,
                   int pad_y) {  // все тоже самое,что и выше только левая координата
    if (ball_x == pad_x + 1 && ball_y > pad_y - 2 && pad_y + 2 > ball_y) {
        return 1;
    }
    return 0;
}

int check_drow_pad(int x, int y, int padx, int pady) {
    if (x == padx && y > pady - 2 &&
        pady + 2 > y) {  //ресуем ракетку с доп условиями посредине на клетку ниже и на клетку выше
        return 1;
    }
    return 0;
}

int check_left_wall(int x) {  // передаем координату х мяча и если она равна 1 это означает, что мы каснулись
                              // левой стены --> 1 - проигрыш левого игрока. 0 - все нормально движемся дальше
    if (x == 1) {
        return 1;
    }
    return 0;
}

int check_right_wall(int x) {  //аналогично с функцией выше
    if (x == 79) {
        return 1;
    }
    return 0;
}

void score_print(int pl1, int pl2) {  // функция счета
    printf("                    player1: %d                    player2: %d          \n", pl1, pl2);
}
