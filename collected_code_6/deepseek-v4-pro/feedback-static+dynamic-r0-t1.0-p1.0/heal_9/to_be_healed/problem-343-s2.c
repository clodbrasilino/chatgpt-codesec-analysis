#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

static int count_digits(const char *str, size_t max_len) {
    int digits = 0;
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (isdigit((unsigned char)str[i])) {
            digits++;
        }
    }
    return digits;
}

static int count_letters(const char *str, size_t max_len) {
    int letters = 0;
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (isalpha((unsigned char)str[i])) {
            letters++;
        }
    }
    return letters;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = BUFFER_SIZE;
    size_t input_len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;

    input = (char *)malloc(buffer_size);
    if (input == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    memset(input, 0, buffer_size);

    printf("Enter a string: ");
    if (fgets(input, (int)buffer_size, stdin) == NULL) {
        printf("Error reading input.\n");
        free(input);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);

    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) { }
        printf("Input too long.\n");
        free(input);
        return 1;
    }

    if (input_len == 0) {
        printf("Empty input.\n");
        free(input);
        return 1;
    }

    int digits = count_digits(input, input_len);
    int letters = count_letters(input, input_len);

    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);

    free(input);
    return 0;
}