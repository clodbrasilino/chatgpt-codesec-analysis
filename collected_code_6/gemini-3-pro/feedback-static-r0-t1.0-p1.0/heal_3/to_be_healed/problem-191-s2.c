#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MONTH_LEN 20

int has_30_days(const char *month_name) {
    if (month_name == NULL) {
        return 0;
    }

    size_t len = 0;
    while (len < MAX_MONTH_LEN && month_name[len] != '\0') {
        len++;
    }

    if (len == MAX_MONTH_LEN) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MAX_MONTH_LEN + 1];

    for (size_t i = 0; i < len; i++) {
        month[i] = (char)tolower((unsigned char)month_name[i]);
    }
    month[len] = '\0';

    if (strcmp(month, "april") == 0 || 
        strcmp(month, "june") == 0 || 
        strcmp(month, "september") == 0 || 
        strcmp(month, "november") == 0 ||
        strcmp(month, "apr") == 0 ||
        strcmp(month, "jun") == 0 ||
        strcmp(month, "sep") == 0 ||
        strcmp(month, "nov") == 0) {
        return 1;
    }

    return 0;
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