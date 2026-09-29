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

char *camel_to_snake(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len > ((SIZE_MAX - 1U) / 2U)) {
        return NULL;
    }

    output = malloc((len * 2U) + 1U);
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
    char buffer[MAX_INPUT_LEN + 2U];
    char *result;
    size_t len;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    while ((len > 0U) && ((buffer[len - 1U] == '\n') || (buffer[len - 1U] == '\r'))) {
        buffer[len - 1U] = '\0';
        len--;
    }

    result = camel_to_snake(buffer);
    if (result == NULL) {
        (void)fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}