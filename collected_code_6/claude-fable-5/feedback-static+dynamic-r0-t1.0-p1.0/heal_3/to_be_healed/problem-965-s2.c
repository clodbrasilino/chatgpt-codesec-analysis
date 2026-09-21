#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096U
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  */

static char *camel_to_snake(const char *input)
{
    size_t len;
    size_t out_size;
    size_t i;
    size_t j;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (len > ((SIZE_MAX - 1U) / 2U)) {
        return NULL;
    }
    out_size = (len * 2U) + 1U;

    output = malloc(out_size);
    if (output == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (isupper(c) != 0) {
            if (i > 0U) {
                output[j] = '_';
                j++;
            }
            output[j] = (char)tolower(c);
            j++;
        } else {
            output[j] = (char)c;
            j++;
        }
    }
    output[j] = '\0';

    return output;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];

    while (fgets(buffer, (int)sizeof(buffer), stdin) != NULL) {
        char *result;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t blen = strlen(buffer);

        while ((blen > 0U) &&
               ((buffer[blen - 1U] == '\n') || (buffer[blen - 1U] == '\r'))) {
            buffer[blen - 1U] = '\0';
            blen--;
        }

        result = camel_to_snake(buffer);
        if (result == NULL) {
            (void)fprintf(stderr, "Conversion failed for input: %s\n", buffer);
            return EXIT_FAILURE;
        }

        if (printf("%s\n", result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }

        free(result);
    }

    return EXIT_SUCCESS;
}