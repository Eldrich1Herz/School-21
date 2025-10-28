/*------------------------------------
    Здравствуй, человек!
    Чтобы получить ключ
    поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

void input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
    Функция получает массив данных
    через stdin.
    Выдает в stdout особую сумму
    и сформированный массив
    специальных элементов
    (выбранных с помощью найденной суммы):
    это и будет частью ключа
-------------------------------------*/
int main() {
    int buffer[10];
    int length;
    input(buffer, &length);

    if (length < 1 || length > 10) {
        printf("n/a");
        return 0;
    }

    int sum = sum_numbers(buffer, length);
    if (sum == 0) {
        printf("n/a");
        return 0;
    }

    int numbers[10];
    int count = find_numbers(buffer, length, sum, numbers);
    printf("%d\n", sum);
    output(numbers, count);
    return 0;
}

/*------------------------------------
    Функция должна находить
    сумму четных элементов
    с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0 && buffer[i] != 0) {
            sum += buffer[i];
        }
    }
    return sum;
}

/*------------------------------------
    Функция должна находить
    все элементы, на которые нацело
    делится переданное число и
    записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[count] = buffer[i];
            count++;
        }
    }
    return count;
}

void input(int *buffer, int *length) {
    if (scanf("%d", length) != 1) {
        *length = 0;
        return;
    }
    for (int i = 0; i < *length; i++) {
        if (scanf("%d", &buffer[i]) != 1) {
            *length = 0;
            return;
        }
    }
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i < length - 1) {
            printf(" ");
        }
    }
    printf("\n");
}