#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return 0;
        }
        ++str;
    }

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *newline;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    newline = strchr(input, '\n');

    if (newline != NULL) {
        if (newline > input && newline[-1] == '\r') {
            --newline;
        }
        *newline = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        return 1;
    }

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");
    return 0;
}