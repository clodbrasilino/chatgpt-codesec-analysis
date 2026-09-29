#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

int starts_with_number(const char *str, int number) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[32];
    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    snprintf(num_str, sizeof(num_str), "%" PRIdMAX, (intmax_t)number);
    size_t len = strnlen(num_str, sizeof(num_str));
    if (strncmp(str, num_str, len) == 0) {
        return 0;
    }
    return -1;
}

int main() {
    const char *test_str = "1234_start";
    int test_num = 1234;
    if (starts_with_number(test_str, test_num) == 0) {
        printf("The string starts with the number %d.\n", test_num);
    } else {
        printf("The string does not start with the number %d.\n", test_num);
    }
    return 0;
}