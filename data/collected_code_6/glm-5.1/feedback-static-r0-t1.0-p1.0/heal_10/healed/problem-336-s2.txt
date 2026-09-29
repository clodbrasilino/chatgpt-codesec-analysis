#include <stdio.h>
#include <strings.h>
#include <stdbool.h>
#include <stdint.h>

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    size_t max_len = 15;
    size_t len = 0;
    while (len < max_len && month[len] != '\0') {
        len++;
    }

    if (len == 0 || len >= max_len) {
        return false;
    }

    return strcasecmp(month, "february") == 0;
}

int main(void) {
    const char *test_months[] = {"January", "February", "february", "FEBRUARY", "March", NULL};
    
    for (size_t i = 0; test_months[i] != NULL; i++) {
        if (has_28_days(test_months[i])) {
            printf("%s contains 28 days\n", test_months[i]);
        } else {
            printf("%s does not contain 28 days exclusively (or is invalid)\n", test_months[i]);
        }
    }

    return 0;
}