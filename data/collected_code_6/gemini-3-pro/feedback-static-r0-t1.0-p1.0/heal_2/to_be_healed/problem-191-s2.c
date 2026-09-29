#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month_name) {
    if (month_name == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(month_name);
    char *month = (char *)malloc(len + 1);
    if (month == NULL) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        month[i] = (char)tolower((unsigned char)month_name[i]);
    }
    month[len] = '\0';

    int result = 0;
    if (strcmp(month, "april") == 0 || 
        strcmp(month, "june") == 0 || 
        strcmp(month, "september") == 0 || 
        strcmp(month, "november") == 0 ||
        strcmp(month, "apr") == 0 ||
        strcmp(month, "jun") == 0 ||
        strcmp(month, "sep") == 0 ||
        strcmp(month, "nov") == 0) {
        result = 1;
    }

    free(month);
    return result;
}

int main(void) {
    const char *test_months[] = {
        "April", "January", "june", "FEBRUARY", "September", "nov", NULL
    };

    for (size_t i = 0; test_months[i] != NULL; i++) {
        if (has_30_days(test_months[i])) {
            printf("%s has 30 days.\n", test_months[i]);
        } else {
            printf("%s does not have 30 days.\n", test_months[i]);
        }
    }

    return 0;
}