#include <stdio.h>
#include <stdlib.h>

int get_ascii_value(char c) {
    return (int)c;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int input = fgetc(stdin);

    if (input == EOF) {
        return EXIT_FAILURE;
    }

    printf("%d\n", get_ascii_value((char)input));

    return EXIT_SUCCESS;
}