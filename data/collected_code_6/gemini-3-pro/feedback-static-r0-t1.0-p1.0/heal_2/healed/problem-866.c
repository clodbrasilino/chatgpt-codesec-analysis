#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_match(const char *input, const char *target) {
    while (*input && *target) {
        if (tolower((unsigned char)*input) != *target) {
            return 0;
        }
        input++;
        target++;
    }
    return (*input == '\0' && *target == '\0');
}

int has_31_days(const char *month_name) {
    if (month_name == NULL) {
        return 0;
    }

    if (is_match(month_name, "january") || is_match(month_name, "jan")) return 1;
    if (is_match(month_name, "march") || is_match(month_name, "mar")) return 1;
    if (is_match(month_name, "may")) return 1;
    if (is_match(month_name, "july") || is_match(month_name, "jul")) return 1;
    if (is_match(month_name, "august") || is_match(month_name, "aug")) return 1;
    if (is_match(month_name, "october") || is_match(month_name, "oct")) return 1;
    if (is_match(month_name, "december") || is_match(month_name, "dec")) return 1;

    return 0;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "MARCH", "april", "May", "june",
        "JULY", "August", "September", "OCTOBER", "November", "December",
        "Jan", "Feb", "INVALID", NULL
    };

    size_t num_tests = sizeof(test_months) / sizeof(test_months[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_months[i] != NULL) {
            int result = has_31_days(test_months[i]);
            printf("%s: %s\n", test_months[i], result ? "Yes" : "No");
        }
    }

    return 0;
}