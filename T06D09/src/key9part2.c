#include <stdio.h>

#define LEN 100

int compare(int *buff1, int len1, int *buff2, int len2) {
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    for (int i = 0; i < len1; i++) {
        if (buff1[i] > buff2[i]) return 1;
        if (buff1[i] < buff2[i]) return -1;
    }
    return 0;
}

void normalize(int *arr, int *len) {
    int count = 0;
    while (count < *len && arr[count] == 0) {
        count++;
    }
    if (count == *len) {
        arr[0] = 0;
        *len = 1;
    } else {
        for (int i = 0; i < *len - count; i++) {
            arr[i] = arr[i + count];
        }
        *len = *len - count;
    }
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int temp[LEN + 1] = {0};
    int index = 0;
    int i1 = len1 - 1, i2 = len2 - 1;
    int carry = 0;

    while (i1 >= 0 || i2 >= 0 || carry) {
        int d1 = (i1 >= 0) ? buff1[i1] : 0;
        int d2 = (i2 >= 0) ? buff2[i2] : 0;
        int total = d1 + d2 + carry;
        carry = total / 10;
        temp[index] = total % 10;
        index++;
        i1--;
        i2--;
    }

    if (index == 0) {
        temp[0] = 0;
        index = 1;
    }

    for (int i = 0; i < index; i++) {
        result[i] = temp[index - 1 - i];
    }
    *result_length = index;
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    if (compare(buff1, len1, buff2, len2) < 0) {
        *result_length = 0;
        return;
    }

    int temp[LEN] = {0};
    int index = 0;
    int i1 = len1 - 1, i2 = len2 - 1;
    int borrow = 0;

    while (i1 >= 0) {
        int d1 = buff1[i1];
        int d2 = (i2 >= 0) ? buff2[i2] : 0;
        int diff = d1 - d2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        temp[index] = diff;
        index++;
        i1--;
        i2--;
    }

    while (index > 1 && temp[index - 1] == 0) {
        index--;
    }

    for (int i = 0; i < index; i++) {
        result[i] = temp[index - 1 - i];
    }
    *result_length = index;
}

int main() {
    int num1[LEN], num2[LEN];
    int len1 = 0, len2 = 0;
    char c;

    while (1) {
        if (scanf("%d", &num1[len1]) != 1) {
            printf("n/a\n");
            return 0;
        }
        len1++;
        c = getchar();
        if (c == '\n' || len1 == LEN) break;
    }

    while (1) {
        if (scanf("%d", &num2[len2]) != 1) {
            printf("n/a\n");
            return 0;
        }
        len2++;
        c = getchar();
        if (c == '\n' || len2 == LEN) break;
    }

    for (int i = 0; i < len1; i++) {
        if (num1[i] < 0 || num1[i] > 9) {
            printf("n/a\n");
            return 0;
        }
    }
    for (int i = 0; i < len2; i++) {
        if (num2[i] < 0 || num2[i] > 9) {
            printf("n/a\n");
            return 0;
        }
    }

    normalize(num1, &len1);
    normalize(num2, &len2);

    int res_sum[LEN + 1];
    int res_sub[LEN];
    int len_sum, len_sub;

    sum(num1, len1, num2, len2, res_sum, &len_sum);
    sub(num1, len1, num2, len2, res_sub, &len_sub);

    for (int i = 0; i < len_sum; i++) {
        printf("%d", res_sum[i]);
        if (i < len_sum - 1) printf(" ");
    }
    printf("\n");

    if (len_sub == 0) {
        printf("n/a\n");
    } else {
        for (int i = 0; i < len_sub; i++) {
            printf("%d", res_sub[i]);
            if (i < len_sub - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
