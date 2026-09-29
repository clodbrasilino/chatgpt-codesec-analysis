#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
{
    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

static int discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    size_t length;
    int replacement_input;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    for (length = 0U;
         length < sizeof input && input[length] != '\0' && input[length] != '\n';
         ++length) {
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (discard_line(stdin) != 0) {
        return EXIT_FAILURE;
    } else {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    replacement_input = fgetc(stdin);
    if (replacement_input == EOF ||
        replacement_input == '\0' ||
        replacement_input == '\n') {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, (char)replacement_input) != 0) {
        return EXIT_FAILURE;
    }

    if (fwrite(input, sizeof input[0], length, stdout) != length) {
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}