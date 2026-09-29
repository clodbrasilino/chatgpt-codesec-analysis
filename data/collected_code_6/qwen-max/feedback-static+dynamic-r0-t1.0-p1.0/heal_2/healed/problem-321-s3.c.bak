#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

long long int get_demlo_number(int n) {
    if (n <= 0 || n > 9999) return -1;
    if (n == 1) return 1;

    char num_str[20];
    sprintf(num_str, "%d", n);

    int len = strlen(num_str);
    char final_num[41] = "";

    for (int i = 0; i < len; ++i) {
        char temp[41];
        strcpy(temp, final_num);
        strncat(temp, num_str + i, 1);
        strncat(temp, final_num, strlen(final_num));
        for (int j = 0; j < i; j++) {
            strncat(temp, num_str + (len - j - 1), 1);
        }
        strcpy(final_num, temp);
    }

    return atoll(final_num);
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1 || number < 0 || number > 9999) {
        printf("Invalid input.\n");
        return 1;
    }

    long long int result = get_demlo_number(number);
    if (result != -1) {
        printf("Demlo number: %lld\n", result);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}