#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has_30_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    if (strcmp(month, "April") == 0 || strcmp(month, "June") == 0 || 
        strcmp(month, "September") == 0 || strcmp(month, "November") == 0) {
        return true;
    }

    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    const char *safe_month = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t src_len = strlen(safe_month);
    if (src_len >= 128) {
        fprintf(stderr, "Month name too long\n");
        return 1;
    }

    if (has_30_days(safe_month)) {
        printf("%s contains 30 days.\n", safe_month);
    } else {
        printf("%s does not contain 30 days.\n", safe_month);
    }

    return 0;
}