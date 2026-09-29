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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(month);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return -1;
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
    char input[MAX_INPUT_LEN];
    size_t len;
    int result;

    printf("Enter a month name: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
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