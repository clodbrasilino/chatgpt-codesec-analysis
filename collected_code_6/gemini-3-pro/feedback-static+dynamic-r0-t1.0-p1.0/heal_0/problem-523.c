#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool check_password_strength(const char *str, size_t min_length) {
    if (str == NULL) {
        return false;
    }

    if (strlen(str) < min_length) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            has_upper = true;
        } else if (islower((unsigned char)str[i])) {
            has_lower = true;
        } else if (isdigit((unsigned char)str[i])) {
            has_digit = true;
        }

        if (has_upper && has_lower && has_digit) {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *test_str1 = "Password123";
    const char *test_str2 = "pass123";
    const char *test_str3 = "PASS123";
    const char *test_str4 = "Password";
    const char *test_str5 = "P1";

    size_t req_length = 8;

    printf("%d\n", check_password_strength(test_str1, req_length));
    printf("%d\n", check_password_strength(test_str2, req_length));
    printf("%d\n", check_password_strength(test_str3, req_length));
    printf("%d\n", check_password_strength(test_str4, req_length));
    printf("%d\n", check_password_strength(test_str5, req_length));

    return 0;
}