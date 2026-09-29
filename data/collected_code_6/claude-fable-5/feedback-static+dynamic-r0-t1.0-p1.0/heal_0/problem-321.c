#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 10

static int findDemlo(const char *str, char *result, size_t result_size)
{
    size_t len;
    size_t i;
    size_t pos;

    if (str == NULL || result == NULL) {
        return -1;
    }

    len = strlen(str);

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
    char input[MAX_INPUT_LEN + 2];
    char output[2 * MAX_INPUT_LEN];
    size_t len;

    printf("Enter a repunit number (only 1s, max 9 digits): ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (findDemlo(input, output, sizeof(output)) != 0) {
        fprintf(stderr, "Invalid input: must be a repunit of at most 9 ones\n");
        return EXIT_FAILURE;
    }

    printf("Demlo number: %s\n", output);

    return EXIT_SUCCESS;
}