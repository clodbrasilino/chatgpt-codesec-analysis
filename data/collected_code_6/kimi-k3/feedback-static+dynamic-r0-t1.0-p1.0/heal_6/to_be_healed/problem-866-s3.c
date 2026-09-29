#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has31Days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    const char *months[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    const size_t monthCount = sizeof(months) / sizeof(months[0]);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(month);
    if (len > 9) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[10];
    for (size_t i = 0; i <= len; i++) {
        buffer[i] = (char)tolower((unsigned char)month[i]);
    }

    for (size_t j = 0; j < monthCount; j++) {
        if (strcmp(buffer, months[j]) == 0) {
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

    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) != NULL) {
        month[strcspn(month, "\n")] = '\0';

        if (has31Days(month)) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    }

    return 0;
}