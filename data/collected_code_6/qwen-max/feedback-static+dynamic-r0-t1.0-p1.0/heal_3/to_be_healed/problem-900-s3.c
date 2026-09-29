#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int starts_with_number(const char *str, int number) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[12];
    snprintf(num_str, sizeof(num_str), "%d", number);
    size_t num_len = 0;
    /* Possible weaknesses found:
     *  Array index 'num_len' is used before limits check. [arrayIndexThenCheck]
     */
    while (num_str[num_len] && num_len < sizeof(num_str) - 1) {
        ++num_len;
    }
    return strncmp(str, num_str, num_len) == 0;
}

int main() {
    const char *test_str = "1234_start";
    int test_num = 1234;
    if (starts_with_number(test_str, test_num)) {
        printf("The string starts with the number %d.\n", test_num);
    } else {
        printf("The string does not start with the number %d.\n", test_num);
    }
    return 0;
}