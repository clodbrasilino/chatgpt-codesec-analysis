#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_valid_password(const char *password, size_t max_len) {
    if (password == NULL) {
        return false;
    }

    size_t len = strnlen(password, max_len);
    if (len < 8 || len >= max_len) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = password[i];
        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else if (ispunct(c)) {
            has_special = true;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <password>\n", argv[0]);
        return 1;
    }

    if (is_valid_password(argv[1], 129)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}