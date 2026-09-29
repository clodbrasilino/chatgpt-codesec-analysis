#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_digit_frequency_valid(const char *num) {
    int digits_count[10] = {0};

    for (int i = 0; num[i] != '\0'; i++) {
        if (isdigit(num[i])) {
            digits_count[num[i] - '0']++;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (digits_count[i] > i) {
            return false;
        }
    }

    return true;
}

int main() {
    const char *test_num1 = "22334";
    const char *test_num2 = "9876565432";

    if (is_digit_frequency_valid(test_num1)) {
        printf("%s is valid\n", test_num1);
    } else {
        printf("%s is invalid\n", test_num1);
    }

    if (is_digit_frequency_valid(test_num2)) {
        printf("%s is valid\n", test_num2);
    } else {
        printf("%s is invalid\n", test_num2);
    }

    return 0;
}