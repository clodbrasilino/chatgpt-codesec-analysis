#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long int get_demlo_number(int n) {
    if (n <= 0) return -1;
    if (n == 1) return 1;

    char num_str[20];
    sprintf(num_str, "%d", n);

    int len = strlen(num_str);
    char final_num[41] = "";

    for (int i = 0; i < len; ++i) {
        if (i == 0) {
            strncpy(final_num, num_str + i, 1);
        } else {
            strncat(final_num, num_str + i, 1);
            strncat(final_num, final_num, 1);
            for (int j = 0; j < i; j++) {
                strncat(final_num, num_str + (len - j - 1), 1);
            }
        }
    }

    return atoll(final_num);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    long long int result = get_demlo_number(number);
    if (result != -1) {
        printf("Demlo number: %lld\n", result);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}