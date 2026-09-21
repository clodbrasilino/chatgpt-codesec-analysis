#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_28_days(const char *month) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[20];
    int i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < sizeof(lower_month) - 1 && month[i] != '\0'; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[i] = '\0';

    if (strcmp(lower_month, "february") == 0 || strcmp(lower_month, "feb") == 0) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *test_months[] = {"February", "March", "Feb", "january", NULL};
    
    for (int i = 0; i < 5; i++) {
        if (test_months[i] != NULL) {
            if (has_28_days(test_months[i])) {
                printf("%s has 28 days.\n", test_months[i]);
            } else {
                printf("%s does not have 28 days.\n", test_months[i]);
            }
        }
    }

    return 0;
}