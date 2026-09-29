#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_whitespace(const char *input, size_t input_len)
{
    char *result;
    size_t i;
    size_t result_len = 0;

    if (input == NULL) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        if (!isspace((unsigned char)input[i])) {
            result[result_len++] = input[i];
        }
    }

    result[result_len] = '\0';

    return result;
}

int main(void)
{
    const char *test_string = "Hello World \t This is a test \n string";
    size_t test_len;
    char *cleaned;

    test_len = strnlen(test_string, 1024);
    
    cleaned = remove_whitespace(test_string, test_len);
    if (cleaned == NULL) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);

    return EXIT_SUCCESS;
}