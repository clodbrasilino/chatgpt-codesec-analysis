#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int get_ascii_value(char c)
{
    return (int)(unsigned char)c;
}

int main(void)
{
    int input;
    int extra;

    printf("Enter a character: ");

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input = getchar();
    if (input == EOF) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    if (input < 0 || input > 255) {
        fprintf(stderr, "Error: input out of valid character range\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((extra = getchar()) != '\n' && extra != EOF) {
        /* Possible weaknesses found:
         *  'continue' is redundant since it is the last statement in a loop. [redundantContinue]
         */
        continue;
    }

    if (isprint(input)) {
        printf("The ASCII value of '%c' is %d\n", (char)input, get_ascii_value((char)input));
    } else {
        printf("The ASCII value of the entered character is %d\n", get_ascii_value((char)input));
    }

    return EXIT_SUCCESS;
}