#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1048576

char *add_spaces(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'len>1048576' is redundant or the array 'input[22]' is accessed at index 1048576, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (input[len] != '\0') {
        len++;
        /* Possible weaknesses found:
         *  Assuming that condition 'len>1048576' is not redundant
         */
        if (len > MAX_INPUT_LENGTH) {
            return NULL;
        }
    }

    size_t extra_spaces = 0;
    for (size_t i = 1; i < len; i++) {
        if (isupper((unsigned char)input[i])) {
            extra_spaces++;
        }
    }

    size_t result_size = len + extra_spaces + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t src = 0;
    size_t dst = 0;
    for (size_t i = 1; i < len; i++) {
        if (isupper((unsigned char)input[i])) {
            size_t copy_len = i - src;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst, input + src, copy_len);
            dst += copy_len;
            result[dst++] = ' ';
            src = i;
        }
    }

    size_t remaining = len - src;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + dst, input + src, remaining);
    dst += remaining;
    result[dst] = '\0';

    return result;
}

int main(void)
{
    const char *input = "HelloWorldThisIsATest";
    char *spaced = add_spaces(input);

    if (spaced == NULL) {
        fprintf(stderr, "Error processing input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", spaced);
    free(spaced);
    return EXIT_SUCCESS;
}