#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long int get_demlo_number(int n) {
    if (n <= 0) return -1;
    if (n == 1) return 1;

    char num_str[22];
    snprintf(num_str, sizeof(num_str), "%d", n);

    size_t len = strlen(num_str);
    char final_num[41] = "";

    for (int i = 0; i < len; ++i) {
        char temp_final_num[41];
        snprintf(temp_final_num, sizeof(temp_final_num), "%s%c", final_num, num_str[i]);
        for (int j = 0; j < i; j++) {
            size_t temp_len = strlen(temp_final_num);
            if (temp_len < sizeof(temp_final_num) - 1) {
                strncat(temp_final_num, &num_str[len - j - 1], 1);
            }
        }
        strncpy(final_num, temp_final_num, sizeof(final_num) - 1);
        final_num[sizeof(final_num) - 1] = '\0';
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