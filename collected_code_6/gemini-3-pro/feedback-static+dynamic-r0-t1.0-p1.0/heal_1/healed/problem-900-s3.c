#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with_number(const char *str, int num) {
    if (str == NULL) {
        return 0;
    }

    char num_str[32];
    int snprintf_result = snprintf(num_str, sizeof(num_str), "%d", num);

    if (snprintf_result < 0 || (size_t)snprintf_result >= sizeof(num_str)) {
        return 0;
    }

    return strncmp(str, num_str, (size_t)snprintf_result) == 0;
}

int main(void) {
    const char *test_str1 = "42 is the answer";
    const char *test_str2 = "420 is not 42";
    const char *test_str3 = "Hello 42";
    const char *test_str4 = NULL;

    int num1 = 42;
    int num2 = 42;
    int num3 = 123;
    int num4 = 42;

    printf("Result 1: %d\n", starts_with_number(test_str1, num1));
    printf("Result 2: %d\n", starts_with_number(test_str2, num2));
    printf("Result 3: %d\n", starts_with_number(test_str3, num3));
    printf("Result 4: %d\n", starts_with_number(test_str4, num4));

    return 0;
}