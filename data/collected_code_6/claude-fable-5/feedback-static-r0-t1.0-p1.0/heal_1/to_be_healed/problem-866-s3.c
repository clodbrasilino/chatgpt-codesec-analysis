#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int has_31_days(const char *month)
{
    const char *months_with_31[] = {
        "January", "March", "May", "July",
        "August", "October", "December"
    };
    size_t count = sizeof(months_with_31) / sizeof(months_with_31[0]);
    size_t i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (strcmp(month, months_with_31[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    size_t len;

    printf("Enter month name: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (has_31_days(buffer)) {
        printf("%s has 31 days\n", buffer);
    } else {
        printf("%s does not have 31 days\n", buffer);
    }

    return EXIT_SUCCESS;
}