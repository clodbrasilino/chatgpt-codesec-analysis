#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_password_strength(const char *str, size_t max_len, size_t min_length) {
    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;
    size_t length = 0;
    size_t i;

    if (str == NULL || max_len == 0) {
        return 0;
    }

    while (length < max_len && str[length] != '\0') {
        length++;
    }

    if (length < min_length || length >= max_len) {
        return 0;
    }

    for (i = 0; i < length; i++) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[257];
    size_t min_len = 8;
    size_t len;

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strcspn(password, "\n");
    password[len] = '\0';

    if (len == sizeof(password) - 1 && password[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Password too long\n");
        return 1;
    }

    if (check_password_strength(password, sizeof(password), min_len)) {
        printf("Password meets requirements\n");
    } else {
        printf("Password does not meet requirements\n");
    }

    return 0;
}