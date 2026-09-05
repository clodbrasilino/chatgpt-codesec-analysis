#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validate_string(const char *str, size_t min_len, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);

    if (len < min_len || len > max_len) {
        return 0;
    }

    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;

    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            has_upper = 1;
        } else if (islower((unsigned char)str[i])) {
            has_lower = 1;
        } else if (isdigit((unsigned char)str[i])) {
            has_digit = 1;
        }
    }

    return has_upper && has_lower && has_digit;
}

int main(void) {
    const char *test1 = "Valid123";
    const char *test2 = "invalid";
    const char *test3 = "INVALID123";
    const char *test4 = "Short1";
    const char *test5 = NULL;

    printf("Test 1: %d\n", validate_string(test1, 8, 20));
    printf("Test 2: %d\n", validate_string(test2, 8, 20));
    printf("Test 3: %d\n", validate_string(test3, 8, 20));
    printf("Test 4: %d\n", validate_string(test4, 8, 20));
    printf("Test 5: %d\n", validate_string(test5, 8, 20));

    return 0;
}