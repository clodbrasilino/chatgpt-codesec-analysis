#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>

#define MAX_INPUT_LEN 4096
#define OUTPUT_BUF_SIZE 256

static int remove_non_alphanumeric(const char *input, char *output, size_t output_size)
{
    size_t input_len;
    size_t out_len = 0;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    unsigned char c;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return -1;
    }

    for (i = 0; i < input_len; i++) {
        c = (unsigned char)input[i];
        
        if (isalnum(c)) {
            if (out_len >= output_size - 1) {
                return -1;
            }
            output[out_len++] = (char)c;
        }
    }

    output[out_len] = '\0';
    return 0;
}

int main(void)
{
    const char *input = "Hello, World! 123 @#$";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_BUF_SIZE];

    memset(output, 0, sizeof(output));

    if (remove_non_alphanumeric(input, output, sizeof(output)) == 0) {
        printf("%s\n", output);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}