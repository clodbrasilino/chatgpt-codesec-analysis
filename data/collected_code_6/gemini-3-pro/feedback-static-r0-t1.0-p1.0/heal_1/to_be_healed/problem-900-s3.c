#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with_number(const char *str, int num) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[32];
    int snprintf_result = snprintf(num_str, sizeof(num_str), "%d", num);

    if (snprintf_result < 0 || (size_t)snprintf_result >= sizeof(num_str)) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t num_len = strlen(num_str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);

    if (str_len < num_len) {
        return 0;
    }

    return strncmp(str, num_str, num_len) == 0;
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