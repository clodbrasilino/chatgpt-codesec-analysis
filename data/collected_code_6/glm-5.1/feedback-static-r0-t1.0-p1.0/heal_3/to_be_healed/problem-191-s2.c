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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    if (has_30_days(argv[1])) {
        printf("%s contains 30 days.\n", argv[1]);
    } else {
        printf("%s does not contain 30 days.\n", argv[1]);
    }

    return 0;
}