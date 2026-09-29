#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096

static int is_alphanumeric_ascii(unsigned char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

char *remove_non_alphanumeric(const char *input)
{
    char *result;
    size_t result_len = 0;
    size_t input_len;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH);

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (is_alphanumeric_ascii(c)) {
            result[result_len] = (char)c;
            result_len++;
        }
    }

    result[result_len] = '\0';
    return result;
}

int main(void)
{
    const char *test = "Hello, World! 123 @#$% C-Programming_2024";
    char *cleaned = remove_non_alphanumeric(test);

    if (cleaned == NULL) {
        fprintf(stderr, "Error: string processing failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}