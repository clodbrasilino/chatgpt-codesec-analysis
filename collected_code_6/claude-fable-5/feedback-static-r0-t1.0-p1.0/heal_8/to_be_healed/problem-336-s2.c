#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT 32

int has_28_days(const char *month)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_INPUT];
    size_t i;
    size_t len;

    if (month == NULL) {
        return -1;
    }

    len = strnlen(month, MAX_INPUT);
    if (len == 0 || len >= MAX_INPUT) {
        return -1;
    }

    for (i = 0; i < len && i < (sizeof(normalized) - 1); i++) {
        if (!isalpha((unsigned char)month[i])) {
            return -1;
        }
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[i] = '\0';

    if (strcmp(normalized, "february") == 0) {
        return 1;
    }

    return 0;
}

static int discard_remaining_input(void)
{
    int ch;
    size_t guard = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < 4096);

    return (ch == EOF) ? -1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    size_t len;
    int result;

    printf("Enter a month name: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        (void)discard_remaining_input();
        if (len == sizeof(input) - 1) {
            fprintf(stderr, "Input too long.\n");
            return EXIT_FAILURE;
        }
    }

    if (len == 0) {
        fprintf(stderr, "Empty input.\n");
        return EXIT_FAILURE;
    }

    result = has_28_days(input);

    if (result == -1) {
        fprintf(stderr, "Invalid month name input.\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("%s contains 28 days.\n", input);
    } else {
        printf("%s does not contain exactly 28 days.\n", input);
    }

    return EXIT_SUCCESS;
}