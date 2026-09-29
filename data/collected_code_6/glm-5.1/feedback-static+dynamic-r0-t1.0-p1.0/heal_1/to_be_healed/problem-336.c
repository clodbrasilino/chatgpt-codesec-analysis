#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[10];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(month);
    if (len == 0 || len >= sizeof(lower)) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }
    lower[len] = '\0';

    if (strcmp(lower, "february") == 0) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    int result = check_28_days(argv[1]);
    printf("%d\n", result);

    return 0;
}