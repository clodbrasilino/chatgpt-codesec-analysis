#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int has31Days(const char *month) {
    const char *months31[] = {
        "January", "March", "May", "July", "August", "October", "December"
    };
    size_t numMonths = sizeof(months31) / sizeof(months31[0]);
    size_t i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < numMonths; i++) {
        if (strcasecmp(month, months31[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[32];
    size_t len;

    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (strchr(month, '\n') == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    len = strnlen(month, sizeof(month));
    if (len > 0 && month[len - 1] == '\n') {
        month[len - 1] = '\0';
    }

    if (has31Days(month)) {
        printf("%s has 31 days.\n", month);
    } else {
        printf("%s does not have 31 days.\n", month);
    }

    return 0;
}