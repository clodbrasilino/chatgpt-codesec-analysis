#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 32

static int has_28_days(const char *month)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_INPUT_LEN];
    size_t len;
    size_t i;

    if (month == NULL) {
        return -1;
    }

    len = strnlen(month, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return -1;
    }

    for (i = 0; i < len && i < sizeof(normalized) - 1; i++) {
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

static void flush_stdin(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    size_t len;
    int result;

    memset(input, 0, sizeof(input));

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
    } else {
        flush_stdin();
    }

    result = has_28_days(input);

    if (result < 0) {
        fprintf(stderr, "Invalid month name\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("%s contains 28 days\n", input);
    } else {
        printf("%s does not contain 28 days\n", input);
    }

    return EXIT_SUCCESS;
}