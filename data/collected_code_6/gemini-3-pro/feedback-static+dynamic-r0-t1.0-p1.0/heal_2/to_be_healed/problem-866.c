#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_31_days(const char *month_name) {
    if (month_name == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[20];
    size_t i = 0;
    
    while (i < sizeof(month) - 1 && month_name[i] != '\0') {
        month[i] = (char)tolower((unsigned char)month_name[i]);
        i++;
    }
    month[i] = '\0';

    if (strcmp(month, "january") == 0 || strcmp(month, "jan") == 0) return 1;
    if (strcmp(month, "march") == 0 || strcmp(month, "mar") == 0) return 1;
    if (strcmp(month, "may") == 0) return 1;
    if (strcmp(month, "july") == 0 || strcmp(month, "jul") == 0) return 1;
    if (strcmp(month, "august") == 0 || strcmp(month, "aug") == 0) return 1;
    if (strcmp(month, "october") == 0 || strcmp(month, "oct") == 0) return 1;
    if (strcmp(month, "december") == 0 || strcmp(month, "dec") == 0) return 1;

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