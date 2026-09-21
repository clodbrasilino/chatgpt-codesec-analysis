#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int starts_with_number(const char *str, int num) {
    if (str == NULL) {
        return 0;
    }

    while (isspace((unsigned char)*str)) {
        str++;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[16];
    int ret = snprintf(num_str, sizeof(num_str), "%d", num);
    if (ret < 0 || ret >= (int)sizeof(num_str)) {
        return 0;
    }

    size_t num_len = (size_t)ret;
    size_t str_len = 0;
    const char *p = str;
    while (*p != '\0' && str_len < num_len) {
        str_len++;
        p++;
    }

    if (str_len < num_len) {
        return 0;
    }

    return (strncmp(str, num_str, num_len) == 0);
}

int main(void) {
    const char *test1 = "123hello";
    const char *test2 = "456world";
    const char *test3 = "  789test";
    const char *test4 = "no_number";

    printf("Test 1: %s\n", starts_with_number(test1, 123) ? "true" : "false");
    printf("Test 2: %s\n", starts_with_number(test2, 123) ? "true" : "false");
    printf("Test 3: %s\n", starts_with_number(test3, 789) ? "true" : "false");
    printf("Test 4: %s\n", starts_with_number(test4, 999) ? "true" : "false");

    return 0;
}