#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t new_len = (len + 1) / 2;

    char *result = malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = input[i];
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test_string = "Hello, World!";
    char *modified_string = remove_odd_index_chars(test_string);

    if (modified_string == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Modified: %s\n", modified_string);

    free(modified_string);
    modified_string = NULL;

    return EXIT_SUCCESS;
}