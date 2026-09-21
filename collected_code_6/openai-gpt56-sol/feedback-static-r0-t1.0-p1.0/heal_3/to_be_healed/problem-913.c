#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool ends_with_number(int character)
{
    return character != EOF &&
           isdigit((unsigned char)character) != 0;
}

int main(void)
{
    int current;
    int last = EOF;
    bool has_input = false;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((current = getchar()) != EOF) {
        if (current == '\n') {
            break;
        }

        if (current == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                return 1;
            }

            break;
        }

        last = current;
        has_input = true;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (puts(has_input && ends_with_number(last) ? "true" : "false") == EOF) {
        return 1;
    }

    return 0;
}