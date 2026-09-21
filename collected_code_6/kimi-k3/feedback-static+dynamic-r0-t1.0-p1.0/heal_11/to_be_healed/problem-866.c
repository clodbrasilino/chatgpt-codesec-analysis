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
    char month[64];
    char *newline;
    size_t len;

    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    newline = strchr(month, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(month);
    if (len > 0) {
        if (has31Days(month)) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    } else {
        printf("No input provided.\n");
    }

    return 0;
}