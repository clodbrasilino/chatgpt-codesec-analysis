#include <ctype.h>
#include <stdio.h>

static size_t last_word_length(FILE *stream)
{
    size_t current_length = 0;
    size_t last_length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (isspace((unsigned char)ch)) {
            if (current_length != 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            ++current_length;
        }
    }

    if (current_length != 0) {
        last_length = current_length;
    }

    return last_length;
}

int main(void)
{
    size_t length = last_word_length(stdin);

    if (ferror(stdin)) {
        return 1;
    }

    if (printf("%zu\n", length) < 0) {
        return 1;
    }

    return 0;
}