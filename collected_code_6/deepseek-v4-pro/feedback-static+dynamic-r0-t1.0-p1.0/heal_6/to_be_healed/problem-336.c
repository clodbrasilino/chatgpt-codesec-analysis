#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t month_len = strlen(month);
    char *lower_month = malloc(month_len + 1);
    if (lower_month == NULL) {
        return 0;
    }

    for (size_t i = 0; i < month_len; i++) {
        lower_month[i] = tolower((unsigned char)month[i]);
    }
    lower_month[month_len] = '\0';

    int result = 0;
    if (strcmp(lower_month, "february") == 0) {
        result = 1;
    }

    free(lower_month);
    return result;
}

int main(void) {
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",
        "february", "FEBRUARY", "Feb", "", NULL
    };

    for (int i = 0; months[i] != NULL; i++) {
        printf("%s: %s\n", months[i], has_28_days(months[i]) ? "has 28 days" : "does not have 28 days");
    }

    return 0;
}