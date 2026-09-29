#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got <no output>
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  */

static size_t length_of_last_word(FILE *stream)
{
    size_t last_length = 0U;
    size_t current_length = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (isspace((unsigned char)ch) != 0) {
            if (current_length != 0U) {
                last_length = current_length;
                current_length = 0U;
            }
        } else {
            ++current_length;
        }
    }

    return current_length != 0U ? current_length : last_length;
}

int main(void)
{
    size_t result = length_of_last_word(stdin);

    if (ferror(stdin) != 0) {
        return 1;
    }

    printf("%zu\n", result);
    return 0;
}