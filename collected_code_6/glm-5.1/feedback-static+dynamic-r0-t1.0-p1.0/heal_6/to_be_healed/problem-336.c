#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(month);
    if (len != 8) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (tolower((unsigned char)month[i]) != "february"[i]) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    int result = check_28_days(argv[1]);
    printf("%d\n", result);

    return 0;
}