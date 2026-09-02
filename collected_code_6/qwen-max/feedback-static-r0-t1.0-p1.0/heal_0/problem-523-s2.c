#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool check_string_requirements(const char *str, size_t length) {
    if (length == 0 || str == NULL) return false;

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    for (size_t i = 0; i < length; i++) {
        if (isupper(str[i])) has_upper = true;
        if (islower(str[i])) has_lower = true;
        if (isdigit(str[i])) has_digit = true;
    }

    return has_upper && has_lower && has_digit && (strlen(str) == length);
}

int main() {
    const char *test_str = "Ab1";
    size_t test_length = 3;

    if (check_string_requirements(test_str, test_length)) {
        printf("The string meets all requirements.\n");
    } else {
        printf("The string does not meet all requirements.\n");
    }

    return 0;
}