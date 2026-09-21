#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    size_t len = strnlen(month, 15);
    if (len == 0 || len == 15) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[16];
    lower[0] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is high; the length parameter appears to be a constant, instead of computing the number of characters left. (risk 5, buffer)
     */
    strncat(lower, month, sizeof(lower) - 1);

    for (size_t i = 0; i < sizeof(lower) && lower[i] != '\0'; i++) {
        lower[i] = (char)tolower((unsigned char)lower[i]);
    }

    const char *months[] = {
        "february"
    };

    for (size_t i = 0; i < sizeof(months) / sizeof(months[0]); i++) {
        if (strcmp(lower, months[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",
        "Invalid", "", NULL
    };

    for (size_t i = 0; i < sizeof(test_months) / sizeof(test_months[0]); i++) {
        if (test_months[i] != NULL) {
            if (has_28_days(test_months[i])) {
                printf("%s contains 28 days\n", test_months[i]);
            } else {
                printf("%s does not contain 28 days or is invalid\n", test_months[i]);
            }
        }
    }

    return 0;
}