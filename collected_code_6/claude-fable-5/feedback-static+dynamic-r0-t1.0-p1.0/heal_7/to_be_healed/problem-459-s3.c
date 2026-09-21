#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

static char *remove_uppercase(const char *input)
{
    char *result;
    size_t input_len;
    size_t result_pos;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        return NULL;
    }

    result = calloc(input_len + 1, sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    result_pos = 0;
    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (!isupper(c)) {
            if (result_pos >= input_len) {
                fprintf(stderr, "Internal bounds error\n");
                free(result);
                return NULL;
            }
            result[result_pos] = (char)c;
            result_pos++;
        }
    }

    result[result_pos] = '\0';
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    char *cleaned;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    len = strnlen(buffer, sizeof(buffer));
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[len - 1] = '\0';
        len--;
    }

    cleaned = remove_uppercase(buffer);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned);
    free(cleaned);

    return EXIT_SUCCESS;
}