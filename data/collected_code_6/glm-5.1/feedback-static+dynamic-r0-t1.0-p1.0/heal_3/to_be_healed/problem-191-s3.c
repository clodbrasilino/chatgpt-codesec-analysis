#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has_30_days(const char * const month) {
    if (month == NULL) {
        return false;
    }

    if (strcmp(month, "April") == 0) {
        return true;
    }
    if (strcmp(month, "June") == 0) {
        return true;
    }
    if (strcmp(month, "September") == 0) {
        return true;
    }
    if (strcmp(month, "November") == 0) {
        return true;
    }

    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    if (has_30_days(argv[1])) {
        printf("%s has 30 days\n", argv[1]);
    } else {
        printf("%s does not have 30 days\n", argv[1]);
    }

    return 0;
}