#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_lowercase(const char *input);

char *remove_lowercase(const char *input)
{
    char *result;
    size_t input_len;
    size_t result_len;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, 4096);

    result = calloc(input_len + 1, sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    result_len = 0;
    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (!islower(c)) {
            if (result_len >= input_len) {
                fprintf(stderr, "Internal bounds error\n");
                free(result);
                return NULL;
            }
            result[result_len] = (char)c;
            result_len++;
        }
    }

    result[result_len] = '\0';
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "HelloWorldFOO123bar",
        "KDeoALOklOOHserfLoAJSIskdsf",
        "ALLUPPERCASE",
        "alllowercase",
        "Mix3d C4s3 Str1ng"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *cleaned = remove_lowercase(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
        printf("Original: %s\n", test_strings[i]);
        printf("Cleaned:  %s\n\n", cleaned);
        free(cleaned);
    }

    return EXIT_SUCCESS;
}