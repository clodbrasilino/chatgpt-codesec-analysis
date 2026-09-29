#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

char *camel_to_snake(const char *input);
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  *  test case 0 failed: expected 'google_assistant', got <no output>
  */

char *camel_to_snake(const char *input)
{
    char *output = NULL;
    size_t input_len = 0;
    size_t out_capacity;
    size_t out_len = 0;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    while ((input_len < MAX_INPUT_LEN) && (input[input_len] != '\0')) {
        input_len++;
    }
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (input_len > ((SIZE_MAX - 1U) / 2U)) {
        return NULL;
    }
    out_capacity = (input_len * 2U) + 1U;

    output = (char *)malloc(out_capacity);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (isupper(c) != 0) {
            if (i > 0U) {
                if (out_len >= (out_capacity - 1U)) {
                    free(output);
                    return NULL;
                }
                output[out_len] = '_';
                out_len++;
            }
            if (out_len >= (out_capacity - 1U)) {
                free(output);
                return NULL;
            }
            output[out_len] = (char)tolower(c);
            out_len++;
        } else {
            if (out_len >= (out_capacity - 1U)) {
                free(output);
                return NULL;
            }
            output[out_len] = (char)c;
            out_len++;
        }
    }

    if (out_len >= out_capacity) {
        free(output);
        return NULL;
    }

    output[out_len] = '\0';
    return output;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    char *result = NULL;
    size_t len = 0;

    (void)memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        (void)fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    while ((len < sizeof(buffer)) && (buffer[len] != '\0')) {
        len++;
    }
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
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
    return EXIT_SUCCESS;
}