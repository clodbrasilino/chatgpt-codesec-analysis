#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool has_31_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return true;
        default:
            return false;
    }
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    int month;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_number>\n", argv[0]);
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(argv[1]) > 2 || argv[1][0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (sscanf(argv[1], "%2d", &month) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (has_31_days(month)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}