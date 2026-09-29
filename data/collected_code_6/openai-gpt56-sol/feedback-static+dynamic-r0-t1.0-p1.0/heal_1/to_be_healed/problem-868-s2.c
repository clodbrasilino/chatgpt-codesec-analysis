#include <ctype.h>
#include <stdio.h>
#include <string.h>

static size_t last_word_length(const char *str)
{
    size_t length = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    i = strlen(str);

    while (i > 0 && isspace((unsigned char)str[i - 1])) {
        --i;
    }

    while (i > 0 && !isspace((unsigned char)str[i - 1])) {
        --i;
        ++length;
    }

    return length;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }

        printf("0\n");
        return 0;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return 1;
        }
    }

    printf("%zu\n", last_word_length(input));
    return 0;
}