#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 10

static int findDemlo(const char *str, char *result, size_t result_size);

static int findDemlo(const char *str, char *result, size_t result_size)
{
    size_t len;
    size_t i;
    size_t pos;

    if (str == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    len = strnlen(str, MAX_INPUT_LEN);

    if (len == 0 || len > 9) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (str[i] != '1') {
            return -1;
        }
    }

    if (result_size < (2 * len)) {
        return -1;
    }

    pos = 0;
    for (i = 1; i <= len; i++) {
        result[pos] = (char)('0' + (int)i);
        pos++;
    }
    for (i = len - 1; i >= 1; i--) {
        result[pos] = (char)('0' + (int)i);
        pos++;
    }
    result[pos] = '\0';

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN + 2];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[2 * MAX_INPUT_LEN];
    size_t len;

    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));

    printf("Enter a repunit number (only 1s, max 9 digits): ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Invalid input: too long\n");
        return EXIT_FAILURE;
    }

    if (findDemlo(input, output, sizeof(output)) != 0) {
        fprintf(stderr, "Invalid input: must be a repunit of at most 9 ones\n");
        return EXIT_FAILURE;
    }

    printf("Demlo number: %s\n", output);

    return EXIT_SUCCESS;
}