#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    size_t len = strnlen(month, 10);
    if (len == 0 || len >= 10) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[11];
    for (size_t i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }
    lower[len] = '\0';

    if (strcmp(lower, "february") == 0) {
        return 1;
    }

    return 0;
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