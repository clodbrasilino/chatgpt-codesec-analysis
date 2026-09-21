#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long long int get_demlo_number(int n) {
    if (n <= 0) return -1;
    if (n == 1) return 1;

    char num_str[20];
    snprintf(num_str, sizeof(num_str), "%d", n);

    int len = strlen(num_str);
    char final_num[41] = "";

    for (int i = 0; i < len; ++i) {
        if (i == 0) {
            final_num[0] = num_str[i];
            final_num[1] = '\0';
        } else {
            int new_len = strlen(final_num);
            if (new_len + 1 < sizeof(final_num)) {
                strncat(final_num, num_str + i, 1);
                strncat(final_num, final_num, 1);
                for (int j = 0; j < i; j++) {
                    if (strlen(final_num) + 1 < sizeof(final_num)) {
                        strncat(final_num, num_str + (len - j - 1), 1);
                    }
                }
            }
        }
    }

    return atoll(final_num);
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
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