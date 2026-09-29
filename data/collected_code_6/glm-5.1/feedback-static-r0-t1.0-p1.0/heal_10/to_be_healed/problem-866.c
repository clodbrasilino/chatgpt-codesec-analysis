#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_31_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[16];
    size_t i;
    for (i = 0; i < sizeof(lower) - 1 && month[i] != '\0'; i++) {
        lower[i] = tolower((unsigned char)month[i]);
    }
    lower[i] = '\0';

    if (strcmp(lower, "january") == 0 ||
        strcmp(lower, "march") == 0 ||
        strcmp(lower, "may") == 0 ||
        strcmp(lower, "july") == 0 ||
        strcmp(lower, "august") == 0 ||
        strcmp(lower, "october") == 0 ||
        strcmp(lower, "december") == 0) {
        return true;
    }

    if (month[i] != '\0') {
        return false;
    }

    return false;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    for (size_t i = 0; i < sizeof(test_months) / sizeof(test_months[0]); i++) {
        printf("%s: %d\n", test_months[i], has_31_days(test_months[i]));
    }

    return 0;
}