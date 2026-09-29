#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NORMALIZED_SIZE 32
#define INPUT_SIZE 64

int has_28_days(const char *month)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[NORMALIZED_SIZE];
    size_t len;
    size_t i;

    if (month == NULL) {
        return 0;
    }

    len = strnlen(month, sizeof(normalized));
    if (len == 0 || len >= sizeof(normalized)) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[len] = '\0';

    if (strcmp(normalized, "february") == 0) {
        return 1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    size_t len;
    int ch;

    printf("Enter a month name: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    if (has_28_days(input)) {
        printf("%s has 28 days.\n", input);
    } else {
        printf("%s does not have exactly 28 days.\n", input);
    }

    return EXIT_SUCCESS;
}