#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 32

static bool has_31_days(const char *month)
{
    static const char *months_31[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lowered[MAX_INPUT_LEN];
    size_t len;
    size_t i;

    if (month == NULL) {
        return false;
    }

    len = strnlen(month, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return false;
    }

    memset(lowered, 0, sizeof(lowered));

    for (i = 0; i < len && i < sizeof(lowered) - 1; i++) {
        lowered[i] = (char)tolower((unsigned char)month[i]);
    }
    lowered[i] = '\0';

    for (i = 0; i < sizeof(months_31) / sizeof(months_31[0]); i++) {
        if (strcmp(lowered, months_31[i]) == 0) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    size_t len;

    memset(input, 0, sizeof(input));

    printf("Enter a month name: ");
    fflush(stdout);

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    if (input[0] == '\0') {
        fprintf(stderr, "No input provided.\n");
        return EXIT_FAILURE;
    }

    if (has_31_days(input)) {
        printf("%s has 31 days.\n", input);
    } else {
        printf("%s does not have 31 days.\n", input);
    }

    return EXIT_SUCCESS;
}